#pragma once

#include "BasicWindow.h"
#include "ui_OptionWindow.h"
#include <QWidget>

class OptionWindow : public BasicWindow
{
	Q_OBJECT

public:
	OptionWindow(QWidget *parent = Q_NULLPTR);
	~OptionWindow();

private:
	Ui::OptionWindow ui;
};
