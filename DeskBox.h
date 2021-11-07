#pragma once

#include <QtWidgets/QWidget>
#include "ui_DeskBox.h"

class DeskBox : public QWidget
{
    Q_OBJECT

public:
    DeskBox(QWidget *parent = Q_NULLPTR);

private:
    Ui::DeskBoxClass ui;
};
