#ifndef PIDPARAM_H
#define PIDPARAM_H

#include <QDialog>

namespace Ui {
class PIDParam;
}

class PIDParam : public QDialog
{
    Q_OBJECT

public:
    explicit PIDParam(QWidget *parent = nullptr);
    ~PIDParam();
    static PIDParam* getPtr();

private:
    int caliMachineNo;

protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);


    void load_data(void);
    void SetCaliParam();

private slots:
    void on_PIDParam_accepted();

    void on_pButton_machine_back_clicked();

    void on_pushButton_clicked();

    void on_comboBox_machine_currentIndexChanged(int index);

private:
    Ui::PIDParam *ui;
};

#endif // PIDPARAM_H
