#include "Interpreter.hpp"
#include <vector>
#include "Block.hpp"
#include "Var_Block.hpp"

static Func_Block* fakeMap(Visible_Block_type type);

// first main
void dataStorage::interpretAll()
{
    std::map<std::string, WriteBackend::Block*>::iterator funcPoolIter;
    for(funcPoolIter = func_pool.begin();
        funcPoolIter != func_pool.end();
        ++funcPoolIter)
    {
        WriteBackend::Func_Block* processFunc = static_cast<WriteBackend::Func_Block*>(funcPoolIter->second);
        std::map<std::string, Visible_Block*>* processVBPool = correspond_pool[processFunc];
        Visible_Block* processVB = (*processVBPool)["start"];

        bodyType_e nextBodyType;
        while(processVB->getNextBlock() != "notExist")
        {
            processVB = (*processVBPool)[processVB->getNextBlock()];

            switch (processVB->getBlockType())  //total 19(start, user-var no need)
            {
            case Visible_Block_type::IF:
                nextBodyType = bodyType_e::IF;
                processFunc->setNextBody(nextBodyType, &var_pool[processVB->getOperandSource1()->name],
                        static_cast<Func_Block*>(*processVB->getSubFunction1()), static_cast<Func_Block*>(*processVB->getSubFunction2()));
//                processFunc->setNextBodyParam(0, &var_pool[]);
                break;
            case Visible_Block_type::WHILE:
                nextBodyType = bodyType_e::WHILE;
                processFunc->setNextBody(nextBodyType, &var_pool[processVB->getOperandSource1()->name],
                        static_cast<Func_Block*>(*processVB->getSubFunction1()),nullptr);
//                processFunc->setNextBodyParam(0, &var_pool[]);
                break;
            case Visible_Block_type::USER_FUNC:
                nextBodyType = bodyType_e::FUNCCALL;
                processFunc->setNextBody(nextBodyType, nullptr, static_cast<Func_Block*>(func_pool[processVB->getRealFuncName()]), nullptr);
                for(int i = 0; i < processVB->getUserFuncOperandsNum(); i++)
                {
                    processFunc->setNextBodyParam(i, &var_pool[processVB->getUserFuncITHOperName(i)]);
                }
                break;
            case Visible_Block_type::BIGGERTHAN:
            case Visible_Block_type::SMALLERTHAN:
            case Visible_Block_type::EQUALCOMPARE:
            case Visible_Block_type::PLUS:
            case Visible_Block_type::MINUS:
            case Visible_Block_type::DIVISION:
            case Visible_Block_type::MULTIPLY:
            case Visible_Block_type::AND:
            case Visible_Block_type::OR:
                nextBodyType = bodyType_e::FUNCCALL;
                processFunc->setNextBody(nextBodyType, nullptr, fakeMap(processVB->getBlockType()),nullptr);
                processFunc->setNextBodyParam(0, &var_pool[processVB->getDestination()->name]);
                processFunc->setNextBodyParam(1, &var_pool[processVB->getOperandSource1()->name]);
                processFunc->setNextBodyParam(2, &var_pool[processVB->getOperandSource2()->name]);
                break;
            case Visible_Block_type::NOT:
            case Visible_Block_type::ASSIGNMENT:
                nextBodyType = bodyType_e::FUNCCALL;
                processFunc->setNextBody(nextBodyType, nullptr, fakeMap(processVB->getBlockType()),nullptr);
                processFunc->setNextBodyParam(0, &var_pool[processVB->getDestination()->name]);
                processFunc->setNextBodyParam(1, &var_pool[processVB->getOperandSource1()->name]);
                break;
            case Visible_Block_type::TAKEINDGET:
                nextBodyType = bodyType_e::FUNCCALL;
                processFunc->setNextBody(nextBodyType, nullptr, fakeMap(processVB->getBlockType()),nullptr);
                processFunc->setNextBodyParam(0, &var_pool[processVB->getDestination()->name]);
                processFunc->setNextBodyParam(1, &var_pool[processVB->getOperandSource1()->name]);
                processFunc->setNextBodyParam(2, &var_pool[processVB->getIndexFakeName()]);
                break;
            case Visible_Block_type::TAKEINDSET:
                nextBodyType = bodyType_e::FUNCCALL;
                processFunc->setNextBody(nextBodyType, nullptr, fakeMap(processVB->getBlockType()), nullptr);
                processFunc->setNextBodyParam(0, &var_pool[processVB->getDestination()->name]);
                processFunc->setNextBodyParam(1, &var_pool[processVB->getIndexFakeName()]);
                processFunc->setNextBodyParam(2, &var_pool[processVB->getOperandSource1()->name]);
                break;
            case Visible_Block_type::PRINT:
                nextBodyType = bodyType_e::FUNCCALL;
                processFunc->setNextBody(nextBodyType, nullptr, fakeMap(processVB->getBlockType()),nullptr);
                processFunc->setNextBodyParam(0,&var_pool[processVB->getOperandSource1()->name]);
                break;
            }
        }
    }
}


static Func_Block* fakeMap(Visible_Block_type type)
{
    switch (type) {
    case Visible_Block_type::PRINT: return &printBlock;
    case Visible_Block_type::BIGGERTHAN: return &biggerThanBlock;
    case Visible_Block_type::SMALLERTHAN: return &smallerThanBlock;
    case Visible_Block_type::EQUALCOMPARE: return &equalBlock;
    case Visible_Block_type::PLUS: return &plusBlock;
    case Visible_Block_type::MINUS: return &minusBlock;
    case Visible_Block_type::DIVISION: return &divisionBlock;
    case Visible_Block_type::MULTIPLY: return &multiplicationBlock;
    case Visible_Block_type::TAKEINDGET: return &subsBlock_get;
    case Visible_Block_type::TAKEINDSET: return &subsBlock_set;
    case Visible_Block_type::ASSIGNMENT: return &assignmentBlock;
    case Visible_Block_type::AND: return &andBlock;
    case Visible_Block_type::NOT: return &notBlock;
    case Visible_Block_type::OR: return &orBlock;
    default: return nullptr;    // will not arrive here
    }
}
