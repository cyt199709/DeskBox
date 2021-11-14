#pragma once

#include <QWidget>
#include "BasicWindow.h"
#include "ui_RegisterWindow.h"

class RegisterWindow : public BasicWindow
{
	Q_OBJECT

public:
	RegisterWindow(QWidget *parent = Q_NULLPTR);
	~RegisterWindow();

private:
	void initControl();

private slots:
	void onOkBtnClicked();
	void onCancelBtnClicked();

private:
	Ui::RegisterWindow ui;
};
