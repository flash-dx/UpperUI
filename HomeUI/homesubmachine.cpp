#include "homesubmachine.h"
#include "ui_homesubmachine.h"
#include "homestartup.h"
#include "uihandler.h"
#include <QDebug>
static HomeSubMachine *winptr = nullptr;
HomeSubMachine::HomeSubMachine(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HomeSubMachine)
{
    ui->setupUi(this);
    ui->tabWidget->setGeometry(0,0,UIHandler::contentWidth,UIHandler::contentHeight);
    ui->HomeSubMachine_btHome->setGeometry(UIHandler::contentWidth-60,5,40,40);

    foreach(WholeMachine_T *vec, UIHandler::getWholeMacArr()){
        foreach(SubMachine_T *sub, vec->sub){
            ui->tabWidget->addTab(new HomeStartup, QString::fromStdString(sub->name));
            qDebug()<<"addTab"<<sub->machineNO;
        }
    }
    //for (int i = 0; i < 12; i++)
    //    ui->tabWidget->addTab(new HomeStartup,QString("tab_%1").arg(i));
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

void HomeSubMachine::on_HomeSubMachine_btHome_clicked()
{
    UIHandler::GoPage(UIHandler::PageId::Page_Home_AllMachine);
}