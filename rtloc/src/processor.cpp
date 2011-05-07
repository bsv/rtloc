#include "inc/processor.h"
#include <QMessageBox>
#include <QDebug>
#include <math.h>

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
    RFTag * item;
    getActiveTags();
    bool find;

    TagList calc_tags;

    // Обновление информации о активных точках
    for(int i = 0; i < all_tags->size(); i ++)
    {
        item = (*all_tags)[i];
        find = false;

        for(int j = 0; j < rftags.size(); j++)
        {
            if(item->getName() == rftags[j]->getName())
            {
                item->setRSSI(rftags[j]->getRSSI());
                calc_tags.append(item);
                find = true;
                break;
            }
        }
        if(!find)
        {
            item->setRSSI(0);
        }
    }

    // Расчет положения по активным точкам
    // (пока только по двум меткам)
    if(calc_tags.size() > 3)
    {

    } else if(calc_tags.size() == 2)
    {
        float x1 = calc_tags[0]->getX();
        float y1 = calc_tags[0]->getY();
        float r1 = calc_tags[0]->getRSSI();

        float x2 = calc_tags[1]->getX();
        float y2 = calc_tags[1]->getY();
        float r2 = calc_tags[1]->getRSSI();

        QList<QPoint> p = calcIntersec(x1, y1, r1, x2, y2, r2);

        if(p.size() == 2)
        {
            man.setXY((p[0].x() + p[1].x())/2,
                    (p[0].y() + p[1].y())/2);
        } else if(p.size() == 1)
        {
            man.setXY(p[0].x(), p[0].y());
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

void Processor::clearTagList()
{
    while (!rftags.isEmpty())
         delete rftags.takeFirst();

    rftags.clear();
}
