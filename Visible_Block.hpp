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
    bool eventFilter(QObject *, QEvent *event) override;
    void ShowContextMenu(const QPoint& pos);
    void deleteBlock();
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
        setStyleSheet("background-color : white");
//        setStyleSheet("border-style : outset");
//        setStyleSheet("border-width : 1px");
//        setStyleSheet("border-color : black");
        setAutoFillBackground(true);
        setGeometry(QRect(20,20,150,80));
        setVisible(true);
        this->setContextMenuPolicy(Qt::CustomContextMenu);
        installEventFilter(this);
        connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(ShowContextMenu(const QPoint&)));
        block_position = this->pos();
        details = "block name:  " + this->name + " \n" + "mother function:  " + motherFunc->name;
        setBlockText(name);
    }
    void setDetails(std::string detail){details = detail;}
    void setBlockText(std::string text) {this->setText(QString::fromStdString(text));}

private:
    std::string name;
    std::string details;            //context menu show details (default is block name + motherFunc name )
    Visible_Block_type block_type;
    Block* motherFunc{nullptr};    //under which function (eg main)
    QPoint block_position{0,0};    //for easier re-draw
    bool movable{true};            // those definition shouldn't move
};

#endif // VISIBLE_BLOCK_H
