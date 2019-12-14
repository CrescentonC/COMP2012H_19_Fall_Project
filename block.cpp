#include "Block.hpp"

namespace WriteBackend
{

_Data_t::_Data_t()
{
    memset(this, 0, sizeof(_Data_t));
}

Block::~Block() {}

} // namespace WriteBackend
