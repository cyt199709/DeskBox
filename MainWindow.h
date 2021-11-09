#pragma once

#include <QWidget>
#include "BasicWindow.h"
#include "ui_MainWindow.h"

class MainWindow : public BasicWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();

private:
	Ui::MainWindow ui;
};
