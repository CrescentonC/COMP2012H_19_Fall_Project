#include "BuiltInOperators.hpp"

namespace WriteBackend
{

static class ForPrintBlock : public BuiltInRunFunc_helper_base
{
    public:
        virtual void operator()(Func_Block *that) override;
} forBuiltInPrint;

static class ForBiggerThanBlock : public BuiltInRunFunc_helper_base
{
    public:
        virtual void operator()(Func_Block *that) override;
} forBuiltInBiggerThan;

static class ForSmallerThanBlock : public BuiltInRunFunc_helper_base
{
    public:
        virtual void operator()(Func_Block *that) override;
} forBuiltInSmallerThan;

static class ForBuiltInEqualBlock : public BuiltInRunFunc_helper_base
{
    public:
        virtual void operator()(Func_Block *that) override;
} forBuiltInEqual;

static class ForPlusBlock : public BuiltInRunFunc_helper_base
{
    public:
        virtual void operator()(Func_Block *that) override;
} forBuiltInPlus;

static class ForMinusBlock : public BuiltInRunFunc_helper_base
{
    public:
        virtual void operator()(Func_Block *that) override;
} forBuiltInMinus;

static class ForDivisionBlock : public BuiltInRunFunc_helper_base
{
    public:
        virtual void operator()(Func_Block *that) override;
} forBuiltInDivision;

static class ForMultiplicationBlock : public BuiltInRunFunc_helper_base
{
    public:
        virtual void operator()(Func_Block *that) override;
} forBuiltInMultiplication;

static class ForSubsGetBlock : public BuiltInRunFunc_helper_base
{
    public:
        virtual void operator()(Func_Block *that) override;
} forBuiltInSubsGet;

static class ForSubsSetBlock : public BuiltInRunFunc_helper_base
{
public:
    virtual void operator()(Func_Block *that) override;
} forBuiltInSubsSet;

static class ForAssignmentBlock : public BuiltInRunFunc_helper_base
{
    public:
        virtual void operator()(Func_Block *that) override;
} forBuiltInAssignment;

static class ForAndBlock : public BuiltInRunFunc_helper_base
{
    public:
        virtual void operator()(Func_Block *that) override;
} forBuiltInAnd;

static class ForOrBlock : public BuiltInRunFunc_helper_base
{
    public:
        virtual void operator()(Func_Block *that) override;
} forBuiltInOr;

static class ForNotBlock : public BuiltInRunFunc_helper_base
{
    public:
        virtual void operator()(Func_Block *that) override;
} forBuiltInNot;

void ForAndBlock::operator()(Func_Block *that)
{
    if (that->numOfParams != 3)
    {
        std::cerr << "built_in func ptr wrong at " << __PRETTY_FUNCTION__ << std::endl;
        return;
    }
    if (that && that->myParams && that->myParams[0].realArg && that->myParams[1].realArg && that->myParams[2].realArg)
    {
        std::type_info const &info0 {typeid(*(that->myParams[0].realArg))};
        std::type_info const &info1 {typeid(*(that->myParams[1].realArg))};
        std::type_info const &info2 {typeid(*(that->myParams[2].realArg))};
        if (info0 == convertToTypeinfo(varType_e::BOOL) && info1 == info2 && info2 == info0)
        {
            (that->myParams[0].realArg)->val._bool = ((that->myParams[1].realArg)->val._bool && (that->myParams[2].realArg)->val._bool);
        }
        else
        {
            std::cerr << "built_in func ptr wrong at " << __PRETTY_FUNCTION__ << std::endl;
            return;
        }
    }
    else
    {
        std::cerr << "built_in func ptr wrong at " << __PRETTY_FUNCTION__ << ": uninitialized real arg" << std::endl;
    }
}

void ForOrBlock::operator()(Func_Block *that)
{
    if (that->numOfParams != 3)
    {
        std::cerr << "built_in func ptr wrong at " << __PRETTY_FUNCTION__ << std::endl;
        return;
    }
    if (that && that->myParams && that->myParams[0].realArg && that->myParams[1].realArg && that->myParams[2].realArg)
    {
        std::type_info const &info0 {typeid(*(that->myParams[0].realArg))};
        std::type_info const &info1 {typeid(*(that->myParams[1].realArg))};
        std::type_info const &info2 {typeid(*(that->myParams[2].realArg))};
        if (info0 == convertToTypeinfo(varType_e::BOOL) && info1 == info2 && info2 == info0)
        {
            (that->myParams[0].realArg)->val._bool = ((that->myParams[1].realArg)->val._bool || (that->myParams[2].realArg)->val._bool);
        }
        else
        {
            std::cerr << "built_in func ptr wrong at " << __PRETTY_FUNCTION__ << std::endl;
            return;
        }
    }
    else
    {
        std::cerr << "built_in func ptr wrong at " << __PRETTY_FUNCTION__ << ": uninitialized real arg" << std::endl;
    }
}

void ForNotBlock::operator()(Func_Block *that)
{
    if (that->numOfParams != 2)
    {
        std::cerr << "built_in func ptr wrong at " << __PRETTY_FUNCTION__ << std::endl;
        return;
    }
    if (that && that->myParams && that->myParams[0].realArg && that->myParams[1].realArg)
    {
        std::type_info const &info0 {typeid(*(that->myParams[0].realArg))};
        std::type_info const &info1 {typeid(*(that->myParams[1].realArg))};
        if (info0 == convertToTypeinfo(varType_e::BOOL) && info1 == info0)
        {
            (that->myParams[0].realArg)->val._bool = !((that->myParams[1].realArg)->val._bool);
        }
        else
        {
            std::cerr << "built_in func ptr wrong at " << __PRETTY_FUNCTION__ << std::endl;
            return;
        }
    }
    else
    {
        std::cerr << "built_in func ptr wrong at " << __PRETTY_FUNCTION__ << ": uninitialized real arg" << std::endl;
    }
}

void ForPrintBlock::operator()(Func_Block *that)
{
    if (that->numOfParams != 1)
    {
        std::cerr << "built_in func ptr wrong at " << __PRETTY_FUNCTION__ << std::endl;
        return;
    }
    if (that && that->myParams && that->myParams[0].realArg)
    {
        (that->myParams[0].realArg)->show_val();
    }
    else
    {
        std::cerr << "built_in func ptr wrong at " << __PRETTY_FUNCTION__ << ": uninitialized real arg" << std::endl;
    }
}

void ForBiggerThanBlock::operator()(Func_Block *that)
{
    if (that && that->numOfParams != 3)
    {
        std::cerr << "built_in func ptr wrong at " << __PRETTY_FUNCTION__ << std::endl;
        return;
    }
    if (that && that->myParams && that->myParams[0].realArg && that->myParams[1].realArg && that->myParams[2].realArg)
    {
        bool &ref {that->myParams[0].realArg->val._bool};
        _Data_t &ref_1 {that->myParams[1].realArg->val};
        _Data_t &ref_2 {that->myParams[2].realArg->val};
        std::type_info const &info1 {typeid(*(that->myParams[1].realArg))};
        std::type_info const &info2 {typeid(*(that->myParams[2].realArg))};
        if (info1 == convertToTypeinfo(varType_e::DOUBLE) && info2 == convertToTypeinfo(varType_e::DOUBLE))
        {
            ref = (ref_1._double > ref_2._double);
        }
        else if (info1 == convertToTypeinfo(varType_e::INT) && info2 == convertToTypeinfo(varType_e::DOUBLE))
        {
            ref = (ref_1._int > ref_2._double);
        }
        else if (info1 == convertToTypeinfo(varType_e::INT) && info2 == convertToTypeinfo(varType_e::INT))
        {
            ref = (ref_1._int > ref_2._int);
        }
        else if (info1 == convertToTypeinfo(varType_e::DOUBLE) && info2 == convertToTypeinfo(varType_e::INT))
        {
            ref = (ref_1._double > ref_2._int);
        }
        else
        {
            std::cerr << "built_in func ptr wrong at " << __PRETTY_FUNCTION__ << std::endl;
            return;
        }
    }
    else
    {
        std::cerr << "built_in func ptr wrong at " << __PRETTY_FUNCTION__ << ": uninitialized real arg" << std::endl;
    }
}

void ForSmallerThanBlock::operator()(Func_Block *that)
{
    forBuiltInBiggerThan(that);
    that->myParams[0].realArg->val._bool = !(that->myParams[0].realArg->val._bool);
}

void ForBuiltInEqualBlock::operator()(Func_Block *that)
{
    if (that && that->numOfParams != 3)
    {
        std::cerr << "built_in func ptr wrong at " << __PRETTY_FUNCTION__ << std::endl;
        return;
    }
    if (that && that->myParams && that->myParams[0].realArg && that->myParams[1].realArg && that->myParams[2].realArg)
    {
        std::type_info const &info1 {typeid(*(that->myParams[0].realArg))};
        std::type_info const &info2 {typeid(*(that->myParams[1].realArg))};
        std::type_info const &info3 {typeid(*(that->myParams[2].realArg))};
        if ( ((info1 == convertToTypeinfo(varType_e::BOOL)) && (info2 == convertToTypeinfo(varType_e::INT)) && (info2 == info3)) )
        {
            // std::cout << that->myParams[2].realArg->val._int << " =?= " << that->myParams[1].realArg->val._int << std::endl;
            that->myParams[0].realArg->val._bool = (that->myParams[1].realArg->val._int == that->myParams[2].realArg->val._int);
        }
        else
        {
            std::cerr << "built_in func ptr wrong at " << __PRETTY_FUNCTION__ << std::endl;
            return;
        }
    }
    else
    {
        std::cerr << "built_in func ptr wrong at " << __PRETTY_FUNCTION__ << ": uninitialized real arg" << std::endl;
    }
}

void ForPlusBlock::operator()(Func_Block *that)
{
    if (that && that->numOfParams != 3)
    {
        std::cerr << "built_in func ptr wrong at " << __PRETTY_FUNCTION__ << std::endl;
        return;
    }
    if (that && that->myParams && that->myParams[0].realArg && that->myParams[1].realArg && that->myParams[2].realArg)
    {
        std::type_info const &info1 {typeid(*(that->myParams[0].realArg))};
        std::type_info const &info2 {typeid(*(that->myParams[1].realArg))};
        std::type_info const &info3 {typeid(*(that->myParams[2].realArg))};
        if (info1 == info2 && info2 == info3 && info3 == convertToTypeinfo(varType_e::INT))
        {
            that->myParams[0].realArg->val._int = that->myParams[1].realArg->val._int + that->myParams[2].realArg->val._int;
        }
        else if (info1 == info2 && info2 == info3 && info3 == convertToTypeinfo(varType_e::DOUBLE))
        {
            that->myParams[0].realArg->val._double = that->myParams[1].realArg->val._double + that->myParams[2].realArg->val._double;
        }
        else
        {
            std::cerr << "built_in func ptr wrong at " << __PRETTY_FUNCTION__ << std::endl;
            return;
        }
    }
    else
    {
        std::cerr << "built_in func ptr wrong at " << __PRETTY_FUNCTION__ << ": uninitialized real arg" << std::endl;
    }
}

void ForMinusBlock::operator()(Func_Block *that)
{
    if (that && that->numOfParams != 3)
    {
        std::cerr << "built_in func ptr wrong at " << __PRETTY_FUNCTION__ << std::endl;
        return;
    }
    if (that && that->myParams && that->myParams[0].realArg && that->myParams[1].realArg && that->myParams[2].realArg)
    {
        std::type_info const &info1 {typeid(*(that->myParams[0].realArg))};
        std::type_info const &info2 {typeid(*(that->myParams[1].realArg))};
        std::type_info const &info3 {typeid(*(that->myParams[2].realArg))};
        if (info1 == info2 && info2 == info3 && info3 == convertToTypeinfo(varType_e::INT))
        {
            that->myParams[0].realArg->val._int = that->myParams[1].realArg->val._int - that->myParams[2].realArg->val._int;
        }
        else if (info1 == info2 && info2 == info3 && info3 == convertToTypeinfo(varType_e::DOUBLE))
        {
            that->myParams[0].realArg->val._double = that->myParams[1].realArg->val._double - that->myParams[2].realArg->val._double;
        }
        else
        {
            std::cerr << "built_in func ptr wrong at " << __PRETTY_FUNCTION__ << std::endl;
            return;
        }
    }
    else
    {
        std::cerr << "built_in func ptr wrong at " << __PRETTY_FUNCTION__ << ": uninitialized real arg" << std::endl;
    }
}

void ForDivisionBlock::operator()(Func_Block *that)
{
    if (that && that->numOfParams != 3)
    {
        std::cerr << "built_in func ptr wrong at " << __PRETTY_FUNCTION__ << std::endl;
        return;
    }
    if (that && that->myParams && that->myParams[0].realArg && that->myParams[1].realArg && that->myParams[2].realArg)
    {
        std::type_info const &info1 {typeid(*(that->myParams[0].realArg))};
        std::type_info const &info2 {typeid(*(that->myParams[1].realArg))};
        std::type_info const &info3 {typeid(*(that->myParams[2].realArg))};
        if (info1 == info2 && info2 == info3 && info3 == convertToTypeinfo(varType_e::INT))
        {
            that->myParams[0].realArg->val._int = that->myParams[1].realArg->val._int / that->myParams[2].realArg->val._int;
        }
        else if (info1 == info2 && info2 == info3 && info3 == convertToTypeinfo(varType_e::DOUBLE))
        {
            that->myParams[0].realArg->val._double = that->myParams[1].realArg->val._double / that->myParams[2].realArg->val._double;
        }
        else
        {
            std::cerr << "built_in func ptr wrong at " << __PRETTY_FUNCTION__ << std::endl;
            return;
        }
    }
    else
    {
        std::cerr << "built_in func ptr wrong at " << __PRETTY_FUNCTION__ << ": uninitialized real arg" << std::endl;
    }
}

void ForMultiplicationBlock::operator()(Func_Block *that)
{
    if (that && that->numOfParams != 3)
    {
        std::cerr << "built_in func ptr wrong at " << __PRETTY_FUNCTION__ << std::endl;
        return;
    }
    if (that && that->myParams && that->myParams[0].realArg && that->myParams[1].realArg && that->myParams[2].realArg)
    {
        std::type_info const &info1 {typeid(*(that->myParams[0].realArg))};
        std::type_info const &info2 {typeid(*(that->myParams[1].realArg))};
        std::type_info const &info3 {typeid(*(that->myParams[2].realArg))};
        if (info1 == info2 && info2 == info3 && info3 == convertToTypeinfo(varType_e::INT))
        {
            that->myParams[0].realArg->val._int = that->myParams[1].realArg->val._int * that->myParams[2].realArg->val._int;
        }
        else if (info1 == info2 && info2 == info3 && info3 == convertToTypeinfo(varType_e::DOUBLE))
        {
            that->myParams[0].realArg->val._double = that->myParams[1].realArg->val._double * that->myParams[2].realArg->val._double;
        }
        else
        {
            std::cerr << "built_in func ptr wrong at " << __PRETTY_FUNCTION__ << std::endl;
            return;
        }
    }
    else
    {
        std::cerr << "built_in func ptr wrong at " << __PRETTY_FUNCTION__ << ": uninitialized real arg" << std::endl;
    }
}

void ForSubsGetBlock::operator()(Func_Block *that)
{
    if (that && that->numOfParams != 3)
    {
        std::cerr << "built_in func ptr wrong at " << __PRETTY_FUNCTION__ << std::endl;
        return;
    }
    if (that && that->myParams && that->myParams[1].realArg && that->myParams[2].realArg && that->myParams[0].realArg)
    {
        std::type_info const &info0 {typeid(*(that->myParams[0].realArg))};
        std::type_info const &info1 {typeid(*(that->myParams[1].realArg))};
        int index {that->myParams[2].realArg->val._int};
        if (info1 == convertToTypeinfo(varType_e::INTARR) && info0 == convertToTypeinfo(varType_e::INT))
        {
            // std::cout << "prev: " << that->myParams[0].realArg->val._int << " = " << that->myParams[1].realArg->val._intArr[index] << std::endl;
            that->myParams[0].realArg->val._int = that->myParams[1].realArg->val._intArr[index];
            // std::cout << "post: " << that->myParams[0].realArg->val._int << " = " << that->myParams[1].realArg->val._intArr[index] << std::endl;
        }
        else if (info1 == convertToTypeinfo(varType_e::DOUBLEARR) && info0 == convertToTypeinfo(varType_e::DOUBLE))
        {
            that->myParams[0].realArg->val._double = that->myParams[1].realArg->val._doubleArr[index];
        }
        else if (info1 == convertToTypeinfo(varType_e::BOOLARR) && info0 == convertToTypeinfo(varType_e::BOOL))
        {
            that->myParams[0].realArg->val._bool = that->myParams[1].realArg->val._boolArr[index];
        }
        else
        {
            std::cerr << "built_in func ptr wrong at " << __PRETTY_FUNCTION__ << std::endl;
        }
    }
    else
    {
        std::cerr << "built_in func ptr wrong at " << __PRETTY_FUNCTION__ << ": uninitialized real arg" << std::endl;
    }
}

void ForSubsSetBlock::operator()(Func_Block *that)
{
    if (that && that->numOfParams != 3)
    {
        std::cerr << "built_in func ptr wrong at " << __PRETTY_FUNCTION__ << std::endl;
        return;
    }
    if (that && that->myParams && that->myParams[1].realArg && that->myParams[2].realArg && that->myParams[0].realArg)
    {
        std::type_info const &info1 {typeid(*(that->myParams[0].realArg))};
        std::type_info const &info0 {typeid(*(that->myParams[2].realArg))};
        int index {that->myParams[1].realArg->val._int};
        if (info1 == convertToTypeinfo(varType_e::INTARR) && info0 == convertToTypeinfo(varType_e::INT))
        {
            // std::cout << "prev: " << that->myParams[0].realArg->val._int << " = " << that->myParams[1].realArg->val._intArr[index] << std::endl;
             that->myParams[0].realArg->val._intArr[index] = that->myParams[2].realArg->val._int;
            // std::cout << "post: " << that->myParams[0].realArg->val._int << " = " << that->myParams[1].realArg->val._intArr[index] << std::endl;
        }
        else if (info1 == convertToTypeinfo(varType_e::DOUBLEARR) && info0 == convertToTypeinfo(varType_e::DOUBLE))
        {
             that->myParams[0].realArg->val._doubleArr[index] = that->myParams[2].realArg->val._double;
        }
        else if (info1 == convertToTypeinfo(varType_e::BOOLARR) && info0 == convertToTypeinfo(varType_e::BOOL))
        {
             that->myParams[0].realArg->val._boolArr[index] = that->myParams[2].realArg->val._bool;
        }
        else
        {
            std::cerr << "built_in func ptr wrong at " << __PRETTY_FUNCTION__ << std::endl;
        }
    }
    else
    {
        std::cerr << "built_in func ptr wrong at " << __PRETTY_FUNCTION__ << ": uninitialized real arg" << std::endl;
    }
}

void ForAssignmentBlock::operator()(Func_Block *that)
{
    if (that && that->numOfParams != 2)
    {
        std::cerr << "built_in func ptr wrong at " << __PRETTY_FUNCTION__ << std::endl;
        return;
    }
    if (that && that->myParams && that->myParams[0].realArg && that->myParams[1].realArg)
    {
        that->myParams[0].realArg->val.set_val(that->myParams[1].realArg->val);
    }
    else
    {
        std::cerr << "built_in func ptr wrong at " << __PRETTY_FUNCTION__ << ": uninitialized real arg" << std::endl;
    }
}

Func_Block printBlock {"BUILT_IN_PRINT", 1, &forBuiltInPrint};
Func_Block biggerThanBlock {"BUILT_IN_BIGGERTHAN", 3, &forBuiltInBiggerThan};
Func_Block smallerThanBlock {"BUILT_IN_SMALLERTHAN", 3, &forBuiltInSmallerThan};
Func_Block equalBlock {"BUILT_IN_EQUAL", 3, &forBuiltInEqual};
Func_Block plusBlock {"BUILT_IN_PLUS", 3, &forBuiltInPlus};
Func_Block minusBlock {"BUILT_IN_MINUS", 3, &forBuiltInMinus};
Func_Block divisionBlock {"BUILT_IN_DIVISION", 3, &forBuiltInDivision};
Func_Block multiplicationBlock {"BUILT_IN_MULTIPLICATION", 3, &forBuiltInMultiplication};
Func_Block subsBlock_get {"BUILT_IN_SUBSGET", 3, &forBuiltInSubsGet};
Func_Block subsBlock_set {"BUILT_IN_SUBSSET", 3, &forBuiltInSubsSet};
Func_Block assignmentBlock {"BUILT_IN_ASSIGNMENT", 2, &forBuiltInAssignment};
Func_Block andBlock {"BUILT_IN_AND", 3, &forBuiltInAnd};
Func_Block notBlock {"BUILT_IN_NOT", 3, &forBuiltInNot};
Func_Block orBlock {"BUILT_IN_OR", 3, &forBuiltInOr};

void builtInOperatorsInit()
{
    printBlock.setParamType(varType_e::ANYTYPE, 0);

    biggerThanBlock.setParamType(varType_e::NUMTYPE, 1);
    biggerThanBlock.setParamType(varType_e::NUMTYPE, 2);
    biggerThanBlock.setParamType(varType_e::BOOL, 0);

    smallerThanBlock.setParamType(varType_e::NUMTYPE, 1);
    smallerThanBlock.setParamType(varType_e::NUMTYPE, 2);
    smallerThanBlock.setParamType(varType_e::BOOL, 0);

    equalBlock.setParamType(varType_e::BOOL, 0);
    equalBlock.setParamType(varType_e::INT, 1);
    equalBlock.setParamType(varType_e::INT, 2);

    plusBlock.setParamType(varType_e::NUMTYPE, 0);
    plusBlock.setParamType(varType_e::NUMTYPE, 1);
    plusBlock.setParamType(varType_e::NUMTYPE, 2);

    minusBlock.setParamType(varType_e::NUMTYPE, 0);
    minusBlock.setParamType(varType_e::NUMTYPE, 1);
    minusBlock.setParamType(varType_e::NUMTYPE, 2);

    divisionBlock.setParamType(varType_e::NUMTYPE, 0);
    divisionBlock.setParamType(varType_e::NUMTYPE, 1);
    divisionBlock.setParamType(varType_e::NUMTYPE, 2);

    multiplicationBlock.setParamType(varType_e::NUMTYPE, 0);
    multiplicationBlock.setParamType(varType_e::NUMTYPE, 1);
    multiplicationBlock.setParamType(varType_e::NUMTYPE, 2);

    subsBlock_get.setParamType(varType_e::NONARRTYPE, 0);
    subsBlock_get.setParamType(varType_e::ARRTYPE, 1);
    subsBlock_get.setParamType(varType_e::INT, 2);

    subsBlock_get.setParamType(varType_e::ARRTYPE, 0);
    subsBlock_get.setParamType(varType_e::INT, 1);
    subsBlock_get.setParamType(varType_e::NONARRTYPE, 2);

    assignmentBlock.setParamType(varType_e::NONARRTYPE, 0);
    assignmentBlock.setParamType(varType_e::NONARRTYPE, 1);
}

} // namespace WriteBackend
