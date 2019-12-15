#include "Visible_Block.hpp"
#include "QImage"
#include "QPainter"
#include "QPen"

//void Visible_Block::paintEvent(QPaintEvent * event)
//{
//    QLabel::paintEvent(event);

//    QImage image(QString::fromStdString(":/Resources/rect.png"));

//    setPixmap(QPixmap::fromImage(image));
////    setVisible(true);
//}

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
    QAction action3("Operand1", this);
    connect(&action3, SIGNAL(triggered()), this, SLOT(setSource1_()));
    QAction action4("Operand2", this);
    connect(&action4, SIGNAL(triggered()), this, SLOT(setSource2_()));
    QAction action5("Destination", this);
    connect(&action5, SIGNAL(triggered()), this, SLOT(setDestination_()));
    myMenu.addAction(&action1);
    myMenu.addAction(&action2);
    myMenu.addAction(&action3);
    myMenu.addAction(&action4);
    myMenu.addAction(&action5);
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

void Visible_Block::setSource1_() {};
void Visible_Block::setSource2_() {};
void Visible_Block::setDestination_() {};

bool Visible_Block::currentBlockVerify()
{
    std::string info_wrong = "\nlack second source operand";
    std::string info_right = "\nverify ok";
    if(block_type != ASSIGNMENT &&
       block_type != NOT &&
       block_type != USER_VAR &&
       block_type != USER_FUNC &&
       block_type != IF &&
       operand_source2 == nullptr)
    {
        details += info_wrong;
        return false;
    }
    else
    {
        if(details.find("\nlack second source operand"))
        {
            details = details.substr(0, details.size()-info_wrong.size());
            details += info_right;
            return true;
        }
    }
    return false; //will not reach here
}
