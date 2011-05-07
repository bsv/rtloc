#ifndef GLWIDGET_H_
#define GLWIDGET_H_

#include <QGLWidget>
#include <QMouseEvent>
#include <QTimer>
#include "processor.h"

class MapItem;

typedef unsigned int uint;

class GLWidget : public QGLWidget
{
	Q_OBJECT
public:
    GLWidget(QWidget *parent = 0);
    virtual ~GLWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    void setTagList(TagList * all_tags);
    void setMan(Man * man);
    void setDrawAcc(bool acc);

protected:
     void initializeGL();
     void paintGL();
     void resizeGL(int width, int height);
     void mousePressEvent(QMouseEvent *event);
     void mouseMoveEvent(QMouseEvent *event);
     void mouseDoubleClickEvent(QMouseEvent *event);

     void getWorldCoordinates(GLdouble viewport_x, GLdouble viewport_y, GLdouble &x, GLdouble &y);
private:
     GLfloat rotationX;
     GLfloat rotationY;
     GLfloat rotationZ;
     GLfloat translationX;
     GLfloat translationY;
     //GLfloat translationZ;

     Man * man_obj;
     TagList * tags;

     QPoint lastPos;

     // Флаг разрешения вывода объектов.
     // Нужен, чтоб предотвратить гонку за
     // tags (изменяется в main_window,
     // выводится в draw)
     bool draw_acc;

     void draw();

     // Timer things
     QTimer timer;

signals:
    void addRFTag(RFTag * tag);
};

#endif /* GLWIDGET_H_ */
