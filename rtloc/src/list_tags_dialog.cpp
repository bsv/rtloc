#include "inc/list_tags_dialog.h"
#include "QTimer"

ListTagsDialog::ListTagsDialog(QWidget *parent)
    : QDialog(parent)
{
	setupUi(this);

	head_labels << "Name" << "ID" << "Power" << "Distance";
	tags_model.setHorizontalHeaderLabels(head_labels);

	list_view->setModel(&tags_model);

	connect(close_button, SIGNAL(clicked()), SLOT(close()));
}

ListTagsDialog::~ListTagsDialog()
{
}

void ListTagsDialog::updateList(TagList * tag_list)
{
    if(isActiveWindow() == TRUE)
    {
    	QList<QStandardItem * > row_items;

    	tags_model.clear();

    	for (TagList::iterator it = tag_list->begin(); it < tag_list->end(); ++it)
    	{
    		row_items.clear();

    		QString mac;

    		row_items.append(new QStandardItem((*it)->getName()));
    		row_items.append(new QStandardItem((*it)->getId()));
    		row_items.append(new QStandardItem(QString().setNum((*it)->getRSSI())));
    		row_items.append(new QStandardItem("0"));

    		tags_model.appendRow(row_items);
    	}

	    tags_model.setHorizontalHeaderLabels(head_labels);
	    list_view->resizeColumnsToContents();
    }
}

QStandardItemModel * ListTagsDialog::getModel()
{
	return &tags_model;
}
