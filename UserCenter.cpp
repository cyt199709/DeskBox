#include "UserCenter.h"
#include "UserLogin.h"
//#include "UserCenterWidgetItem.h"
#include <QLabel>
#include <QPushButton>
#include <QSettings>
#include <QDateTime>

extern QDateTime gTime;
extern QString gPath;
extern QString gAccount;
extern QList<QString> gFileList;

UserCenter::UserCenter(QWidget *parent)
	: BasicWindow(parent)
{
	ui.setupUi(this);
	loadStyleSheet("UserCenter");
	setAttribute(Qt::WA_DeleteOnClose, true);
	setAttribute(Qt::WA_QuitOnClose, false);
	initControl();

	connect(ui.sysMin, &QPushButton::clicked, this, &UserCenter::onShowMin);
	connect(ui.sysClose, &QPushButton::clicked, this, &UserCenter::onShowClose);
}

UserCenter::~UserCenter()
{
}

void UserCenter::initControl()
{
	QSettings settings(gPath + "Account", QSettings::IniFormat);
	ui.userNameLabel->setText(QString::fromLocal8Bit("用户名:") + settings.value(gAccount).toString());
	ui.accountLabel->setText(QString::fromLocal8Bit("账号:") + gAccount);
	ui.timeLabel->setText(QString::fromLocal8Bit("最后打开软件时间") + gTime.toString());
	QPixmap pix(":/Resources/Icon/trLogo.png");
	pix.scaled(ui.icon->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	ui.icon->setPixmap(pix);

	connect(ui.fileBtn, &QPushButton::clicked, [this]() {
		ui.userStackWidget->setCurrentIndex(1);
		ui.fileListWidget->clear();
		foreach(QString filePath, gFileList)
		{
			ui.fileListWidget->addItem(filePath);
		}
	});
	connect(ui.softInfoBtn, &QPushButton::clicked, [this]() {ui.userStackWidget->setCurrentIndex(2); });
	connect(ui.returnBtn1, &QPushButton::clicked, [this]() {ui.userStackWidget->setCurrentIndex(0); });
	connect(ui.returnBtn2, &QPushButton::clicked, [this]() {ui.userStackWidget->setCurrentIndex(0); });
	connect(ui.loginOutBtn, &QPushButton::clicked, [this]() {qApp->quit();});
}
