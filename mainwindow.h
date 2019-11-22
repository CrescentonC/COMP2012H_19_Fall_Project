#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "runwindow.h"
#include <QMainWindow>
#include "block.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow const *get_ui() const { return ui; }
    RunWindow* &get_runWindow() { return runWindow; }

private slots:
    void on_runButton_clicked();
    void on_clearButton_clicked();
    void on_saveButton_clicked();
    void when_runWindow_closed();

private:
    Ui::MainWindow *ui;
    RunWindow *runWindow {nullptr};
};
#endif // MAINWINDOW_H
