#include "mainwin.h"
#include "ui_mainwin.h"
#include "uihandler.h"

#include "HomeUI/homeallmachine.h"
#include "HomeUI/homemain.h"
#include "HomeUI/homesubmachine.h"
#include "DataUI/datamenu.h"
#include "DataUI/dataline.h"
#include "DataUI/dataview.h"
#include "DataUI/datainvaildview.h"

#include "SetupUI/setupmenu.h"
#include "SetupUI/systemname.h"
#include "SetupUI/lockscreenset.h"
#include "SetupUI/languageset.h"
#include "SetupUI/adminpassword.h"
#include "SetupUI/wifimenu.h"
#include "SetupUI/network.h"
#include "SetupUI/timeset.h"
#include "SetupUI/user.h"
#include "SetupUI/adduser.h"
#include "SetupUI/updateuser.h"
#include "SetupUI/machinecalibration.h"
#include "SetupUI/camerasetup.h"
#include "SetupUI/testloop.h"
#include "SetupUI/projectparam.h"
#include "SetupUI/systemparam.h"
#include "SetupUI/usbfile.h"
#include "SetupUI/light.h"
#include "SetupUI/pumpparam.h"
#include "SetupUI/pidparam.h"
#include "SetupUI/logview.h"
#include "SetupUI/uppermachine.h"
#include "SetupUI/uppermachineSetting.h"
#include "SetupUI/version.h"
#include "SetupUI/version2.h"

const static int FOOTER_HEIGHT = 150;
const static int BOTTOMBUTTON_HEIGHT = 123;
const static int BOTTOM_BUTTON_WIDTH = 342;
static MainWin *winptr = nullptr;

MainWin::MainWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWin)
{
    ui->setupUi(this);

    UIHandler::contentWidth = UIHandler::screenWidth;
    UIHandler::contentHeight = UIHandler::screenHeight - UIHandler::headerHeight - FOOTER_HEIGHT;

    ui->stackedWidget->setGeometry(0,0,UIHandler::contentWidth,UIHandler::contentHeight);
    ui->MainWin_lbFooterBG->setGeometry(0,UIHandler::contentHeight,UIHandler::screenWidth,FOOTER_HEIGHT);

    ui->MainWin_btSetup->setGeometry((UIHandler::screenWidth/3-338)/2+10,UIHandler::contentHeight+14,BOTTOM_BUTTON_WIDTH,BOTTOMBUTTON_HEIGHT);
    ui->MainWin_btSetup->setStyleSheet("QPushButton {font-size:60px;padding-left:30;color:#a7a7a7;background: url(:/images/setuprelease.png)}");
    ui->MainWin_btHome->setGeometry(UIHandler::screenWidth/3+ui->MainWin_btSetup->x(),UIHandler::contentHeight+14,BOTTOM_BUTTON_WIDTH,BOTTOMBUTTON_HEIGHT);
    ui->MainWin_btHome->setStyleSheet("QPushButton {font-size:60px;padding-left:30;color:#ffffff;background: url(:/images/homepress.png);background-repeat:no-repeat}");
    ui->MainWin_btData->setGeometry(UIHandler::screenWidth/3+ui->MainWin_btHome->x(),UIHandler::contentHeight+14,BOTTOM_BUTTON_WIDTH,BOTTOMBUTTON_HEIGHT);
    ui->MainWin_btData->setStyleSheet("QPushButton {font-size:60px;padding-left:30;color:#a7a7a7;background: url(:/images/datarelease.png)}");

    ui->stackedWidget->addWidget(HomeMain::getPtr());
    ui->stackedWidget->addWidget(DataMenu::getPtr());
    ui->stackedWidget->addWidget(DataView::getPtr());
    ui->stackedWidget->addWidget(DataLine::getPtr());
    ui->stackedWidget->addWidget(DataInvaildView::getPtr());
    ui->stackedWidget->addWidget(SetupMenu::getPtr());
    ui->stackedWidget->addWidget(SystemName::getPtr());
    ui->stackedWidget->addWidget(LockScreenSet::getPtr());
    ui->stackedWidget->addWidget(LanguageSet::getPtr());
    ui->stackedWidget->addWidget(AdminPassword::getPtr());
    ui->stackedWidget->addWidget(WifiMenu::getPtr());
    ui->stackedWidget->addWidget(NetWork::getPtr());
    ui->stackedWidget->addWidget(TimeSet::getPtr());
    ui->stackedWidget->addWidget(User::getPtr());
    ui->stackedWidget->addWidget(AddUser::getPtr());
    ui->stackedWidget->addWidget(UpdateUser::getPtr());
    ui->stackedWidget->addWidget(MachineCalibration::getPtr());
    ui->stackedWidget->addWidget(CameraSetup::getPtr());
    ui->stackedWidget->addWidget(TestLoop::getPtr());
    ui->stackedWidget->addWidget(ProjectParam::getPtr());
    ui->stackedWidget->addWidget(UsbFile::getPtr());
    ui->stackedWidget->addWidget(Light::getPtr());
    ui->stackedWidget->addWidget(PumpParam::getPtr());
    ui->stackedWidget->addWidget(PIDParam::getPtr());
    ui->stackedWidget->addWidget(LogView::getPtr());
    ui->stackedWidget->addWidget(UpperMachine::getPtr());
    ui->stackedWidget->addWidget(UpperMachineSetting::getPtr());
    ui->stackedWidget->addWidget(SystemParam::getPtr());
    ui->stackedWidget->addWidget(version::getPtr());
    ui->stackedWidget->addWidget(Version2::getPtr());

    ui->stackedWidget->addWidget(HomeAllMachine::getPtr());
    ui->stackedWidget->addWidget(HomeSubMachine::getPtr());

    connect(UIHandler::getPtr(),&UIHandler::Go,this,&MainWin::GoPage);
    connect(UIHandler::getPtr(),&UIHandler::sig_FooterSetEnabled,this,&MainWin::FooterSetEnabled);
    GoPage(UIHandler::PageId::Page_Home_AllMachine);
}

MainWin::~MainWin()
{
    delete ui;
}

MainWin *MainWin::getPtr()
{
    if (winptr == nullptr)
        winptr = new MainWin;
    return winptr;
}

void MainWin::on_MainWin_btSetup_clicked()
{
    UIHandler::GoPage(UIHandler::PageId::Page_Setup_Menu);
    ui->MainWin_btSetup->setStyleSheet("QPushButton {font-size:60px;padding-left:30;color:#ffffff;background: url(:/images/setuppress.png);background-repeat:no-repeat}");
    ui->MainWin_btHome->setStyleSheet("QPushButton {font-size:60px;padding-left:30;color:#a7a7a7;background: url(:/images/homerelease.png);background-repeat:no-repeat}");
    ui->MainWin_btData->setStyleSheet("QPushButton {font-size:60px;padding-left:30;color:#a7a7a7;background: url(:/images/datarelease.png);background-repeat:no-repeat}");
}

void MainWin::on_MainWin_btHome_clicked()
{
    UIHandler::GoPage(UIHandler::PageId::Page_Home_Main);
    ui->MainWin_btSetup->setStyleSheet("QPushButton {font-size:60px;padding-left:30;color:#a7a7a7;background: url(:/images/setuprelease.png);background-repeat:no-repeat}");
    ui->MainWin_btHome->setStyleSheet("QPushButton {font-size:60px;padding-left:30;color:#ffffff;background: url(:/images/homepress.png);background-repeat:no-repeat}");
    ui->MainWin_btData->setStyleSheet("QPushButton {font-size:60px;padding-left:30;color:#a7a7a7;background: url(:/images/datarelease.png);background-repeat:no-repeat}");
}

void MainWin::on_MainWin_btData_clicked()
{
    UIHandler::GoPage(UIHandler::PageId::Page_Data_Menu);
    ui->MainWin_btSetup->setStyleSheet("QPushButton {font-size:60px;padding-left:30;color:#a7a7a7;background: url(:/images/setuprelease.png);background-repeat:no-repeat}");
    ui->MainWin_btHome->setStyleSheet("QPushButton {font-size:60px;padding-left:30;color:#a7a7a7;background: url(:/images/homerelease.png);background-repeat:no-repeat}");
    ui->MainWin_btData->setStyleSheet("QPushButton {font-size:60px;padding-left:30;color:#ffffff;background: url(:/images/datapress.png);background-repeat:no-repeat}");
}

void MainWin::FooterSetEnabled(bool enable)
{
    ui->MainWin_btSetup->setEnabled(enable);
    ui->MainWin_btHome->setEnabled(enable);
    ui->MainWin_btData->setEnabled(enable);
}

void MainWin::GoPage(UIHandler::PageId id)
{
    qDebug()<<"main GoPage,id="<<id<<ui->stackedWidget->currentWidget()->objectName();
    if (id == UIHandler::PageId::Page_Home_AllMachine && ui->stackedWidget->currentWidget() != HomeAllMachine::getPtr())
        ui->stackedWidget->setCurrentWidget(HomeAllMachine::getPtr());
    else if (id == UIHandler::PageId::Page_Home_Main && ui->stackedWidget->currentWidget() != HomeSubMachine::getPtr())
        ui->stackedWidget->setCurrentWidget(HomeSubMachine::getPtr());
    else if (id == UIHandler::PageId::Page_Data_Menu && ui->stackedWidget->currentWidget() != DataMenu::getPtr())
        ui->stackedWidget->setCurrentWidget(DataMenu::getPtr());
    else if (id == UIHandler::PageId::Page_Data_View && ui->stackedWidget->currentWidget() != DataView::getPtr())
    {
        ui->stackedWidget->setCurrentWidget(DataView::getPtr());
        //set_LbTitle_SampleInfo();
    }
    else if (id == UIHandler::PageId::Page_Data_Line && ui->stackedWidget->currentWidget() != DataLine::getPtr())
    {
        ui->stackedWidget->setCurrentWidget(DataLine::getPtr());
        //set_LbTitle_SampleInfo();
    }
    else if (id == UIHandler::PageId::Page_Data_InvalidView && ui->stackedWidget->currentWidget() != DataInvaildView::getPtr())
    {
        ui->stackedWidget->setCurrentWidget(DataInvaildView::getPtr());
        //set_LbTitle_SampleInfo();
    }
    else if (id == UIHandler::PageId::Page_Setup_Menu && ui->stackedWidget->currentWidget() != SetupMenu::getPtr())
        ui->stackedWidget->setCurrentWidget(SetupMenu::getPtr());
    else if (id == UIHandler::PageId::Page_Setup_SystemName && ui->stackedWidget->currentWidget() != SystemName::getPtr())
        ui->stackedWidget->setCurrentWidget(SystemName::getPtr());
    else if (id == UIHandler::PageId::Page_Setup_LockScreen && ui->stackedWidget->currentWidget() != LockScreenSet::getPtr())
        ui->stackedWidget->setCurrentWidget(LockScreenSet::getPtr());
    else if (id == UIHandler::PageId::Page_Setup_Language && ui->stackedWidget->currentWidget() != LanguageSet::getPtr())
        ui->stackedWidget->setCurrentWidget(LanguageSet::getPtr());
    else if (id == UIHandler::PageId::Page_Setup_Password && ui->stackedWidget->currentWidget() != AdminPassword::getPtr())
        ui->stackedWidget->setCurrentWidget(AdminPassword::getPtr());
    else if (id == UIHandler::PageId::Page_Setup_Wifi && ui->stackedWidget->currentWidget() != WifiMenu::getPtr())
        ui->stackedWidget->setCurrentWidget(WifiMenu::getPtr());
    else if (id == UIHandler::PageId::Page_Setup_Network && ui->stackedWidget->currentWidget() != NetWork::getPtr())
        ui->stackedWidget->setCurrentWidget(NetWork::getPtr());
    else if (id == UIHandler::PageId::Page_Setup_Time && ui->stackedWidget->currentWidget() != TimeSet::getPtr())
        ui->stackedWidget->setCurrentWidget(TimeSet::getPtr());
    else if (id == UIHandler::PageId::Page_Setup_User && ui->stackedWidget->currentWidget() != User::getPtr())
        ui->stackedWidget->setCurrentWidget(User::getPtr());
    else if (id == UIHandler::PageId::Page_User_AddUser && ui->stackedWidget->currentWidget() != AddUser::getPtr())
        ui->stackedWidget->setCurrentWidget(AddUser::getPtr());
    else if (id == UIHandler::PageId::Page_User_UpdateUser && ui->stackedWidget->currentWidget() != UpdateUser::getPtr())
        ui->stackedWidget->setCurrentWidget(UpdateUser::getPtr());
    else if (id == UIHandler::PageId::Page_Setup_Machine && ui->stackedWidget->currentWidget() != MachineCalibration::getPtr())
        ui->stackedWidget->setCurrentWidget(MachineCalibration::getPtr());
    else if (id == UIHandler::PageId::Page_Setup_Camera && ui->stackedWidget->currentWidget() != CameraSetup::getPtr())
        ui->stackedWidget->setCurrentWidget(CameraSetup::getPtr());
    else if (id == UIHandler::PageId::Page_Setup_TestLoop && ui->stackedWidget->currentWidget() != TestLoop::getPtr())
        ui->stackedWidget->setCurrentWidget(TestLoop::getPtr());
    else if (id == UIHandler::PageId::Page_Setup_ProjectParam && ui->stackedWidget->currentWidget() != ProjectParam::getPtr())
        ui->stackedWidget->setCurrentWidget(ProjectParam::getPtr());
    else if (id == UIHandler::PageId::Page_Setup_SystemParam && ui->stackedWidget->currentWidget() != SystemParam::getPtr())
        ui->stackedWidget->setCurrentWidget(SystemParam::getPtr());
    else if (id == UIHandler::PageId::Page_Setup_UsbFile && ui->stackedWidget->currentWidget() != UsbFile::getPtr())
        ui->stackedWidget->setCurrentWidget(UsbFile::getPtr());
    else if (id == UIHandler::PageId::Page_Setup_Light && ui->stackedWidget->currentWidget() != Light::getPtr())
        ui->stackedWidget->setCurrentWidget(Light::getPtr());
    else if (id == UIHandler::PageId::Page_Setup_PumpParam && ui->stackedWidget->currentWidget() != PumpParam::getPtr())
        ui->stackedWidget->setCurrentWidget(PumpParam::getPtr());
    else if (id == UIHandler::PageId::Page_Setup_PID && ui->stackedWidget->currentWidget() != PIDParam::getPtr())
        ui->stackedWidget->setCurrentWidget(PIDParam::getPtr());
    else if (id == UIHandler::PageId::Page_Setup_Log && ui->stackedWidget->currentWidget() != LogView::getPtr())
        ui->stackedWidget->setCurrentWidget(LogView::getPtr());
    else if (id == UIHandler::PageId::Page_Setup_UpperMachine && ui->stackedWidget->currentWidget() != UpperMachine::getPtr())
        ui->stackedWidget->setCurrentWidget(UpperMachine::getPtr());
    else if (id == UIHandler::PageId::Page_Setup_UpperMachineSetting && ui->stackedWidget->currentWidget() != UpperMachineSetting::getPtr())
        ui->stackedWidget->setCurrentWidget(UpperMachineSetting::getPtr());
    else if (id == UIHandler::PageId::Page_Setup_Version){
        if (UIHandler::get_int_Param("ProjectMode") == 0){
            if (id == UIHandler::PageId::Page_Setup_Version && ui->stackedWidget->currentWidget() != Version2::getPtr())
                       ui->stackedWidget->setCurrentWidget(Version2::getPtr());
        }
        else {
            if(ui->stackedWidget->currentWidget() != version::getPtr())
                ui->stackedWidget->setCurrentWidget(version::getPtr());
        }
    }
}
