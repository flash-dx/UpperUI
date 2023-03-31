#ifndef LIGHT_H
#define LIGHT_H

#include <QDialog>
#include <string>

namespace Ui {
class Light;
}

class Light : public QDialog
{
    Q_OBJECT

public:
    explicit Light(QWidget *parent = nullptr);
    ~Light();
    static Light* getPtr();

private:
    int caliMachineNo;

    void load_data();

private slots:
    void on_pButton_backl_clicked();

    void on_pButton_work_clicked();

    void on_pButton_hard_clicked();

    void on_pButton_set_clicked();

    void on_pButton_set_xy_clicked();

    void on_pButton_get_light_clicked();

    void on_comboBox_machine_currentIndexChanged(int index);

    void CameraView(std::string imgstr, int machineNo);
    void RefreshLight(int lightvalue, int machineNo);

protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

private:
    Ui::Light *ui;
};

#endif // LIGHT_H
