#include "block.h"

Block::Block(QWidget *parent): QLabel {parent} {}

Block::Block(Block *const &p, Block *const &n, QWidget *pa): QLabel {pa}, prev {p}, next {n} {}

int Block::run()
{
    if (next)
    {
        return next->run();
    }
    return -1;
}
