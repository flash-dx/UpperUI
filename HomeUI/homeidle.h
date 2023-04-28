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
    void UpdateUI(int machineNo);

protected:
    void showEvent(QShowEvent *event);

private slots:
    void on_Home_Idle_btOpenDoor_clicked();
    void on_Home_Idle_btPen_clicked();

private:
    Ui::HomeIdle *ui;        
    QMovie *movie;
    void DisplayStep(bool bDisplay);


};

#endif // IDLE_H
