#include "OptionWindow.h"
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QBoxLayout>

extern QString gAccount;

OptionWindow::OptionWindow(QWidget *parent)
	: BasicWindow(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose, true);
	setAttribute(Qt::WA_QuitOnClose, false);

	initControl();
}

OptionWindow::~OptionWindow()
{
}

void OptionWindow::initControl()
{

}

void OptionWindow::initAccount()
{
	QWidget* accountOptionWindow = new QWidget(this);
	QLabel* userName = new QLabel(QString::fromLocal8Bit("êÇ³Æ:"));
	QLabel* account = new QLabel(QString::fromLocal8Bit("ÕËºÅ:"));
	QLabel* tel = new QLabel(QString::fromLocal8Bit("µç»°:"));
	QLabel* mail = new QLabel(QString::fromLocal8Bit("ÓÊÏä:"));
	QPushButton* changePwd = new QPushButton(QString::fromLocal8Bit("ÐÞ¸ÄÃÜÂë"));
	QPushButton* changeName = new QPushButton(QString::fromLocal8Bit("ÐÞ¸Ä"));
	QPushButton* changeTel = new QPushButton(QString::fromLocal8Bit("ÐÞ¸Ä"));
	QPushButton* changeMail = new QPushButton(QString::fromLocal8Bit("ÐÞ¸Ä"));

	changePwd->setObjectName("ChangePwdBtn");
	changeName->setObjectName("ChangeNameBtn");
	changeTel->setObjectName("ChangeTelBtn");
	changeMail->setObjectName("ChangeMailBtn");

	connect(changePwd, &QPushButton::clicked, this, &OptionWindow::onAccountChangeBtnClicked);
	connect(changeName, &QPushButton::clicked, this, &OptionWindow::onAccountChangeBtnClicked);
	connect(changeTel, &QPushButton::clicked, this, &OptionWindow::onAccountChangeBtnClicked);
	connect(changeMail, &QPushButton::clicked, this, &OptionWindow::onAccountChangeBtnClicked);

	QLabel* accountLabel = new QLabel(gAccount);
	QLineEdit* nameLineEdit = new QLineEdit(this);
	QLineEdit* telLineEdit = new QLineEdit(this);
	QLineEdit* mailLineEdit = new QLineEdit(this);

	QHBoxLayout* userNameLayout = new QHBoxLayout(accountOptionWindow);
	userNameLayout->addWidget(userName);
	userNameLayout->addWidget(nameLineEdit);
	userNameLayout->addWidget(changeName);

	QHBoxLayout* accountLayout = new QHBoxLayout(accountOptionWindow);
	accountLayout->addWidget(account);
	accountLayout->addWidget(accountLabel);
	accountLayout->addStretch();

	QHBoxLayout* telLayout = new QHBoxLayout(accountOptionWindow);
	telLayout->addWidget(userName);
	telLayout->addWidget(telLineEdit);
	telLayout->addWidget(changeTel);

	QHBoxLayout* mailLayout = new QHBoxLayout(accountOptionWindow);
	mailLayout->addWidget(mail);
	mailLayout->addWidget(mailLineEdit);
	mailLayout->addWidget(changeMail);

	QVBoxLayout* mainLayout = new QVBoxLayout(accountOptionWindow);
	mainLayout->addLayout(accountLayout);
	mainLayout->addLayout(userNameLayout);
	mainLayout->addLayout(telLayout);
	mainLayout->addLayout(mailLayout);
	mainLayout->addWidget(changePwd);
	mainLayout->addStretch();
	accountOptionWindow->setLayout(mainLayout);
}

void OptionWindow::onAccountChangeBtnClicked()
{
	QWidget* item = qobject_cast<QWidget*>(sender());
	if (item->objectName() == "ChangePwdBtn")
	{

	}
	else if (item->objectName() == "ChangeNameBtn")
	{

	}
	else if (item->objectName() == "ChangeTelBtn")
	{

	}
	else if (item->objectName() == "ChangeMailBtn")
	{

	}
}