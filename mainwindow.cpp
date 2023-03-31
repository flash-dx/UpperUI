#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "uihandler.h"
#include <QScreen>
#include <QDebug>
#include <QDateTime>

#include "logindlg.h"
#include "mainwin.h"

static MainWindow *mainWindow = nullptr;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mainWindow = this;
    UISetup();
    UIHandler::Init();

    ui->stackedWidget->addWidget(LoginDlg::getPtr());
    ui->stackedWidget->addWidget(MainWin::getPtr());

    ui->stackedWidget->setCurrentWidget(LoginDlg::getPtr());

    connect(UIHandler::getPtr(),&UIHandler::EnterLogin,this,&MainWindow::EnterLogin);
    startTimer(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);
    ui->MainWindow_lbTime->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
}

const static int HEADER_HEIGHT = 50;

void MainWindow::UISetup()
{
    int screenWidth = QGuiApplication::screens().at(0)->geometry().width();
    int screenHeight = QGuiApplication::screens().at(0)->geometry().height();
    screenWidth = 1920;
    screenHeight = 1080;

    //showFullScreen();

    UIHandler::screenWidth = screenWidth;
    UIHandler::screenHeight = screenHeight;
    UIHandler::headerHeight = HEADER_HEIGHT;

    setGeometry(0,0,screenWidth,screenHeight);

    ui->MainWindow_lbTitleBG->setGeometry(0,0,screenWidth,HEADER_HEIGHT);
    ui->stackedWidget->setGeometry(0,HEADER_HEIGHT,screenWidth,screenHeight-HEADER_HEIGHT);

    ui->MainWindow_lbUser->setGeometry(50,0,350,HEADER_HEIGHT);
    ui->MainWindow_lbUser->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
    ui->MainWindow_lbUser->setStyleSheet("font-size: 30px; color: #b5b5b5; background: transparent;");
    ui->MainWindow_lbTime->setGeometry(screenWidth - 350, 0, 350, HEADER_HEIGHT);
    ui->MainWindow_lbTime->setAlignment(Qt::AlignCenter);
    ui->MainWindow_lbTime->setStyleSheet("font-size: 30px; color: #b5b5b5; background: transparent;");
    ui->MainWindow_lbTime->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
}

void MainWindow::EnterLogin(bool bEnter)
{
    if (bEnter){
        ui->stackedWidget->setCurrentWidget(LoginDlg::getPtr());
        ui->MainWindow_lbUser->setText("");
    }
    else{
        ui->stackedWidget->setCurrentWidget(MainWin::getPtr());
        ui->MainWindow_lbUser->setText(UIHandler::getDisplayUser());
    }
}
