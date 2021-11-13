#include "SysTray.h"
#include <QIcon>
#include <QMenu>

SysTray::SysTray(QWidget* parent)
	: QSystemTrayIcon(parent)
	, m_parent(parent)
{
	initSysTray();
	show();
}

SysTray::~SysTray()
{
}

void SysTray::onIconActivated(QSystemTrayIcon::ActivationReason reason)
{
	if (reason == QSystemTrayIcon::Trigger)
	{
		m_parent->show();
		m_parent->activateWindow();
	}
	else if(reason == QSystemTrayIcon::Context)
	{
		addSysTrayMenu();
	}
}

void SysTray::initSysTray()
{
	setToolTip(QStringLiteral("DeskBox"));
	QPixmap pix(":/Resources/Icon/trLogo.png");
	pix.scaled(32, 32);
	setIcon(QIcon(pix));

	connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(onIconActivated(QSystemTrayIcon::ActivationReason)));
}

void SysTray::addSysTrayMenu() 
{
	QMenu* pMenu = new QMenu(m_parent);
	QAction* pOpen = new QAction(QString::fromLocal8Bit("ÏÔÊ¾"));
	QAction* pExit = new QAction(QString::fromLocal8Bit("ÍË³ö"));

	pMenu->addAction(pOpen);
	pMenu->addAction(pExit);

	connect(pOpen, SIGNAL(triggered(bool)), m_parent, SLOT(onShowNormal(bool)));
	connect(pExit, SIGNAL(triggered(bool)), m_parent, SLOT(onShowQuit(bool)));

	pMenu->exec(QCursor::pos());
	foreach(QAction * pAction, pMenu->actions()) 
		delete pAction;
	delete pMenu;
}