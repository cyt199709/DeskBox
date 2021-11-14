#pragma once

#include <QLabel>

class ClickLabel : public QLabel
{
	Q_OBJECT

public:
	ClickLabel(QWidget *parent);
	~ClickLabel();

protected:
	void mousePressEvent(QMouseEvent* event) override;

signals:
	void clicked();
};
