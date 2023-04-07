#ifndef HOME_IDLE_H
#define HOME_IDLE_H

#include <QDialog>
#include <QMovie>
#include "uihandler.h"

namespace Ui {
class HomeIdle;
}

class HomeIdle : public QDialog
{
    Q_OBJECT
public:
    explicit HomeIdle(QWidget *parent = nullptr);
    ~HomeIdle();
    static HomeIdle *getPtr();

protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

private slots:
    void on_Home_Idle_btOpenDoor_clicked();
    void UpdateUI();
    //void TwoBtnMessageBox_Ack(int ack);
    void OneBtnMessageBox_Ack(int ack);
    void on_Home_Idle_btPen_clicked();
    void Sample_Changed(QString res1, QString res2, QString res3);
    void InputBox_Close();
    void on_Home_Idle_btReady_clicked();

    void on_Home_Idle_btSequence_clicked();
    void slot_DoorKeyDown(int machineNo);

signals:
    void sig_QrCodeChange(int result);

private:
    Ui::HomeIdle *ui;        
    QMovie *movie;


};

#endif // IDLE_H
