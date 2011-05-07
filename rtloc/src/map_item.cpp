#include "inc/map_item.h"
#include <QGLWidget>
#include "inc/GLWidget.h"

MapItem::MapItem()
{
    setXY(0, 0);
}

MapItem::MapItem(QString name_new, int x_new, int y_new)
{
    setXY(x_new, y_new);
    setName(name_new);
}

void MapItem::draw(GLWidget * w)
{
    glColor3f(1.0, 0, 0);
    glPointSize(4.0);

	glBegin(GL_POINTS);
		glVertex2f(x, y);
	glEnd();

	QFont font;
	font.setPointSize(10);
	w->renderText(x, y, name, font);
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
