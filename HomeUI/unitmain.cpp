#include "unitmain.h"
#include "ui_unitmain.h"
#include "uihandler.h"
#include <QDebug>

UnitMain::UnitMain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UnitMain)
{
    ui->setupUi(this);
    ui->stackedWidget->setGeometry(0,0,UIHandler::contentWidth,UIHandler::contentHeight-50);
    startupWin = new HomeStartup(this);
    idleWin = new HomeIdle(this);
    testWin = new HomeTest(this);
    ui->stackedWidget->addWidget(startupWin);
    ui->stackedWidget->addWidget(idleWin);
    ui->stackedWidget->addWidget(testWin);
}

UnitMain::~UnitMain()
{
    delete ui;
}

void UnitMain::UpdateUI(int machineNo)
{
    HomeStage stage = UIHandler::getStage(machineNo);
    qDebug()<<"UnitMain::UpdateUI"<<stage;
    if (stage == Stage_selfcheck){
        if (ui->stackedWidget->currentWidget() != startupWin)
            ui->stackedWidget->setCurrentWidget(startupWin);
        startupWin->UpdateUI(machineNo);
    }
    else if (stage == Stage_idle){
        if (ui->stackedWidget->currentWidget() != idleWin)
            ui->stackedWidget->setCurrentWidget(idleWin);
    }
    else if (stage == Stage_test){
        if (ui->stackedWidget->currentWidget() != testWin)
            ui->stackedWidget->setCurrentWidget(testWin);
    }
}
