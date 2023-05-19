#include "unitmain.h"
#include "ui_unitmain.h"
#include "uihandler.h"
#include <QDebug>
#include "DataUI/dataview.h"
#include "DataUI/datainvaildview.h"
#include "DataUI/dataline.h"

UnitMain::UnitMain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UnitMain)
{
    ui->setupUi(this);
    ui->stackedWidget->setGeometry(0,0,UIHandler::contentWidth,UIHandler::contentHeight-50);
    startupWin = new HomeStartup(this);
    idleWin = new HomeIdle(this);
    testWin = new HomeTest(this);
    dataViewWin = new DataView(this,1);
    invalidWin = new DataInvaildView(this,1);
    lineWin = new DataLine(this,1);

    ui->stackedWidget->addWidget(startupWin);
    ui->stackedWidget->addWidget(idleWin);
    ui->stackedWidget->addWidget(testWin);
    ui->stackedWidget->addWidget(dataViewWin);
    ui->stackedWidget->addWidget(invalidWin);
    ui->stackedWidget->addWidget(lineWin);
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
    }
    else if (stage == Stage_idle){
        if (ui->stackedWidget->currentWidget() != idleWin)
            ui->stackedWidget->setCurrentWidget(idleWin);
        idleWin->UpdateUI(machineNo);
        testWin->resetUi();
    }
    else if (stage == Stage_test){
        if (ui->stackedWidget->currentWidget() != testWin)
            ui->stackedWidget->setCurrentWidget(testWin);
        testWin->UpdateUI(machineNo);
    }
    else if (stage == Stage_result)
    {
        if (ui->stackedWidget->currentWidget() != dataViewWin)
            ui->stackedWidget->setCurrentWidget(dataViewWin);
        testWin->resetUi();
        dataViewWin->updateUI(machineNo);
    }
    else if (stage == Stage_eresult)
    {
        if (ui->stackedWidget->currentWidget() != invalidWin)
            ui->stackedWidget->setCurrentWidget(invalidWin);
        testWin->resetUi();
        invalidWin->updateUI(machineNo);
    }
    else if (stage == Stage_line)
    {
        if (ui->stackedWidget->currentWidget() != lineWin)
            ui->stackedWidget->setCurrentWidget(lineWin);
        lineWin->updateUI(machineNo);
    }
}

void UnitMain::updateChart(int machineNo, int cycle)
{
    HomeStage stage = UIHandler::getStage(machineNo);
    if (stage == Stage_test){
        testWin->updateChart(machineNo,cycle);
    }
}
