#ifndef GLWIDGET_H_
#define GLWIDGET_H_

#include <QGLWidget>
#include <QMouseEvent>
#include <QTimer>
#include "processor.h"

class MapItem;

typedef unsigned int uint;


/// Класс отчечает за графическое отображение процесса навигации.
/**
 * Изображение отрисовывается в главном окне с использованием OpenGL.
 */
class GLWidget : public QGLWidget
{
	Q_OBJECT
public:
    GLWidget(QWidget *parent = 0);
    virtual ~GLWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    /**
     * Передача указателя на список объектов карты в GLWidget.
     *
     * @param all_tags - указатель на список расположеных на карт точек доступа
     */
    void setTagList(TagList * all_tags);

    /**
     * Передача указателя объекта, для котороо вычисляется расчет координат.
     * Данный указатель позволяет GLWidget отрисовать объект на карте.
     *
     * @param man - указатель на объект наблюдения.
     */
    void setMan(Man * man);

    /**
     * Установка и запрет вызова функции draw(),
     * которая отвечает за отрисовку объектов карты.
     * Функция изменяет флаг draw_acc. Предназначена для предотвращения
     * конфликтов связанных с одновременным вызовом функции draw() в GLWidget
     * и изменением объектов карты в других частях программы.
     *
     * @param acc = true - отрисовка разрешена, в противном случае - запрещена.
     */
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

     /**
      * Флаг разрешения отрисовки обектов на карте.
      * Необходим для предотвращения гонок за использование
      * объектов, отображаемых на карте.
      */
     bool draw_acc;

     void draw();

     // Timer things
     QTimer timer;

signals:
    /**
     * Сигнал вызывается при добавлении объекта на карту.
     */
    void addRFTag(RFTag * tag);
};

#endif /* GLWIDGET_H_ */
