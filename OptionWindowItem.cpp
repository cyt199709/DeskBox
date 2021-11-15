#include "OptionWindowItem.h"

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
	ui.colorLabel->setVisible(false);
}
