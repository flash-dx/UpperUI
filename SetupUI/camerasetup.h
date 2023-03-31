#ifndef CAMERASETUP_H
#define CAMERASETUP_H

#include <QDialog>
#include <QImage>
#include <string>

using namespace std;

namespace Ui {
class CameraSetup;
}

class CameraSetup : public QDialog
{
    Q_OBJECT

public:
    explicit CameraSetup(QWidget *parent = nullptr);
    ~CameraSetup();
    virtual void timerEvent(QTimerEvent *e);
    static CameraSetup* getPtr();

private:
    bool bView= false;
    int caliMachineNo;

protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

    void sendSubParam();
    void load_data(void);
    void updataTlvData();

private slots:
    void on_pButton_backl_clicked();

    void on_pButton_open_view_clicked();

    void on_pButton_stop_view_clicked();

    void on_pButton_open_light_clicked();

    void on_pButton_close_light_clicked();

    void on_pButton_auto_focus_clicked();

    void on_pButton_time_clicked();

    void on_pButton_gain_clicked();

    void on_pButton_focus_clicked();

    void on_pButton_reset_clicked();

    void on_pButton_temp_clicked();

    void on_pButton_area_clicked();

    void on_cBox_show_box_clicked();

    void CameraView(QImage img,int machineNo = 0);
    void on_pButton_picture_clicked();

    void on_cBox_show_box_stateChanged(int arg1);
    void slot_autoFocusNotify(int status, int value, int machineNo);

    void on_comboBox_machine_currentIndexChanged(int index);

    void slot_CamerView(string imgstr, int machineNo);

    void on_comboBox_lightLevel_currentIndexChanged(int index);

    void on_pButton_shutter_on_clicked();

    void on_pButton_shutter_off_clicked();

private:
    Ui::CameraSetup *ui;
};

#endif // CAMERASETUP_H
