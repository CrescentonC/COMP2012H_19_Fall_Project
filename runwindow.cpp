#include "runwindow.h"
#include "ui_runwindow.h"
#include "ui_mainwindow.h"
#include "mainwindow.hpp"
#include <iostream>
#include "dataStorage.hpp"

RunWindow::RunWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RunWindow)
{
    ui->setupUi(this);
    ui->showDataArea_content_layout->setAlignment(Qt::AlignTop);
    ui->showFlowArea_content_layout->setAlignment(Qt::AlignTop);
    ui->showOutputArea_content_layout->setAlignment(Qt::AlignTop);
}

RunWindow::~RunWindow()
{
    delete ui;
}

void RunWindow::resetAfterClose()
{
    // TODO
}

void RunWindow::on_closeButton_clicked()
{
    this->close();
}

void RunWindow::on_stepButton_clicked()
{
    // TODO
    Func_Block::set_isStepping(true);
    dataStorage::func_pool["main"]->run();
}

void RunWindow::on_runButton_clicked()
{
    Func_Block::set_isStepping(false);
    std::cout << "should be run" << std::endl;
    dataStorage::func_pool["main"]->run();
}

void RunWindow::closeEvent(QCloseEvent *event)
{
    QMainWindow::closeEvent(event);
    resetAfterClose();
    emit runWindowClosed_signal();
}
