#include "UserLogin.h"
#include "MainWindow.h"

UserLogin::UserLogin(QWidget*parent)
	: BasicWindow(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
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
	close();
	MainWindow* mainWindow = new MainWindow;
	mainWindow->show();
}

void UserLogin::initControl()
{
	connect(ui.LoginBtn, &QPushButton::clicked, this, &UserLogin::onLoginBtnClicked);
}