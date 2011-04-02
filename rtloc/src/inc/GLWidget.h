#ifndef GLWIDGET_H_
#define GLWIDGET_H_

#include <QGLWidget>
#include <QMouseEvent>

class GLWidget : public QGLWidget
{
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

private:
     GLfloat rotationX;
     GLfloat rotationY;
     GLfloat rotationZ;
     QColor faceColors[6];
     QPoint lastPos;

     void draw();
     int faceAtPosition(const QPoint &pos);

};

#endif /* GLWIDGET_H_ */
