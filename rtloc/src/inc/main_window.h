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

    TagList all_tags;

    // ������ ��� ����������� �����
    GLWidget glw;

    // ������� ����
    QMenu * menu;
    QMenu * run_menu;

    QAction * run_act;

    QTimer time_upd_list;
    QTimer timer_upd_pos;

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

    void updateMap();
    void addRFTag(RFTag * tag);
    void updateTagList();
};

#endif // MAIN_WINDOW_H
