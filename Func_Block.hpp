#pragma once

#include "Block.hpp"

#include <QPushButton>
#include <QObject>
#include "runwindow.h"

namespace WriteBackend
{

enum bodyType_e
{
    IF,
    WHILE,
    FUNCCALL,
    ERROR,
};

extern std::type_info const &convertToTypeinfo(varType_e _t);
extern void setRunWindowStep(QPushButton* *ptr);
extern void setRunWindowPtr(RunWindow* *ptr);
extern ::RunWindow* *runWindowPtr;

class Func_Block;
class BuiltInRunFunc_helper_base
{
    public:
        virtual void operator()(Func_Block*) = 0;
        virtual ~BuiltInRunFunc_helper_base() {}
}; // later one the callback function definition should be derived class definition with override function operator()

class Func_Block: public Block
{
    friend class ForPrintBlock;
    friend class ForBiggerThanBlock;
    friend class ForSmallerThanBlock;
    friend class ForBuiltInEqualBlock;
    friend class ForPlusBlock;
    friend class ForMinusBlock;
    friend class ForDivisionBlock;
    friend class ForMultiplicationBlock;
    friend class ForSubsGetBlock;
    friend class ForSubsSetBlock;
    friend class ForAssignmentBlock;
    friend class ForNotBlock;
    friend class ForAndBlock;
    friend class ForOrBlock;

    private: // data members
        BuiltInRunFunc_helper_base *myRunFunc {nullptr}; // for something like plus, minus, subscription, logic and, logic or... but not if/for/while/statement
                                                         // so for those built-in operators/functions, the 'myBody' field would be empty

        unsigned int const numOfParams {0};              // real numm including the next funcBlock ptr;

        struct Param_info_t    //参数结构体                          // a single struct is for a single arg taken by the function
        {
            varType_e argType {varType_e::ERRTYPE};      // once set in the function definition phase, NOTE should be fixed throughout the program
            Block *realArg {nullptr};                    // real args for exe, will be changed a lot, real type can be Func_Block or Var_Block
        } *myParams {nullptr};                           // ptr: dynamic array which contains all params, num should be fixed after function definition

        struct FuncBody_info_t    //每行代码，一行一行是什么                       // info needed for a single statement(line) in the function
        {
            bodyType_e statType { bodyType_e::ERROR };   // indicating whether this block is a normal funcition call or one of these statements: if for while
            Block* *condition {nullptr};                 // it is just a ptr to ptr to ensure it refers to a correct thing, NOTE this is not nullptr only for <if> <for> <while>

            struct bodyFunc_info
            {
                Func_Block* func {nullptr};              // the func to be called, NOTE once the funciton is defined, should not change
                Block** *args {nullptr};                 // args for calling the corresponding func, NOTE once the function is defined, should not change; ptr to ptr to ensure it refers to a correct thing
            } bodyFuncs[2];                              // normally this will just be an array of one element,
                                                         // only for if statement, this array will contain 2 elements, the first func for true, second for false
        };

        std::deque<FuncBody_info_t> myBody;              // everything in this deque should be fixed after the funtion is fully defined

        static bool isStepping;

    public: // member funcs

        static void set_isStepping(bool v);

        Func_Block() = delete;

        Func_Block(Func_Block const &) = delete;

        // numOfParam should always bigger or eq to 0
        Func_Block(std::string name, unsigned int numOfParam, BuiltInRunFunc_helper_base *runFunc = nullptr); //弹窗输入比较好

        ~Func_Block() override;

        // =============================================== for dealing with the funciton params =============================================

        void setParamType(varType_e t, int which);  //1.设置第几个参数是干什么的，前端显示名字-后端只是数字  --declaration 结束

        bool setRealArg(Block* b, int which);  //2.  初始call使用
        // =============================================== for dealing with the funciton params =============================================


        // myBody
        // =============================================== for dealing with the function body ===============================================
        void clearMyBody(); // clear anytime the user changes the function definition by drag & drop or somehting

        void setNextBody(bodyType_e type, Block* *condition, Func_Block *func1, Func_Block *func2); // set the next "line" of code which the user write

        bool setNextBodyParam(unsigned int whichParam, int val, unsigned int whichFunc = 0); // set the parameters for the fucntion callings in next "line"

        bool setNextBodyParam(unsigned int whichParam, Block** ref, unsigned int whichFunc = 0); // set the parameters for the function callings in the next "line", just another interface which allow user to ref to global var
        // =============================================== for dealing function bodies ===============================================

        virtual void run() override;

        virtual void show_val() override;

    private:
        void runFunc(FuncBody_info_t &toRun, int which = 0);

        static inline bool typeCheck(std::type_info const &info, varType_e const &type_e); // check whether the var 'info' is valid according to the type_e
};

} // namespace WriteBackend
