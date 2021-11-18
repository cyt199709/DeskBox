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
	void updateSearchStyle();
	void updateTable();

private slots:
	void onAddClicked(TYPE type, QString filePath);
	void onMenuBtnClicked();
	void onMenuItemClicked();
	void onSearchLineEditChanged();
	//void onItemDelete(MainWindowItem*);

protected:
	virtual void paintEvent(QPaintEvent* event);
	virtual void dragEnterEvent(QDragEnterEvent* event);
	virtual void dragMoveEvent(QDragEnterEvent* event);
	virtual void dropEvent(QDropEvent* event);
	virtual bool eventFilter(QObject* obj, QEvent* event);

private:
	Ui::MainWindow ui;

private:
	QList<MainWindowItem*> m_toolList;
	QList<MainWindowItem*> m_fileList;
	QList<QString> m_filePathList;
	QList<QString> m_toolPathList;
};
