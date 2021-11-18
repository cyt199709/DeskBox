#include "UserLogin.h"
#include "MainWindow.h"
#include "RegisterWindow.h"
#include <QSettings>
#include <QApplication>
#include <QStandardPaths>
#include <QMessageBox>
#include <QCryptographicHash>

QString gPath = QStandardPaths::standardLocations(QStandardPaths::HomeLocation).at(0) + "/AppData/Local/DeskBox/";
QString gAccount;

UserLogin::UserLogin(QWidget*parent)
	: BasicWindow(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose, true);
	setAttribute(Qt::WA_QuitOnClose, true);
	initTitleBar();
	setTitleBarTitle("", ":/Resources/Icon/DeskBoxLogo.png");
	loadStyleSheet("UserLogin");
	initControl();
}

UserLogin::~UserLogin()
{
}


void UserLogin::onLoginBtnClicked()
{
	QString account = ui.AccountLineEdit->text();
	QString pwd = ui.PasswordLineEdit->text();

	QSettings settings(gPath + QString("Account"), QSettings::IniFormat);
	if (!settings.childGroups().contains(account))
	{
		QMessageBox::information(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("账号不存在"));
		ui.AccountLineEdit->clear();
		ui.PasswordLineEdit->clear();
		return;
	}
		 
	if (settings.value(account + "/" + QString("Password")).toString() != QCryptographicHash::hash(pwd.toUtf8(), QCryptographicHash::Md5).toHex())
	{
		QMessageBox::information(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("密码错误!"));
		ui.PasswordLineEdit->clear();
		return;
	}

	gAccount = account;

	QSettings User(QApplication::applicationDirPath() + "/" + QString("UserInfo.ini"), QSettings::IniFormat);
	User.setValue("Default/act", account);
	if (ui.KeepPwdCheckBox->isChecked())
	{
		User.setValue("Default/pwd", pwd);
	}

	close();
	MainWindow* mainWindow = new MainWindow;
	mainWindow->show();
}

void UserLogin::onKeepPwdCheckStateChanged(int state)
{
	QSettings settings(QApplication::applicationDirPath() + "/" + QString("UserInfo.ini"), QSettings::IniFormat);
	if (state == 0)
		settings.setValue("Default/PwdCheck", "false");
	else if (state == 2)
		settings.setValue("Default/PwdCheck", "true");
}

void UserLogin::onRegistBtnClicked()
{
	RegisterWindow* registerWindow = new RegisterWindow;
	registerWindow->show();
}

void UserLogin::onForgetPwdBtnClicked()
{

}

void UserLogin::initControl()
{
	QSettings settings(QApplication::applicationDirPath() + "/" + QString("UserInfo.ini"), QSettings::IniFormat);
	QString str = settings.value("Default/act").toString();
	if (settings.value("Default/PwdCheck").toBool())
		ui.KeepPwdCheckBox->setChecked(true);
	if (!str.isEmpty())
	{
		ui.AccountLineEdit->setText(str);
		if (ui.KeepPwdCheckBox->isChecked())
		{
			ui.PasswordLineEdit->setText(settings.value("Default/pwd").toString());
		}
	}
	connect(ui.LoginBtn, &QPushButton::clicked, this, &UserLogin::onLoginBtnClicked);
	connect(ui.KeepPwdCheckBox, &QCheckBox::stateChanged, this, &UserLogin::onKeepPwdCheckStateChanged);
	connect(ui.RegisterBtn, &QPushButton::clicked, this, &UserLogin::onRegistBtnClicked);
	connect(ui.ForgetPwdBtn, &QPushButton::clicked, this, &UserLogin::onForgetPwdBtnClicked);
}