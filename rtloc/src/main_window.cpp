#include "inc/main_window.h"
#include <QHBoxLayout>

MainWindow::MainWindow(Processor * proc_new, QWidget *parent)
    : QMainWindow(parent)
{
	setupUi(this);
	proc = proc_new;

	menu = menubar->addMenu("Menu");
	menu->addAction("Create map", this, SLOT(createMap()));
    menu->addAction("Open map", this, SLOT(openMap()));
    menu->addAction("Save map", this, SLOT(saveMap()));
    menu->addAction("Map settings", this, SLOT(mapSettings()));
    menu->addSeparator();
    menu->addAction("Create floor", this, SLOT(createFloor()));
    menu->addAction("View floors", this, SLOT(viewListFloors()));
    menu->addAction("View tags", this, SLOT(viewListTags()));

	run_menu = menubar->addMenu("Run");
	run_act = run_menu->addAction("Start locating");

	connect(run_act, SIGNAL(triggered()), SLOT(runLoc()));
	connect(&time_upd_list, SIGNAL(timeout()), SLOT(updateTagList()));
	connect(&tags_dialog, SIGNAL(finished(int)), &time_upd_list, SLOT(stop()));
	connect(&glw, SIGNAL(addRFTag(RFTag *)), SLOT(addRFTag(RFTag *)));
	connect(&timer_upd_pos, SIGNAL(timeout()), SLOT(updateMap()));

	timer_upd_pos.start(1000);

	glw.setTagList(&all_tags);
	glw.setMan(proc->getMan());

	h_layout->addWidget(&glw);
}

void MainWindow::updateMap()
{
    glw.setDrawAcc(false);

    proc->calcPos(&all_tags);

    glw.setDrawAcc(true);
}

void MainWindow::updateTagList()
{
   TagList * list = proc->getActiveTags();
   tags_dialog.updateList(list);
}

void MainWindow::addRFTag(RFTag * tag)
{
    all_tags.push_back(tag);
}


MainWindow::~MainWindow()
{
}

/*void MainWindow::getListTags()
{
	QStandardItemModel * model = tags_dialog.getModel();
	QList<QStandardItem * > row_items;
	TagList * rftags = proc->getActiveTags();

	model->clear();

	for (TagList::iterator it = rftags->begin(); it < rftags->end(); ++it)
	{
	    row_items.clear();

	    QString mac;

	    row_items.append(new QStandardItem((*it)->getName()));
	    row_items.append(new QStandardItem((*it)->getId()));
	    row_items.append(new QStandardItem(QString().setNum((*it)->getRSSI())));
	    row_items.append(new QStandardItem("0"));

	    model->appendRow(row_items);
	}
}*/

void MainWindow::runLoc()
{
    if(run_act->text() == "Start locating")
    {
        run_act->setText("Stop locating");
    } else
    {
        run_act->setText("Start locating");
    }
}

void MainWindow::createFloor()
{
}

void MainWindow::viewListFloors()
{
}

void MainWindow::viewListTags()
{
    time_upd_list.start(1000);
	tags_dialog.show();
}

void MainWindow::saveMap()
{
}

void MainWindow::openMap()
{
}

void MainWindow::createMap()
{
}

void MainWindow::mapSettings()
{
}
