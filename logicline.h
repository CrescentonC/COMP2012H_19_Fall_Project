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
#include "drawpalette.h"

extern void setMainWindowVBPool(std::map<std::string, Visible_Block*>* *ppptr); // for getting the current vb pool of main window

class LogicLine : public QLabel
{
    friend void checkAllLineInPool();
    Q_OBJECT

public:
    LogicLine(QWidget *pa, QPoint stt, QPoint end);

    void checkConnection();
protected:
    QPoint start;

    QPoint end;

    void paintEvent(QPaintEvent *event) override;

    bool eventFilter(QObject*, QEvent *e) override;

};

#endif // LOGICLINE_H
