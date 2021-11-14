#pragma once

#include "BasicWindow.h"
#include "ui_SkinWindow.h"

class SkinWindow : public BasicWindow
{
	Q_OBJECT

public:
	SkinWindow(QWidget *parent = Q_NULLPTR);
	~SkinWindow();

private:
	void initControl();
	
private slots:
	void onShowClose();

private:
	Ui::SkinWindow ui;
};
