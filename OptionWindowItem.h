#pragma once

#include <QWidget>
#include "ui_OptionWindowItem.h"

class OptionWindowItem : public QWidget
{
	Q_OBJECT

public:
	OptionWindowItem(QWidget *parent = Q_NULLPTR);
	~OptionWindowItem();

private:
	Ui::OptionWindowItem ui;
};