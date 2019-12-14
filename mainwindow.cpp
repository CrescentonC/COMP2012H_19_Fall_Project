#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "iostream"
#include "Block.hpp"
#include "VarFunManager.hpp"

using namespace WriteBackend;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , runWindow {new RunWindow()}
{
    ui->setupUi(this);
    connect(runWindow, &RunWindow::runWindowClosed_signal, this, &MainWindow::when_runWindow_closed);

    // init main function
    currentFunc = "main";
    func_pool["main"] = new Func_Block("main", 0);
    visible_block_pool = new std::map<std::string, Visible_Block*>;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete runWindow;
}

std::string MainWindow::getAvailName(std::string prefix)
{
    int id = 0;
    std::string availableName;
    do{
        availableName = prefix + "_" + std::to_string(id);
        id ++;
    }while((*visible_block_pool).count(availableName));
    return availableName;
}

void MainWindow::on_runButton_clicked()
{
    this->setEnabled(false);
    runWindow->show();
}

void MainWindow::on_clearButton_clicked()
{
    // TODO
}

void MainWindow::on_saveButton_clicked()
{
    // TODO
}

void MainWindow::when_runWindow_closed()
{
    this->setEnabled(true);
}


void MainWindow::on_andButton_clicked()
{
    std::string thisName = getAvailName("and");
    Visible_Block *blk = new Visible_Block(thisName, AND, func_pool[currentFunc], ui->canvasArea_content);
    (*visible_block_pool)[thisName] = blk;
}
