#include "OptionWindowItem.h"
#include <QPainter>
#include <QSettings>

OptionWindowItem::OptionWindowItem(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

OptionWindowItem::~OptionWindowItem()
{
}

void OptionWindowItem::initControl()
{
	QPainter painter(ui.colorLabel);
	QSettings settings(QApplication::applicationDirPath() + "/tradeprintinfo.ini", QSettings::IniFormat);
	QColor color(settings.value("Default/red").toInt(), settings.value("Default/green").toInt(), settings.value("Default/blue").toInt());
	painter.fillRect(ui.colorLabel->rect(), color);
	ui.colorLabel->setVisible(false);
}

void OptionWindowItem::setContext(const QString& text)
{
	ui.context->setText(text);
}

QString OptionWindowItem::getContext() const
{
	return ui.context->text();
}

void OptionWindowItem::enterEvent(QEvent* event)
{
	ui.colorLabel->setVisible(true);
	__super::enterEvent(event);
}

void OptionWindowItem::leaveEvent(QEvent* event)
{
	ui.colorLabel->setVisible(false);
	__super::leaveEvent(event);
}

void OptionWindowItem::resizeEvent(QResizeEvent* event)
{
	__super::resizeEvent(event);
}
