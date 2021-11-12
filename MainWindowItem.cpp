#include "MainWindowItem.h"
#include <QMouseEvent>
#include <QFileIconProvider>
#include <QPainter>
#include <QDesktopServices>
#include <QFileDialog>
#include <QMouseEvent>
#include <QMenu>

MainWindowItem::MainWindowItem(QWidget *parent, TYPE type, const QString& filePath)
	: QWidget(parent)
	, m_type(type)
	, m_filePath(filePath)
	, m_isPressed(false)
{
	setAttribute(Qt::WA_DeleteOnClose);
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
	setFixedSize(80, 80);
	initControl();
}

MainWindowItem::~MainWindowItem()
{
}

void MainWindowItem::initControl()
{
	m_icon = new QLabel(this);
	m_name = new QLabel(this);
	getFileInfo();
	m_icon->setAlignment(Qt::AlignCenter);
	m_name->setAlignment(Qt::AlignCenter);

	m_layout = new QVBoxLayout(this);
	m_layout->addWidget(m_icon);
	m_layout->addWidget(m_name);
	m_layout->setContentsMargins(5, 5, 5, 5);
	m_layout->setSpacing(0);
	setLayout(m_layout);
}

void MainWindowItem::getFileInfo()
{
	if (m_filePath.isEmpty() && m_type != ADD_TOOL && m_type != ADD_FILE)
		return;

	QPixmap pixmap(70, 50);
	pixmap.fill(QColor(0, 0, 0, 1));
	QPainter painter(&pixmap);
	if (m_type == TOOL || m_type == REG_FILE)
	{
		QFileInfo fileInfo(m_filePath);
		QFileIconProvider iconProvider;
		m_fileIcon = iconProvider.icon(fileInfo);
		m_fileName = fileInfo.fileName();
		if (!m_fileName.contains(".exe") && m_type == TOOL)
			close();
	}
	else if (m_type == FOLDER)
	{
		QFileInfo fileInfo(m_filePath);
		QFileIconProvider iconProvider;
		m_fileIcon = iconProvider.icon(fileInfo);
		m_fileName = fileInfo.fileName();
		painter.drawPixmap(10, 0, 50, 50, m_fileIcon.pixmap(50, 50));
	}
	else
	{
		QPen pen;
		pen.setStyle(Qt::DashLine);
		pen.setWidth(1);
		pen.setColor(Qt::black);
		painter.setPen(pen);
		painter.drawRect(10, 0, 49, 49);
		painter.drawLine(15, 25, 55, 25);
		painter.drawLine(35, 5, 35, 45);
		m_fileName = QString::fromLocal8Bit("添加");
	}
	m_icon->setPixmap(pixmap);
	update();
}

void MainWindowItem::mouseDoubleClickEvent(QMouseEvent* event)
{
	if (m_type != ADD_TOOL && m_type != ADD_FILE)
		QDesktopServices::openUrl(QUrl::fromLocalFile(m_filePath));
	else if(m_type == ADD_TOOL)
	{
		QString path = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("选择文件"), ".", QString::fromLocal8Bit("可执行文件 (*.exe)"));
		emit signalItemClicked(ADD_TOOL, path);
	}
	else if (m_type == ADD_FILE)
	{
		QString path = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("选择文件"), ".", QString::fromLocal8Bit("所有文件 (*.*)"));
		emit signalItemClicked(ADD_FILE, path);
	}

	return QWidget::mouseDoubleClickEvent(event);
}

void MainWindowItem::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		if (m_type != ADD_TOOL && m_type != ADD_FILE)
		{
			return QWidget::mouseDoubleClickEvent(event);
		}
		m_isPressed = true;
	}
	if (event->button() == Qt::RightButton)
	{
		if(m_type != ADD_TOOL && m_type != ADD_FILE)
		{
			QMenu* pMenu = new QMenu(this);
			QAction* pOpen = new QAction(QString::fromLocal8Bit("打开"), this);
			QAction* pDel = new QAction(QString::fromLocal8Bit("删除"), this);

			pOpen->setData(1);
			pDel->setData(2);

			pMenu->addAction(pOpen);
			pMenu->addAction(pDel);

			connect(pOpen, &QAction::triggered, this, &MainWindowItem::onActionClicked);
			connect(pDel, &QAction::triggered, this, &MainWindowItem::onActionClicked);

			pMenu->exec(event->pos());

			QList<QAction*> list = pMenu->actions();
			foreach(QAction* pAction, list) delete pAction;
			delete pMenu;
		}
	}
}

void MainWindowItem::mouseReleaseEvent(QMouseEvent* event)
{
	if (m_isPressed)
	{
		if (m_type == ADD_TOOL) 
		{
			QString path = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("选择文件"), ".", QString::fromLocal8Bit("可执行文件 (*.exe)"));
			emit signalItemClicked(ADD_TOOL, path);
		}
		if (m_type == ADD_FILE)
		{
			QString path = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("选择文件"), ".", QString::fromLocal8Bit("所有文件 (*.*)"));
			emit signalItemClicked(ADD_FILE, path);
		}
	}
	m_isPressed = false;
}

void MainWindowItem::paintEvent(QPaintEvent* event)
{
	QPixmap pixmap(70, 50);
	pixmap.fill(QColor(0, 0, 0, 1));
	QPainter painter(&pixmap);
	if (m_type == TOOL || m_type == REG_FILE)
	{
		if (!m_fileName.contains(".exe") && m_type == TOOL)
			close();
	}
	else if (m_type == FOLDER)
	{
		painter.drawPixmap(10, 0, 50, 50, m_fileIcon.pixmap(50, 50));
	}
	else
	{
		QPen pen;
		pen.setStyle(Qt::DashLine);
		pen.setWidth(1);
		pen.setColor(Qt::black);
		painter.setPen(pen);
		painter.drawRect(10, 0, 49, 49);
		painter.drawLine(15, 25, 55, 25);
		painter.drawLine(35, 5, 35, 45);
	}
	QFontMetrics fontWidth(m_name->font());
	QString name = fontWidth.elidedText(m_fileName, Qt::ElideRight, 70);
	m_name->setText(name);
	m_name->setToolTip(m_fileName);
	m_icon->setPixmap(pixmap);
}

void MainWindowItem::onActionClicked()
{
	QAction* pAction = qobject_cast<QAction*>(sender());
	int data = pAction->data().toInt();

	switch (data)
	{
	case 1:
		break;
		QDesktopServices::openUrl(QUrl::fromLocalFile(m_filePath));
	case 2:
		emit signalItemDelete(m_type, m_filePath);
		break;
	default:
		break;
	}
}