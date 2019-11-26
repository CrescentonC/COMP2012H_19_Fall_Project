#ifndef BLOCK_H
#define BLOCK_H
#include <QLabel>
#include <QEvent>
#include <QMenu>
#include <QMouseEvent>
#include <QDebug>
#include <QMessageBox>

class Block : public QLabel
{
    Q_OBJECT

public:
    Block(QWidget *parent = nullptr);
    Block(Block *const &p, Block *const &n, QWidget *pa = nullptr);
    virtual int run();

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

protected slots:
    // detailed info comment at cpp
    bool eventFilter(QObject *, QEvent *event) override;
    void ShowContextMenu(const QPoint& pos);
    virtual void showDetails();
    void deleteBlock();

private:
    Block *prev {nullptr};
    Block *next {nullptr};
};

#endif // BLOCK_H
