#pragma once

#include <QWidget>
#include "ui_UserCenter.h"

class UserCenter : public QWidget
{
	Q_OBJECT

public:
	UserCenter(QWidget *parent = Q_NULLPTR);
	~UserCenter();

private:
	Ui::UserCenter ui;
};
