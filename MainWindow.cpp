#include "MainWindow.h"
#include "MainWindowItem.h"
#include "CommonUtils.h"
#include "NotifyManager.h"
#include "SysTray.h"
#include "SkinWindow.h"
#include "OptionWindow.h"
#include "UserCenter.h"
#include <QMenu>
#include <QSettings>
#include <QTableWidgetItem>
#include <QTableWidget>
#include <QMessageBox>
#include <QFileInfo>
#include <QSystemTrayIcon>
#include <QMimeData>

QList<QString> gFileList;

MainWindow::MainWindow(QWidget *parent)
	: BasicWindow(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	setAttribute(Qt::WA_QuitOnClose, true);
	initTitleBar();
	setTitleBarTitle("", ":/Resources/Icon/big_logo.png");
	loadStyleSheet("MainWindow");
	initControl();
	setAcceptDrops(true);
}

MainWindow::~MainWindow()
{

}

void MainWindow::initControl()
{
	connect(ui.MenuBtn, &QPushButton::clicked, this, &MainWindow::onMenuBtnClicked);
	ui.ToolTableWidget->setColumnCount(5);
	ui.ToolTableWidget->setRowCount(16);
	ui.ToolTableWidget->setAcceptDrops(true);
	ui.ToolTableWidget->setDragEnabled(true);
	ui.ToolTableWidget->setDragDropMode(QAbstractItemView::DragDrop);
	ui.ToolTableWidget->setSelectionMode(QAbstractItemView::NoSelection);
	ui.FileTableWidget->setColumnCount(5);
	ui.FileTableWidget->setRowCount(16);
	ui.FileTableWidget->setAcceptDrops(true);
	ui.FileTableWidget->setDragEnabled(true);
	ui.FileTableWidget->setDragDropMode(QAbstractItemView::DragDrop);
	ui.FileTableWidget->setSelectionMode(QAbstractItemView::NoSelection);
	getIniInfo();

	connect(ui.SearchLineEdit, &QLineEdit::textChanged, this, &MainWindow::onSearchLineEditChanged);

	SysTray* systray = new SysTray(this);
	setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);
	disconnect(m_dis);
	connect(m_titleBar, &TitleBar::signalButtonCloseClicked, [this]() {	QApplication::quit(); });

	connect(NotifyManager::getInstance(), &NotifyManager::signalSkinChanged, [this]() {
		updateSearchStyle();
		});

	qApp->installEventFilter(this);
}

void MainWindow::getIniInfo()
{
	MainWindowItem* addToolItem = new MainWindowItem(ui.ToolTableWidget, ADD_TOOL);
	connect(addToolItem, &MainWindowItem::signalAddClicked, this, &MainWindow::onAddClicked);
	m_toolList.push_back(addToolItem);
	MainWindowItem* addFileItem = new MainWindowItem(ui.FileTableWidget, ADD_FILE);
	connect(addFileItem, &MainWindowItem::signalAddClicked, this, &MainWindow::onAddClicked);
	m_fileList.push_back(addFileItem);

	QSettings fileSettings(QApplication::applicationDirPath() + "/" + QString("fileInfo.ini"), QSettings::IniFormat);
	QSettings ToolSettings(QApplication::applicationDirPath() + "/" + QString("ToolInfo.ini"), QSettings::IniFormat);

	QStringList fileList = fileSettings.childGroups();
	foreach(QString file, fileList)
	{
		fileSettings.beginGroup(file);
		QString filePath = fileSettings.value("filePath").toString();
		TYPE type = (TYPE)fileSettings.value("type").toInt();
		fileSettings.endGroup();
		QFileInfo fileInfo(filePath);
		if(fileInfo.isSymLink())
			filePath = fileInfo.symLinkTarget();
		MainWindowItem* item = new MainWindowItem(ui.FileTableWidget, type, filePath);
		if (item->createSuccess())
		{
			m_fileList.push_back(item);
			gFileList.push_back(item->getFilePath());
			connect(item, &MainWindowItem::signalItemPress, this, &MainWindow::onItemClicked);
		}
		else
			delete item;
	}

	QStringList toolList = ToolSettings.childGroups();
	foreach(QString file, toolList)
	{
		QString filePath = ToolSettings.value(file + "/filePath").toString();
		TYPE type = (TYPE)ToolSettings.value("type").toInt();
		QFileInfo fileInfo(filePath);
		if (fileInfo.isSymLink())
			filePath = fileInfo.symLinkTarget();
		MainWindowItem* item = new MainWindowItem(ui.FileTableWidget, type, filePath);
		if (item->createSuccess())
		{
			m_toolList.push_back(item);
			gFileList.push_back(item->getFilePath());
			connect(item, &MainWindowItem::signalItemPress, this, &MainWindow::onItemClicked);
		}
		else
			delete item;
	}
	updateTable();
}

void MainWindow::updateSearchStyle()
{
	ui.searchWidget->setStyleSheet(QString("QWidget#searchWidget{background-color:rgba(%1,%2,%3,50);border-bottom:1px solid rgba(%1,%2,%3,30)}")
		.arg(m_colorBackGround.red())
		.arg(m_colorBackGround.green())
		.arg(m_colorBackGround.blue()));
}

bool MainWindow::eventFilter(QObject* obj, QEvent* event) {
	if (event->type() == QEvent::MouseButtonPress && obj != ui.SearchLineEdit)
	{
		ui.SearchLineEdit->clearFocus();
		this->setFocus();
	}
	return QWidget::eventFilter(obj, event);
}

void MainWindow::updateTable()
{

	for (int i = 0; i < m_fileList.size(); i++)
	{
		ui.FileTableWidget->setCellWidget(i / 5, i % 5, m_fileList[i]);
	}
	for (int i = 0; i < m_toolList.size(); i++)
	{
		ui.ToolTableWidget->setCellWidget(i / 5, i % 5, m_toolList[i]);
	}
}

void MainWindow::onAddClicked(TYPE type, QString filePath)
{
	QSettings fileSettings(QApplication::applicationDirPath() + "/" + QString("fileInfo.ini"), QSettings::IniFormat);
	QSettings toolSettings(QApplication::applicationDirPath() + "/" + QString("ToolInfo.ini"), QSettings::IniFormat);
	if (filePath.isEmpty())
		return;
	QFileInfo fileinfo(filePath);
	
	if (type == TOOL)
	{
		QStringList file = toolSettings.childGroups();
		if (file.contains(fileinfo.fileName()) || filePath == fileSettings.value(fileinfo.fileName() + "/filePath").toString()) {
			QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("文件已存在"));
			return;
		}
		MainWindowItem* item = new MainWindowItem(ui.ToolTableWidget, TOOL, filePath);
		if (item->createSuccess())
		{
			int pos = m_toolList.size();
			m_toolList.push_back(item);
			gFileList.push_back(item->getFilePath());
			toolSettings.setValue(fileinfo.fileName() + "/type", type);
			toolSettings.setValue(fileinfo.fileName() + "/filePath", filePath);
			ui.ToolTableWidget->setCellWidget(pos / 5, pos % 5, m_toolList[pos]);
			connect(item, &MainWindowItem::signalItemPress, this, &MainWindow::onItemClicked);
		}
		else
			delete item;
	}
	else if(type == REG_FILE)
	{
		QStringList file = fileSettings.childGroups();
		if (file.contains(fileinfo.fileName()) || filePath == fileSettings.value(fileinfo.fileName() + "/filePath").toString()) {
			QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("文件已存在"));
			return;
		}
		MainWindowItem* item = new MainWindowItem(ui.FileTableWidget, REG_FILE, filePath);
		if (item->createSuccess())
		{
			int pos = m_fileList.size();
			m_fileList.push_back(item);
			gFileList.push_back(item->getFilePath());
			fileSettings.setValue(fileinfo.fileName() + "/type", type);
			fileSettings.setValue(fileinfo.fileName() + "/filePath", filePath);
			ui.FileTableWidget->setCellWidget(pos / 5, pos % 5, m_fileList[pos]);
			connect(item, &MainWindowItem::signalItemPress, this, &MainWindow::onItemClicked);
		}
		else 
			delete item;
	}
	else if (type == FOLDER)
	{
		QStringList file = fileSettings.childGroups();
		if (file.contains(fileinfo.fileName()) || filePath == fileSettings.value(fileinfo.fileName() + "/filePath").toString()) {
			QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("文件夹已存在"));
			return;
		}
		MainWindowItem* item = new MainWindowItem(ui.FileTableWidget, FOLDER, filePath);
		if (item->createSuccess())
		{
			int pos = m_fileList.size();
			m_fileList.push_back(item);
			fileSettings.setValue(fileinfo.fileName() + "/type", type);
			fileSettings.setValue(fileinfo.fileName() + "/filePath", filePath);
			ui.FileTableWidget->setCellWidget(pos / 5, pos % 5, m_fileList[pos]);
			connect(item, &MainWindowItem::signalItemPress, this, &MainWindow::onItemClicked);
		}
		else
			delete item;
	}
}

void MainWindow::onMenuBtnClicked()
{
	QMenu* pMenu = new QMenu(this);
	QAction* pOwner = new QAction(QString::fromLocal8Bit("个人中心"), this);
	QAction* pOption = new QAction(QString::fromLocal8Bit("设置"), this);
	QAction* pSkinChange = new QAction(QString::fromLocal8Bit("换肤"), this);

	pOwner->setData(1);
	pOption->setData(2);
	pSkinChange->setData(3);

	pMenu->addAction(pOwner);
	pMenu->addAction(pOption);
	pMenu->addAction(pSkinChange);

	connect(pOwner, &QAction::triggered, this, &MainWindow::onMenuItemClicked);
	connect(pOption, &QAction::triggered, this, &MainWindow::onMenuItemClicked);
	connect(pSkinChange, &QAction::triggered, this, &MainWindow::onMenuItemClicked);

	pMenu->exec(cursor().pos());

	QList<QAction*> list = pMenu->actions();
	foreach(QAction * pAction, list) delete pAction;
	delete pMenu;
}

void MainWindow::onMenuItemClicked()
{
	QAction* pAction = qobject_cast<QAction*>(sender());
	int data = pAction->data().toInt();

	switch (data)
	{
	case 1:
	{
		UserCenter* userCenter = new UserCenter;
		userCenter->show();
		break;
	}
	case 2:
	{
		OptionWindow* optionWindow = new OptionWindow();
		optionWindow->show();
		break;
	}case 3:
	{
		SkinWindow* skinWindow = new SkinWindow();
		skinWindow->show();
		break;
	}
	default:
		break;
	}
}

void MainWindow::onSearchLineEditChanged()
{
	QString str = ui.SearchLineEdit->text();
	if (str.isEmpty())
	{
		foreach(MainWindowItem * item, m_fileList) 
			item->setVisible(true);
		foreach(MainWindowItem * item, m_toolList)
			item->setVisible(true);
		return;
	}
	foreach(MainWindowItem * item, m_fileList)
	{
		if (!item->getFileName().contains(str) && item->getType() != ADD_TOOL && item->getType() != ADD_FILE)
			item->setVisible(false);
	}
	foreach(MainWindowItem * item, m_toolList)
	{
		if (!item->getFileName().contains(str) && item->getType() != ADD_TOOL && item->getType() != ADD_FILE)
			item->setVisible(false);
	}

}

void MainWindow::paintEvent(QPaintEvent* event)
{
	return BasicWindow::paintEvent(event);
}

void MainWindow::onItemClicked(MainWindowItem* item)
{
	foreach(MainWindowItem* tool, m_toolList)
	{
		if (tool == item)
		{
			item->setFocus();
		}
		else
		{
			tool->clearFocus();
		}
	}
	foreach(MainWindowItem* file, m_fileList)
	{
		if (file == item)
		{
			item->setFocus();
		}
		else
		{
			file->clearFocus();
		}
	}
}

void MainWindow::dragEnterEvent(QDragEnterEvent* event)
{
	event->accept();
}

void MainWindow::dragMoveEvent(QDragMoveEvent* event)
{

}

void MainWindow::dropEvent(QDropEvent* event)
{
	QList<QUrl> urls = event->mimeData()->urls();
	if (urls.isEmpty())
		return;

	foreach(QUrl url, urls)
	{
		QString filePath = url.toLocalFile();
		QFileInfo fileInfo(filePath);
		if (fileInfo.isSymLink())
			filePath = fileInfo.symLinkTarget();
		if (fileInfo.isDir())
			onAddClicked(FOLDER, filePath);
		else if (fileInfo.isExecutable())
			onAddClicked(TOOL, filePath);
		else if (fileInfo.isFile())
			onAddClicked(REG_FILE, filePath);
	}
}