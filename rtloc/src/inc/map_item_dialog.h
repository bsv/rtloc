#ifndef MAP_ITEM_DIALOG_H
#define MAP_ITEM_DIALOG_H

#include <QtGui/QDialog>
#include <QStandardItemModel>
#include "../ui_map_item_dialog.h"

class MapItemDialog : public QDialog, public Ui::MapItemDialogClass
{
    Q_OBJECT

public:
    MapItemDialog(QWidget *parent = 0);
    MapItemDialog(float x, float y, QWidget *parent = 0);
    ~MapItemDialog();

    QString getName();
    int getX();
    int getY();
};

#endif // MAP_ITEM_DIALOG_H
