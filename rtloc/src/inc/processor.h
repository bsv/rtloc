#ifndef PROCESSOR_H_
#define PROCESSOR_H_

#include <QList>
#include <QObject>
#include <QTimer>
#include <QPoint>
#include "RFTag.h"
#include  "../wlanapi/wlanapi.h"

typedef QList<RFTag *> TagList;
typedef QList<QPoint *> PointList;
typedef MapItem Man;

/// Масштаб для максимаольной видимости точки в метрах
#define SCALE_RSSI 50

/**
 * Класс для обработки данных
 */
class Processor : public QObject
{
	Q_OBJECT
public:
    Processor(QObject *parent = 0);
    virtual ~Processor();

    TagList * getActiveTags();
    Man * getMan();

    /**
     * Расчет позиции объекта
     */
    void calcPos(TagList * all_tags);

    /**
     * Обновление информации о мощности сигнала меток,
     * отмеченных на карте
     *
     * @param all_tags - метки, отмеченные на карте.
     *
     * @param calc_tags - метки, по которым будет производится
     * расчет положения объекта. Это метки, которые находятся
     * в радиусе действия антенны приемника и отмечены на карте.
     */
    void updateRfTags(TagList * all_tags, TagList * calc_tags);

    /**
     *  Расчет центра тяжести треугольника (пересечение медиан)
     */
    QPoint calcCentroid(float x1, float y1,
            float x2, float y2, float x3, float y3);

    /**
     * Нахождение таких точек пересечения окружностей, которые
     * принадлежат одновременно всем окружностям.
     *
     * @param calc_tags - список точек доступа,
     * по которым будет производиться расчет
     *
     * @param points - список точек пересечения окружностей
     */
    void getAllIntersec(TagList * calc_tags, PointList * points);

    /**
     * Расчет точек пересечения окружностей
     */
    QList<QPoint> calcIntersec(float x1, float y1,
            float r1, float x2, float y2, float r2);

private:
    /// Список обнаруженных меток
    /// Обнавляется с помощью getActiveTags()
    TagList rftags;
    Man man;

    wlanapi * wi;

    void clearTagList();

    /**
     *  Удаляет список точек пересечения
     *
     * @param list - указатель на список, который
     * требуется удалить.
     */
    void deleteList(PointList * list);
};

#endif /* PROCESSOR_H_ */
