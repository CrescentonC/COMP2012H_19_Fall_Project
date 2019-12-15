#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <map>
#include "runwindow.h"
#include <QMainWindow>
#include "Block.hpp"
#include "Func_Block.hpp"
#include "Visible_Block.hpp"
#include "dataStorage.hpp"

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
    void on_andButton_clicked();
    void on_assignmentButton_clicked();
    void on_biggerThanButton_clicked();
    void on_divisionButton_clicked();
//    void on_endButton_clicked();
    void on_equalButton_clicked();
//    void on_forButton_clicked();
    void on_funcDefButton_clicked();
    void on_ifButton_clicked();
    void on_minusButton_clicked();
    void on_multiplyButton_clicked();
    void on_notButton_clicked();
    void on_orButton_clicked();
    void on_plusButton_clicked();
    void on_printButton_clicked();
    void on_smallerThanButton_clicked();
//    void on_startButton_clicked();
    void on_takeIndButton_clicked();
    void on_varDefButton_clicked();
    void on_whileButton_clicked();

private:
    Ui::MainWindow *ui;
    RunWindow *runWindow {nullptr};
    std::string currentFunc {};     //name of the current function
    std::map<std::string, Visible_Block*> *visible_block_pool; // connect name and visible_block

    std::string getAvailName(std::string prefix);
};
#endif // MAINWINDOW_H
