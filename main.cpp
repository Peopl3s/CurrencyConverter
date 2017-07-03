#include "mainwindow.h"
#include <QApplication>
#include "currency.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow m;
    m.show();

    return a.exec();
}
