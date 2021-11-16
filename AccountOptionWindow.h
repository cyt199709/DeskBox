#pragma once

#include <QWidget>
#include "ui_AccountOptionWindow.h"

class AccountOptionWindow : public QWidget
{
	Q_OBJECT

public:
	AccountOptionWindow(QWidget *parent = Q_NULLPTR);
	~AccountOptionWindow();
	
private:
	void initControl();

private slots:
	void onNameChangeBtnClicked();
	void onTelChangeBtnClicked();
	void onMailChangeBtnClicked();
	void onPwdChangeBtnClicked();

private:
	Ui::AccountOptionWindow ui;
};
