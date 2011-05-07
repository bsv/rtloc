#ifndef PROCESSOR_H_
#define PROCESSOR_H_

#include <QList>
#include <QObject>
#include <QTimer>
#include <QPoint>
#include "RFTag.h"
#include  "../wlanapi/wlanapi.h"

typedef QList<RFTag *> TagList;
typedef MapItem Man;

// Масштаб для максимаольной видимости точки в метрах
#define SCALE_RSSI 100

class Processor : public QObject
{
	Q_OBJECT
public:
    Processor(QObject *parent = 0);
    virtual ~Processor();

    TagList * getActiveTags();
    Man * getMan();


    void calcPos(TagList * all_tags);

    // Расчет центра тяжести треугольника (пересечение медиан)
    QPoint calcCentroid(float x1, float y1,
            float x2, float y2, float x3, float y3);

    // Расчет точек пересечения окружностей
    QList<QPoint> calcIntersec(float x1, float y1,
            float r1, float x2, float y2, float r2);

private:
    TagList rftags;
    Man man;

    wlanapi * wi;

    void clearTagList();
};

#endif /* PROCESSOR_H_ */
