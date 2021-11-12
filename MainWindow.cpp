#include "MainWindow.h"
#include "CommonUtils.h"

MainWindow::MainWindow(QWidget *parent)
	: BasicWindow(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	initTitleBar();
	setTitleBarTitle("", ":/Resources/Icon/big_logo.png");
	loadStyleSheet("MainWindow");
	//initControl();
}

MainWindow::~MainWindow()
{

}

void MainWindow::initControl()
{

}

void MainWindow::onAddToolClicked()
{
}

void MainWindow::onAddFileClicked()
{

}