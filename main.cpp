#include "mainwindow.h"
#include "outline.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    tmp::outline()->show();
    w.raise();
//    w.show();
    return a.exec();
}
