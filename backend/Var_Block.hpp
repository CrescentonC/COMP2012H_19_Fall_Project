#pragma once

#include "Block.hpp"

namespace WriteBackend
{

template <typename T>
class Var_Block: public Block
{
    static_assert(ofOneOfTypes<T, bool, int, double, bool*, int*, double*>::val, "Not one of bool, int, double, bool*, int*, double*");

    private: // data members
        using myRawType = T;
        using myTypeWithoutPtr = typename getRidOfPtr<T>::_type;
        static constexpr bool is_arr_type {ofOneOfTypes<T, bool*, int*, double*>::val};
        unsigned int _size;

    public: // member funcs
        Var_Block() = delete;

        Var_Block(Var_Block const &) = delete;

        Var_Block(std::string _n, T _v, unsigned int _s = 0): Block {_n, _v}, _size {is_arr_type ? _s : 0}
        {
            // NOTE maybe need unique name checking?
            if (is_arr_type)
            {
                if (!(this->val._void))
                {
                    this->val._void = reinterpret_cast<void*>(new myTypeWithoutPtr [_size]);
                    memset(this->val._void, 0, _s*sizeof(myTypeWithoutPtr));
                }
            }
        }

        Var_Block(std::string _n, Var_Block const &other): Block {_n}
        {
            (*this) = other;
        }

        Var_Block const &operator=(Var_Block const &other)
        {
            if (is_copyAble(other))
            {
                if (!is_arr_type)
                {
                    memcpy(&(this->val), &other.val, sizeof(_Data_t));
                }
                else if (is_arr_type)
                {
                    if (this->val._void)
                    {
                        delete [] reinterpret_cast<myTypeWithoutPtr*>(this->val._void);
                    }
                    this->val._void = reinterpret_cast<void*>(new myTypeWithoutPtr [other._size]);
                    for (unsigned int i {0}; i < other._size; ++i)
                    {
                        reinterpret_cast<myTypeWithoutPtr*>(this->val._void)[i] =  reinterpret_cast<myTypeWithoutPtr*>(other.val._void)[i];
                    }
                }
            }
            return other;
        };

        ~Var_Block()
        {
            if (is_arr_type)
            {
                delete [] static_cast<myTypeWithoutPtr*>(val._void);
            }
        }

        myTypeWithoutPtr &operator[](size_t ind)
        {
            if (!is_arr_type)
            {
                return *(reinterpret_cast<myTypeWithoutPtr*>(&val._double));
            }
            else if (is_arr_type)
            {
                return (reinterpret_cast<myTypeWithoutPtr*>(val._void))[ind % _size];
            }
        }

        Block const &operator=(Block const &other)
        {
            if (is_copyAble(other))
            {
                (*this) = *(static_cast<Var_Block<T> const *>(&other));
            }
            else
            {
                std::cerr << "different actual type, cannot perform assignment" << std::endl;
            }
            return other;
        }

        virtual void run() override {}

        virtual void step() override {}

        virtual void show_val() override
        {
            if (!is_arr_type)
            {
                std::cout << name << ": " << *(reinterpret_cast<myTypeWithoutPtr*>(&val._double)) << std::endl;
            }
            else if (is_arr_type)
            {
                std::cout << name << ": ";
                for (unsigned int i {0}; i < this->_size; ++i)
                {
                    std::cout << (reinterpret_cast<myTypeWithoutPtr*>(val._void))[i] << " ";
                }
                std::cout << std::endl;
            }
        }

        bool is_copyAble(Block const &other)
        {
            return typeid(*this) == typeid(other);
        }

        void set_value(myTypeWithoutPtr val, int pos = -1)
        {
            if (pos < static_cast<int>(_size))
            {
                (*this)[pos] = val;
            }
        }

        template <int arr_size>
        void set_value(myTypeWithoutPtr const (&val)[arr_size], unsigned int startingPos = 0)
        {
            if (is_arr_type)
            {
                for (unsigned int i {0}; (i < arr_size && (i + startingPos) < _size); ++i)
                {
                    (*this)[i + startingPos] = val[i];
                }
            }
        }
};

} // namespace WriteBackend