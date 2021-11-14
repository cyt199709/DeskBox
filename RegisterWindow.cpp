#include "RegisterWindow.h"
#include <QRegExp>
#include <QStandardPaths>
#include <QSettings>
#include <QCryptographicHash>

const QString path = QStandardPaths::standardLocations(QStandardPaths::HomeLocation).at(0) + "/AppData/Local/DeskBox/";

RegisterWindow::RegisterWindow(QWidget *parent)
	: BasicWindow(parent)
{
	ui.setupUi(this);
	loadStyleSheet("RegisterWindow");
	setAttribute(Qt::WA_QuitOnClose, false);
	setAttribute(Qt::WA_DeleteOnClose, true);
	initControl();
}

RegisterWindow::~RegisterWindow()
{
}

void RegisterWindow::initControl()
{
	connect(ui.sysMin, &QPushButton::clicked, [this]() {this->showMinimized(); });
	connect(ui.sysClose, &QPushButton::clicked, [this]() {this->close(); });
	connect(ui.OkBtn, SIGNAL(clicked()), this, SLOT(onOkBtnClicked()));
	connect(ui.CancelBtn, SIGNAL(clicked()), this, SLOT(onCancelBtnClicked()));
}

void RegisterWindow::onOkBtnClicked()
{
	QRegExp userNameReg("^[a-zA-Z0-9_-]{4,16}$");
	if (!userNameReg.exactMatch(ui.UserNameLineEdit->text()))
	{
		ui.TipLabel->setText(QString::fromLocal8Bit("用户名不能包含(!@#$%^&*\\/)等特殊字符"));
		return;
	}

	if (!userNameReg.exactMatch(ui.AccountLineEdit->text()))
	{
		ui.TipLabel->setText(QString::fromLocal8Bit("账号不能包含(!@#$%^&*\\/)等特殊字符"));
		return;
	}

	QRegExp passwordReg("^.*(?=.{6,})(?=.*\\d)(?=.*[A-Z])(?=.*[a-z])(?=.*[!@#$%^&*? ]).*$");
	QString str = ui.PasswordLineEdit->text();
	if (!passwordReg.exactMatch(ui.PasswordLineEdit->text()))
	{
		ui.TipLabel->setText(QString::fromLocal8Bit("密码最少6位, 包括至少一个大写，小写，数字，特殊字符"));
		return;
	}

	if (ui.ConfirmPasswordLineEdit->text() != ui.PasswordLineEdit->text())
	{
		ui.TipLabel->setText(QString::fromLocal8Bit("两次输入的密码不同"));
		return;
	}

	QRegExp emailReg("^([A-Za-z0-9_\-\.])+\@([A-Za-z0-9_\-\.])+\.([A-Za-z]{2,4})$");
	if (!emailReg.exactMatch(ui.EmailLineEdit->text()))
	{
		ui.TipLabel->setText(QString::fromLocal8Bit("邮箱格式不正确"));
		return;
	}

	QSettings settings(path + QString("Account"), QSettings::IniFormat);

	if(settings.childGroups().contains(ui.AccountLineEdit->text()))
	{
		ui.TipLabel->setText(QString::fromLocal8Bit("账号已存在"));
		return;
	}

	settings.setValue(ui.AccountLineEdit->text() + QString("/UserName"), ui.UserNameLineEdit->text());
	settings.setValue(ui.AccountLineEdit->text() + QString("/Password"), QCryptographicHash::hash(ui.PasswordLineEdit->text().toUtf8(), QCryptographicHash::Md5).toHex());
	settings.setValue(ui.AccountLineEdit->text() + QString("/Email"), ui.EmailLineEdit->text());
	settings.setValue(ui.AccountLineEdit->text() + QString("/Birthday"), ui.DateEdit->text());
	close();
}

void RegisterWindow::onCancelBtnClicked()
{
	close();
}