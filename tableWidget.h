#pragma once

#include <QTableWidget>

class tableWidget : public QTableWidget
{
	Q_OBJECT

public:
	tableWidget(QWidget *parent);
	~tableWidget();

protected:
	/*virtual void dragEnterEvent(QDragEnterEvent* event);
	virtual void dragMoveEvent(QDragEnterEvent* event);
	virtual void dragLeaveEvent(QDragEnterEvent* event);
	virtual void dropEvent(QDropEvent* event) override;*/
};
