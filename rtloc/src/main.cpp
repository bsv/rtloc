#include "inc/main_window.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Processor * proc = new Processor();
    MainWindow w(proc);

    w.show();

    return a.exec();
}
