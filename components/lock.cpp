#include "lock.h"
#include "ui_lock.h"
#include "../uihandler.h"
#include "mainwin.h"

#include <QStyleOption>
#include <QPainter>

static Lock *messageBox = nullptr;
Lock::Lock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Lock)
{
    ui->setupUi(this);
    int init_x = (UIHandler::contentWidth-675)/2;
    int init_y = (UIHandler::screenHeight-409)/2;
    //setGeometry(init_x,init_y,675,409);
    setGeometry(0,0,UIHandler::contentWidth,UIHandler::screenHeight);
    ui->Com_Lock_lbBack->setGeometry(init_x,init_y,675,409);
    ui->Com_Lock_btUnlock->setGeometry(init_x+(675-67)/2,init_y+275,67,67);
    ui->Com_Lock_lbUser->setGeometry(init_x+0,init_y+70,675,50);
    ui->Com_Lock_lbUser->setAlignment(Qt::AlignCenter);
    ui->Com_LocklePassword->setGeometry(init_x+(675-405)/2,init_y+150,405,70);
    ui->Com_Lock_lbMessage->setGeometry(init_x+400,init_y+285,250,40);
    ui->Com_Lock_lbMessage->setAlignment(Qt::AlignRight);
   // this->setWindowFlag(Qt::FramelessWindowHint);
    //this->setAttribute(Qt::WA_TranslucentBackground,true);

   // ui->Com_Lock_lbBack->setStyleSheet("background: url(:/images/lockbg.png) transparent");
  //  ui->Com_Lock_btUnlock->setStyleSheet("background: url(:/images/lockarrow.png)");
   // ui->Com_Lock_lbUser->setStyleSheet("background: transparent; font-size: 50px");
   // ui->Com_Lock_lbMessage->setStyleSheet("background: transparent; font-size: 40px");

    ui->Com_LocklePassword->setEchoMode(QLineEdit::Password);
}

Lock::~Lock()
{
    delete ui;
}

void Lock::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);    
    QPainter p(this);    
    p.fillRect(rect(),QColor(0,0,0,100));
}

Lock *Lock::getPtr(){
    if (messageBox == nullptr)
    {
        messageBox = new Lock(MainWin::getPtr());
    }
    return messageBox;
}

void Lock::display(){
    getPtr()->ui->Com_Lock_lbUser->setText(UIHandler::getPtr()->getDisplayUser());
    getPtr()->ui->Com_Lock_lbMessage->setText("");
    getPtr()->ui->Com_LocklePassword->setText("");
    getPtr()->ui->Com_LocklePassword->setPlaceholderText(tr("输入密码"));
    getPtr()->setWindowFlags(getPtr()->windowFlags() | Qt::WindowStaysOnTopHint);
    getPtr()->show();
}

void Lock::on_Com_Lock_btUnlock_clicked()
{
    if (UIHandler::getPtr()->Login(UIHandler::getUser(),ui->Com_LocklePassword->text()) == 0){
        messageBox->close();
        UIHandler::getPtr()->GlobalMessage(2);
    }else {
        getPtr()->ui->Com_Lock_lbMessage->setText(tr("密码错误"));
    }
}
