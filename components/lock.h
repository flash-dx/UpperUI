#ifndef LOCK_H
#define LOCK_H

#include <QWidget>

namespace Ui {
class Lock;
}

class Lock : public QWidget
{
    Q_OBJECT

public:
    explicit Lock(QWidget *parent = nullptr);
    ~Lock();
    static Lock *getPtr();
    static void display();

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_Com_Lock_btUnlock_clicked();

private:
    Ui::Lock *ui;
};

#endif // LOCK_H
