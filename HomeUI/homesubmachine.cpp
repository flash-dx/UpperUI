#include "homesubmachine.h"
#include "ui_homesubmachine.h"
#include "homestartup.h"
#include "uihandler.h"
#include <QDebug>
static HomeSubMachine *winptr = nullptr;
static QHash<int,HomeStartup *> subUI;
HomeSubMachine::HomeSubMachine(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HomeSubMachine)
{
    ui->setupUi(this);
    ui->tabWidget->setGeometry(0,0,UIHandler::contentWidth,UIHandler::contentHeight);
    ui->HomeSubMachine_btHome->setGeometry(UIHandler::contentWidth-60,5,40,40);

    foreach(WholeMachine_T *vec, UIHandler::getWholeMacArr()){
        foreach(SubMachine_T *sub, vec->sub){
            HomeStartup *startup = new HomeStartup;
            ui->tabWidget->addTab(startup, QString::fromStdString(sub->name));
            subUI[sub->machineNO] = startup;
            qDebug()<<"addTab"<<sub->machineNO;
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

void HomeSubMachine::UpdateUI(int machineNo)
{
    qDebug()<<"HomeSubMachine::UpdateUI"<<machineNo;
    if (subUI.keys().contains(machineNo))
        subUI[machineNo]->Update();
}

void HomeSubMachine::on_HomeSubMachine_btHome_clicked()
{
    UIHandler::GoPage(UIHandler::PageId::Page_Home_AllMachine);
}
