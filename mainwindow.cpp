#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "iostream"
#include "Block.hpp"
#include "VarFunManager.hpp"
#include "QInputDialog"

using namespace WriteBackend;
using namespace dataStorage;

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
    Visible_Block *blk = new Visible_Block(currentFunc, USER_FUNC, func_pool[currentFunc], ui->showDefinedArea_content, false);
    blk->setMinimumSize(150, 50);
    visible_func_pool[currentFunc] = blk;
    ui->showDefinedArea_content_layout->addWidget(blk);
    visible_block_pool = new std::map<std::string, Visible_Block*>;
    correspond_pool[func_pool[currentFunc]] = visible_block_pool;

    // ================= for setting up the logic wire push button ====================
    QPushButton *logicWire = new QPushButton {ui->canvas_area};
    logicWire->setText("Logic Wire");
    logicWire->setGeometry(QRect(24, 24, 120, 72));
    QFont font2;
    font2.setFamily(QString::fromUtf8("Arial"));
    font2.setPointSize(12);
    logicWire->setFont(font2);
    // ================= for setting up the logic wire push button ====================
    ui->showDefinedArea_content_layout->setAlignment(Qt::AlignTop);
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

void MainWindow::on_assignmentButton_clicked()
{
    std::string thisName = getAvailName("assignment");
    Visible_Block *blk = new Visible_Block(thisName, ASSIGNMENT, func_pool[currentFunc], ui->canvasArea_content);
    (*visible_block_pool)[thisName] = blk;
}

void MainWindow::on_divisionButton_clicked()
{
    std::string thisName = getAvailName("division");
    Visible_Block *blk = new Visible_Block(thisName, DIVISION, func_pool[currentFunc], ui->canvasArea_content);
    (*visible_block_pool)[thisName] = blk;
}

void MainWindow::on_biggerThanButton_clicked()
{
    std::string thisName = getAvailName("biggerThan");
    Visible_Block *blk = new Visible_Block(thisName, BIGGERTHAN, func_pool[currentFunc], ui->canvasArea_content);
    (*visible_block_pool)[thisName] = blk;
}

//void MainWindow::on_endButton_clicked()
//{
//    std::string thisName = getAvailName("end");
//    Visible_Block *blk = new Visible_Block(thisName, END, func_pool[currentFunc], ui->canvasArea_content);
//    (*visible_block_pool)[thisName] = blk;
//}

void MainWindow::on_equalButton_clicked()
{
    std::string thisName = getAvailName("equalCompare");
    Visible_Block *blk = new Visible_Block(thisName, EQUALCOMPARE, func_pool[currentFunc], ui->canvasArea_content);
    (*visible_block_pool)[thisName] = blk;
}

//void MainWindow::on_forButton_clicked()
//{
//    std::string thisName = getAvailName("for");
//    Visible_Block *blk = new Visible_Block(thisName, FOR, func_pool[currentFunc], ui->canvasArea_content);
//    (*visible_block_pool)[thisName] = blk;
//}


void MainWindow::on_ifButton_clicked()
{
    std::string thisName = getAvailName("IF");
    Visible_Block *blk = new Visible_Block(thisName, Visible_Block_type::IF, func_pool[currentFunc], ui->canvasArea_content);
    (*visible_block_pool)[thisName] = blk;
}

void MainWindow::on_minusButton_clicked()
{
    std::string thisName = getAvailName("minus");
    Visible_Block *blk = new Visible_Block(thisName, MINUS, func_pool[currentFunc], ui->canvasArea_content);
    (*visible_block_pool)[thisName] = blk;
}

void MainWindow::on_multiplyButton_clicked()
{
    std::string thisName = getAvailName("multiply");
    Visible_Block *blk = new Visible_Block(thisName, MULTIPLY, func_pool[currentFunc], ui->canvasArea_content);
    (*visible_block_pool)[thisName] = blk;
}

void MainWindow::on_notButton_clicked()
{
    std::string thisName = getAvailName("NOT");
    Visible_Block *blk = new Visible_Block(thisName, NOT, func_pool[currentFunc], ui->canvasArea_content);
    (*visible_block_pool)[thisName] = blk;
}

void MainWindow::on_orButton_clicked()
{
    std::string thisName = getAvailName("OR");
    Visible_Block *blk = new Visible_Block(thisName, OR, func_pool[currentFunc], ui->canvasArea_content);
    (*visible_block_pool)[thisName] = blk;
}

void MainWindow::on_plusButton_clicked()
{
    std::string thisName = getAvailName("plus");
    Visible_Block *blk = new Visible_Block(thisName, PLUS, func_pool[currentFunc], ui->canvasArea_content);
    (*visible_block_pool)[thisName] = blk;
}

void MainWindow::on_printButton_clicked()
{
    std::string thisName = getAvailName("print");
    Visible_Block *blk = new Visible_Block(thisName, PRINT, func_pool[currentFunc], ui->canvasArea_content);
    (*visible_block_pool)[thisName] = blk;
}

void MainWindow::on_smallerThanButton_clicked()
{
    std::string thisName = getAvailName("smallerThan");
    Visible_Block *blk = new Visible_Block(thisName, SMALLERTHAN, func_pool[currentFunc], ui->canvasArea_content);
    (*visible_block_pool)[thisName] = blk;
}

//void MainWindow::on_startButton_clicked()
//{
//    std::string thisName = getAvailName("start");
//    Visible_Block *blk = new Visible_Block(thisName, START, func_pool[currentFunc], ui->canvasArea_content);
//    (*visible_block_pool)[thisName] = blk;
//}

void MainWindow::on_takeIndSetButton_clicked()
{
    std::string thisName = getAvailName("takeIndSet");
    Visible_Block *blk = new Visible_Block(thisName, TAKEIND, func_pool[currentFunc], ui->canvasArea_content);
    (*visible_block_pool)[thisName] = blk;
}

void MainWindow::on_takeIndGetButton_clicked()
{
    std::string thisName = getAvailName("takeIndGet");
    Visible_Block *blk = new Visible_Block(thisName, TAKEIND, func_pool[currentFunc], ui->canvasArea_content);
    (*visible_block_pool)[thisName] = blk;
}

void MainWindow::on_whileButton_clicked()
{
    std::string thisName = getAvailName("while");
    Visible_Block *blk = new Visible_Block(thisName, Visible_Block_type::WHILE, func_pool[currentFunc], ui->canvasArea_content);
    (*visible_block_pool)[thisName] = blk;
}


/////////////////////////////////////////////////
void MainWindow::on_funcDefButton_clicked()
{
    std::string thisName = getAvailName("func_def");
    Visible_Block *blk = new Visible_Block(thisName, USER_FUNC, func_pool[currentFunc], ui->showDefinedArea_content, false);
    blk->setMinimumSize(150, 50);
    ui->showDefinedArea_content_layout->addWidget(blk);
    (*visible_block_pool)[thisName] = blk;
}

void MainWindow::on_varDefButton_clicked()
{
    bool ok = false;
    QString inputText = QInputDialog::getText(this, "variable definition", "varible name", QLineEdit::Normal, "2333", &ok);
    std::string thisName = inputText.toStdString();
//    ok = false;

    Visible_Block *blk = new Visible_Block(thisName, USER_VAR, func_pool[currentFunc], ui->showDefinedArea_content, false);
    blk->setMinimumSize(150, 50);
    ui->showDefinedArea_content_layout->addWidget(blk);
    (*visible_block_pool)[thisName] = blk;
}
/////////////////////////////////////////////////

