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
	void addWindow(QWidget* window, OptionWindowItem* item);

private slots:
	void onOptionWindowItemClicked(QListWidgetItem* item);

private:
	Ui::OptionWindow ui;

private:
	QMap<QListWidgetItem*, QWidget*> m_optionWindowItemMap;
	QMetaObject::Connection m_dis;
};
