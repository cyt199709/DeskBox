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
#include <QCheckBox>
#include <QFileInfo>
#include <QDir>

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
	setWindowTitle(QString::fromLocal8Bit("设置"));

	QList<int> leftWidgetSize;
	leftWidgetSize << 200 << width() - 200;
	ui.splitter->setSizes(leftWidgetSize);

	ui.listWidget->setStyle(new CustomProxyStyle(this));

	connect(ui.listWidget, &QListWidget::itemClicked, this, &OptionWindow::onOptionWindowItemClicked);

	connect(ui.sysMin, &QPushButton::clicked, this, &OptionWindow::onShowMin);
	connect(ui.sysClose, &QPushButton::clicked, this, &OptionWindow::onShowClose);
	
	AccountOptionWindow* accountWindow = new AccountOptionWindow(this);
	OptionWindowItem* accountItem = new OptionWindowItem(accountWindow);
	accountItem->setContext(QString::fromLocal8Bit("账号设置"));
	addWindow(accountWindow, accountItem);
	m_optionWindowMap.key((QWidget*)(accountWindow))->setSelected(true);
	ui.rightStackedWidget->setCurrentWidget(accountWindow);
	connect(accountItem, &OptionWindowItem::signalClicked, this, &OptionWindow::onOptionWindowItemClicked);

	initStartWindow();
}

void OptionWindow::initStartWindow()
{
	QWidget* start = new QWidget(this);
	QCheckBox* startCheckBox = new QCheckBox(QString::fromLocal8Bit("开机自启"), this);
	QVBoxLayout* vLayout = new QVBoxLayout(this);
	vLayout->addStretch(20);
	vLayout->addWidget(startCheckBox);
	vLayout->addStretch(160);
	start->setLayout(vLayout);

	OptionWindowItem* startItem = new OptionWindowItem(start);
	startItem->setContext(QString::fromLocal8Bit("设置开机自启"));
	QSettings settings(QApplication::applicationDirPath() + "/" + QString("UserInfo.ini"), QSettings::IniFormat);
	if (settings.value("Default/start").toBool())
	{
		startCheckBox->setChecked(true);
	}

	addWindow(start, startItem);
	connect(startCheckBox, &QCheckBox::stateChanged, this, &OptionWindow::onStartStateChanged);
	connect(startItem, &OptionWindowItem::signalClicked, this, &OptionWindow::onOptionWindowItemClicked);
}

void OptionWindow::addWindow(QWidget* window, OptionWindowItem* item)
{
	ui.rightStackedWidget->addWidget(window);
	QListWidgetItem* aItem = new QListWidgetItem(ui.listWidget);
	m_optionWindowMap.insert(aItem, window);
	m_optionWindowItemMap.insert(window, item);

	ui.listWidget->addItem(aItem);
	ui.listWidget->setItemWidget(aItem, item);
}

void OptionWindow::onOptionWindowItemClicked()
{
	OptionWindowItem* item = (OptionWindowItem*)sender();
	QWidget* optionWindowWidget = m_optionWindowItemMap.key(item);
	ui.rightStackedWidget->setCurrentWidget(optionWindowWidget);
}

void OptionWindow::onStartStateChanged(int state)
{
	QSettings settings("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::Registry64Format);
	QSettings userSettings(QApplication::applicationDirPath() + "/" + QString("UserInfo.ini"), QSettings::IniFormat);
	QFileInfo fileInfo(QApplication::applicationFilePath());
	QString name = fileInfo.baseName();
	QString path = settings.value(name).toString();

	if (state == 0)
	{
		settings.remove(name);
	}
	else if (state == 2)
	{
		userSettings.setValue("Default/start", true);
		QString newPath = QDir::toNativeSeparators(QApplication::applicationFilePath());
		if (path != newPath)
		{
			settings.setValue(name, newPath);
		}
	}
}