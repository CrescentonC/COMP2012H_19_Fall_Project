#pragma once

#include <QLabel>
#include <QEvent>
#include <QMenu>
#include <QMouseEvent>
#include <QDebug>
#include <QMessageBox>
#include <iostream>
#include <typeinfo>
#include <memory.h>
#include <deque>
#include <map>

namespace WriteBackend
{

using Invalid_type = char*;

template <typename T1, typename T2>
struct ofSameType { static constexpr bool val {false}; };

template <typename T>
struct ofSameType<T, T> { static constexpr bool val {true}; };

template <typename... T>
struct ofOneOfTypes { static constexpr bool val {false}; };

template <typename T, typename S, typename... Other>
struct ofOneOfTypes<T, S, Other...> { static constexpr bool val { ofSameType<T,S>::val || ofOneOfTypes<T, Other...>::val }; };

template <typename T>
struct getRidOfPtr { using _type = T; };

template <typename T>
struct getRidOfPtr<T*> { using _type = typename getRidOfPtr<T>::_type; };

template <typename T>
struct isPtr {static constexpr bool val {false}; };
template <typename T>
struct isPtr<T*> {static constexpr bool val {true}; };

template <typename T>
constexpr bool determineIfPtr(T) { return isPtr<T>::val; }

enum varType_e
{
    BOOL,
    INT,
    DOUBLE,
    BOOLARR,
    INTARR,
    DOUBLEARR,
    ERRTYPE = -1,
    ANYTYPE = -2,
    NUMTYPE = -3,
    NUMARRTYPE = -4,
    ARRTYPE = -5,
    NONARRTYPE = -6,
};

//extern std::map<std::string, varType_e> varTypeMap;

union _Data_t
{
    public:
        int _int;
        double _double;
        bool _bool;
        int *_intArr;
        double *_doubleArr;
        bool *_boolArr;
        void *_void;
        _Data_t();
        _Data_t(_Data_t const &_d) = default;

        template <typename T>
        _Data_t(T _d)
        {
            set_val(_d);
        }

        template <typename T>
        void set_val(T _d)
        {
            memset(this, 0, sizeof(_Data_t));
            memcpy(this, &_d, sizeof(T));
        }
};

class Block
{
    friend class ForPrintBlock;
    friend class ForBiggerThanBlock;
    friend class ForSmallerThanBlock;
    friend class ForBuiltInEqualBlock;
    friend class ForPlusBlock;
    friend class ForMinusBlock;
    friend class ForDivisionBlock;
    friend class ForMultiplicationBlock;
    friend class ForSubsBlock;
    friend class ForAssignmentBlock;
    friend class ForNotBlock;
    friend class ForAndBlock;
    friend class ForOrBlock;

    friend class Func_Block;
    friend class Visible_Block;


public:
        std::string name;
        _Data_t val;

        Block() = delete;

        Block(Block const &_d) = delete;

        Block(std::string _n): name {_n}, val {}  {}

        template <typename T>
        Block(std::string _n, T _v): name {_n}, val {_v} {}

        virtual ~Block();

        virtual void run() = 0;

        virtual void show_val() = 0;
};

} // namespace WriteBackend
