#pragma once

#include <QWidget>
#include "ui_OptionWindowItem.h"

class OptionWindowItem : public QWidget
{
	Q_OBJECT

public:
	OptionWindowItem(QWidget *parent = Q_NULLPTR);
	~OptionWindowItem();

private:
	void initControl();

public:
	void setContext(const QString& text);
	QString getContext() const;

private:
	void enterEvent(QEvent* event);
	void leaveEvent(QEvent* event);
	void resizeEvent(QResizeEvent* event);

private:
	Ui::OptionWindowItem ui;
};
