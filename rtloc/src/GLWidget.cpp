/*
 * GLWidget.cpp
 *
 *  Created on: 25.03.2011
 *      Author: Администратор
 */

#include "inc/GLWidget.h"
#include <QColorDialog>
#include <QTextStream>
#include "inc/map_item_dialog.h"
#include "inc/RFTag.h"

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{
	QTextStream out(stdout);
		out << "\nGLWidget start working\n";
	// Вызывает ошибку при выходе
	//http://bugreports.qt.nokia.com/browse/QTBUG-13260?page=com.atlassian.jira.plugin.system.issuetabpanels%3Aall-tabpanel
//  setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
    //

	rotationX = 0;
    rotationY = 0;
    rotationZ = 0;

    items.clear();

    translationX = 0;
    translationY = 0;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer->start(100);
    //faceColors[0] = Qt::red;
}

GLWidget::~GLWidget()
{
	QTextStream out(stdout);
	out << "\nGLWidget stop working\n";
	delete timer;
	items.clear();
}

QSize GLWidget::minimumSizeHint() const
 {
     return QSize(100, 100);
 }

QSize GLWidget::sizeHint() const
{
     return QSize(400, 400);
}

void GLWidget::initializeGL()
{

    qglClearColor(Qt::black);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void GLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    if(height == 0) height = 1;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLfloat aspect = (GLfloat)width / (GLfloat)height;
#if 0
    glFrustum(-aspect, aspect, -1.0, 1.0, 4.0, 15.0);
#else
    if(width <= height)
    	glOrtho( 0, 100.0, 			0, 100.0/aspect, 	1.0, -1.0 );
    else
    	glOrtho( 0, 100.0*aspect, 	0, 100.0, 			1.0, -1.0 );
#endif
    glMatrixMode(GL_MODELVIEW);
    updateGL();
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw();
}

void GLWidget::draw()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(translationX, translationY, 0);
    glRotatef(rotationX, 1.0, 0.0, 0.0);
    glRotatef(rotationY, 0.0, 1.0, 0.0);
    glRotatef(rotationZ, 0.0, 0.0, 1.0);


    glFrontFace(GL_CW);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    	glVertex3f( 10,  10,  0.5);
    	glVertex3f( 10,  20,  0.5);
    	glVertex3f( 20,  20,  0.5);
    	glVertex3f( 20,  10,  0.5);
    glEnd();

    glColor3f(1.0, 0, 0);
    glPointSize(4.0);


    for(int i = 0; i < items.size(); i++)
    {
    	items[i]->draw(this);
    }
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{

	if(event->button() == Qt::LeftButton)
	{
		lastPos = event->pos();

		GLdouble x, y;

		getWorldCoordinates(event->x(), event->y(), x,y);

		MapItemDialog item_dlg(x, y);
		item_dlg.exec();

		if(item_dlg.result() == QDialog::Accepted)
		{
			items.push_back(new MapItem(item_dlg.getName(), item_dlg.getX(), item_dlg.getY()));

			QTextStream out(stdout);
			out << "w = " << width() << " h = " << height();
		}

	}
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    GLfloat dx = (GLfloat)(event->x()  - lastPos.x()) / width();
    GLfloat dy = (GLfloat)(lastPos.y() - event->y()) / height();

    if (event->buttons() & Qt::LeftButton) {
        //rotationX += 180 * dy;
        //rotationY += 180 * dx;
    	updateGL();
    } else if (event->buttons() & Qt::RightButton) {
       //rotationX += 180 * dy;
       //rotationZ += 180 * dx;
    	translationX += dx*100;
    	translationY += dy*100;
       updateGL();
    }
    lastPos = event->pos();
}

void GLWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    int face = -1;//faceAtPosition(event->pos());
    if (face != -1)
    {
        //QColor color = QColorDialog::getColor(faceColors[face], this);
        //if (color.isValid())
        //{
        //    faceColors[face] = color;
        //    updateGL();
        //}
    }
}


//
//	GLWidget::getWorldCoordinates()
//
void GLWidget::getWorldCoordinates( GLdouble viewport_x, GLdouble viewport_y, GLdouble &x, GLdouble &y )
{
	QTextStream out(stdout);
	GLdouble z=0;
	GLdouble model[16];
	    glGetDoublev(GL_MODELVIEW_MATRIX, model);
	GLdouble proj[16];
	    glGetDoublev(GL_PROJECTION_MATRIX, proj);
	GLint viewport[4];
	    glGetIntegerv(GL_VIEWPORT, viewport);

	    gluUnProject(viewport_x, viewport[3] - viewport_y, 0,  model, proj, viewport, &x,&y,&z);

	    out << "\nData\n" << x << " " << y << " " << z;
}

#if 0
int GLWidget::faceAtPosition(const QPoint &pos)
{
    const int MaxSize = 512;
    GLuint buffer[MaxSize];
    GLint viewport[4];

    glGetIntegerv(GL_VIEWPORT, viewport);
    glSelectBuffer(MaxSize, buffer);
    glRenderMode(GL_SELECT);
    glInitNames();
    glPushName(0);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluPickMatrix((GLdouble)pos.x(),
                (GLdouble)(viewport[3] - pos.y()),
                5.0, 5.0, viewport);
    GLfloat x = (GLfloat)width() / height();
    glFrustum(-x, x, -1.0, 1.0, 4.0, 15.0);
    draw();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    if (!glRenderMode(GL_RENDER))
        return -1;
    return buffer[3];
}
#endif
