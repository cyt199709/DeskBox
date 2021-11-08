#pragma once

#include <QDialog>
#include "TitleBar.h"

class BasicWindow : public QDialog
{
	Q_OBJECT

public:
	BasicWindow(QWidget *parent = nullptr);
	virtual ~BasicWindow();

public:
	void loadStyleSheet(const QString& sheetName);

private:
	void initBackGroundColor();

protected:
	void paintEvent(QPaintEvent*);
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);

protected:
	void initTitleBar(ButtonType buttonType = MIN_BUTTON);
	void setTitleBarTitle(const QString& title, const QString& icon = "");

public slots:
	void onShowClose(bool);
	void onShowMin(bool);
	void onShowHide(bool);
	void onShowNormal(bool);
	void onShowQuit(bool);
	void onSignalSkinChanged(const QColor& color);

	void onButtonMinClicked();
	void onButtonMaxClicked();
	void onButtonRestoreClicked();
	void onButtonCloseClicked();

protected:
	QPoint m_mousePoint;
	bool m_mousePressed;
	QColor m_colorBackGround;
	QString m_styleName;
	TitleBar* m_titleBar;
};
