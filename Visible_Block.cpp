#include "Visible_Block.hpp"
#include "QImage"
#include "QPainter"
#include "QPen"
#include "QInputDialog"
#include "dataStorage.hpp"
#include <typeinfo>

using namespace dataStorage;

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
            if(block_type == USER_FUNC)
            {
                emit user_func_clicked(name);
            }
        }

        if(rect().contains(e->pos()) && e->button() == Qt::RightButton)
        {
            emit customContextMenuRequested(e->pos());
        }
    }
    else if(event->type() == QEvent::MouseMove && isHover)
    {
        QMouseEvent*e = static_cast<QMouseEvent*>(event);

        if(movable)
        {
            int dx = e->pos().x() - lastPoint.x();
            int dy = e->pos().y() - lastPoint.y();
            int new_x = x() + dx;
            int new_y = y() + dy;

            move(new_x, new_y);
            block_position = this->pos();
        }
    }
    else if(event->type() == QEvent::MouseButtonRelease)
    {
        if(isHover) isHover = false;
    }

    return false;
}

void Visible_Block::ShowContextMenu(const QPoint& pos)
{
    QMenu myMenu("my menu", this);

    myMenu.addAction(tr("Delete"), this, SLOT(deleteBlock()));
    myMenu.addAction(tr("Details"), this, SLOT(showDetails()));

    if(block_type == Visible_Block_type::AND ||
            block_type == Visible_Block_type::BIGGERTHAN ||
            block_type == Visible_Block_type::DIVISION ||
            block_type == Visible_Block_type::EQUALCOMPARE ||
            block_type == Visible_Block_type::MINUS ||
            block_type == Visible_Block_type::MULTIPLY ||
            block_type == Visible_Block_type::OR ||
            block_type == Visible_Block_type::PLUS ||
            block_type == Visible_Block_type::SMALLERTHAN)
    {
        myMenu.addAction(tr("Operand1"), this, SLOT(setSource1()));
        myMenu.addAction(tr("Operand2"), this, SLOT(setSource2()));
        myMenu.addAction(tr("Destination"), this, SLOT(setDestination()));
    }

    else if(block_type == Visible_Block_type::ASSIGNMENT ||
            block_type == Visible_Block_type::NOT)
    {
        myMenu.addAction(tr("Operand1"), this, SLOT(setSource1()));
        myMenu.addAction(tr("Destination"), this, SLOT(setDestination()));
    }

    else if(block_type == Visible_Block_type::TAKEINDGET ||
            block_type == Visible_Block_type::TAKEINDSET)
    {
        myMenu.addAction(tr("Array name"), this, SLOT(setSource1()));
        myMenu.addAction(tr("Array Index"), this, SLOT(setArrInd()));
        myMenu.addAction(tr("Destination"), this, SLOT(setDestination()));
    }

    else if(block_type == Visible_Block_type::IF)
    {
        myMenu.addAction(tr("Bool Operand"), this, SLOT(setSource1()));
        myMenu.addAction(tr("IF true"), this, SLOT(setSubFunc1()));
        myMenu.addAction(tr("IF false"), this, SLOT(setSubFunc2()));
    }

    else if(block_type == Visible_Block_type::WHILE)
    {
        myMenu.addAction(tr("Bool Operand"), this, SLOT(setSource1()));
        myMenu.addAction(tr("Loop Func"),this, SLOT(setSubFunc1()));
    }

    else if(block_type == Visible_Block_type::USER_FUNC)
    {
        myMenu.addAction(tr("Edit Function"), this, SLOT(editFunc()));
    }

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
    emit visible_block_delete(name);
    this->deleteLater();
}

void Visible_Block::setSource1()
{
    QString inputText = QInputDialog::getText(this, "Destination", "destination variable name",
                                              QLineEdit::Normal, "VAR2333");
    std::string inputName = inputText.toStdString();

    std::map<std::string, WriteBackend::Block*>::iterator iter;
    iter = var_pool.find(inputName);
    if(iter != var_pool.end())
    {
        operand_source1 = var_pool[inputName];
    }
}

void Visible_Block::setSource2()
{
    QString inputText = QInputDialog::getText(this, "Destination", "destination variable name",
                                              QLineEdit::Normal, "VAR2333");
    std::string inputName = inputText.toStdString();

    std::map<std::string, WriteBackend::Block*>::iterator iter;
    iter = var_pool.find(inputName);
    if(iter != var_pool.end())
    {
        operand_source2 = var_pool[inputName];
    }
}

void Visible_Block::setDestination()
{
    QString inputText = QInputDialog::getText(this, "Destination", "destination variable name",
                                              QLineEdit::Normal, "VAR2333");
    std::string inputName = inputText.toStdString();

    std::map<std::string, WriteBackend::Block*>::iterator iter;
    iter = var_pool.find(inputName);
    if(iter != var_pool.end())
    {
        operand_destination = var_pool[inputName];
    }
}

void Visible_Block::setArrInd()
{
    int inputValue = QInputDialog::getInt(this, "Array Index", "array index:",0, 0);
    if(operand_source1 != nullptr)
    {
        if(typeid(*operand_source1) == typeid(Var_Block<bool*>))
        {
            if(static_cast<unsigned int>(inputValue) < static_cast<Var_Block<bool*>*>(operand_source1)->getSize())
            {
                arrIndex = inputValue;
            }
        }
        if(typeid(*operand_source1) == typeid(Var_Block<int*>))
        {
            if(static_cast<unsigned int>(inputValue) < static_cast<Var_Block<int*>*>(operand_source1)->getSize())
            {
                arrIndex = inputValue;
            }
        }
        if(typeid(*operand_source1) == typeid(Var_Block<double*>))
        {
            if(static_cast<unsigned int>(inputValue) < static_cast<Var_Block<double*>*>(operand_source1)->getSize())
            {
                arrIndex = inputValue;
            }
        }
    }
}

void Visible_Block::setSubFunc1()
{
    QString inputText = QInputDialog::getText(this, "SubFunction1", "function name",
                                              QLineEdit::Normal, "FUNC2333");
    std::string inputName = inputText.toStdString();

    std::map<std::string, WriteBackend::Block*>::iterator iter;
    iter = func_pool.find(inputName);
    if(iter != func_pool.end())
    {
        subFunction1 = func_pool[inputName];
    }
}

void Visible_Block::setSubFunc2()
{
    QString inputText = QInputDialog::getText(this, "SubFunction2", "function name",
                                              QLineEdit::Normal, "FUNC2333");
    std::string inputName = inputText.toStdString();

    std::map<std::string, WriteBackend::Block*>::iterator iter;
    iter = func_pool.find(inputName);
    if(iter != func_pool.end())
    {
        subFunction2 = func_pool[inputName];
    }
}

void Visible_Block::editFunc()
{
    emit user_func_edit(name);
}

bool Visible_Block::currentBlockVerify()
{
    std::string info_wrong = "\nlack second source operand";
    std::string info_right = "\nverify ok";
    bool status = false;
    if(block_type == Visible_Block_type::AND ||
            block_type == Visible_Block_type::BIGGERTHAN ||
            block_type == Visible_Block_type::DIVISION ||
            block_type == Visible_Block_type::EQUALCOMPARE ||
            block_type == Visible_Block_type::MINUS ||
            block_type == Visible_Block_type::MULTIPLY ||
            block_type == Visible_Block_type::OR ||
            block_type == Visible_Block_type::PLUS ||
            block_type == Visible_Block_type::SMALLERTHAN)
    {
        if(operand_source1 == nullptr ||
                operand_source2 == nullptr ||
                operand_destination == nullptr)
            status = false;
    }

    else if(block_type == Visible_Block_type::ASSIGNMENT ||
            block_type == Visible_Block_type::NOT)
    {
        if(operand_source1 == nullptr ||
           operand_source2 == nullptr)
        status = false;
    }

    else if(block_type == Visible_Block_type::TAKEINDGET ||
            block_type == Visible_Block_type::TAKEINDSET)
    {
        if(operand_source1 == nullptr ||
           arrIndex == -1 ||
           operand_destination == nullptr)
        status = false;
    }

    else if(block_type == Visible_Block_type::IF||
            block_type == Visible_Block_type::WHILE)
    {
        if(operand_source1 == nullptr || subFunction1 == nullptr)
            status = false;
        if(block_type == Visible_Block_type::IF && subFunction2 == nullptr)
            status = false;
    }


    if(status == false)
    {
        details += info_wrong;
        setStyleSheet("background-color : red");
        return false;
    }
    else
    {
        if(details.find("\nlack second source operand"))
        {
            details = details.substr(0, details.size()-info_wrong.size());
            details += info_right;
            setStyleSheet("background-color : white");
            return true;
        }
    }
    return false; //will not reach here
}
