#include "ClickLabel.h"
#include "SkinWindow.h"
#include "NotifyManager.h"
#include <QGridLayout>

SkinWindow::SkinWindow(QWidget *parent)
	: BasicWindow(parent)
{
	ui.setupUi(this);
	loadStyleSheet("SkinWindow");
	setAttribute(Qt::WA_QuitOnClose, false);
	setAttribute(Qt::WA_DeleteOnClose, true);
	initControl();
}

SkinWindow::~SkinWindow()
{
}

void SkinWindow::initControl()
{

	QList<QColor> colorList = { QColor(162, 167, 167), QColor(40, 166, 107), QColor(218, 67, 68), QColor(177, 99, 158),
								QColor(107, 81, 92), QColor(107, 81, 92), QColor(82, 92, 160), QColor(21, 156, 199),
								QColor(79, 169, 172), QColor(155, 183, 154), QColor(128, 77, 77), QColor(240, 188, 189)
	};

	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			ClickLabel* label = new ClickLabel(this);
			label->setCursor(Qt::PointingHandCursor);

			// C++11支持 lambda表达式，不需要写槽函数
			connect(label, &ClickLabel::clicked, [row, col, colorList]() {
				NotifyManager::getInstance()->notifyOtherWindowChangeSkin(colorList.at(row * 4 + col));
				});

			label->setFixedSize(84, 84);
			QPalette palette;
			palette.setColor(QPalette::Background, colorList.at(row * 4 + col));
			label->setAutoFillBackground(true);
			label->setPalette(palette);

			ui.gridLayout->addWidget(label, row, col);
		}
	}

	connect(ui.sysMin, SIGNAL(clicked(bool)), this, SLOT(onShowMin(bool)));
	connect(ui.sysClose, SIGNAL(clicked()), this, SLOT(onShowClose()));
}

void SkinWindow::onShowClose()
{
	close();
}