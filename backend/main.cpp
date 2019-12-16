#include "Func_Block.hpp"
#include "Var_Block.hpp"
#include "BuiltInOperators.hpp"
#include "ProgramManager.hpp"

using namespace WriteBackend;

int main()
{
    builtInOperatorsInit();

    std::map<std::string, Block*> varPool; // varPool to store all vars and check any name collision

    // ========================== try my custom function: PrintSmallerOne ====================================
    varPool["biggerThanStore"] = new Var_Block<bool> {"biggerThanStore", false};
    varPool["biggerNum"] = new Var_Block<int> {"biggerNum", 240};
    varPool["smallerNum"] = new Var_Block<int> {"smallerNum", 12};
    varPool["againB"] = new Var_Block<int> {"againB", 123};
    varPool["againS"] = new Var_Block<int> {"againS", 13};

    Func_Block printSmallerOne {"test_printSmallerOne", 2};
    printSmallerOne.setParamType(varType_e::INT, 0);
    printSmallerOne.setParamType(varType_e::INT, 1);

    printSmallerOne.setNextBody(bodyType_e::FUNCCALL, nullptr, &smallerThanBlock, nullptr); // 1st 'line' of code
    printSmallerOne.setNextBodyParam(0, &varPool["biggerThanStore"]);
    printSmallerOne.setNextBodyParam(1, 0);
    printSmallerOne.setNextBodyParam(2, 1);

    printSmallerOne.setNextBody(bodyType_e::FUNCCALL, nullptr, &printBlock, nullptr); // 2nd 'line' of code
    printSmallerOne.setNextBodyParam(0, &varPool["biggerThanStore"]);

    printSmallerOne.setNextBody(bodyType_e::IF, &varPool["biggerThanStore"], &printBlock, &printBlock); // 3rd 'line' of code
    printSmallerOne.setNextBodyParam(0, 0, 0);
    printSmallerOne.setNextBodyParam(0, 1, 1);

    printSmallerOne.setNextBody(bodyType_e::FUNCCALL, nullptr, &printBlock, nullptr); // 4th 'line' of code
    printSmallerOne.setNextBodyParam(0, 0);

    printSmallerOne.setNextBody(bodyType_e::FUNCCALL, nullptr, &printBlock, nullptr); // 5th 'line' of code
    printSmallerOne.setNextBodyParam(0, 1);

    // <---------------run!
    printSmallerOne.setRealArg(varPool["biggerNum"], 0);
    printSmallerOne.setRealArg(varPool["smallerNum"], 1);
    // printSmallerOne.run();

    // <---------------run again!
    printSmallerOne.setRealArg(varPool["againB"], 0);
    printSmallerOne.setRealArg(varPool["againS"], 1);
    // printSmallerOne.run();
    // ========================== try my custom function: PrintSmallerOne ====================================


    // ========================== try my custom function: PrintSum(actually 4 operations) ========================================
    varPool["plusStore"] = new Var_Block<double> {"plusStore", 0.00};
    varPool["doubleA"] = new Var_Block<double> {"doubleA", 2.24};
    varPool["doubleB"] = new Var_Block<double> {"doubleB", 3.00};

    Func_Block printSum {"printSum", 2};
    printSum.setParamType(varType_e::DOUBLE, 0);
    printSum.setParamType(varType_e::DOUBLE, 1);
    
    printSum.setNextBody(bodyType_e::FUNCCALL, nullptr, &multiplicationBlock, nullptr);
    printSum.setNextBodyParam(0, &(varPool["plusStore"]));
    printSum.setNextBodyParam(1, 0);
    printSum.setNextBodyParam(2, 1);

    printSum.setNextBody(bodyType_e::FUNCCALL, nullptr, &printBlock, nullptr);
    printSum.setNextBodyParam(0, &(varPool["plusStore"]));

    // <-------------------- run!
    printSum.setRealArg((varPool["doubleA"]), 0);
    printSum.setRealArg((varPool["doubleB"]), 1);
    // printSum.run();
    // ========================== try my custom function: PrintSum ========================================

    
    // ========================== try my custom function: recursive func ========================================
    varPool["recurCounter"] = new Var_Block<int> {"recurCounter", 4};
    varPool["CONST_ONE"] = new Var_Block<int> {"CONST_ONE", 1};
    varPool["CONST_ZERO"] = new Var_Block<int> {"CONST_ZERO", 0};
    varPool["equalStore"] = new Var_Block<bool> {"equalStore", false};
                                                                                                      // -----VVVVVV------ translated into c++
    Func_Block recursiveFunc {"recursiveFunc", 1};
    recursiveFunc.setParamType(varType_e::INT, 0);                                                    // void recursiveFunc(int &a)

    recursiveFunc.setNextBody(bodyType_e::FUNCCALL, nullptr, &printBlock, nullptr);                   // { printBlock(a);
    recursiveFunc.setNextBodyParam(0, 0);

    recursiveFunc.setNextBody(bodyType_e::FUNCCALL, nullptr, &euqalBlock, nullptr);                   // equalStore = (a == 0);
    recursiveFunc.setNextBodyParam(0, &(varPool["equalStore"]));
    recursiveFunc.setNextBodyParam(1, 0);
    recursiveFunc.setNextBodyParam(2, &(varPool["CONST_ZERO"]));

    recursiveFunc.setNextBody(bodyType_e::FUNCCALL, nullptr, &minusBlock, nullptr);                   // a = a - 1;
    recursiveFunc.setNextBodyParam(0, 0);
    recursiveFunc.setNextBodyParam(1, 0);
    recursiveFunc.setNextBodyParam(2, &(varPool["CONST_ONE"]));

    recursiveFunc.setNextBody(bodyType_e::IF, &(varPool["equalStore"]), &printBlock, &recursiveFunc); // if (equalStore) {printBlock(a);} else {recursiveFunc(a);} }
    recursiveFunc.setNextBodyParam(0, 0, 0);
    recursiveFunc.setNextBodyParam(0, 0, 1);

    // <------------------------ run!
    recursiveFunc.setRealArg((varPool["recurCounter"]), 0);
    // recursiveFunc.run();
    // ========================== try my custom function: recursive func =======================================



    // ========================== try my ultimate function: binary search ========================================
    varPool["bsStore"] = new Var_Block<int> {"bsStore", -2};

    varPool["bs_plusStore"] = new Var_Block<int> {"bs_plusStore", 0};
    varPool["bs_divisionStore"] = new Var_Block<int> {"bs_divisionStore", 0};
    varPool["bs_subsStore"] = new Var_Block<int> {"bs_subsStore", 0};
    varPool["bs_biggerThanStore"] = new Var_Block<bool> {"bs_biggerThanStore", false};
    varPool["bs_equalStore"] = new Var_Block<bool> {"bs_equalStore", false};

    varPool["CONST_NEGATIVEONE"] = new Var_Block<int> {"CONST_NEGATIVEONE", -1};
    varPool["CONST_TWO"] = new Var_Block<int> {"CONST_TWO", 2};
        

    Func_Block binarySearch_main {"binarySearch_main", 4}; // it is like foward declaration here
    binarySearch_main.setParamType(varType_e::INTARR, 0);
    binarySearch_main.setParamType(varType_e::INT, 1);
    binarySearch_main.setParamType(varType_e::INT, 2);
    binarySearch_main.setParamType(varType_e::INT, 3);
        // ================== helper three, when true in third if ====================
    Func_Block bS_FFT {"bS_FFT", 4};
    bS_FFT.setParamType(varType_e::INTARR, 0);
    bS_FFT.setParamType(varType_e::INT, 1);
    bS_FFT.setParamType(varType_e::INT, 2);
    bS_FFT.setParamType(varType_e::INT, 3);

    bS_FFT.setNextBody(bodyType_e::FUNCCALL, nullptr, &plusBlock, nullptr);
    bS_FFT.setNextBodyParam(0, 1);
    bS_FFT.setNextBodyParam(1, &(varPool["bs_divisionStore"]));
    bS_FFT.setNextBodyParam(2, &(varPool["CONST_ONE"]));

    bS_FFT.setNextBody(bodyType_e::FUNCCALL, nullptr, &binarySearch_main, nullptr);
    bS_FFT.setNextBodyParam(0, 0);
    bS_FFT.setNextBodyParam(1, 1);
    bS_FFT.setNextBodyParam(2, 2);
    bS_FFT.setNextBodyParam(3, 3);


        // ================== helper three, when false in third if ====================
    Func_Block bS_FFF {"bS_FFT", 4};
    bS_FFF.setParamType(varType_e::INTARR, 0);
    bS_FFF.setParamType(varType_e::INT, 1);
    bS_FFF.setParamType(varType_e::INT, 2);
    bS_FFF.setParamType(varType_e::INT, 3);

    bS_FFF.setNextBody(bodyType_e::FUNCCALL, nullptr, &minusBlock, nullptr);
    bS_FFF.setNextBodyParam(0, 2);
    bS_FFF.setNextBodyParam(1, &(varPool["bs_divisionStore"]));
    bS_FFF.setNextBodyParam(2, &(varPool["CONST_ONE"]));

    bS_FFF.setNextBody(bodyType_e::FUNCCALL, nullptr, &binarySearch_main, nullptr);
    bS_FFF.setNextBodyParam(0, 0);
    bS_FFF.setNextBodyParam(1, 1);
    bS_FFF.setNextBodyParam(2, 2);
    bS_FFF.setNextBodyParam(3, 3);
    
        // ================== helper two, when false in second if =====================
    Func_Block bS_FF {"bS_FF", 4};
    bS_FF.setParamType(varType_e::INTARR, 0);
    bS_FF.setParamType(varType_e::INT, 1);
    bS_FF.setParamType(varType_e::INT, 2);
    bS_FF.setParamType(varType_e::INT, 3);

    bS_FF.setNextBody(bodyType_e::FUNCCALL, nullptr, &subsBlock, nullptr);
    bS_FF.setNextBodyParam(0, &(varPool["bs_subsStore"]));
    bS_FF.setNextBodyParam(1, 0);
    bS_FF.setNextBodyParam(2, &(varPool["bs_divisionStore"]));

    bS_FF.setNextBody(bodyType_e::FUNCCALL, nullptr, &smallerThanBlock, nullptr);
    bS_FF.setNextBodyParam(0, &(varPool["bs_biggerThanStore"]));
    bS_FF.setNextBodyParam(1, &(varPool["bs_subsStore"]));
    bS_FF.setNextBodyParam(2, 3);

    bS_FF.setNextBody(bodyType_e::IF, &(varPool["bs_biggerThanStore"]), &bS_FFT, &bS_FFF);
    bS_FF.setNextBodyParam(0, 0, 0);
    bS_FF.setNextBodyParam(1, 1, 0);
    bS_FF.setNextBodyParam(2, 2, 0);
    bS_FF.setNextBodyParam(3, 3, 0);
    bS_FF.setNextBodyParam(0, 0, 1);
    bS_FF.setNextBodyParam(1, 1, 1);
    bS_FF.setNextBodyParam(2, 2, 1);
    bS_FF.setNextBodyParam(3, 3, 1);


        // ================== helper one, when false in the first if ============
    Func_Block bS_F {"bS_F", 4};
    bS_F.setParamType(varType_e::INTARR, 0);
    bS_F.setParamType(varType_e::INT, 1);
    bS_F.setParamType(varType_e::INT, 2);
    bS_F.setParamType(varType_e::INT, 3);

    bS_F.setNextBody(bodyType_e::FUNCCALL, nullptr, &plusBlock, nullptr);
    bS_F.setNextBodyParam(0, &(varPool["bs_plusStore"]));
    bS_F.setNextBodyParam(1, 1);
    bS_F.setNextBodyParam(2, 2);

    bS_F.setNextBody(bodyType_e::FUNCCALL, nullptr, &divisionBlock, nullptr);
    bS_F.setNextBodyParam(0, &(varPool["bs_divisionStore"]));
    bS_F.setNextBodyParam(1, &(varPool["bs_plusStore"]));
    bS_F.setNextBodyParam(2, &(varPool["CONST_TWO"]));

    bS_F.setNextBody(bodyType_e::FUNCCALL, nullptr, &subsBlock, nullptr);
    bS_F.setNextBodyParam(0, &(varPool["bs_subsStore"]));
    bS_F.setNextBodyParam(1, 0);
    bS_F.setNextBodyParam(2, &(varPool["bs_divisionStore"]));
    bS_F.setNextBodyParam(3, nullptr);

    bS_F.setNextBody(bodyType_e::FUNCCALL, nullptr, &euqalBlock, nullptr);
    bS_F.setNextBodyParam(0, &(varPool["bs_equalStore"]));
    bS_F.setNextBodyParam(1, &(varPool["bs_subsStore"]));
    bS_F.setNextBodyParam(2, 3);

    bS_F.setNextBody(bodyType_e::IF, &(varPool["bs_equalStore"]), &assignmentBlock, &bS_FF);
    bS_F.setNextBodyParam(0, &(varPool["bsStore"]), 0);
    bS_F.setNextBodyParam(1, &(varPool["bs_divisionStore"]), 0);
    bS_F.setNextBodyParam(0, 0, 1);
    bS_F.setNextBodyParam(1, 1, 1);
    bS_F.setNextBodyParam(2, 2, 1);
    bS_F.setNextBodyParam(3, 3, 1);

        // ============== main func definition for bs ==================

    binarySearch_main.setNextBody(bodyType_e::FUNCCALL, nullptr, &biggerThanBlock, nullptr); // { bs_biggerThanStore = (a > b)
    binarySearch_main.setNextBodyParam(0, &(varPool["bs_biggerThanStore"]));
    binarySearch_main.setNextBodyParam(1, 1);
    binarySearch_main.setNextBodyParam(2, 2);

    binarySearch_main.setNextBody(bodyType_e::IF, &(varPool["bs_biggerThanStore"]), &assignmentBlock, &bS_F); 
    binarySearch_main.setNextBodyParam(0, &(varPool["bsStore"]), 0);
    binarySearch_main.setNextBodyParam(1, &(varPool["CONST_NEGATIVEONE"]), 0);
    binarySearch_main.setNextBodyParam(0, 0, 1);
    binarySearch_main.setNextBodyParam(1, 1, 1);
    binarySearch_main.setNextBodyParam(2, 2, 1);
    binarySearch_main.setNextBodyParam(3, 3, 1);

    Func_Block binarySearch_drive {"binarySearch_drive", 4};
    binarySearch_drive.setParamType(varType_e::INTARR, 0);
    binarySearch_drive.setParamType(varType_e::INT, 1);
    binarySearch_drive.setParamType(varType_e::INT, 2);
    binarySearch_drive.setParamType(varType_e::INT, 3);

    binarySearch_drive.setNextBody(bodyType_e::FUNCCALL, nullptr, &binarySearch_main, nullptr);
    binarySearch_drive.setNextBodyParam(0, 0);
    binarySearch_drive.setNextBodyParam(1, 1);
    binarySearch_drive.setNextBodyParam(2, 2);
    binarySearch_drive.setNextBodyParam(3, 3);

    binarySearch_drive.setNextBody(bodyType_e::FUNCCALL, nullptr, &printBlock, nullptr);
    binarySearch_drive.setNextBodyParam(0, &(varPool["bsStore"]));
    
    // <---------------------- binary Search run!!!!!!! please work!!!!!!!!!!
    varPool["bsArg_arr"] = new Var_Block<int*> {"bsArg_arr", nullptr, 5};
    reinterpret_cast<Var_Block<int*>*>(varPool["bsArg_arr"])->set_value({1,2,3,4,5}, 0);
    varPool["bsArg_start"] = new Var_Block<int> {"bsArg_start", 0};
    varPool["bsArg_end"] = new Var_Block<int> {"bsArg_end", 4};
    varPool["bsArg_key"] = new Var_Block<int> {"bsArg_key", 5};
    
    binarySearch_drive.setRealArg(varPool["bsArg_arr"], 0);
    binarySearch_drive.setRealArg(varPool["bsArg_start"], 1);
    binarySearch_drive.setRealArg(varPool["bsArg_end"], 2);
    binarySearch_drive.setRealArg(varPool["bsArg_key"], 3);

    Func_Block::setRunning(true);
    binarySearch_drive.run();
    // =================================== alwight!!!!! ===========================

    for (auto i : varPool)
    {
        delete i.second;
    }
}