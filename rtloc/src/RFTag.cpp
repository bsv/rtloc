#include "inc/RFTag.h"
#include "inc/GLWidget.h"
#include <math.h>

RFTag::RFTag()
{
    setXY(0, 0);
    rssi = 0;
}

RFTag::RFTag(QString name_new, int x_new, int y_new)
    : MapItem(name_new, x_new, y_new)
{
    rssi = 0;
}

void RFTag::draw(GLWidget * w)
{
    glColor3f(0, 1, 0);
    glPointSize(4.0);

    glBegin(GL_POINTS);
        glVertex2f(x, y);
    glEnd();

    QFont font;
    font.setPointSize(10);
    w->renderText(x, y, name, font);
    w->renderText(x, y+10, QString().setNum(rssi), font);

    glBegin(GL_LINE_LOOP);
        for (int i = 0; i < 256; i++) {
          double angle = 2*3.14*i/256;
          glVertex2f(x + rssi*cos(angle), y + rssi*sin(angle));
        }
    glEnd();

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

int RFTag::getRadius()
{
    return rssi; // Для некоторых типов меток необходимо
                 // производить более сложный расчет, учитывающий
                 // нелинейность затухания сигнала, пропорциональный
                 // квадрату расстояния.

}
