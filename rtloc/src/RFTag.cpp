#include "inc/RFTag.h"
#include "inc/GLWidget.h"

RFTag::RFTag()
{
}

RFTag::RFTag(QString name_new, int x_new, int y_new)
    : MapItem(name_new, x_new, y_new)
{
}

void RFTag::draw(GLWidget * w)
{
    glColor3f(0, 1.0, 0);
    glPointSize(4.0);

    glBegin(GL_POINTS);
        glVertex2f(x, y);
    glEnd();

    QFont font;
    font.setPointSize(10);
    w->renderText(x, y, name, font);
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
