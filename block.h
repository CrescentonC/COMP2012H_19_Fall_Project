#ifndef BLOCK_H
#define BLOCK_H
#include <QLabel>


class Block : public QLabel
{
    Q_OBJECT

public:
    Block();
    virtual int run();
};

#endif // BLOCK_H
