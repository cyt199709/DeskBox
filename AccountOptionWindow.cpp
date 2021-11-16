#include "AccountOptionWindow.h"
#include <QSettings>
#include <QBoxLayout>
#include <QCryptoGraphicHash>
#include <QMessageBox>

extern QString gAccount;
extern QString gPath;

AccountOptionWindow::AccountOptionWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	initControl();
}

AccountOptionWindow::~AccountOptionWindow()
{
}

void AccountOptionWindow::initControl()
{
	QSettings settings(gPath + "Account", QSettings::IniFormat);
	ui.UserNameLineEdit->setText(settings.value(gAccount + "/UserName").toString());
	ui.AccountLineEdit->setText(gAccount);
	ui.TelLineEdit->setText(settings.value(gAccount + "/Tel").toString());
	ui.MailLineEdit->setText(settings.value(gAccount + "/Email").toString());

	connect(ui.NameChangeBtn, &QPushButton::clicked, this, &AccountOptionWindow::onNameChangeBtnClicked);
	connect(ui.TelChangeBtn, &QPushButton::clicked, this, &AccountOptionWindow::onTelChangeBtnClicked);
	connect(ui.MailChangeBtn, &QPushButton::clicked, this, &AccountOptionWindow::onMailChangeBtnClicked);

	connect(ui.PasswordChangeBtn, &QPushButton::clicked, this, &AccountOptionWindow::onPwdChangeBtnClicked);
}

void AccountOptionWindow::onNameChangeBtnClicked()
{
	QString text = ui.NameChangeBtn->text();
	if (text == QString::fromLocal8Bit("�޸�"))
	{
		ui.NameChangeBtn->setText(QString::fromLocal8Bit("ȷ��"));
		ui.UserNameLineEdit->setEnabled(true);
	}
	else{
		ui.UserNameLineEdit->setEnabled(false);
		QSettings settings(gPath + "Account", QSettings::IniFormat);
		if (!ui.UserNameLineEdit->text().isEmpty())
			settings.setValue(gAccount + "/UserName", ui.UserNameLineEdit->text());
		ui.NameChangeBtn->setText(QString::fromLocal8Bit("�޸�"));
	}
}

void AccountOptionWindow::onTelChangeBtnClicked()
{
	QString text = ui.TelChangeBtn->text();
	if (text == QString::fromLocal8Bit("�޸�"))
	{
		ui.TelChangeBtn->setText(QString::fromLocal8Bit("ȷ��"));
		ui.TelLineEdit->setEnabled(true);
	}else{
		ui.TelLineEdit->setEnabled(false);
		QSettings settings(gPath + "Account", QSettings::IniFormat);
		if (!ui.TelLineEdit->text().isEmpty())
			settings.setValue(gAccount + "/Tel", ui.TelLineEdit->text());
		ui.TelChangeBtn->setText(QString::fromLocal8Bit("�޸�"));
	}
}

void AccountOptionWindow::onMailChangeBtnClicked()
{
	QString text = ui.MailChangeBtn->text();
	if (text == QString::fromLocal8Bit("�޸�"))
	{
		ui.MailChangeBtn->setText(QString::fromLocal8Bit("ȷ��"));
		ui.MailLineEdit->setEnabled(true);
	}else{
		ui.MailLineEdit->setEnabled(false);
		QSettings settings(gPath + "Account", QSettings::IniFormat);
		if (!ui.MailLineEdit->text().isEmpty())
			settings.setValue(gAccount + "/Email", ui.MailLineEdit->text());
		ui.MailChangeBtn->setText(QString::fromLocal8Bit("�޸�"));
	}
}

void AccountOptionWindow::onPwdChangeBtnClicked()
{
	QWidget* pwdChangeWidget = new QWidget(nullptr);
	QLabel* oriPwd = new QLabel(QString::fromLocal8Bit("ԭ����"));
	QLabel* newPwd = new QLabel(QString::fromLocal8Bit("������"));
	QLineEdit* oriPwdLineEdit = new QLineEdit;
	QLineEdit* newPwdLineEdit = new QLineEdit;
	QPushButton* confirm = new QPushButton(QString::fromLocal8Bit("ȷ��"));
	QPushButton* cancel = new QPushButton(QString::fromLocal8Bit("ȡ��"));
	QHBoxLayout* mainLayout = new QHBoxLayout;
	QVBoxLayout* vlayout1 = new QVBoxLayout;
	QVBoxLayout* vlayout2 = new QVBoxLayout;
	vlayout1->addWidget(oriPwd);
	vlayout1->addWidget(newPwd);
	vlayout1->addWidget(confirm);

	vlayout2->addWidget(oriPwdLineEdit);
	vlayout2->addWidget(newPwdLineEdit);
	vlayout2->addWidget(cancel);
	mainLayout->addLayout(vlayout1);
	mainLayout->addLayout(vlayout2);

	pwdChangeWidget->setLayout(mainLayout);

	pwdChangeWidget->show();
	connect(cancel, &QPushButton::clicked, pwdChangeWidget, &QWidget::close);
	pwdChangeWidget->setAttribute(Qt::WA_DeleteOnClose);

	connect(confirm, &QPushButton::clicked, [oriPwdLineEdit, newPwdLineEdit]() {
		QSettings settings(gPath + "Account", QSettings::IniFormat);
		QString text = oriPwdLineEdit->text();
		if (QCryptographicHash::hash(text.toUtf8(), QCryptographicHash::Md5).toHex() != settings.value(gAccount + "/Password").toString())
		{
			QMessageBox::information(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�������"));
			return;
		}
		if (newPwdLineEdit->text().isEmpty())
			return;
		settings.setValue(gAccount + "/Password", QCryptographicHash::hash(newPwdLineEdit->text().toUtf8(), QCryptographicHash::Md5).toHex());
	});
}