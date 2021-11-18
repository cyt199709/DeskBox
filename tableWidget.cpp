#include "tableWidget.h"
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>

tableWidget::tableWidget(QWidget *parent)
	: QTableWidget(parent)
{
	setAcceptDrops(true);
	setDragEnabled(true);
	setDragDropMode(QAbstractItemView::DragDrop);
}

tableWidget::~tableWidget()
{
}

//void tableWidget::dragEnterEvent(QDragEnterEvent* event)
//{
//	if(event->mimeData()->hasUrls())
//		event->accept();
//}
//
//void tableWidget::dragMoveEvent(QDragEnterEvent* event)
//{
//}
//
//void tableWidget::dragLeaveEvent(QDragEnterEvent* event)
//{
//}
//
//void tableWidget::dropEvent(QDropEvent* event)
//{
//	QList<QUrl> urls = event->mimeData()->urls();
//	if (urls.isEmpty())
//		return;
//	//qDebug() << urls.size();
//	foreach(QUrl u, urls)
//	{
//		QString filepath = u.toLocalFile();
//	}
//}
