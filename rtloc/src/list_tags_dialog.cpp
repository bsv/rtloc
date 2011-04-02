#include "inc/list_tags_dialog.h"
#include "QTimer"

ListTagsDialog::ListTagsDialog(QWidget *parent)
    : QDialog(parent)
{
	setupUi(this);

	head_labels << "Name" << "ID" << "Power" << "Distance";
	tags_model.setHorizontalHeaderLabels(head_labels);

	list_view->setModel(&tags_model);

	connect(update_button, SIGNAL(clicked()), SLOT(updateList()));
	connect(close_button, SIGNAL(clicked()), SLOT(close()));

	/*QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateList()));
	timer->start(1000);*/
}

ListTagsDialog::~ListTagsDialog()
{
}

void ListTagsDialog::updateList()
{
    if(isActiveWindow() == TRUE)
    {
	    emit update();
	    tags_model.setHorizontalHeaderLabels(head_labels);
	    list_view->resizeColumnsToContents();
    }
}

QStandardItemModel * ListTagsDialog::getModel()
{
	return &tags_model;
}
