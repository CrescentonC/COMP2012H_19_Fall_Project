#pragma once

#include "Func_Block.hpp"
#include "Var_Block.hpp"

namespace WriteBackend
{

extern void builtInOperatorsInit();

extern Func_Block printBlock;
extern Func_Block biggerThanBlock;
extern Func_Block smallerThanBlock;
extern Func_Block equalBlock;
extern Func_Block plusBlock;
extern Func_Block minusBlock;
extern Func_Block divisionBlock;
extern Func_Block multiplicationBlock;
extern Func_Block subsBlock_get;
extern Func_Block subsBlock_set;
extern Func_Block assignmentBlock;
extern Func_Block andBlock;
extern Func_Block notBlock;
extern Func_Block orBlock;


} // namespace WriteBackend
