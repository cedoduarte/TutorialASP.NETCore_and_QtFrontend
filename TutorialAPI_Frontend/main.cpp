#include "mainwindow.h"
#include "user.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
    User::registerMetaType();
    MainWindow w;
    w.show();
    return a.exec();
}
