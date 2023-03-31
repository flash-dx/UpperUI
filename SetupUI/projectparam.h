#ifndef PROJECTPARAM_H
#define PROJECTPARAM_H

#include <QDialog>

namespace Ui {
class ProjectParam;
}

class ProjectParam : public QDialog
{
    Q_OBJECT

public:
    explicit ProjectParam(QWidget *parent = nullptr);
    ~ProjectParam();

    static ProjectParam* getPtr();

private:
    int caliMachineNo;

private slots:
    void on_pButton_machine_back_clicked();

    void on_rButton_c1_clicked();

    void on_rButton_c2_clicked();

    void on_rButton_c3_clicked();

    void on_rButton_c4_clicked();

    void on_rButton_c5_clicked();

    void on_rButton_b1_clicked();

    void on_rButton_b2_clicked();

    void on_spinBox_high_valueChanged(int arg1);

    void on_spinBox_pre_valueChanged(const QString &arg1);

    void on_comboBox_machine_currentIndexChanged(int index);

    void on_checkBox_temp_clicked(bool checked);

protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

    void load_data(void);

private:
    Ui::ProjectParam *ui;
};

#endif // PROJECTPARAM_H
