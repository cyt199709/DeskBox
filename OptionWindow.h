#pragma once

#include "BasicWindow.h"
#include "ui_OptionWindow.h"
#include <QWidget>
#include <QListWidgetItem>

class OptionWindowItem;

class OptionWindow : public BasicWindow
{
	Q_OBJECT

public:
	OptionWindow(QWidget *parent = Q_NULLPTR);
	~OptionWindow();

private:
	void initControl();
	void initStartWindow();
	void addWindow(QWidget* window, OptionWindowItem* item);

private slots:
	void onOptionWindowItemClicked();
	void onStartStateChanged(int state);

private:
	Ui::OptionWindow ui;

private:
	QMap<QListWidgetItem*, QWidget*> m_optionWindowMap;
	QMap< QWidget*, OptionWindowItem*> m_optionWindowItemMap;
	QMetaObject::Connection m_dis;
};
