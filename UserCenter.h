#pragma once

#include <QWidget>
#include "ui_UserCenter.h"
#include "BasicWindow.h"

class UserCenter : public BasicWindow
{
	Q_OBJECT

public:
	UserCenter(QWidget *parent = Q_NULLPTR);
	~UserCenter();

private:
	void initControl();

private:
	Ui::UserCenter ui;

private:
	/*QWidget* m_mainWindow;
	QWidget* m_softInfoWindow;
	QWidget* m_fileListWindow;
	QMap<QWidget*, QWidget*> m_widgetMap;*/
};
