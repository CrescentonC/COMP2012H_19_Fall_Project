#include "mainwindow.hpp"
#include "logicline.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::cout << "hher" << std::endl;
    MainWindow w;
    std::cout << "hher" << std::endl;
    builtInOperatorsInit();
    setMainWindowVBPool(w.getCurrentVBPool());
    w.show();
    return a.exec();
}
