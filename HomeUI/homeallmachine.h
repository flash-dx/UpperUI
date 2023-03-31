#ifndef HOMEALLMACHINE_H
#define HOMEALLMACHINE_H

#include <QDialog>
#include <QLabel>

typedef enum{
    TYPE_TCPICON,
    TYPE_DOORICON,
    TYPE_BOXICON,
    TYPE_MESSAGEICON,
}ICONTYPE;


namespace Ui {
class HomeAllMachine;
}

class HomeAllMachine : public QDialog
{
    Q_OBJECT

public:
    static HomeAllMachine *getPtr();
    ~HomeAllMachine();
protected:
    void showEvent(QShowEvent *event);
    virtual void hideEvent(QHideEvent *event) Q_DECL_OVERRIDE ;
    bool eventFilter(QObject *obj, QEvent *event);
private slots:
    void on_machine_Clicked(int machineNo);
    void slot_DoorKeyDown(int machineNo);

    void on_pBtn_PowerOff_clicked();

    void on_pBtn_loginOut_clicked();

private:
    explicit HomeAllMachine(QWidget *parent = nullptr);
private:
    void initUi();
    void updateStatus(QLabel *lb1 ,int machineNo);
    void updateIcon(ICONTYPE type,int machineNo);

private:
    Ui::HomeAllMachine *ui;
};

#endif // HOMEALLMACHINE_H
