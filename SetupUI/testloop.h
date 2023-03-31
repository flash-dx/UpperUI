#ifndef TESTLOOP_H
#define TESTLOOP_H

#include <QDialog>


namespace Ui {
class TestLoop;
}

class TestLoop : public QDialog
{
    Q_OBJECT

public:
    explicit TestLoop(QWidget *parent = nullptr);
    ~TestLoop();
    static TestLoop* getPtr();

private:
    int caliMachineNo;

private slots:
    void on_pButton_machine_back_clicked();

    void on_pButton_enter_test_clicked();

    void on_pButton_exit_test_clicked();

    void on_comboBox_machine_currentIndexChanged(int index);

//X    void slot_sequenceFinish(SequenceResult result, int machineNo);

    void on_spinBox_test_count_valueChanged(int arg1);

protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

    void enableButton(bool en);
    void load_data();

private:
    Ui::TestLoop *ui;
};

#endif // TESTLOOP_H
