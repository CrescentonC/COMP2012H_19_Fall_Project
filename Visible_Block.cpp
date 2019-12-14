#include "Visible_Block.hpp"

bool Visible_Block::eventFilter(QObject *, QEvent *event)
{
    static QPoint lastPoint;
    static bool isHover = false;

    if(event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *e = static_cast<QMouseEvent*>(event);

        if(rect().contains(e->pos()) && e->button() == Qt::LeftButton)
        {
            lastPoint = e->pos();
            isHover = true;
        }

        if(rect().contains(e->pos()) && e->button() == Qt::RightButton)
        {
            emit customContextMenuRequested(e->pos());
        }
    }
    else if(event->type() == QEvent::MouseMove && isHover && movable)
    {
//        setStyleSheet("background-color : white");
        QMouseEvent*e = static_cast<QMouseEvent*>(event);

        int dx = e->pos().x() - lastPoint.x();
        int dy = e->pos().y() - lastPoint.y();
        int new_x = x() + dx;
        int new_y = y() + dy;

        move(new_x, new_y);
        block_position = this->pos();
    }
    else if(event->type() == QEvent::MouseButtonRelease && isHover && movable)
    {
        isHover = false;
    }

    return false;
}

void Visible_Block::ShowContextMenu(const QPoint& pos)
{
    QMenu myMenu("my menu", this);
    QAction action1("Delete", this);
    connect(&action1, SIGNAL(triggered()), this, SLOT(deleteBlock()));
    QAction action2("Details", this);
    connect(&action2, SIGNAL(triggered()), this, SLOT(showDetails()));
    myMenu.addAction(&action1);
    myMenu.addAction(&action2);
    myMenu.exec(mapToGlobal(pos));
}

void Visible_Block::showDetails()
{
    qDebug()<<"base block show details" << endl;
    QMessageBox showDetailsBox(QMessageBox::Information, "showDetails",QString::fromStdString(details));
    showDetailsBox.exec();
}

void Visible_Block::deleteBlock()
{
    // seems strange...
    this->deleteLater();
}
