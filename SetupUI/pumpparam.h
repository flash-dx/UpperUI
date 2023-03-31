#ifndef PUMPPARAM_H
#define PUMPPARAM_H

#include <QDialog>

namespace Ui {
class PumpParam;
}

class PumpParam : public QDialog
{
    Q_OBJECT

public:
    explicit PumpParam(QWidget *parent = nullptr);
    ~PumpParam();
    static PumpParam* getPtr();

private:
    int caliMachineNo;

protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

    void load_data(void);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_comboBox_machine_currentIndexChanged(int index);

private:
    Ui::PumpParam *ui;
};

#endif // PUMPPARAM_H
