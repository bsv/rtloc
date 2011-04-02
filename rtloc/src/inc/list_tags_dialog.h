#ifndef VIEW_LIST_TAGS_H
#define VIEW_LIST_TAGS_H

#include <QtGui/QDialog>
#include <QStandardItemModel>
#include "../ui_list_tags_dialog.h"

class ListTagsDialog : public QDialog, public Ui::ListTagsDialogClass
{
    Q_OBJECT

public:
    ListTagsDialog(QWidget *parent = 0);
    ~ListTagsDialog();

    QStandardItemModel * getModel();

private:
    QStandardItemModel tags_model;
    QStringList head_labels;

signals:
	void update();

public slots:
	void updateList();
};

#endif // VIEW_LIST_TAGS_H
