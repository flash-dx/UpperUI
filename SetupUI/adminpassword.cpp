#include "adminpassword.h"
#include "ui_adminpassword.h"
#include "../uihandler.h"
#include <QMessageBox>
#include "components/twobutton.h"

static AdminPassword *winptr = nullptr;

AdminPassword *AdminPassword::getPtr()
{
    if (winptr == nullptr)
        winptr = new AdminPassword;
    return winptr;
}

AdminPassword::AdminPassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminPassword)
{
    ui->setupUi(this);

    int init_x = (UIHandler::contentWidth-798)/2;
    int init_y = (UIHandler::contentHeight-375)/2;

    ui->label_background->setGeometry(init_x,init_y,798,375);
    ui->label_oldpwd->setGeometry(init_x+20,init_y+60,260,64);
    ui->lineEdit_oldpwd->setGeometry(init_x+320,init_y+60,400,64);
    ui->label_newpwd->setGeometry(init_x+20,ui->label_oldpwd->y()+94,260,64);
    ui->lineEdit_newpwd->setGeometry(init_x+320,ui->label_oldpwd->y()+94,400,64);
    ui->label_newpwd_2->setGeometry(init_x+20,ui->label_newpwd->y()+94,260,64);
    ui->lineEdit_newpwd_2->setGeometry(init_x+320,ui->label_newpwd->y()+94,400,64);
    ui->label_msg->setGeometry(init_x,init_y+400,798,50);
    ui->label_msg->setAlignment(Qt::AlignCenter);
    ui->pushButton_Cencel->setGeometry(UIHandler::contentWidth-299-100,UIHandler::contentHeight-106-30,299,106);
    ui->pushButton_OK->setGeometry(UIHandler::contentWidth-299-100,ui->pushButton_Cencel->y()-106-20,299,106);
    ui->lineEdit_oldpwd->setEchoMode(QLineEdit::Password);
    ui->lineEdit_newpwd->setEchoMode(QLineEdit::Password);
    ui->lineEdit_newpwd_2->setEchoMode(QLineEdit::Password);
    setStyleSheet("QWidget{background-color:#f5f5f5;}QLabel{background:transparent}QLineEdit{background-color:#f5f5f5;}");
}

AdminPassword::~AdminPassword()
{
    delete ui;
}

void AdminPassword::showEvent(QShowEvent *event){
    Q_UNUSED(event);

    ui->label_oldpwd->setText(tr("旧密码"));
    ui->label_newpwd->setText(tr("新密码"));
    ui->label_newpwd_2->setText(tr("确认新密码"));
    ui->label_msg->setText("");
    ui->pushButton_OK->setText(tr("确定"));
    ui->pushButton_Cencel->setText(tr("取消"));
    ui->lineEdit_oldpwd->setText("");
    ui->lineEdit_newpwd->setText("");
    ui->lineEdit_newpwd_2->setText("");

    UIHandler::setBtTextCenter(ui->pushButton_OK, 48,"background-image: url(:/images/confirmbt.png);text-align:left;");
    UIHandler::setBtTextCenter(ui->pushButton_Cencel, 48,"background-image: url(:/images/cancelbt.png);text-align:left;");

    UIHandler::NotifyTitle("setup_passwd",5);
}

void AdminPassword::hideEvent(QHideEvent *event){
    Q_UNUSED(event);

}

void AdminPassword::on_pushButton_OK_clicked()
{
    if (ui->lineEdit_oldpwd->text()=="")
     {
        ui->label_msg->setText(tr("密码不能为空！"));
        return;
      }
    if (ui->lineEdit_newpwd->text()=="")
     {
        ui->label_msg->setText(tr("新密码不能为空！"));
        return;
      }

    if (ui->lineEdit_newpwd->text()!=ui->lineEdit_newpwd_2->text())
     {
        ui->label_msg->setText(tr("新密码和确认密码必须相同！"));
        return;
      }

     if( UIHandler::get_string_Param("AdminPassword") != ui->lineEdit_oldpwd->text())
     {
        ui->label_msg->setText(tr("密码错误！"));
        return;
     }

     UIHandler::updata_string_Param("AdminPassword",ui->lineEdit_newpwd->text());
     if( UIHandler::get_string_Param("AdminPassword") != ui->lineEdit_newpwd->text())
     {
         ui->label_msg->setText(tr("修改失败!"));
         return;
     }
     UIHandler::GoPage(UIHandler::PageId::Page_Setup_Menu);
}

void AdminPassword::on_pushButton_Cencel_clicked()
{
      UIHandler::GoPage(UIHandler::PageId::Page_Setup_Menu);
}
