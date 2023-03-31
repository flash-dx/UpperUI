#include "mainwin.h"
#include "ui_mainwin.h"
#include "uihandler.h"

#include "HomeUI/homeidle.h"
#include "HomeUI/homestartup.h"
#include "HomeUI/homeready.h"
#include "HomeUI/hometest.h"
#include "HomeUI/homeallmachine.h"
#include "DataUI/dataview.h"
#include "DataUI/datainvaildview.h"
#include "DataUI/dataline.h"
#include "components/e04.h"

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

    ui->stackedWidget->addWidget(DataView::getPtr(1));
    ui->stackedWidget->addWidget(DataInvaildView::getPtr(1));
    ui->stackedWidget->addWidget(DataLine::getPtr(1));
    ui->stackedWidget->addWidget(HomeStartup::getPtr());
    ui->stackedWidget->addWidget(HomeIdle::getPtr());
    ui->stackedWidget->addWidget(HomeReady::getPtr());
    ui->stackedWidget->addWidget(HomeTest::getPtr());
    ui->stackedWidget->addWidget(E04::getPtr());
    ui->stackedWidget->addWidget(HomeAllMachine::getPtr());

    ui->stackedWidget->setCurrentWidget(HomeAllMachine::getPtr());
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
