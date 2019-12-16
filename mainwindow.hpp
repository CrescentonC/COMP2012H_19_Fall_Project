#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <map>
#include "runwindow.h"
#include <QMainWindow>
#include "Block.hpp"
#include "Func_Block.hpp"
#include "Visible_Block.hpp"
#include "dataStorage.hpp"
#include "drawpalette.h"
#include "logicline.h"

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
    std::map<std::string, Visible_Block*>* *getCurrentVBPool() {return &visible_block_pool;}

private slots:
    void on_runButton_clicked();
    void on_clearButton_clicked();
    void when_runWindow_closed();
    void _on_logicWireButton_toggled(bool checked);
    void on_andButton_clicked();
    void on_assignmentButton_clicked();
    void on_biggerThanButton_clicked();
    void on_divisionButton_clicked();
    void on_equalButton_clicked();
    void on_funcDefButton_clicked();
    void on_ifButton_clicked();
    void on_minusButton_clicked();
    void on_multiplyButton_clicked();
    void on_notButton_clicked();
    void on_orButton_clicked();
    void on_plusButton_clicked();
    void on_printButton_clicked();
    void on_smallerThanButton_clicked();
    void on_startButton_clicked();
    void on_takeIndSetButton_clicked();
    void on_takeIndGetButton_clicked();
    void on_varDefButton_clicked();
    void on_whileButton_clicked();

    void eraseBlock(std::string deleteName);
    void hideAllFlowBlk();
    void retrieveAllFlowBlk();
    void add_user_func_blk(std::string addFuncName);
    void switch_user_func(std::string targetFuncName);

private:
    Ui::MainWindow *ui;

    RunWindow *runWindow {nullptr};

    std::string currentFunc {};     //name of the current function

    std::map<std::string, Visible_Block*> *visible_block_pool; // connect name and visible_block

    DrawPalette *dp;

    std::string getAvailName(std::string prefix);  
};
#endif // MAINWINDOW_H
