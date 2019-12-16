#include "drawpalette.h"
#include "logicline.h"

static std::vector<LogicLine*> linePool;

void checkAllLineInPool()
{
    for (auto i : linePool)
    {
        i->checkConnection();
    }
}

bool removeLine(LogicLine *l)
{
    auto i {std::find(linePool.begin(), linePool.end(), l)};
    if (i != linePool.end())
    {
        linePool.erase(i);
        (*i)->deleteLater();
        return true;
    }
    return false;
}

DrawPalette::DrawPalette(QWidget *pa, QPushButton *myBtn): QLabel(pa), myToggleButton {myBtn}, isPainting {false}
{
    setAutoFillBackground(false);
    setStyleSheet("QLabel { background-color : none; }");
    setVisible(false);
    setMouseTracking(true);
    installEventFilter(this);
}

bool DrawPalette::eventFilter(QObject *, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *e = static_cast<QMouseEvent*>(event);
        if (rect().contains(e->pos())
        && (e->button() == Qt::LeftButton)
        && (e->pos().x() > 24 && (e->pos().y() > 24)))
        {
            if (isPainting)
            {
                isPainting = false;

                LogicLine *l {new LogicLine {parentWidget(), startPoint, currentPoint}};
                linePool.push_back(l);

                myToggleButton->toggle();
                setVisible(false);
                update();
            }
            else
            {
                startPoint = currentPoint = e->pos();
                isPainting = true;
                update();
            }
        }
    }
    else if (event->type() == QEvent::MouseMove && isPainting)
    {
        QMouseEvent *e = static_cast<QMouseEvent*>(event);
        currentPoint = e->pos();
        update();
    }
    return false;
}

void DrawPalette::paintEvent(QPaintEvent *event)
{
    setGeometry(parentWidget()->geometry());

    QLabel::paintEvent(event);
    if (isPainting)
    {
        QPainter painter(this);
        QColor color = Qt::green;
        color.setAlpha(150);
        QPen pen(color);

        pen.setWidth(10);
        painter.setPen(pen);
        painter.drawPoint(startPoint);

        QLineF line(startPoint, currentPoint);
        pen.setWidth(3);
        painter.setPen(pen);
        painter.drawLine(line);
    }
}
