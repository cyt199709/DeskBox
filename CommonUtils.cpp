#include "CommonUtils.h"
#include <QFile>
#include <QApplication>
#include <QSettings>

CommonUtils::CommonUtils()
{
}

void CommonUtils::loadStyleSheet(QWidget* widget, const QString& sheetName)
{
	QFile file(":/Resources/QSS/" + sheetName + ".css");
	file.open(QIODevice::ReadOnly);
	if (file.isOpen())
	{
		widget->setStyleSheet("");
		QString qssStyleSheet = QLatin1String(file.readAll());
		widget->setStyleSheet(qssStyleSheet);
	}
	file.close();
}

void CommonUtils::setDefaultSkinColor(const QColor& color)
{
	const QString& path = QApplication::applicationDirPath() + "/" + QString("tradeprintinfo.ini");
	QSettings settings(path, QSettings::IniFormat);
	settings.setValue("DefaultSkin/red", color.red());
	settings.setValue("DefaultSkin/green", color.green());
	settings.setValue("DefaultSkin/blue", color.blue());
}

QColor CommonUtils::getDefaultSkinColor()
{
	const QString&& path = QApplication::applicationDirPath() + "/" + QString("tradeprintinfo.ini");
	if (!QFile::exists(path))
		setDefaultSkinColor(QColor(162, 167, 167));

	QSettings settings(path, QSettings::IniFormat);
	QColor color;
	color.setRed(settings.value("DefaultSkin/red").toInt());
	color.setGreen(settings.value("DefaultSkin/green").toInt());
	color.setBlue(settings.value("DefaultSkin/blue").toInt());
	return color;
}
