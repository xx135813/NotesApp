#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;                       // ui/1: MainWindow – the main application window
    w.show();                           // ui/1 displayed

    return a.exec();
}
