#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtGui/QMainWindow>
#include "../../ui_main_window.h"
#include "processor.h"
#include "GLWidget.h"
#include "list_tags_dialog.h"

class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(Processor * proc_new, QWidget *parent = 0);
    ~MainWindow();

private:

    ListTagsDialog tags_dialog;

    // ������, ���������� �� ���������� ���������
    Processor * proc;

    // ������ ��� ����������� �����
    GLWidget glw;

    // ������� ����
    QMenu * menu;
    QMenu * run_menu;

    QAction * run_act;

public slots:

    // ������ ����������������
    // �� ����� ������������� ����� ������������
    // ������������� �����
    void runLoc();

    // �������� ����
    void createMap();
    void createFloor();
    void viewListFloors();
    void viewListTags();
    void saveMap();
    void openMap();
    void mapSettings();

    void getListTags();
};

#endif // MAIN_WINDOW_H
