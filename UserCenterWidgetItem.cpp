#include "UserCenterWidgetItem.h"

UserCenterWidgetItem::UserCenterWidgetItem(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

UserCenterWidgetItem::~UserCenterWidgetItem()
{
}

void UserCenterWidgetItem::setContext(const QString& context)
{
	ui.label->setText(context);
}

void UserCenterWidgetItem::getCOntext() const
{
	return ui.label->text();
}

void UserCenterWidgetItem::mousePressEvent(QMouseEvent* event)
{
	emit signalWidgetClicked(this);
}
