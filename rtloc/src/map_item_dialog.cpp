/*
 * MapItemDialog.cpp
 *
 *  Created on: 06.05.2011
 *      Author: bsv
 */

#include "inc/map_item_dialog.h"

MapItemDialog::MapItemDialog(QWidget * parent)
	: QDialog(parent)
{
	setupUi(this);
}

MapItemDialog::MapItemDialog(float x, float y, QWidget *parent)
{
	setupUi(this);
	name_edit->setText("¬ведите им€");
	x_spin->setValue((int)x);
	y_spin->setValue((int)y);
}

QString MapItemDialog::getName()
{
	return name_edit->text();
}

int MapItemDialog::getX()
{
	return x_spin->value();
}

int MapItemDialog::getY()
{
	return y_spin->value();
}

MapItemDialog::~MapItemDialog()
{
}
