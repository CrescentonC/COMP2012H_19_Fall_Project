#ifndef VISIBLE_BLOCK_H
#define VISIBLE_BLOCK_H

#include <QLabel>
#include <QEvent>
#include <QMenu>
#include <QMouseEvent>
#include <QDebug>
#include <QMessageBox>
#include "Block.hpp"
#include <vector>
using namespace WriteBackend;

enum Visible_Block_type{
    USER_VAR,
    USER_FUNC,
    AND,
    ASSIGNMENT,
    BIGGERTHAN,
    DIVISION,
    EQUALCOMPARE,
    IF,
    MINUS,
    MULTIPLY,
    NOT,
    OR,
    PLUS,
    PRINT,
    SMALLERTHAN,
    START,
    TAKEINDGET,
    TAKEINDSET,
    WHILE
};

// not inherit from Block
class Visible_Block : public QLabel
{
    Q_OBJECT

protected slots:
    bool eventFilter(QObject *, QEvent *event) override;
    void ShowContextMenu(const QPoint& pos);
    void deleteBlock();
    void editFunc();
    virtual void showDetails(); //show belong to which function

public slots:
    void setSource1();
    void setSource2();
    void setDestination();
    void setArrInd();
    void setSubFunc1();
    void setSubFunc2();
    void setUserFuncOperands(int pos = -1);

signals:
    void visible_block_delete(std::string);
    void user_func_clicked(std::string);
    void user_func_edit(std::string);

public:
    Visible_Block() = delete;
    Visible_Block(std::string _n, Visible_Block_type type,
                  Block* parentFunc, QWidget *pa, bool _movable = true) : QLabel {pa},
                                                                          name{_n},
                                                                          block_type{type},
                                                                          motherFunc{parentFunc},
                                                                          movable{_movable}
    {
        setStyleSheet("border : none");
        setStyleSheet("background-color : white");
        setAutoFillBackground(true);
//        setGeometry(QRect(200, 200, 150, 80));
        setVisible(true);
        this->setContextMenuPolicy(Qt::CustomContextMenu);
        installEventFilter(this);
        connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(ShowContextMenu(const QPoint&)));
        block_position = this->pos();
        details = "block name:  " + this->name + " \n" + "mother function:  " + motherFunc->name;
        setAlignment(Qt::AlignCenter);
        setFont(QFont("Comic Sans MS", 10, QFont::Bold));
        setBlockText(name);
    }
    void setBlockText(std::string text) {this->setText(QString::fromStdString(text));}
    bool currentBlockVerify(void);  //verify whether correct ammount of operands
    void setUserFuncOperandsNum(int operandsNum) {userFuncOperandsNum = operandsNum;}
    int  getUserFuncOperandsNum(void){return userFuncOperandsNum;}
    void insertFuncParamTypeInfo(std::string typeInfo){funcParamTypeInfo.push_back(typeInfo);funcParamTypeInfo.shrink_to_fit();}
    void copyFuncParamTypeInfo(std::vector<std::string> source){funcParamTypeInfo = source;}
    std::vector<std::string> getFuncParamTypeInfo(){return funcParamTypeInfo;}

    void setNextBlock(Block* blk){nextLogicBlock = blk;}

private:
    std::string name;
    std::string details;            //context menu show details (default is block name + motherFunc name )
    std::string verifyInfo;
    std::vector<std::string> funcParamTypeInfo;
    Visible_Block_type block_type;

    Block* nextLogicBlock{nullptr};

    //================================= predefined func operands =============================
    Block* operand_source1{nullptr};
    Block* operand_source2{nullptr};
    Block* operand_destination{nullptr};
    int arrIndex{-1};               // takeIndGet-Set
    Block* subFunction1{nullptr};   // IF-true / while
    Block* subFunction2{nullptr};   // IF-false
    //================================= predefined func operands =============================

    //================================= User-defined func operands ===========================
    int userFuncOperandsNum{0};
    std::vector<Block*> userFuncOperands;
    //================================= User-defined func operands ===========================

    Block* motherFunc{nullptr};    //under which function (eg main) also known as motherVar
    QPoint block_position{0,0};    //for easier re-draw (not use)
    bool movable{true};            // those definition shouldn't move
};

#endif // VISIBLE_BLOCK_H
