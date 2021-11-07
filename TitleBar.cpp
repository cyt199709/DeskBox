#include <QBoxLayout>
#include <QPainter>

#include "TitleBar.h"

#define BUTTON_HEIGHT 27
#define BUTTON_WIDTH  27
#define TITLE_HEIGHT  27

TitleBar::TitleBar(QWidget* parent)
	: QWidget(parent)
	, m_isPressed(false)
	, m_buttonType(MIN_MAX_BUTTON)
{
	initControl();
	initConnections();
	loadStyleSheet("Title");
}

TitleBar::~TitleBar()
{
}

void TitleBar::setTitleIcon(const QString& filepath)
{
	QPixmap titleIcon(filepath);
	m_pIcon->setFixedSize(titleIcon.size());
	m_pIcon->setPixmap(titleIcon);
}

void TitleBar::setTitleContent(const QString& titleContent)
{
	m_pTitleContent->setText(titleContent);
	m_titleContent = titleContent;
}

void TitleBar::setTitleWidth(int width)
{
	setFixedWidth(width);
}

void TitleBar::setButton(ButtonType buttonType)
{
	m_buttonType = buttonType;

	switch (buttonType)
	{
	case MIN_BUTTON:
		m_pMaxBtn->setVisible(false);
		m_pRestoreBtn->setVisible(false);
		break;
	case MIN_MAX_BUTTON:
		m_pRestoreBtn->setVisible(false);
		break;
	case ONLY_CLOSE_BUTTON:
		m_pMinBtn->setVisible(false);
		m_pMaxBtn->setVisible(false);
		m_pRestoreBtn->setVisible(false);
		break;
	default:
		break;
	}
}

void TitleBar::saveRestoreInfo(const QPoint& point, const QSize& size)
{
	m_restorePos = point;
	m_restoreSize = size;
}

void TitleBar::getRestoreInfo(QPoint& point, QSize& size)
{
	point = m_restorePos;
	size = m_restoreSize;
}

void TitleBar::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	QPainterPath pathBack;
	pathBack.setFillRule(Qt::WindingFill);
	pathBack.addRoundedRect(QRect(0, 0, width(), height()), 3, 3);
	painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

	if (width() != parentWidget()->width())
	{
		setFixedWidth(parentWidget()->width());
	}
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent* event)
{
	if (m_buttonType == MIN_MAX_BUTTON)
	{
		if (m_pMaxBtn->isVisible())
			onButtonMaxClicked();
		else
			onButtonRestoreClicked();
	}

	return QWidget::mouseDoubleClickEvent(event);
}

void TitleBar::mousePressEvent(QMouseEvent* event)
{
	if (m_buttonType == MIN_MAX_BUTTON)
	{
		if (m_pMaxBtn->isVisible())
		{
			m_isPressed = true;
			m_startMovePos = event->globalPos();
		}
	}
	else
	{
		m_isPressed = true;
		m_startMovePos = event->globalPos();
	}
}

void TitleBar::mouseMoveEvent(QMouseEvent* event)
{
	if (m_isPressed)
	{
		QPoint movePoint = event->globalPos() - m_startMovePos;
		QPoint widgetPos = parentWidget()->pos();
		m_startMovePos = event->globalPos();
		parentWidget()->move(movePoint + widgetPos);
	}

	return QWidget::mouseMoveEvent(event);
}

void TitleBar::mouseReleaseEvent(QMouseEvent* event)
{
	m_isPressed = false;
	return QWidget::mouseReleaseEvent(event);
}

void TitleBar::initControl()
{
	m_pIcon = new QLabel(this);
	m_pTitleContent = new QLabel(this);

	m_pMinBtn = new QPushButton(this);
	m_pMaxBtn = new QPushButton(this);
	m_pRestoreBtn = new QPushButton(this);
	m_pCloseBtn = new QPushButton(this);

	m_pMinBtn->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
	m_pMaxBtn->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
	m_pRestoreBtn->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
	m_pCloseBtn->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));

	m_pIcon->setObjectName("TitleIcon");
	m_pTitleContent->setObjectName("TitleContent");
	m_pMinBtn->setObjectName("MinBtn");
	m_pMaxBtn->setObjectName("MaxBtn");
	m_pRestoreBtn->setObjectName("RestoreBtn");
	m_pCloseBtn->setObjectName("CloseBtn");

	QHBoxLayout* titleLayout = new QHBoxLayout;
	titleLayout->addWidget(m_pIcon);
	titleLayout->addWidget(m_pTitleContent);
	titleLayout->addWidget(m_pMinBtn);
	titleLayout->addWidget(m_pMaxBtn);
	titleLayout->addWidget(m_pRestoreBtn);
	titleLayout->addWidget(m_pCloseBtn);

	titleLayout->setContentsMargins(5, 0, 0, 0);

	m_pTitleContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	setFixedHeight(TITLE_HEIGHT);
	setWindowFlags(Qt::FramelessWindowHint);
}

void TitleBar::initConnections()
{
	connect(m_pMinBtn, &QPushButton::clicked, this, &TitleBar::onButtonMinClicked);
	connect(m_pMaxBtn, &QPushButton::clicked, this, &TitleBar::onButtonMaxClicked);
	connect(m_pRestoreBtn, &QPushButton::clicked, this, &TitleBar::onButtonRestoreClicked);
	connect(m_pCloseBtn, &QPushButton::clicked, this, &TitleBar::onButtonCloseClicked);
}

void TitleBar::loadStyleSheet(const QString& sheetName)
{
	QFile file(":/Resources/QSS" + sheetName + ".css");
	file.open(QFile::ReadOnly);
	if (file.isOpen())
	{
		QString styleSheet = this->styleSheet();
		styleSheet += QLatin1String(file.readAll());
		setStyleSheet(styleSheet);
	}
	file.close();
}

void TitleBar::onButtonMinClicked()
{
	emit signalButtonMinClicked();
}

void TitleBar::onButtonMaxClicked()
{
	m_pRestoreBtn->setVisible(true);
	m_pMaxBtn->setVisible(false);
	emit signalButtonMaxClicked();
}

void TitleBar::onButtonRestoreClicked()
{
	m_pRestoreBtn->setVisible(false);
	m_pMaxBtn->setVisible(true);
	emit signalButtonRestoreClicked();
}

void TitleBar::onButtonCloseClicked()
{
	emit signalButtonCloseClicked();
}