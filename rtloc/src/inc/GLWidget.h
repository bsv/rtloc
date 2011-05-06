#ifndef GLWIDGET_H_
#define GLWIDGET_H_

#include <QGLWidget>
#include <QMouseEvent>
#include <QTimer>

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
protected:
     void initializeGL();
     void paintGL();
     void resizeGL(int width, int height);
     void mousePressEvent(QMouseEvent *event);
     void mouseMoveEvent(QMouseEvent *event);
     void mouseDoubleClickEvent(QMouseEvent *event);

     void getWorldCoordinates(GLdouble viewport_x, GLdouble viewport_y, GLdouble &x, GLdouble &y);

     QList<MapItem *> items;

private:
     GLfloat rotationX;
     GLfloat rotationY;
     GLfloat rotationZ;
     GLfloat translationX;
     GLfloat translationY;
     //GLfloat translationZ;

     QPoint lastPos;

     void draw();

     // Timer things
     QTimer *timer;
};

#endif /* GLWIDGET_H_ */
