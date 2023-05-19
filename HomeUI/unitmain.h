#ifndef UNITMAIN_H
#define UNITMAIN_H

#include <QDialog>
#include "homeidle.h"
#include "hometest.h"
#include "homestartup.h"
namespace Ui {
class UnitMain;
}

class UnitMain : public QDialog
{
    Q_OBJECT

public:
    explicit UnitMain(QWidget *parent = nullptr);
    ~UnitMain();
    void UpdateUI(int machineNo);
    void updateChart(int machineNo,int cycle);

private:
    Ui::UnitMain *ui;
    HomeStartup *startupWin;
    HomeIdle *idleWin;
    HomeTest *testWin;
};

#endif // UNITMAIN_H
