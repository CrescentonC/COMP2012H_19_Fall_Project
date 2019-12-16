#include "Visible_Block.hpp"
#include "QImage"
#include "QPainter"
#include "QPen"
#include "QInputDialog"
#include "dataStorage.hpp"
#include <typeinfo>
#include "QDebug"
#include "drawpalette.h"

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
        checkAllLineInPool();
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

    else if(block_type == Visible_Block_type::USER_FUNC && !movable)
    {
        myMenu.addAction(tr("Edit Function"), this, SLOT(editFunc()));
    }

    else if(block_type == Visible_Block_type::USER_FUNC && movable)
    {
        myMenu.addAction("Operand Modify", this, SLOT(setUserFuncOperands()));
    }

    myMenu.exec(mapToGlobal(pos));
}

void Visible_Block::showDetails()
{
    currentBlockVerify();
    details = "block name: " + name + "\nMother: " + motherFunc->name;
    if(block_type == USER_FUNC)
    {
        details += "\nparam typeInfo: ";
        for(std::vector<std::string>::iterator paramTypeIter = funcParamTypeInfo.begin();
            paramTypeIter != funcParamTypeInfo.end();
            paramTypeIter++)
        {
            details += *paramTypeIter + " ";
        }
    }
    if(block_type != USER_VAR) details += "\nVerify Info" + verifyInfo;
    else
    {
        std::string typeName;
        if(typeid(*motherFunc) == typeid(Var_Block<bool>)) typeName = "bool";
        else if(typeid(*motherFunc) == typeid(Var_Block<int>)) typeName = "int";
        else if(typeid(*motherFunc) == typeid(Var_Block<double>)) typeName = "double";
        else if(typeid(*motherFunc) == typeid(Var_Block<bool*>)) typeName = "bool arr";
        else if(typeid(*motherFunc) == typeid(Var_Block<int*>)) typeName = "int arr";
        else if(typeid(*motherFunc) == typeid(Var_Block<double*>)) typeName = "double arr";
        details += "\nVar type : " + typeName;
    }
    QMessageBox showDetailsBox(QMessageBox::Information, "showDetails",QString::fromStdString(details));
    showDetailsBox.exec();
}

void Visible_Block::deleteBlock()
{
    // seems strange...
    emit visible_block_delete(name);
    this->deleteLater();
    checkAllLineInPool();
}

void Visible_Block::setSource1()
{
    QString inputText = QInputDialog::getText(this, "Source1", "source1 variable name",
                                              QLineEdit::Normal, "VAR2333");
    std::string inputName = inputText.toStdString();

    std::map<std::string, WriteBackend::Block*>::iterator iter;
    iter = var_pool.find(inputName);
    if(iter != var_pool.end())
    {
        operand_source1 = var_pool[inputName];
    }
    else
    {
        QMessageBox warningBox(QMessageBox::Information, "warning",
                               QString::fromStdString(inputName + " does not exist\nsource 1 unchanged"));
        warningBox.exec();
    }
    currentBlockVerify();
}


void Visible_Block::setSource2()
{
    QString inputText = QInputDialog::getText(this, "Source2", "source2 variable name",
                                              QLineEdit::Normal, "VAR2333");
    std::string inputName = inputText.toStdString();

    std::map<std::string, WriteBackend::Block*>::iterator iter;
    iter = var_pool.find(inputName);
    if(iter != var_pool.end())
    {
        operand_source2 = var_pool[inputName];
    }
    else
    {
        QMessageBox warningBox(QMessageBox::Information, "warning",
                               QString::fromStdString(inputName + " does not exist\nsource 2 unchanged"));
        warningBox.exec();
    }
    currentBlockVerify();
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
    else
    {
        QMessageBox warningBox(QMessageBox::Information, "warning",
                               QString::fromStdString(inputName + " does not exist\n Destination unchanged"));
        warningBox.exec();
    }
    currentBlockVerify();
}



void Visible_Block::setArrInd()
{
    int inputValue = QInputDialog::getInt(this, "Array Index", "array index:",0, 0);

    //====================fake a int var=============================
    std::string fake_name = getAvailNameFake();
    var_pool[fake_name] = new Var_Block<int>(fake_name, inputValue);
    indexFakeName = fake_name;
    //====================fake a int var=============================

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
    if(arrIndex != inputValue)
    {
        QMessageBox warningBox(QMessageBox::Information, "warning",
                               QString::fromStdString(std::to_string(inputValue) + " is invalid,\narray index unchanged"));
        warningBox.exec();
    }

    currentBlockVerify();
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
    else
    {
        QMessageBox warningBox(QMessageBox::Information, "warning",
                               QString::fromStdString(inputName + " does not exist\n subFunction1 unchanged"));
        warningBox.exec();
    }
    currentBlockVerify();
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
    else
    {
        QMessageBox warningBox(QMessageBox::Information, "warning",
                               QString::fromStdString(inputName + " does not exist\n subFunction2 unchanged"));
        warningBox.exec();
    }
    currentBlockVerify();
}

void Visible_Block::setUserFuncOperands(int pos)
{
    //=============================== get postion =======================================
    if(pos < 0)
    {
        pos = QInputDialog::getInt(this, "Set Operands", "Operands position(start from 0):",0, 0);
    }
    //=============================== get postion =======================================

    //=============== fill up at first time, prevent retrieve vector null iter ==========
    if(userFuncOperands.empty())
    {
        for(int i = 0; i < userFuncOperandsNum; i++)
            userFuncOperands.push_back(nullptr);
    }
    //=============== fill up at first time, prevent retrieve vector null iter ==========

    std::vector<Block*>::iterator operIter = userFuncOperands.begin() + pos;

    QString inputText = QInputDialog::getText(this, "Set Operands", "Setting Operand #" + QString::number(pos),
                                              QLineEdit::Normal, "VAR2333");
    std::string inputName = inputText.toStdString();

    std::map<std::string, WriteBackend::Block*>::iterator iter;
    iter = var_pool.find(inputName);
    if(iter != var_pool.end())
    {
        // replace the origin operand with the new operand
        std::replace(operIter, operIter+1, *operIter, var_pool[inputName]);
    }
    else
    {
        QMessageBox warningBox(QMessageBox::Information, "warning",
                               QString::fromStdString(inputName + " does not exist\n" +
                                                      "Setting Operand #" + std::to_string(pos) + " unchanged"));
        warningBox.exec();
    }
    userFuncOperands.shrink_to_fit();
    currentBlockVerify();
}

void Visible_Block::setUserFuncOperandsT(int pos)
{
    //=============================== get postion =======================================
    if(pos < 0)
    {
        pos = QInputDialog::getInt(this, "Set OperandsT", "OperandsT position(start from 0):",0, 0);
    }
    //=============================== get postion =======================================

    //=============== fill up at first time, prevent retrieve vector null iter ==========
    if(userFuncOperandsT.empty())
    {
        for(int i = 0; i < userFuncOperandsNumT; i++)
            userFuncOperandsT.push_back(nullptr);
    }
    //=============== fill up at first time, prevent retrieve vector null iter ==========

    std::vector<Block*>::iterator operIter = userFuncOperandsT.begin() + pos;

    QString inputText = QInputDialog::getText(this, "Set OperandsT", "Setting Operand #" + QString::number(pos),
                                              QLineEdit::Normal, "VAR2333");
    std::string inputName = inputText.toStdString();

    std::map<std::string, WriteBackend::Block*>::iterator iter;
    iter = var_pool.find(inputName);
    if(iter != var_pool.end())
    {
        // replace the origin operand with the new operand
        std::replace(operIter, operIter+1, *operIter, var_pool[inputName]);
    }
    else
    {
        QMessageBox warningBox(QMessageBox::Information, "warning",
                               QString::fromStdString(inputName + " does not exist\n" +
                                                      "Setting Operand #" + std::to_string(pos) + " unchanged"));
        warningBox.exec();
    }
    userFuncOperandsT.shrink_to_fit();
    currentBlockVerify();
}

void Visible_Block::setUserFuncOperandsF(int pos)
{
    //=============================== get postion =======================================
    if(pos < 0)
    {
        pos = QInputDialog::getInt(this, "Set OperandsF", "OperandsT position(start from 0):",0, 0);
    }
    //=============================== get postion =======================================

    //=============== fill up at first time, prevent retrieve vector null iter ==========
    if(userFuncOperandsF.empty())
    {
        for(int i = 0; i < userFuncOperandsNumF; i++)
            userFuncOperandsF.push_back(nullptr);
    }
    //=============== fill up at first time, prevent retrieve vector null iter ==========

    std::vector<Block*>::iterator operIter = userFuncOperandsF.begin() + pos;

    QString inputText = QInputDialog::getText(this, "Set OperandsF", "Setting Operand #" + QString::number(pos),
                                              QLineEdit::Normal, "VAR2333");
    std::string inputName = inputText.toStdString();

    std::map<std::string, WriteBackend::Block*>::iterator iter;
    iter = var_pool.find(inputName);
    if(iter != var_pool.end())
    {
        // replace the origin operand with the new operand
        std::replace(operIter, operIter+1, *operIter, var_pool[inputName]);
    }
    else
    {
        QMessageBox warningBox(QMessageBox::Information, "warning",
                               QString::fromStdString(inputName + " does not exist\n" +
                                                      "Setting Operand #" + std::to_string(pos) + " unchanged"));
        warningBox.exec();
    }
    userFuncOperandsF.shrink_to_fit();
    currentBlockVerify();
}

void Visible_Block::editFunc()
{
    emit user_func_edit(name);
}

bool Visible_Block::currentBlockVerify()
{
    std::string info_wrong = "\nlack components:";
    std::string info_right = "\nverify ok";
    bool status = true;
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
        if(operand_source1 == nullptr) info_wrong += "\n lack Operand 1";
        if(operand_source2 == nullptr) info_wrong += "\n lack Operand 2";
        if(operand_destination == nullptr) info_wrong += "\n lack Destination";
    }

    else if(block_type == Visible_Block_type::ASSIGNMENT ||
            block_type == Visible_Block_type::NOT)
    {
        if(operand_source1 == nullptr ||
           operand_destination == nullptr)
        status = false;
        if(operand_source1 == nullptr) info_wrong += "\n lack Operand 1";
        if(operand_destination == nullptr) info_wrong += "\n lack Destination";
    }

    else if(block_type == Visible_Block_type::TAKEINDGET ||
            block_type == Visible_Block_type::TAKEINDSET)
    {
        if(operand_source1 == nullptr ||
           arrIndex == -1 ||
           operand_destination == nullptr)
        status = false;
        if(operand_source1 == nullptr) info_wrong += "\n lack Operand 1";
        if(operand_destination == nullptr) info_wrong += "\n lack Destination";
        if(arrIndex == -1) info_wrong += "\n lack arrIndex";
    }

    else if(block_type == Visible_Block_type::IF)
    {
        if(operand_source1 == nullptr || subFunction1 == nullptr || subFunction2 == nullptr)
        {
            status = false;
            if(operand_source1 == nullptr) info_wrong += "\n lack Operand 1";
            if(subFunction1 == nullptr) info_wrong += "\n lack subFunction 1";
            if(subFunction2 == nullptr) info_wrong += "\n lack subFunction 2";
        }

        std::vector<Block*>::iterator operIter = userFuncOperandsT.begin();
        for(int i=0; operIter != userFuncOperandsT.end(); ++operIter)
        {
            if(*operIter == nullptr)
            {
                info_wrong += "\n lack "+std::to_string(i)+"-th operand in subfunction True";
                status = false;
            }
            i++;
        }

        std::vector<Block*>::iterator operIter2 = userFuncOperandsF.begin();
        for(int i=0; operIter2 != userFuncOperandsF.end(); ++operIter2)
        {
            if(*operIter2 == nullptr)
            {
                info_wrong += "\n lack "+std::to_string(i)+"-th operand in subfunction False";
                status = false;
            }
            i++;
        }
    }

    else if(block_type == Visible_Block_type::WHILE)
    {
        if(operand_source1 == nullptr || subFunction1 == nullptr)
        {
            status = false;
            if(operand_source1 == nullptr) info_wrong += "\n lack Operand 1";
            if(subFunction1 == nullptr) info_wrong += "\n lack subFunction 1";
        }

        std::vector<Block*>::iterator operIter = userFuncOperandsT.begin();
        for(int i=0; operIter != userFuncOperandsT.end(); ++operIter)
        {
            if(*operIter == nullptr)
            {
                info_wrong += "\n lack "+std::to_string(i)+"-th operand in subfunction";
                status = false;
            }
            i++;
        }
    }

    else if(block_type == Visible_Block_type::USER_FUNC && movable)
    {
        std::vector<Block*>::iterator operIter = userFuncOperands.begin();
        for(int i = 0; i < userFuncOperandsNum; i++)
        {
            if(*operIter == nullptr)
            {
                info_wrong += "\n lack "+std::to_string(i)+"-th operand";
                status = false;
            }
            operIter++;
        }
    }

    else if(block_type == Visible_Block_type::PRINT)
    {
        if(operand_source1 == nullptr) status = false;
        info_wrong += "\n lack Operand1";
    }


    if(status == false)
    {
        verifyInfo = info_wrong;
        setStyleSheet("background-color : #e34646");
        return false;
    }
    else
    {
        verifyInfo = info_right;
        setStyleSheet("background-color : white");
        return true;
    }
}

std::string Visible_Block::getAvailNameFake()
{
    int id = 0;
    std::string availableName;
    do{
        availableName = "Ind_" + std::to_string(id);
        id++;
    }while(var_pool.count(availableName));
    return availableName;
}

std::string Visible_Block::getUserFuncITHOperName(int index)
{
    return userFuncOperands.at(index)->name;
}

std::string Visible_Block::getUserFuncITHOperNameT(int index)
{
    return userFuncOperandsT.at(index)->name;
}

std::string Visible_Block::getUserFuncITHOperNameF(int index)
{
    return userFuncOperandsF.at(index)->name;
}
