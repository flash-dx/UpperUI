#include "systemparam.h"
#include "ui_systemparam.h"

#include "../uihandler.h"


static SystemParam *winptr = nullptr;

SystemParam *SystemParam::getPtr()
{
    if (winptr == nullptr)
        winptr = new SystemParam;
    return winptr;
}

SystemParam::SystemParam(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SystemParam)
{
    ui->setupUi(this);

    ui->rButton_normal->setStyleSheet("QRadioButton::indicator{width:35px;height:35px;}");
    ui->rButton_play->setStyleSheet("QRadioButton::indicator{width:35px;height:35px;}");
    ui->rButton_check->setStyleSheet("QRadioButton::indicator{width:35px;height:35px;}");
    ui->rButton_project->setStyleSheet("QRadioButton::indicator{width:35px;height:35px;}");
    ui->rButton_test->setStyleSheet("QRadioButton::indicator{width:35px;height:35px;}");

    ui->pButton_machine_back->setGeometry(UIHandler::contentWidth-299-100,UIHandler::contentHeight-106-30,299,106);
    ui->groupBox->setGeometry((UIHandler::contentWidth-600)/2,(UIHandler::contentHeight-600)/2,600,600);
    setStyleSheet("background-color:#f5f5f5;");
}

SystemParam::~SystemParam()
{
    delete ui;
}

static int preProjectMode;
void SystemParam::showEvent(QShowEvent *event){
    Q_UNUSED(event);

    ui->retranslateUi(this);
    preProjectMode = UIHandler::getPtr()->get_int_Param("ProjectMode");
    if (UIHandler::getPtr()->get_int_Param("ProjectMode")==0)
        ui->rButton_project->setChecked(true);
    else if (UIHandler::getPtr()->get_int_Param("ProjectMode")==2)
        ui->rButton_check->setChecked(true);
    else if (UIHandler::getPtr()->get_int_Param("ProjectMode")==3)
        ui->rButton_play->setChecked(true);
    else if (UIHandler::getPtr()->get_int_Param("ProjectMode")==4)
        ui->rButton_test->setChecked(true);
    else
        ui->rButton_normal->setChecked(true);

    UIHandler::setBtTextCenter(ui->pButton_machine_back, 48,"background-image: url(:/images/back.png);text-align:left;padding-bottom:20px;");

    UIHandler::NotifyTitle("setup_sysparam",5);
}

void SystemParam::hideEvent(QHideEvent *event){
    Q_UNUSED(event);

}

void SystemParam::on_rButton_normal_clicked()
{
     UIHandler::getPtr()->updata_int_Param("ProjectMode",1);
}

void SystemParam::on_rButton_project_clicked()
{
     UIHandler::getPtr()->updata_int_Param("ProjectMode",0);
}

void SystemParam::on_rButton_check_clicked()
{
     UIHandler::getPtr()->updata_int_Param("ProjectMode",2);
}

void SystemParam::on_rButton_play_clicked()
{
     UIHandler::getPtr()->updata_int_Param("ProjectMode",3);
}

void SystemParam::on_rButton_test_clicked()
{
     UIHandler::getPtr()->updata_int_Param("ProjectMode",4);
}

void SystemParam::on_pButton_machine_back_clicked()
{
    if (UIHandler::getPtr()->get_int_Param("ProjectMode") != preProjectMode)
        ;//UIHandler::UpdateState(UIHandler::StateId::State_SetupMenu_Update);
     UIHandler::GoPage(UIHandler::PageId::Page_Setup_Menu);
}
