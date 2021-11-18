#include "DeskBox.h"
#include "UserLogin.h"
#include <QtWidgets/QApplication>
#include <QDateTime>

QDateTime gTime;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gTime = QDateTime::currentDateTime();
    /*DeskBox w;
    w.show();*/
    UserLogin* w = new UserLogin;
    w->show();
    return a.exec();
}
