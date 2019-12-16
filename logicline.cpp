#include "logicline.h"

LogicLine::LogicLine(QWidget *pa, QPoint stt, QPoint end) : QLabel(pa), start {stt}, end {end}
{
    setStyleSheet("border : none");
    setStyleSheet("background-color : none");
    setAutoFillBackground(false);
    setGeometry(QRect(20, 20, 150, 80));
    setVisible(true);
    installEventFilter(this);

    QPoint lefttop;

    lefttop.setX(std::max(0, std::min(stt.x(), end.x()) - 10));
    lefttop.setY(std::max(0, std::min(stt.y(), end.y()) - 10));

    int width = abs(stt.x() - end.x()) + 20;
    int height = abs(stt.y() - end.y()) + 20;

    setGeometry(QRect(lefttop.x(), lefttop.y(), width, height));

    start = stt - lefttop;
    this->end = end - lefttop;



    update();
}

void LogicLine::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);
    QPixmap image(size());

    image.fill(Qt::transparent);

    QPainter painter(&image);
    QColor color = Qt::green;
    color.setAlpha(150);
    QPen pen(color);

    pen.setWidth(10);
    painter.setPen(pen);
    painter.drawPoint(start);
    painter.drawPoint(end);

    QLineF line(start, end);
    pen.setWidth(3);
    painter.setPen(pen);
    painter.drawLine(line);

    setPixmap(image);
    setMask(image.mask());
}

bool LogicLine::eventFilter(QObject *, QEvent *event)
{
    static QPoint lastPoint;
    static bool isHover = false;
    if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *e = static_cast<QMouseEvent*>(event);
        if (rect().contains(e->pos())
                && e->button() == Qt::LeftButton)
        {
            lastPoint = e->pos();
            isHover = true;
        }
        if (rect().contains(e->pos()) && e->button() == Qt::RightButton)
        {
            this->deleteLater();
        }
    }
    else if (event->type() == QEvent::MouseMove && isHover)
    {
        QMouseEvent *e = static_cast<QMouseEvent*>(event);
        int dx = e->pos().x() - lastPoint.x();
        int dy = e->pos().y() - lastPoint.y();
        int new_x = x() + dx;
        int new_y = y() + dy;
        move(new_x, new_y);
    }
    else if (event->type() == QEvent::MouseButtonRelease && isHover)
    {
        isHover = false;
    }
    return false;
}
