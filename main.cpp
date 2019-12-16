#include "mainwindow.hpp"
#include "logicline.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    builtInOperatorsInit();
    setMainWindowVBPool(w.getCurrentVBPool());
    w.show();
    return a.exec();
}
