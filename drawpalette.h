#ifndef DRAWPALETTE_H
#define DRAWPALETTE_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QEvent>
#include <QMouseEvent>
#include <QPainter>
#include "logicline.h"

class DrawPalette : public QLabel
{
public:
    DrawPalette(QWidget *pa, QPushButton *myBtn);

protected slots:
    bool eventFilter(QObject *, QEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

private:
    QPushButton *myToggleButton;

    bool isPainting;

    QPoint startPoint;

    QPoint currentPoint;
};

#endif // DRAWPALETTE_H
