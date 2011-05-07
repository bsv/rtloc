#ifndef MAPITEM_H_
#define MAPITEM_H_

#include <QString>

class GLWidget;

class MapItem
{
public:
    MapItem();
    MapItem(QString name_new, int x_new, int y_new);
    virtual ~MapItem();

    QString getName();
    void setName(QString name_new);
    int getX();
    int getY();
    void setXY(int x_new, int y_new);
    virtual void draw(GLWidget * w);

protected:
    QString name;
    int x, y;
};

#endif /* MAPITEM_H_ */
