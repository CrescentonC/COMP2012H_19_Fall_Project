#include "runwindow.h"
#include "ui_runwindow.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <iostream>

RunWindow::RunWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RunWindow)
{
    ui->setupUi(this);
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

void RunWindow::closeEvent(QCloseEvent *event)
{
    QMainWindow::closeEvent(event);
    resetAfterClose();
    emit runWindowClosed_signal();
}
