#include "homesubmachine.h"
#include "ui_homesubmachine.h"
#include "unitmain.h"
#include "uihandler.h"
#include <QDebug>
static HomeSubMachine *winptr = nullptr;
static QHash<int,UnitMain *> subUI;
HomeSubMachine::HomeSubMachine(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HomeSubMachine)
{
    ui->setupUi(this);
    ui->tabWidget->setGeometry(0,0,UIHandler::contentWidth,UIHandler::contentHeight);
    ui->HomeSubMachine_btHome->setGeometry(UIHandler::contentWidth-60,5,40,40);

    foreach(WholeMachine_T *vec, UIHandler::getWholeMacArr()){
        foreach(SubMachine_T *sub, vec->sub){
            UnitMain *unit = new UnitMain;
            ui->tabWidget->addTab(unit, QString::fromStdString(sub->name));
            subUI[sub->machineNO] = unit;
        }
    }

    connect(UIHandler::getPtr(),&UIHandler::UpdateUI,this,&HomeSubMachine::UpdateUI);
}

HomeSubMachine::~HomeSubMachine()
{
    delete ui;
}

HomeSubMachine *HomeSubMachine::getPtr()
{
    if (winptr == nullptr)
        winptr = new HomeSubMachine;
    return winptr;
}

void HomeSubMachine::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    int currMachineNo = UIHandler::getCurrMachineId();
    if (currMachineNo == -1)
        currMachineNo = UIHandler::getPrevMachineId();
    qDebug()<<"HomeSubMachine::showEvent"<<currMachineNo;
    if (currMachineNo >= 0 && subUI[currMachineNo] != ui->tabWidget->currentWidget()){
        ui->tabWidget->setCurrentWidget(subUI[currMachineNo]);
    }
}

void HomeSubMachine::hideEvent(QHideEvent *event)
{
    Q_UNUSED(event);
    UIHandler::setCurrMachineId(-1);
}

void HomeSubMachine::UpdateUI(int machineNo)
{
    if (subUI.keys().contains(machineNo))
        subUI[machineNo]->UpdateUI(machineNo);
}

void HomeSubMachine::on_HomeSubMachine_btHome_clicked()
{
    UIHandler::GoPage(UIHandler::PageId::Page_Home_AllMachine);
}

void HomeSubMachine::on_tabWidget_currentChanged(int index)
{
    Q_UNUSED(index);
    foreach(int id, subUI.keys()){
        if (subUI[id] == ui->tabWidget->currentWidget())
            UIHandler::setCurrMachineId(id);
    }
}
