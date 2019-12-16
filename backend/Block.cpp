#include "Block.hpp"

namespace WriteBackend
{

_Data_t::_Data_t()
{
    memset(this, 0, sizeof(_Data_t));
}

Block::Block(std::string _n): name {_n}, val{} {}

Block::~Block() {}

} // namespace WriteBackend