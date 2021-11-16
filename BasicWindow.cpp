#include "BasicWindow.h"
#include "NotifyManager.h"
#include "CommonUtils.h"
#include <QStyleOption>
#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>
#include <QMouseEvent>

QColor gBackColor;

BasicWindow::BasicWindow(QWidget *parent)
	: QDialog(parent)
{
	m_colorBackGround = CommonUtils::getDefaultSkinColor();
	gBackColor = m_colorBackGround;
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground, true);
	connect(NotifyManager::getInstance(), SIGNAL(signalSkinChanged(const QColor&)), this, SLOT(onSignalSkinChanged(const QColor&)));
}

BasicWindow::~BasicWindow()
{
}

void BasicWindow::loadStyleSheet(const QString& sheetName)
{
	m_styleName = sheetName;
	QFile file(":/Resources/QSS/" + sheetName + ".css");
	file.open(QIODevice::ReadOnly);
	if (file.isOpen())
	{
		setStyleSheet("");
		QString qssStyleSheet = QLatin1String(file.readAll());

		QString r = QString::number(m_colorBackGround.red());
		QString g = QString::number(m_colorBackGround.green());
		QString b = QString::number(m_colorBackGround.blue());

		QString r1 = QString::number(m_colorBackGround.red() + 10);
		QString g1 = QString::number(m_colorBackGround.green() + 10);
		QString b1 = QString::number(m_colorBackGround.blue() + 10);
		r1 = QString::number((r1.toInt() > 255) ? 255 : r1.toInt());
		g1 = QString::number((g1.toInt() > 255) ? 255 : g1.toInt());
		b1 = QString::number((b1.toInt() > 255) ? 255 : b1.toInt());

		qssStyleSheet += QString("QWidget[titleSkin=true]\
								{background-color:rgb(%1,%2,%3);\
								border-top-left-radius:4px;}\
								QWidget[bottomSkin=true]\
								{border-top:1px solid rgba(%1,%2,%3,100);\
								background-color:rgba(%1,%2,%3,50);\
								border-bottom-left-radius:4px;\
								border-bottom-right-radius:4px;}\
								QWidget[rightSkin=true]\
								{border-top:1px solid rgba(%4,%5,%6,100);\
								background-color:rgb(%4,%5,%6);\
								border-bottom-left-radius:4px;\
								border-bottom-right-radius:4px;}")
								.arg(r).arg(g).arg(b).arg(r1).arg(g1).arg(b1);
		setStyleSheet(qssStyleSheet);
	}

	file.close();
}

void BasicWindow::initBackGroundColor()
{
	QStyleOption opt;
	opt.init(this);

	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void BasicWindow::paintEvent(QPaintEvent* event)
{
	initBackGroundColor();
	QDialog::paintEvent(event);
}

void BasicWindow::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_mousePressed = true;
		m_mousePoint = event->globalPos() - pos();
		event->accept();
	}
}

void BasicWindow::mouseMoveEvent(QMouseEvent* event)
{
	if (m_mousePressed && (event->buttons() && Qt::LeftButton))
	{
		move(event->globalPos() - m_mousePoint);
		event->accept();
	}
}

void BasicWindow::mouseReleaseEvent(QMouseEvent* event)
{
	m_mousePressed = false;
	event->accept();
}

void BasicWindow::initTitleBar(ButtonType buttonType)
{
	m_titleBar = new TitleBar(this);
	m_titleBar->setButton(buttonType);
	m_titleBar->move(0, 0);


	connect(m_titleBar, SIGNAL(signalButtonMinClicked()), this, SLOT(onButtonMinClicked()));
	connect(m_titleBar, SIGNAL(signalButtonRestoreClicked()), this, SLOT(onButtonRestoreClicked()));
	connect(m_titleBar, SIGNAL(signalButtonMaxClicked()), this, SLOT(onButtonMaxClicked()));
	m_dis = connect(m_titleBar, SIGNAL(signalButtonCloseClicked()), this, SLOT(onButtonCloseClicked()));
}

void BasicWindow::setTitleBarTitle(const QString& title, const QString& icon)
{
	m_titleBar->setTitleIcon(icon);
	m_titleBar->setTitleContent(title);
}

void BasicWindow::onShowClose(bool)
{
	close();
}

void BasicWindow::onShowMin(bool)
{
	showMinimized();
}

void BasicWindow::onShowHide(bool)
{
	if (Qt::Tool == (windowFlags() & Qt::Tool))
	{
		hide();
	}
	else
	{
		showMinimized();
	}
}

void BasicWindow::onShowNormal(bool)
{
	showNormal();
	activateWindow();
}

void BasicWindow::onShowQuit(bool)
{
	QApplication::quit();
}

void BasicWindow::onSignalSkinChanged(const QColor& color)
{
	m_colorBackGround = color;
	loadStyleSheet(m_styleName);
}

void BasicWindow::onButtonMinClicked()
{
	if (Qt::Tool == (windowFlags() & Qt::Tool))
	{
		hide();
	}
	else
	{
		showMinimized();
	}
}

void BasicWindow::onButtonMaxClicked()
{
	m_titleBar->saveRestoreInfo(pos(), QSize(width(), height()));
	QRect desktopRect = QApplication::desktop()->availableGeometry();
	QRect factRect = QRect(desktopRect.x() - 3, desktopRect.y() - 3, desktopRect.x() + 6, desktopRect.y() + 6);
	setGeometry(factRect);
}

void BasicWindow::onButtonRestoreClicked()
{
	QPoint windowPos;
	QSize windowSize;
	m_titleBar->getRestoreInfo(windowPos, windowSize);
	setGeometry(QRect(windowPos, windowSize));
}

void BasicWindow::onButtonCloseClicked()
{
	close();
}
