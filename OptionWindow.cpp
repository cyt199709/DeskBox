#include "OptionWindow.h"
#include "OptionWindowItem.h"
#include "AccountOptionWindow.h"
#include "CommonUtils.h"
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QBoxLayout>
#include <QSettings>
#include <QCryptoGraphicHash>
#include <QMessageBox>

extern QString gAccount;
extern QString gPath;
extern QColor gBackColor;

OptionWindow::OptionWindow(QWidget *parent)
	: BasicWindow(parent)
{
	ui.setupUi(this);
	loadStyleSheet("OptionWindow");
	setAttribute(Qt::WA_DeleteOnClose, true);
	setAttribute(Qt::WA_QuitOnClose, false);
	initControl();
}

OptionWindow::~OptionWindow()
{
}

void OptionWindow::initControl()
{
	loadStyleSheet("OptionWindow");
	setWindowTitle(QString::fromLocal8Bit("…Ë÷√"));

	QList<int> leftWidgetSize;
	leftWidgetSize << 200 << width() - 200;
	ui.splitter->setSizes(leftWidgetSize);

	ui.listWidget->setStyle(new CustomProxyStyle(this));

	connect(ui.listWidget, &QListWidget::itemClicked, this, &OptionWindow::onOptionWindowItemClicked);

	connect(ui.sysMin, &QPushButton::clicked, this, &OptionWindow::onShowMin);
	connect(ui.sysClose, &QPushButton::clicked, this, &OptionWindow::onShowClose);
	
	AccountOptionWindow* accountWindow = new AccountOptionWindow(this);
	OptionWindowItem* item = new OptionWindowItem(accountWindow);
	addWindow(accountWindow, item);
	connect(accountWindow, &AccountOptionWindow::onConfirmClicked, [this]() {close(); });
	connect(accountWindow, &AccountOptionWindow::onCancelClicked, [this]() {close(); });
}

void OptionWindow::addWindow(QWidget* window, OptionWindowItem* item)
{
	ui.rightStackedWidget->addWidget(window);
	QListWidgetItem* aItem = new QListWidgetItem(ui.listWidget);
	m_optionWindowItemMap.insert(aItem, window);

	aItem->setSelected(true);
	item->setContext(QString::fromLocal8Bit("’À∫≈…Ë÷√"));

	ui.listWidget->addItem(aItem);
	ui.listWidget->setItemWidget(aItem, item);

	onOptionWindowItemClicked(aItem);
}

void OptionWindow::onOptionWindowItemClicked(QListWidgetItem* item)
{
	QWidget* optionWindowWidget = m_optionWindowItemMap.find(item).value();
	ui.rightStackedWidget->setCurrentWidget(optionWindowWidget);
}