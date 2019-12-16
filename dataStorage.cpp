#include "dataStorage.hpp"
#include "drawpalette.h"


namespace dataStorage {
std::map<std::string, WriteBackend::Block*> func_pool;

std::map<std::string, Visible_Block*> visible_func_pool;

std::map<std::string, WriteBackend::Block*> var_pool;

std::map<std::string, Visible_Block*> visible_var_pool;

std::map<WriteBackend::Block*, std::map<std::string, Visible_Block*>*> correspond_pool;
}
