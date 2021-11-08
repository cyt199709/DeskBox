#pragma once

#include <QWidget>
#include <QProxyStyle>

class CustomProxyStyle : public QProxyStyle
{
public:
	CustomProxyStyle(QObject* parent = nullptr)
	{
		setParent(parent);
	}

	virtual void drawPrimitive(PrimitiveElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget = 0) const
	{
		if (PE_FrameFocusRect == element)
		{
			return;
		}
		else
		{
			QProxyStyle::drawPrimitive(element, option, painter, widget);
		}
	}
};

class CommonUtils
{
public:
	CommonUtils();

public:
	static void loadStyleSheet(QWidget* widget, const QString& sheetName);
	static void setDefaultSkinColor(const QColor& color);
	static QColor getDefaultSkinColor();
};

