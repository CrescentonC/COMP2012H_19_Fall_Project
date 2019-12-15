#include "Func_Block.hpp"


namespace WriteBackend
{

static ::QPushButton* *runWindowStep {nullptr};
void setRunWindowStep(QPushButton* *ptr) {runWindowStep = ptr;}

std::type_info const &convertToTypeinfo(varType_e _t)
{
    switch(_t)
    {
    case BOOL:
        return typeid(Var_Block<bool>);
    case INT:
        return typeid(Var_Block<int>);
    case DOUBLE:
        return typeid(Var_Block<double>);
    case BOOLARR:
        return typeid(Var_Block<bool*>);
    case INTARR:
        return typeid(Var_Block<int*>);
    case DOUBLEARR:
        return typeid(Var_Block<double*>);
    default:
        return typeid(Invalid_type);
    }
}

Func_Block::Func_Block(std::string name, unsigned int numOfParam, BuiltInRunFunc_helper_base *runFunc): Block {name},
                                                                                                        myRunFunc {runFunc},
                                                                                                        numOfParams {numOfParam},
                                                                                                        myParams {numOfParams ? new Param_info_t [numOfParams] : nullptr},
                                                                                                        myBody {} {}


bool Func_Block::isStepping {false};

void Func_Block::set_isStepping(bool v)
{
    Func_Block::isStepping = v;
}

Func_Block::~Func_Block()
{
    for (auto i : myBody)
    {
        if (i.bodyFuncs[0].args) delete [] i.bodyFuncs[0].args;
        if (i.bodyFuncs[1].args) delete [] i.bodyFuncs[1].args;
    } // NOTE  wierd... but seems that only delete these things here will not cause problem....
    if (myParams) delete [] myParams;
}

inline bool Func_Block::typeCheck(std::type_info const &info, varType_e const &type_e) // check whether the var 'info' is valid according to the type_e
{
    return ((type_e == varType_e::ANYTYPE) ||
            ((type_e == varType_e::NUMTYPE) && ((info == convertToTypeinfo(varType_e::INT)) || (info == convertToTypeinfo(varType_e::DOUBLE)))) ||
            ((type_e == varType_e::NUMARRTYPE) && ((info == convertToTypeinfo(varType_e::INTARR)) || (info == convertToTypeinfo(varType_e::DOUBLEARR)))) ||
            (info == convertToTypeinfo(type_e)) ||
            ((type_e == varType_e::ARRTYPE) && ((info == convertToTypeinfo(varType_e::INTARR)) || (info == convertToTypeinfo(varType_e::BOOLARR)) || (info == convertToTypeinfo(varType_e::DOUBLEARR)))) ||
            ((type_e == varType_e::NONARRTYPE) && ((info == convertToTypeinfo(varType_e::INT)) || (info == convertToTypeinfo(varType_e::DOUBLE)) || (info == convertToTypeinfo(varType_e::BOOL))))
           );
}

void Func_Block::setParamType(varType_e t, int which)
{
    myParams[which].argType = t;
}

bool Func_Block::setRealArg(Block* b, int which)
{
    std::type_info const& info {typeid(*b)};
    if (typeCheck(info, myParams[which].argType)) // typecheck
    {
        myParams[which].realArg = b;
        return true;
    }
    std::cerr << "type wrong in " << __PRETTY_FUNCTION__ << std::endl;
    return false;
}

void Func_Block::clearMyBody()
{
    myBody.clear();
}

void Func_Block::setNextBody(bodyType_e type, Block* *condition, Func_Block *func1, Func_Block *func2) // set the next "line" of code which the user write
{
    if (
            (!func1) ||
            ( (type == bodyType_e::IF) && ((!condition) || (!(*condition)) || (typeid(**condition) != typeid(Var_Block<bool>))) ) ||
            (myRunFunc) ||
            (type == bodyType_e::ERROR)
       )
    {
        std::cerr << "type wrong in " << __PRETTY_FUNCTION__ << std::endl;
        return;
    }
    myBody.push_back({});
    (myBody.back()).statType = type;
    (myBody.back()).condition = condition;
    (((myBody.back()).bodyFuncs)[0]).func = func1;
    (((myBody.back()).bodyFuncs)[0]).args = new Block** [func1->numOfParams];
    if (func2) // only for the if block, the func2 is not nullptr
    {
        (((myBody.back()).bodyFuncs)[1]).func = func2;
        (((myBody.back()).bodyFuncs)[1]).args = new Block** [func2->numOfParams];
    }
}

bool Func_Block::setNextBodyParam(unsigned int whichParam, int val, unsigned int whichFunc) // set the parameters for the fucntion callings in next "line"
{
    // NOTE this function should be called right after the previous function to ensure the correctness
    if ((whichParam < myBody.back().bodyFuncs[whichFunc].func->numOfParams) && whichFunc < 2)
    {
        if ( typeCheck(convertToTypeinfo(myParams[val].argType), ((myBody.back().bodyFuncs[whichFunc]).func->myParams[whichParam].argType)) )
        {
            // std::cout << name << " set " << myBody.back().bodyFuncs[whichFunc].func->name << " " << whichParam << " " << &(myParams[val].realArg) << std::endl;
            (myBody.back().bodyFuncs[whichFunc]).args[whichParam] = &(myParams[val].realArg);
            return true;
        }
    }
    std::cerr << "type wrong in " << __PRETTY_FUNCTION__ << std::endl;
    return false;
}

bool Func_Block::setNextBodyParam(unsigned int whichParam, Block** ref, unsigned int whichFunc) // set the parameters for the function callings in the next "line", just another interface which allow user to ref to global var
{
    if (!ref) return true;
    // NOTE this function should be called right after the previous funciton called to ensure the correctness
    if ((whichParam < myBody.back().bodyFuncs[whichFunc].func->numOfParams) && whichFunc < 2)
    {
        if ( typeCheck(typeid(**ref), myBody.back().bodyFuncs[whichFunc].func->myParams[whichParam].argType) )
        {
            // std::cout << name << " set " << myBody.back().bodyFuncs[whichFunc].func->name << " " << whichParam << " " << *ref << std::endl;
            (myBody.back().bodyFuncs[whichFunc]).args[whichParam] = ref;
            return true;
        }
    }
    std::cerr << "type wrong in " << __PRETTY_FUNCTION__ << std::endl;
    return false;
}

void Func_Block::runFunc(FuncBody_info_t &toRun, int which)
{
    // step 1, set the param for the next properly, no typeCheck here but should be fine since we have already checked type previously
    std::cout << name << " calling " << toRun.bodyFuncs[which].func->name << std::endl;

    // step 1.5: dealing with stepping
    if (Func_Block::isStepping)
    {
        QEventLoop el;
        QObject::connect(*runWindowStep, &QPushButton::clicked, &el, &QEventLoop::quit);
        el.exec();
    }

    Param_info_t *temp = toRun.bodyFuncs[which].func->numOfParams ? new Param_info_t [toRun.bodyFuncs[which].func->numOfParams] : nullptr;
    for (unsigned int i {0}; i < (toRun.bodyFuncs[which].func->numOfParams); ++i)
    {
        // std::cout << ((toRun.bodyFuncs[which]).args[i]) << " " << (((toRun.bodyFuncs[which]).args[i]) ? *((toRun.bodyFuncs[which]).args[i]) : nullptr) << std::endl;
        temp[i].argType = (((toRun.bodyFuncs[which]).func)->myParams[i]).argType;
        temp[i].realArg = (toRun.bodyFuncs[which].func->myParams[i]).realArg;
        (toRun.bodyFuncs[which].func->myParams[i]).realArg = ((toRun.bodyFuncs[which]).args[i]) ? *((toRun.bodyFuncs[which]).args[i]) : nullptr;
    }

    // step 2, run the proper next properly
    toRun.bodyFuncs[which].func->run();

    // step 3, reset the param of the func being runned
    for (unsigned int i {0}; i < (toRun.bodyFuncs[which].func->numOfParams); ++i)
    {
        (toRun.bodyFuncs[which].func->myParams[i]).realArg = temp[i].realArg;
    }
    if (temp) { delete [] temp; }
}

void Func_Block::run()
{
    if (myRunFunc)
    {
        myRunFunc->operator()(this);
        return;
    }
    for (auto i : myBody)
    {
        switch(i.statType)
        {
        case bodyType_e::FUNCCALL:
            runFunc(i);
            break;
        case bodyType_e::WHILE:
            while((**(i.condition)).val._bool) { runFunc(i); }
            break;
        case bodyType_e::IF:
            if ((**(i.condition)).val._bool) { runFunc(i, 0); }
            else { runFunc(i, 1); }
            break;
        case bodyType_e::ERROR:
        default:
            std::cerr << "something wrong at " << name << std::endl;
            exit(-1);
        }
    }
}

void Func_Block::show_val() {}

} // namespace WriteBackend
