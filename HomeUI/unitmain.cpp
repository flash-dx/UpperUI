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
    startupWin = new HomeStartup;
    idleWin = new HomeIdle;
    testWin = new HomeTest;
    ui->stackedWidget->addWidget(startupWin);
    ui->stackedWidget->addWidget(idleWin);
    ui->stackedWidget->addWidget(testWin);
}

UnitMain::~UnitMain()
{
    delete ui;
}

void UnitMain::UpdateUI()
{
    HomeStage stage = UIHandler::getStage();
    qDebug()<<"UnitMain::UpdateUI";
    if (stage == Stage_selfcheck && ui->stackedWidget->currentWidget() != startupWin)
        ui->stackedWidget->setCurrentWidget(startupWin);
    else if (stage == Stage_idle && ui->stackedWidget->currentWidget() != idleWin)
        ui->stackedWidget->setCurrentWidget(idleWin);
    else if (stage == Stage_test && ui->stackedWidget->currentWidget() != testWin)
        ui->stackedWidget->setCurrentWidget(testWin);
}
