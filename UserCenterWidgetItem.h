#pragma once

#include <QWidget>
#include "ui_UserCenterWidgetItem.h"

class UserCenterWidgetItem : public QWidget
{
	Q_OBJECT

public:
	UserCenterWidgetItem(QWidget *parent = Q_NULLPTR);
	~UserCenterWidgetItem();

	void setContext(const QString& context);
	void getCOntext() const;

protected:
	void mousePressEvent(QMouseEvent* event) override;

signals:
	void signalWidgetClicked(QWidget*);

private:
	Ui::UserCenterWidgetItem ui;
};
