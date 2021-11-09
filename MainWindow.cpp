#include "MainWindow.h"
#include "CommonUtils.h"

MainWindow::MainWindow(QWidget *parent)
	: BasicWindow(parent)
{
	ui.setupUi(this);
	//ui.FileTableView->setStyle(new CustomProxyStyle(this));
}

MainWindow::~MainWindow()
{
}
