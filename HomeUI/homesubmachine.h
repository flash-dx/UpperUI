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

protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

private slots:
    void UpdateUI(int machineNo);
    void on_HomeSubMachine_btHome_clicked();

    void on_tabWidget_currentChanged(int index);

private:
    Ui::HomeSubMachine *ui;
};

#endif // HOMESUBMACHINE_H
