#include "Block.hpp"

namespace WriteBackend
{
//static bool initialized = false;

_Data_t::_Data_t()
{
    memset(this, 0, sizeof(_Data_t));
//    if(!initialized)
//    {
//        varTypeMap["bool"] = BOOL;
//        varTypeMap["int"] = INT;
//        varTypeMap["double"] = DOUBLE;
//        varTypeMap["boolarr"] = BOOLARR;
//        varTypeMap["intarr"] = INTARR;
//        varTypeMap["doublearr"] = DOUBLEARR;
//        initialized = true;
//    }
}

Block::~Block() {}

//std::map<std::string, varType_e> varTypeMap;

} // namespace WriteBackend
