#ifndef PROCESSOR_H_
#define PROCESSOR_H_

#include <QList>
#include <QObject>
#include "RFTag.h"
#include  "../wlanapi/wlanapi.h"

typedef QList<RFTag *> TagList;
typedef MapItem Man;

class Processor : public QObject
{
	Q_OBJECT
public:
    Processor(QObject *parent = 0);
    virtual ~Processor();

    TagList * getActiveTags();
    Man * getMan();

private:
    TagList rftags;
    Man man;

    wlanapi * wi;

    void clearTagList();
};

#endif /* PROCESSOR_H_ */
