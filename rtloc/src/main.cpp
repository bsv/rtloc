#include "inc/main_window.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
	QTextCodec *codec = QTextCodec::codecForName("UTF-8");
	QTextCodec::setCodecForCStrings(codec);

    QApplication a(argc, argv);

    Processor * proc = new Processor();
    MainWindow w(proc);

    w.show();

    return a.exec();
}
