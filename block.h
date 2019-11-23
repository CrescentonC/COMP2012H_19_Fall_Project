#ifndef BLOCK_H
#define BLOCK_H
#include <QLabel>


class Block : public QLabel
{
    Q_OBJECT

public:
    Block();
    Block(Block *const &p, Block *const &n);
    virtual int run() = 0;
    Block const *get_prev() const
    {
        return prev;
    }
    Block const *get_next() const
    {
        return next;
    }
    void set_prev(Block *const &p)
    {
        prev = p;
    }
    void set_next(Block *const &n)
    {
        next = n;
    }

private:
    Block *prev {nullptr};
    Block *next {nullptr};
};

#endif // BLOCK_H
