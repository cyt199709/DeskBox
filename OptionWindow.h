#pragma once

#include "BasicWindow.h"
#include "ui_OptionWindow.h"
#include <QWidget>
#include <QListWidgetItem>

class OptionWindow : public BasicWindow
{
	Q_OBJECT

public:
	OptionWindow(QWidget *parent = Q_NULLPTR);
	~OptionWindow();

private:
	void initControl();
	void initAccount();

private slots:
	void onAccountChangeBtnClicked();

private:
	Ui::OptionWindow ui;

private:
	QMap<QListWidgetItem*, QWidget*> m_optionWindowItemMap;
};
