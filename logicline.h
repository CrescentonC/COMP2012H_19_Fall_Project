#ifndef LOGICLINE_H
#define LOGICLINE_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QPoint>
#include <QLabel>
#include <QImage>
#include <QBitmap>
#include <iostream>
#include "Visible_Block.hpp"

extern void setMainWindowVBPool(std::map<std::string, Visible_Block*>* *ppptr); // for getting the current vb pool of main window

class LogicLine : public QLabel
{
    Q_OBJECT

public:
    LogicLine(QWidget *pa, QPoint stt, QPoint end);

    void setPrev(Visible_Block *p) {prev = p;}

    void setNext(Visible_Block *n) {next = n;}

    Visible_Block const *getPrev() const {return prev;}

    Visible_Block const *getNext() const {return next;}

protected:
    QPoint start;

    QPoint end;

    Visible_Block *prev;

    Visible_Block *next;

    void paintEvent(QPaintEvent *event) override;

    bool eventFilter(QObject*, QEvent *e) override;

    void checkConnection();
};

#endif // LOGICLINE_H
