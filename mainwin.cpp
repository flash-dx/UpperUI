#include "mainwin.h"
#include "ui_mainwin.h"
#include "uihandler.h"

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

    ui->stackedWidget->setGeometry(0,UIHandler::headerHeight,UIHandler::contentWidth,UIHandler::contentHeight);
    ui->MainWin_lbFooterBG->setGeometry(0,UIHandler::screenHeight-FOOTER_HEIGHT,UIHandler::screenWidth,FOOTER_HEIGHT);

    ui->MainWin_btSetup->setGeometry((UIHandler::screenWidth/3-338)/2+10,UIHandler::screenHeight-FOOTER_HEIGHT+14,BOTTOM_BUTTON_WIDTH,BOTTOMBUTTON_HEIGHT);
    ui->MainWin_btSetup->setStyleSheet("QPushButton {font-size:60px;padding-left:30;color:#a7a7a7;background: url(:/images/setuprelease.png)}");
    ui->MainWin_btHome->setGeometry(UIHandler::screenWidth/3+ui->MainWin_btSetup->x(),UIHandler::screenHeight-FOOTER_HEIGHT+14,BOTTOM_BUTTON_WIDTH,BOTTOMBUTTON_HEIGHT);
    ui->MainWin_btHome->setStyleSheet("QPushButton {font-size:60px;padding-left:30;color:#ffffff;background: url(:/images/homepress.png);background-repeat:no-repeat}");
    ui->MainWin_btData->setGeometry(UIHandler::screenWidth/3+ui->MainWin_btHome->x(),UIHandler::screenHeight-FOOTER_HEIGHT+14,BOTTOM_BUTTON_WIDTH,BOTTOMBUTTON_HEIGHT);
    ui->MainWin_btData->setStyleSheet("QPushButton {font-size:60px;padding-left:30;color:#a7a7a7;background: url(:/images/datarelease.png)}");
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
