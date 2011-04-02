#include "inc/map_item.h"

MapItem::MapItem()
{
    setXY(0, 0);
}

MapItem::MapItem(QString name_new, int x_new, int y_new)
{
    setXY(x_new, y_new);
    setName(name_new);
}

MapItem::~MapItem()
{
}

int MapItem::getX()
{
    return x;
}

int MapItem::getY()
{
    return y;
}

void MapItem::setXY(int x_new, int y_new)
{
    x = x_new;
    y = y_new;
}

QString MapItem::getName()
{
    return name;
}

void MapItem::setName(QString name_new)
{
    name = name_new;
}