#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , runWindow {new RunWindow()}
{
    ui->setupUi(this);
    connect(runWindow, &RunWindow::runWindowClosed_signal, this, &MainWindow::when_runWindow_closed);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete runWindow;
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
