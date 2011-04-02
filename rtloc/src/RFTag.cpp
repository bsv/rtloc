#include "inc/RFTag.h"

RFTag::RFTag()
{
}

RFTag::RFTag(QString name_new, int x_new, int y_new)
    : MapItem(name_new, x_new, y_new)
{
}

RFTag::~RFTag()
{
}

QString RFTag::getId()
{
    return id;
}

void RFTag::setId(QString id_new)
{
    id = id_new;
}

void RFTag::setRSSI(int rssi_new)
{
    rssi = rssi_new;
}

int RFTag::getRSSI()
{
    return rssi;
}
