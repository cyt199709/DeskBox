#pragma once

#include <QWidget>
#include "BasicWindow.h"
#include "ui_UserLogin.h"

class UserLogin : public BasicWindow
{
	Q_OBJECT

public:
	UserLogin(QWidget *parent = Q_NULLPTR);
	~UserLogin();

private slots:
	void onLoginBtnClicked();
	void onKeepPwdCheckStateChanged(int state);
	void onRegistBtnClicked();
	void onForgetPwdBtnClicked();

private:
	void initControl();

private:
	Ui::UserLogin ui;
};
