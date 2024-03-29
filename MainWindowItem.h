#pragma once

#include <QWidget>
#include <QIcon>
#include <QLabel> 
#include <QBoxLayout> 

enum TYPE {
	TOOL,
	REG_FILE,
	FOLDER,
	ADD_TOOL,
	ADD_FILE
};

class MainWindowItem : public QWidget
{
	Q_OBJECT

public:
	MainWindowItem(QWidget *parent = Q_NULLPTR, TYPE type = TOOL, const QString& filePath = "");
	~MainWindowItem();

	bool createSuccess();
	QString getFileName();
	QString getFilePath();
	TYPE getType();

private:
	void initControl();
	void getFileInfo();
	virtual void mouseDoubleClickEvent(QMouseEvent* event);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);

	virtual void paintEvent(QPaintEvent* event);

signals:
	void signalAddClicked(TYPE, QString);
	void signalItemDelete(TYPE, QString);
	void signalItemPress(MainWindowItem*);

private slots:
	void onActionClicked();

private:
	TYPE m_type;
	QString m_filePath;
	QIcon m_fileIcon;
	QString m_fileName;

	QLabel* m_icon;
	QLabel* m_name;
	QVBoxLayout* m_layout;
	QPixmap* m_backPix;

	bool m_isPressed;
	bool m_isSuccess;
};
