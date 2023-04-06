#ifndef HOME_STARTUP_H
#define HOME_STARTUP_H

#include <QDialog>
#include <QMovie>
#include "uihandler.h"

namespace Ui {
class HomeStartup;
}

class HomeStartup : public QDialog
{
    Q_OBJECT

public:
    explicit HomeStartup(QWidget *parent = nullptr);
public:
    ~HomeStartup();
    static HomeStartup *getPtr();

protected:
    void timerEvent(QTimerEvent *e);
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

private slots:
    void on_Home_Startup_btOpenDoor_clicked();
    void UpdateUI();


private:
    Ui::HomeStartup *ui;
    QMovie *movie;
};

#endif // HOME_STARTUP_H
