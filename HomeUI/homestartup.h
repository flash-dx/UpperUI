#ifndef HOME_STARTUP_H
#define HOME_STARTUP_H

#include <QDialog>
#include <QMovie>

namespace Ui {
class HomeStartup;
}

class HomeStartup : public QDialog
{
    Q_OBJECT

public:
    explicit HomeStartup(QWidget *parent = nullptr);
    void UpdateUI(int machineNo);

public:
    ~HomeStartup();

protected:
    void timerEvent(QTimerEvent *e);

private slots:
    void on_Home_Startup_btOpenDoor_clicked();


private:
    Ui::HomeStartup *ui;
    QMovie *movie;
};

#endif // HOME_STARTUP_H
