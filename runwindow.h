#ifndef RUNWINDOW_H
#define RUNWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>

namespace Ui {
class RunWindow;
}

class RunWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RunWindow(QWidget *parent = nullptr);
    ~RunWindow() override;

private:
    Ui::RunWindow *ui;
    void resetAfterClose();

private slots:
    void on_closeButton_clicked();
    virtual void closeEvent(QCloseEvent *event) override;

signals:
    void runWindowClosed_signal();
};

#endif // RUNWINDOW_H
