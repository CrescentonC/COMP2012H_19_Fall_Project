#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "iostream"
#include "Block.hpp"
#include "VarFunManager.hpp"
#include "QInputDialog"
#include "ui_runwindow.h"
#include "QDebug"
#include "Interpreter.hpp"
#include "logicline.h"

using namespace WriteBackend;
using namespace dataStorage;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , runWindow {new RunWindow()}
{
    ui->setupUi(this);
    connect(runWindow, &RunWindow::runWindowClosed_signal, this, &MainWindow::when_runWindow_closed);

    //=================== init main function =========================================
    currentFunc = "main";
    func_pool["main"] = new Func_Block("main", 0);
    Visible_Block *blk = new Visible_Block(currentFunc, USER_FUNC, func_pool[currentFunc], ui->showDefinedArea_content, false);
    blk->setMinimumSize(150, 50);
    visible_func_pool[currentFunc] = blk;
    ui->showDefinedArea_content_layout->addWidget(blk);
    visible_block_pool = new std::map<std::string, Visible_Block*>;
    correspond_pool[func_pool[currentFunc]] = visible_block_pool;
    connect(blk, &Visible_Block::user_func_edit, this, &MainWindow::switch_user_func);
    visible_func_pool[currentFunc]->setStyleSheet("background-color : #375291");

    // ================= for setting up the logic wire push button ====================
    QPushButton *logicWire = new QPushButton {ui->canvas_area};
    logicWire->setCheckable(true);
    logicWire->setText("Logic Wire");
    logicWire->setGeometry(QRect(24, 24, 120, 72));
    QFont font2;
    font2.setFamily(QString::fromUtf8("Arial"));
    font2.setPointSize(12);
    logicWire->setFont(font2);
    connect(logicWire, &QPushButton::toggled, this, &MainWindow::_on_logicWireButton_toggled);
    // ================= for setting up the logic wire push button ====================

    ui->showDefinedArea_content_layout->setAlignment(Qt::AlignTop);

    setRunWindowStep(&(runWindow->getMyUI()->stepButton)); // for debugging window to know what is the step button
    setRunWindowPtr(&runWindow);
    dp = new DrawPalette {ui->canvasArea_content, logicWire};
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
    dataStorage::interpretAll();
    this->setEnabled(false);
    runWindow->show();
}

void MainWindow::on_clearButton_clicked()
{
    // TODO
}

void MainWindow::_on_logicWireButton_toggled(bool checked)
{
    dp->setVisible(checked);
}

void MainWindow::when_runWindow_closed()
{
    this->setEnabled(true);
}

void MainWindow::on_andButton_clicked()
{
    std::string thisName = getAvailName("and");
    Visible_Block *blk = new Visible_Block(thisName, AND, func_pool[currentFunc], ui->canvasArea_content);
    blk->setMinimumSize(150, 80);
    (*visible_block_pool)[thisName] = blk;
    connect(blk, &Visible_Block::visible_block_delete, this, &MainWindow::eraseBlock);
    blk->setSource1();
    blk->setSource2();
    blk->setDestination();
    blk->currentBlockVerify();
}

void MainWindow::on_assignmentButton_clicked()
{
    std::string thisName = getAvailName("assignment");
    Visible_Block *blk = new Visible_Block(thisName, ASSIGNMENT, func_pool[currentFunc], ui->canvasArea_content);
    blk->setMinimumSize(150, 80);
    (*visible_block_pool)[thisName] = blk;
    connect(blk, &Visible_Block::visible_block_delete, this, &MainWindow::eraseBlock);
    blk->setSource1();
    blk->setDestination();
    blk->currentBlockVerify();
}

void MainWindow::on_divisionButton_clicked()
{
    std::string thisName = getAvailName("division");
    Visible_Block *blk = new Visible_Block(thisName, DIVISION, func_pool[currentFunc], ui->canvasArea_content);
    blk->setMinimumSize(150, 80);
    (*visible_block_pool)[thisName] = blk;
    connect(blk, &Visible_Block::visible_block_delete, this, &MainWindow::eraseBlock);
    blk->setSource1();
    blk->setSource2();
    blk->setDestination();
    blk->currentBlockVerify();
}

void MainWindow::on_biggerThanButton_clicked()
{
    std::string thisName = getAvailName("biggerThan");
    Visible_Block *blk = new Visible_Block(thisName, BIGGERTHAN, func_pool[currentFunc], ui->canvasArea_content);
    blk->setMinimumSize(150, 80);
    (*visible_block_pool)[thisName] = blk;
    connect(blk, &Visible_Block::visible_block_delete, this, &MainWindow::eraseBlock);
    blk->setSource1();
    blk->setSource2();
    blk->setDestination();
    blk->currentBlockVerify();
}

void MainWindow::on_equalButton_clicked()
{
    std::string thisName = getAvailName("equalCompare");
    Visible_Block *blk = new Visible_Block(thisName, EQUALCOMPARE, func_pool[currentFunc], ui->canvasArea_content);
    blk->setMinimumSize(150, 80);
    (*visible_block_pool)[thisName] = blk;
    connect(blk, &Visible_Block::visible_block_delete, this, &MainWindow::eraseBlock);
    blk->setSource1();
    blk->setSource2();
    blk->setDestination();
    blk->currentBlockVerify();
}



void MainWindow::on_minusButton_clicked()
{
    std::string thisName = getAvailName("minus");
    Visible_Block *blk = new Visible_Block(thisName, MINUS, func_pool[currentFunc], ui->canvasArea_content);
    blk->setMinimumSize(150, 80);
    (*visible_block_pool)[thisName] = blk;
    connect(blk, &Visible_Block::visible_block_delete, this, &MainWindow::eraseBlock);
    blk->setSource1();
    blk->setSource2();
    blk->setDestination();
    blk->currentBlockVerify();
}

void MainWindow::on_multiplyButton_clicked()
{
    std::string thisName = getAvailName("multiply");
    Visible_Block *blk = new Visible_Block(thisName, MULTIPLY, func_pool[currentFunc], ui->canvasArea_content);
    blk->setMinimumSize(150, 80);
    (*visible_block_pool)[thisName] = blk;
    connect(blk, &Visible_Block::visible_block_delete, this, &MainWindow::eraseBlock);
    blk->setSource1();
    blk->setSource2();
    blk->setDestination();
    blk->currentBlockVerify();
}

void MainWindow::on_notButton_clicked()
{
    std::string thisName = getAvailName("NOT");
    Visible_Block *blk = new Visible_Block(thisName, NOT, func_pool[currentFunc], ui->canvasArea_content);
    blk->setMinimumSize(150, 80);
    (*visible_block_pool)[thisName] = blk;
    connect(blk, &Visible_Block::visible_block_delete, this, &MainWindow::eraseBlock);
    blk->setSource1();
    blk->setDestination();
    blk->currentBlockVerify();
}

void MainWindow::on_orButton_clicked()
{
    std::string thisName = getAvailName("OR");
    Visible_Block *blk = new Visible_Block(thisName, OR, func_pool[currentFunc], ui->canvasArea_content);
    blk->setMinimumSize(150, 80);
    (*visible_block_pool)[thisName] = blk;
    connect(blk, &Visible_Block::visible_block_delete, this, &MainWindow::eraseBlock);
    blk->setSource1();
    blk->setSource2();
    blk->setDestination();
    blk->currentBlockVerify();
}

void MainWindow::on_plusButton_clicked()
{
    std::string thisName = getAvailName("plus");
    Visible_Block *blk = new Visible_Block(thisName, PLUS, func_pool[currentFunc], ui->canvasArea_content);
    blk->setMinimumSize(150, 80);
    (*visible_block_pool)[thisName] = blk;
    connect(blk, &Visible_Block::visible_block_delete, this, &MainWindow::eraseBlock);
    blk->setSource1();
    blk->setSource2();
    blk->setDestination();
    blk->currentBlockVerify();
}

void MainWindow::on_printButton_clicked()
{
    std::string thisName = getAvailName("print");
    Visible_Block *blk = new Visible_Block(thisName, PRINT, func_pool[currentFunc], ui->canvasArea_content);
    blk->setMinimumSize(150, 80);
    (*visible_block_pool)[thisName] = blk;
    connect(blk, &Visible_Block::visible_block_delete, this, &MainWindow::eraseBlock);
    blk->setSource1();
    blk->currentBlockVerify();
}

void MainWindow::on_smallerThanButton_clicked()
{
    std::string thisName = getAvailName("smallerThan");
    Visible_Block *blk = new Visible_Block(thisName, SMALLERTHAN, func_pool[currentFunc], ui->canvasArea_content);
    blk->setMinimumSize(150, 80);
    (*visible_block_pool)[thisName] = blk;
    connect(blk, &Visible_Block::visible_block_delete, this, &MainWindow::eraseBlock);
    blk->setSource1();
    blk->setSource2();
    blk->setDestination();
    blk->currentBlockVerify();
}

void MainWindow::on_startButton_clicked()
{
    std::string thisName = "start"; //only one start function
    Visible_Block *blk = new Visible_Block("start", START, func_pool[currentFunc], ui->canvasArea_content);
    blk->setMinimumSize(150, 80);
    (*visible_block_pool)[thisName] = blk;
    connect(blk, &Visible_Block::visible_block_delete, this, &MainWindow::eraseBlock);
}

void MainWindow::on_takeIndSetButton_clicked()
{
    std::string thisName = getAvailName("takeIndSet");
    Visible_Block *blk = new Visible_Block(thisName, TAKEINDSET, func_pool[currentFunc], ui->canvasArea_content);
    blk->setMinimumSize(150, 80);
    (*visible_block_pool)[thisName] = blk;
    connect(blk, &Visible_Block::visible_block_delete, this, &MainWindow::eraseBlock);
    blk->setSource1();  //things to set into
    blk->setDestination(); // array
    blk->setArrInd();
    blk->currentBlockVerify();
}

void MainWindow::on_takeIndGetButton_clicked()
{
    std::string thisName = getAvailName("takeIndGet");
    Visible_Block *blk = new Visible_Block(thisName, TAKEINDGET, func_pool[currentFunc], ui->canvasArea_content);
    blk->setMinimumSize(150, 80);
    (*visible_block_pool)[thisName] = blk;
    connect(blk, &Visible_Block::visible_block_delete, this, &MainWindow::eraseBlock);
    blk->setSource1();  //array
    blk->setArrInd();
    blk->setDestination();  //receiver
    blk->currentBlockVerify();
}



/////////////////////////////////////////////////
void MainWindow::on_funcDefButton_clicked()
{
    std::string thisName;
    QString inputText;
    do{
        inputText = QInputDialog::getText(this, "function definition", "function name", QLineEdit::Normal, "FUNC2333");
        thisName = inputText.toStdString();
    }while(func_pool.count(thisName));
    int paramNum = QInputDialog::getInt(this, "function definition", "parameter ammount:",0,0);
    func_pool[thisName] = new Func_Block(thisName, static_cast<unsigned int>(paramNum));

    Visible_Block *blk = new Visible_Block(thisName, USER_FUNC, func_pool[thisName], ui->showDefinedArea_content, false);
    blk->setMinimumSize(150, 50);
    ui->showDefinedArea_content_layout->addWidget(blk);
    visible_func_pool[thisName] = blk;
    blk->setUserFuncOperandsNum(paramNum);

    for(int i = 0; i < paramNum; i++)
    {
        inputText = QInputDialog::getText(this, "function definition",
                                          QString::number(i) + "-th param type:\n(bool, int, double, bool*, int*, double*",
                                          QLineEdit::Normal, "bool");
        std::string thistype = inputText.toStdString();
        if(thistype == "bool") reinterpret_cast<Func_Block*>(func_pool[thisName])->setParamType(BOOL,i);
        else if(thistype == "int") reinterpret_cast<Func_Block*>(func_pool[thisName])->setParamType(INT,i);
        else if(thistype == "double") reinterpret_cast<Func_Block*>(func_pool[thisName])->setParamType(DOUBLE,i);
        else if(thistype == "bool*") reinterpret_cast<Func_Block*>(func_pool[thisName])->setParamType(BOOLARR,i);
        else if(thistype == "int*") reinterpret_cast<Func_Block*>(func_pool[thisName])->setParamType(INTARR,i);
        else if(thistype == "double*") reinterpret_cast<Func_Block*>(func_pool[thisName])->setParamType(DOUBLEARR,i);
        blk->insertFuncParamTypeInfo(thistype);
    }

    correspond_pool[func_pool[thisName]] = new std::map<std::string, Visible_Block*>;
    connect(blk, &Visible_Block::user_func_clicked, this, &MainWindow::add_user_func_blk);
    connect(blk, &Visible_Block::user_func_edit, this, &MainWindow::switch_user_func);
    connect(blk, &Visible_Block::visible_block_delete, this, &MainWindow::eraseBlock);
}

void MainWindow::on_varDefButton_clicked()
{
    // =========================== get name and type(format:str) ==============================
    QString inputText;
    std::string thisName;
    do{
        inputText = QInputDialog::getText(this, "variable definition", "varible name", QLineEdit::Normal, "VAR2333");
        thisName = inputText.toStdString();
    }while(var_pool.count(thisName));
    inputText = QInputDialog::getText(this, "variable definition", "varible type:\n(bool, int, double, bool*, int*, double*",
                                      QLineEdit::Normal, "bool");
    std::string thisType = inputText.toStdString();
    // =========================== get name and type(format:str) ==============================

    // =========================== for distribute variable type ===============================
    if(thisType == "bool")
    {
        bool inputValue = QInputDialog::getInt(this, "variable definition", "varible value:",0,0,1);
        var_pool[thisName] = new Var_Block<bool>(thisName, inputValue);
    }
    else if(thisType == "int")
    {
        int inputValue = QInputDialog::getInt(this, "variable definition", "varible value:",0);
        var_pool[thisName] = new Var_Block<int>(thisName, inputValue);
    }
    else if(thisType == "double")
    {
        double inputValue = QInputDialog::getDouble(this, "variable definition", "varible value:",0);
        var_pool[thisName] = new Var_Block<double>(thisName, inputValue);
    }
    else if(thisType == "bool*")
    {
        int arrLenth = QInputDialog::getInt(this, "variable definition", "array length:",2,2);
        var_pool[thisName] = new Var_Block<bool*>(thisName, nullptr, static_cast<unsigned int>(arrLenth));
        for(int i = 0; i < arrLenth; i++)
        {
            bool inputValue = QInputDialog::getInt(this, "variable definition", "varible value:",0,0,1);
            reinterpret_cast<Var_Block<bool*>*>(var_pool[thisName])->set_value(inputValue, i);
        }
    }
    else if(thisType == "int*")
    {
        int arrLenth = QInputDialog::getInt(this, "variable definition", "array length:",2,2);
        var_pool[thisName] = new Var_Block<int*>(thisName, nullptr, static_cast<unsigned int>(arrLenth));
        for(int i = 0; i < arrLenth; i++)
        {
            int inputValue = QInputDialog::getInt(this, "variable definition", "varible value:",0);
            reinterpret_cast<Var_Block<int*>*>(var_pool[thisName])->set_value(inputValue, i);
        }
    }
    else if(thisType == "double*")
    {
        int arrLenth = QInputDialog::getInt(this, "variable definition", "array length:",2,2);
        var_pool[thisName] = new Var_Block<double*>(thisName, nullptr, static_cast<unsigned int>(arrLenth));
        for(int i = 0; i < arrLenth; i++)
        {
            double inputValue = QInputDialog::getDouble(this, "variable definition", "varible value:",0);
            reinterpret_cast<Var_Block<double*>*>(var_pool[thisName])->set_value(inputValue, i);
        }
    }
    // =========================== for distribute variable type ===============================

    // =========================== display out on the display area ============================
    Visible_Block *blk = new Visible_Block(thisName, USER_VAR, var_pool[thisName], ui->showDefinedArea_content, false);

    blk->setMinimumSize(150, 50);
    ui->showDefinedArea_content_layout->addWidget(blk);
    visible_var_pool[thisName] = blk;
    connect(blk, &Visible_Block::visible_block_delete, this, &MainWindow::eraseBlock);
}
/////////////////////////////////////////////////


//=================================== other slots ===============================
void MainWindow::eraseBlock(std::string deleteName)
{
    visible_block_pool->erase(deleteName);
    visible_var_pool.erase(deleteName);
    visible_func_pool.erase(deleteName);
    func_pool.erase(deleteName);
    var_pool.erase(deleteName);
}

void MainWindow::hideAllFlowBlk()
{
    std::map<std::string, Visible_Block*>::iterator iter;
    for(iter = visible_block_pool->begin(); iter != visible_block_pool->end(); ++iter)
    {
        iter->second->setVisible(false);
    }
}

void MainWindow::hideAllLine()
{
    std::map<std::string, LogicLine*>::iterator iter;
    for (iter = dataStorage::linePool.begin(); )
}

void MainWindow::retrieveAllFlowBlk()
{
    std::map<std::string, Visible_Block*>::iterator iter;
    if(visible_block_pool->empty()) return;
    for(iter = visible_block_pool->begin(); iter != visible_block_pool->end(); ++iter)
    {
        iter->second->setVisible(true);
    }
}

void MainWindow::retrieveAllLine()
{

}

void MainWindow::add_user_func_blk(std::string addFuncName)
{
    std::string thisName = getAvailName(addFuncName);
    Visible_Block *blk = new Visible_Block(thisName, Visible_Block_type::USER_FUNC, func_pool[currentFunc], ui->canvasArea_content);
    blk->setMinimumSize(150, 80);
    (*visible_block_pool)[thisName] = blk;
    blk->setUserFuncOperandsNum(visible_func_pool[addFuncName]->getUserFuncOperandsNum());
    blk->copyFuncParamTypeInfo(visible_func_pool[addFuncName]->getFuncParamTypeInfo());
    for(int i = 0; i < blk->getUserFuncOperandsNum(); i++)
    {
        blk->setUserFuncOperands(i);
    }
    blk->setRealFuncName(addFuncName);
    blk->currentBlockVerify();
    connect(blk, &Visible_Block::visible_block_delete, this, &MainWindow::eraseBlock);
}

void MainWindow::on_whileButton_clicked()
{
    std::string thisName = getAvailName("while");
    Visible_Block *blk = new Visible_Block(thisName, Visible_Block_type::WHILE, func_pool[currentFunc], ui->canvasArea_content);
    blk->setMinimumSize(150, 80);
    (*visible_block_pool)[thisName] = blk;
    connect(blk, &Visible_Block::visible_block_delete, this, &MainWindow::eraseBlock);
    blk->setSource1();

    blk->setSubFunc1();
    blk->setUserFuncOperandsNumT(visible_func_pool[(*blk->getSubFunction1())->name]->getUserFuncOperandsNum());
    for(int i = 0; i < blk->getUserFuncOperandsNumT(); i++)
    {
        blk->setUserFuncOperandsT(i);
    }
    blk->setRealFuncNameT((*blk->getSubFunction1())->name);
    qDebug() << "here ok" + QString::number(blk->getUserFuncOperandsNumT());

    blk->currentBlockVerify();
}

void MainWindow::on_ifButton_clicked()
{
    std::string thisName = getAvailName("IF");
    Visible_Block *blk = new Visible_Block(thisName, Visible_Block_type::IF, func_pool[currentFunc], ui->canvasArea_content);
    blk->setMinimumSize(150, 80);
    (*visible_block_pool)[thisName] = blk;
    connect(blk, &Visible_Block::visible_block_delete, this, &MainWindow::eraseBlock);
    blk->setSource1();

    blk->setSubFunc1();
    blk->setUserFuncOperandsNumT(visible_func_pool[(*blk->getSubFunction1())->name]->getUserFuncOperandsNum());
    for(int i = 0; i < blk->getUserFuncOperandsNumT(); i++)
    {
        blk->setUserFuncOperandsT(i);
    }
    blk->setRealFuncNameT((*blk->getSubFunction1())->name);

    blk->setSubFunc2();
    blk->setUserFuncOperandsNumF(visible_func_pool[(*blk->getSubFunction2())->name]->getUserFuncOperandsNum());
    for(int i = 0; i < blk->getUserFuncOperandsNumF(); i++)
    {
        blk->setUserFuncOperandsF(i);
    }
    blk->setRealFuncNameF((*blk->getSubFunction2())->name);

    blk->currentBlockVerify();
}

void MainWindow::switch_user_func(std::string targetFuncName)
{
//    qDebug() << QString::fromStdString(targetFuncName);
    visible_func_pool[currentFunc]->setStyleSheet("background-color : white");
    hideAllFlowBlk();

    currentFunc = targetFuncName;
    visible_block_pool = correspond_pool[func_pool[currentFunc]];
    visible_func_pool[currentFunc]->setStyleSheet("background-color : #375291");
    retrieveAllFlowBlk();
}

