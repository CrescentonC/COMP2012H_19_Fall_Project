#include "block.h"

Block::Block(QWidget *parent): QLabel {parent} {}

Block::Block(Block *const &p, Block *const &n, QWidget *pa): QLabel {pa}, prev {p}, next {n}
{
    setStyleSheet("border : none");
    setStyleSheet("background-color : yellow");
    setAutoFillBackground(false);
    setGeometry(QRect(20, 20, 150, 80));
    setVisible(true);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    installEventFilter(this);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(ShowContextMenu(const QPoint&)));
}

int Block::run()
{
    if (next)
    {
        return next->run();
    }
    return -1;
}

/**
 * @brief Block::eventFilter
 * @param event
 *  handle 2 situations:
 *  1. left click and drag
 *  2. right click and show a menu
 */
bool Block::eventFilter(QObject *, QEvent *event)
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
    else if(event->type() == QEvent::MouseMove && isHover)
    {
        QMouseEvent*e = static_cast<QMouseEvent*>(event);

        int dx = e->pos().x() - lastPoint.x();
        int dy = e->pos().y() - lastPoint.y();
        int new_x = x() + dx;
        int new_y = y() + dy;

        move(new_x, new_y);
    }
    else if(event->type() == QEvent::MouseButtonRelease && isHover)
    {
        isHover = false;
    }

    return false;
}

void Block::ShowContextMenu(const QPoint& pos)
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

void Block::showDetails()
{
    qDebug()<<"base block show details" << endl;
    QMessageBox showDetailsBox(QMessageBox::Information, "showDetails", "base block show details");
    showDetailsBox.exec();
}

void Block::deleteBlock()
{
    // seems strange...
    this->deleteLater();
}
