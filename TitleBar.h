#pragma once

#include <QObject>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QLabel>
#include <QPushButton>

// 标题栏按钮类型
enum ButtonType
{
	MIN_BUTTON = 0,
	MIN_MAX_BUTTON,
	ONLY_CLOSE_BUTTON
};

class TitleBar : public QObject
{
	Q_OBJECT

public:
	TitleBar(QWidget *parent);
	~TitleBar();

public:
	void setTitleIcon(QString& filepath);
	void setTitleContent(QString& titleContent);
	void setTitleWidth(int width);
	void setButton(ButtonType buttonType);

	void saveRestoreInfo(const QPoint& point, const QSize& size);
	void getRestoreInfo(const QPoint& point, const QSize& size);
	
private:
	void paintEvent(QPaintEvent* event);
	void mouseDoubleClickEvent(QMouseEvent* event);
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);

	void initControl();
	void initConnections();
	void loadStyleSheet(const QString& sheetName); 

signals:
	void signalButtonMinClicked();
	void signalButtonMaxClicked();
	void signalButtonRestoreClicked();
	void signalButtonCloseClicked();

private slots:
	void onButtonMinClicked();
	void onButtonMaxClicked();
	void onButtonRestoreClicked();
	void onButtonCloseClicked();


private:
	QLabel* m_pIcon;
	QLabel* m_pTitleContent;

	QPushButton* m_pMinBtn;
	QPushButton* m_pMaxBtn;
	QPushButton* m_pRestoreBtn;
	QPushButton* m_pCloseBtn;

	QPoint m_restorePos;
	QSize m_restoreSize;

	bool m_isPressed;
	QPoint m_startMovePos;

	QString m_titleContent;
	ButtonType m_buttonType;
};
