#ifndef DATASTORAGE_HPP
#define DATASTORAGE_HPP
#include <map>
#include "Block.hpp"
#include "Func_Block.hpp"
#include "Visible_Block.hpp"


namespace dataStorage
{
// map from name-> real Func_Block*
extern std::map<std::string, WriteBackend::Block*> func_pool;

// map from name-> visible_Block* for func
extern std::map<std::string, Visible_Block*> visible_func_pool;

// map from name->Var_Block*
extern std::map<std::string, WriteBackend::Block*> var_pool;

// map from name->visible_Block* for var
extern std::map<std::string, Visible_Block*> visible_var_pool;

// map from Func_Block*->VisbleBlock_Pool*      func -> its Visible_Block pool
extern std::map<WriteBackend::Block*, std::map<std::string, Visible_Block*>*> correspond_pool;
}

#endif // DATASTORAGE_HPP
