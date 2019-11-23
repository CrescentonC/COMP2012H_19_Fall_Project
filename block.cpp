#include "block.h"

Block::Block() = default;

Block::Block(Block *const &p, Block *const &n): prev {p}, next {n} {}

int Block::run()
{
    if (next)
    {
        return next->run();
    }
    return -1;
}
