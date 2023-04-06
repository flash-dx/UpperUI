#ifndef HOMESUBMACHINE_H
#define HOMESUBMACHINE_H

#include <QDialog>

namespace Ui {
class HomeSubMachine;
}

class HomeSubMachine : public QDialog
{
    Q_OBJECT

public:
    explicit HomeSubMachine(QWidget *parent = nullptr);
    ~HomeSubMachine();
    static HomeSubMachine *getPtr();

private slots:
    void on_HomeSubMachine_btHome_clicked();

private:
    Ui::HomeSubMachine *ui;
};

#endif // HOMESUBMACHINE_H
