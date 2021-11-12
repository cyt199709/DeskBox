#pragma once

#include <QWidget>
#include <QLinkedList>
#include "BasicWindow.h"
#include "ui_MainWindow.h"

class MainWindowItem;
enum TYPE;

class MainWindow : public BasicWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();

private:
	void initControl();
	void getIniInfo();

private slots:
	void onAddClicked(TYPE type, QString filePath);
	void onMenuBtnClicked();
	void onMenuItemClicked();

protected:
	virtual void paintEvent(QPaintEvent* event);

private:
	Ui::MainWindow ui;

private:
	QList<MainWindowItem*> m_toolList;
	QList<MainWindowItem*> m_fileList;
};
