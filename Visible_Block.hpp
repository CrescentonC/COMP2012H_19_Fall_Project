#ifndef VISIBLE_BLOCK_H
#define VISIBLE_BLOCK_H

#include <QLabel>
#include <QEvent>
#include <QMenu>
#include <QMouseEvent>
#include <QDebug>
#include <QMessageBox>
#include "Block.hpp"
using namespace WriteBackend;

enum Visible_Block_type{
    USER_VAR,
    USER_FUNC,
    AND,
    ASSIGNMENT,
    BIGGERTHAN,
    DIVISION,
    //END,
    EQUALCOMPARE,
    //FOR,
    IF,
    MINUS,
    MULTIPLY,
    NOT,
    OR,
    PLUS,
    PRINT,
    SMALLERTHAN,
    //START,
    TAKEIND,
    WHILE
};

// not inherit from Block
class Visible_Block : public QLabel
{
    Q_OBJECT

protected slots:
//    void paintEvent(QPaintEvent *) override;
    bool eventFilter(QObject *, QEvent *event) override;
    void ShowContextMenu(const QPoint& pos);
    void deleteBlock();
    void setSource1_();
    void setSource2_();
    void setDestination_();
    virtual void showDetails(); //show belong to which function

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
    void setDetails(std::string detail){details = detail;}
    void setBlockText(std::string text) {this->setText(QString::fromStdString(text));}
    void setSource1(Block* source1){operand_source1 = source1;}
    void setSource2(Block* source2){operand_source2 = source2;}
    void setDestination(Block* destination){operand_destination = destination;}
    void setMother(Block* mother){motherFunc = mother;}
    bool currentBlockVerify(void);  //verify whether correct ammount of operands

private:
    std::string name;
    std::string details;            //context menu show details (default is block name + motherFunc name )
    Visible_Block_type block_type;
    Block* operand_source1{nullptr};
    Block* operand_source2{nullptr};
    Block* operand_destination{nullptr};
//    void* operand_destination2{nullptr};    //only for "IF" second block
    Block* motherFunc{nullptr};    //under which function (eg main) also known as motherVar
    QPoint block_position{0,0};    //for easier re-draw
    bool movable{true};            // those definition shouldn't move
};

#endif // VISIBLE_BLOCK_H
