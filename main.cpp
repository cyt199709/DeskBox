#include "DeskBox.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DeskBox w;
    w.show();
    return a.exec();
}
