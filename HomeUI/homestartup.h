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
    ~HomeStartup();

protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);
    void timerEvent(QTimerEvent *e);

private:
    Ui::HomeStartup *ui;
};

#endif // HOME_STARTUP_H
