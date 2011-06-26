#include "inc/processor.h"
#include <QMessageBox>
#include <QDebug>
#include <qmath.h>

Processor::Processor(QObject *parent)
	: QObject(parent)
{
    wi = new wlanapi();
}

/**
 * Вычисляем положение объекта
 * Обнавляем значения мощности сигнала
 * для активных точек в all_tags
 */
void Processor::calcPos(TagList * all_tags)
{
    // по этому списку будем производить расчет
    TagList * calc_tags = new TagList();

    // Список точек пересечения окружностей
    // (окружность - область действия антенны)
    PointList * points = new PointList();

    // Получаем данные об активных метках и обновляем rftags
    getActiveTags();

    // Обновляем информацию об активных точках,
    // присутствующих на карте
    updateRfTags(all_tags, calc_tags);

    // Находим общие точки пересечения зон действия активных меток
    getAllIntersec(calc_tags, points);

    // Выводим количество найденных точек
    //QTextStream out(stdout);
    //out << "NPOints = " << points->size() << endl;

    // Расчет положения по активным точкам
    int x = 0, y = 0;
    int count_points = points->size();

    for(int i = 0; i < count_points; i++)
    {
        x += (*points)[i]->x();
        y += (*points)[i]->y();
    }

    if(count_points !=0)
    {
        man.setXY(x/count_points, y/count_points);
    }

    // Удаляем созданные объекты
    delete calc_tags;
    deleteList(points);
}

void Processor::getAllIntersec(TagList * calc_tags, PointList * points)
{
    RFTag * tag1 = NULL;
    RFTag * tag2 = NULL;
    PointList::iterator point;
    bool found = false;
    QTextStream out(stdout);

    points->clear();

    for(int tag_i = 0; tag_i < calc_tags->size(); tag_i++)
    {
        tag1 = (*calc_tags)[tag_i];

        for(int tag_j = tag_i+1; tag_j < calc_tags->size(); tag_j++)
        {
            tag2 = (*calc_tags)[tag_j];

            // Пересчет в метры радиусов действия точек доступа
            float r1 = tag1->getRSSI();
            float r2 = tag2->getRadius();

            QList<QPoint> p = calcIntersec(tag1->getX(),
                    tag1->getY(), r1,
                    tag2->getX(),
                    tag2->getY(), r2);

            // Добавляем новые точки в список
            for(int i = 0; i < p.size(); i++)
            {
                point = points->begin();
                found = false;

                while(point != points->end())
                {
                    if(**point == p[i])
                    {
                        found = true;
                        break;
                    }
                    ++point;
                }
                if(!found)
                {
                    points->append(new QPoint(p[i]));
                }
            }
        }
    }

    // Оставляем в points только общие точки для всех окружностей
    TagList::iterator tag = calc_tags->begin();

    point = points->begin();

    while(point != points->end())
    {
        tag = calc_tags->begin();
        found = false;

        while(tag != calc_tags->end())
        {
            // квадрат радиуса
            int r_sqr = qPow((*point)->x() - (*tag)->getX(), 2) +
                    qPow((*point)->y() - (*tag)->getY(), 2);

            // радиус действия точки доступа
            int r = (*tag)->getRadius();

            // Если точка находится за пределами зоны действия
            // хоть однй точки доступа, то удаляем её
            if((int)(qSqrt(r_sqr)) > r)
            {
                found = true;
                break;
            }
            ++tag;
        }

        if(found)
        {
            delete *point;
            point = points->erase(point);
        } else
        {
            ++point;
        }
    }
}

void Processor::updateRfTags(TagList * all_tags, TagList * calc_tags)
{
    RFTag * item;
    bool find;

    for(int i = 0; i < all_tags->size(); i ++)
    {
        item = (*all_tags)[i];
        find = false;

        for(int j = 0; j < rftags.size(); j++)
        {
            if(item->getName() == rftags[j]->getName())
            {
                item->setRSSI(rftags[j]->getRSSI());
                calc_tags->append(item);
                find = true;
                break;
            }
        }
        if(!find)
        {
            item->setRSSI(0);
        }
    }
}


// Расчет центра тяжести треугольника (пересечение медиан)
QPoint Processor::calcCentroid(float x1, float y1, float x2, float y2, float x3, float y3)
{
    float xa = (x2 + x3)/2;
    float ya = (y2 + y3)/2;

    float xb = (x1 + x3)/2;
    float yb = (y1 + y3)/2;

    float a = (ya - y1)/(xa - x1);
    float b = (ya - y1)*x1/(xa - x1) - y1;

    float c = a/(yb - y2) - 1/(xb - x2);
    float d = (b + y2)/(yb - y2) - x2/(xb - x2);

    return QPoint(d/c, a*(d/c) - b);
}

// Расчет точек пересечения окружностей
QList<QPoint> Processor::calcIntersec(float x1, float y1, float r1, float x2, float y2, float r2)
{

    float a1 = 2*x2-2*x1;
    float b1 = 2*y2-2*y1;
    float c1 = r1*r1-r2*r2+x2*x2-x1*x1+y2*y2-y1*y1;

    float a = (b1/a1)*(b1/a1)+1;
    float b = 2*x1*b1/a1-2*c1*b1/(a1*a1)-2*y1;
    float c = (c1/a1)*(c1/a1)+x1*x1+y1*y1-r1*r1 - 2*x1*c1/a1;

    float D = b*b-4*a*c;

    QList<float> y;

    if (D > 0)
    {
           y.append((-b+sqrt(D))/(2*a));
           y.append((-b-sqrt(D))/(2*a));
    } else if (D == 0)
    {
           y.append(sqrt(D)/(2*a));
    }

    QList<QPoint> points;

    for(int i = 0; i < y.size(); i++)
    {
        int x = (c1-b1*y[i])/a1;
        points.append(QPoint(x, y[i]));
    }
    return points;
}


Processor::~Processor()
{
    delete wi;
    clearTagList();
}

Man * Processor::getMan()
{
    return &man;
}

TagList * Processor::getActiveTags()
{
    RFTag * tag;

    clearTagList();

    try {
        wi->get_adapter_list();
        const AP_LIST &ap_list = wi->get_ap_list(NULL);

        for (AP_LIST::const_iterator it = ap_list.begin(); it < ap_list.end(); ++it)
        {
            QString name = it->name;

            if(!name.isEmpty())
            {
                tag = new RFTag();
                QString mac;

                mac += QString("%1").arg(it->mac_address.u[0], 2, 16);
                mac += QString(" - %1").arg(it->mac_address.u[1], 2, 16);
                mac += QString(" - %1").arg(it->mac_address.u[2], 2, 16);
                mac += QString(" - %1").arg(it->mac_address.u[3], 2, 16);
                mac += QString(" - %1").arg(it->mac_address.u[4], 2, 16);
                mac += QString(" - %1").arg(it->mac_address.u[5], 2, 16);

                tag->setName(it->name);
                tag->setId(mac);

                // Одновременно переводим RSSI в метры
                tag->setRSSI((-it->rssi)/100.0 * SCALE_RSSI);

                rftags.append(tag);
            }
        }
    } catch (std::exception &e) {
         QMessageBox msgBox;
         msgBox.setText(e.what());
         msgBox.exec();
    }

    return &rftags;
}

void Processor::deleteList(PointList * list)
{
    while (!list->isEmpty())
             delete list->takeFirst();
    delete list;
}

void Processor::clearTagList()
{
    while (!rftags.isEmpty())
         delete rftags.takeFirst();

    rftags.clear();
}
