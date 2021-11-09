#include "DeskBox.h"
#include "UserLogin.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*DeskBox w;
    w.show();*/
    UserLogin* w = new UserLogin;
    w->show();
    return a.exec();
}
