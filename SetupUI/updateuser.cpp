#include "updateuser.h"
#include "ui_updateuser.h"
#include "../uihandler.h"
#include <QMessageBox>

#include "components/twobutton.h"


static UpdateUser *winptr = nullptr;

UpdateUser *UpdateUser::getPtr()
{
    if (winptr == nullptr)
        winptr = new UpdateUser;
    return winptr;
}

UpdateUser::UpdateUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateUser)
{
    ui->setupUi(this);

    int btnW = 299;
    int btnH = 106;
    int btnRight = 100;
    int btnBottom = 30;
    int btnLeft = UIHandler::contentWidth - btnW - btnRight;
    int btnTop = UIHandler::contentHeight - btnBottom - btnH;
    int btnAdd = 20;

    ui->pButton_edituser_ok->setGeometry(btnLeft, btnTop - (btnH + btnAdd),   btnW,btnH);
    ui->pButton_edituser_back->setGeometry(btnLeft, btnTop,                     btnW,btnH);

    ui->label_background->setGeometry(566,180,811,485);

    ui->label_edituser_user->setGeometry(609,272,225,60);
    ui->lEdit_edituser_user->setGeometry(848,258,404,64);
    ui->label_edituser_disp_name->setGeometry(575,353,255,60);
    ui->lEdit_edituser_disp_name->setGeometry(848,339,404,64);
    ui->label_edituser_pwd->setGeometry(581,434,250,60);
    ui->lEdit_edituser_pwd->setGeometry(848,420,404,64);
    ui->label_edituser_pwd_2->setGeometry(575,514,258,60);
    ui->lEdit_edituser_pwd_2->setGeometry(848,500,404,64);
    ui->cBox_edituser_type->setGeometry(850,581,250,40);

    ui->label_msg->setGeometry(566,671,810,50);
    ui->label_msg->setAlignment(Qt::AlignCenter);


    ui->lEdit_edituser_pwd_2->setEchoMode(QLineEdit::Password);
    ui->lEdit_edituser_pwd->setEchoMode(QLineEdit::Password);
    setStyleSheet("QWidget{background-color:#f5f5f5;}QLabel{background:transparent;}QCheckBox{background-color:#ffffff;}");
}

void UpdateUser::show_data()
{
    //qDebug()<<"UpdateUser::show_data--getCurrIndex=="<<UIHandler::pUserModel->getCurrIndex();
    //qDebug()<<"UpdateUser::show_data--getCurName=="<<UIHandler::pUserModel->getCurName();
    QList<USERINFO> userList = UIHandler::getUserList();
    ui->lEdit_edituser_user->setText(str2q(userList[currUserIndex].name));
    ui->lEdit_edituser_disp_name->setText(str2q(userList[currUserIndex].displayname));
    ui->lEdit_edituser_pwd->setText("");
    ui->lEdit_edituser_pwd_2->setText("");
    if (userList[currUserIndex].usertype==3)
        ui->cBox_edituser_type->setChecked(true);
    else
        ui->cBox_edituser_type->setChecked(false);

}

UpdateUser::~UpdateUser()
{
    delete ui;
}

void UpdateUser::showEvent(QShowEvent *event){
    Q_UNUSED(event);

    currUserIndex = UIHandler::getCurrUserListIndex();
   show_data();

   ui->label_edituser_user->setText(tr("帐号"));
   ui->label_edituser_disp_name->setText(tr("显示名"));
   ui->label_edituser_pwd->setText(tr("新密码"));
   ui->label_edituser_pwd_2->setText(tr("确认新密码"));
   ui->pButton_edituser_ok->setText(tr("   确认修改"));
   ui->pButton_edituser_back->setText(tr("  返回"));
   ui->cBox_edituser_type->setText(tr("审核权限"));
   ui->label_msg->setText("");

   ui->cBox_edituser_type->setIconSize(QSize(40,40));
   ui->cBox_edituser_type->setStyleSheet("QCheckBox::indicator{width:35px;height:35px;}");

   UIHandler::setBtTextCenter(ui->pButton_edituser_ok, 48,"background-image: url(:/images/confirmbt.png);text-align:left;");
   UIHandler::setBtTextCenter(ui->pButton_edituser_back, 48,"background-image: url(:/images/back.png);text-align:left;");

   UIHandler::NotifyTitle("setup_userupdate",5);

}

void UpdateUser::hideEvent(QHideEvent *event){
    Q_UNUSED(event);

}

void UpdateUser::on_pButton_edituser_back_clicked()
{
    UIHandler::GoPage(UIHandler::PageId::Page_Setup_User);
}

void UpdateUser::on_pButton_edituser_ok_clicked()
{
    int type          = ui->cBox_edituser_type->checkState()? 3:1;
    QString user      = ui->lEdit_edituser_user->text();
    QString disp_name =ui->lEdit_edituser_disp_name->text();
    QString pwd       = ui->lEdit_edituser_pwd->text();
    QString pwd_2     = ui->lEdit_edituser_pwd_2->text();

     if(pwd == "" && pwd_2 == "")
     {
         QList<USERINFO> userList = UIHandler::getUserList();
         if(type == userList[currUserIndex].usertype)
             return;
     }
     else if (user == "")
     {
         ui->label_msg->setText(tr("用户名不能为空！"));
        return;
      }
    else if (pwd == "")
     {
        ui->label_msg->setText(tr("密码不能为空！"));
        return;
      }
    else if (pwd != pwd_2)
     {
        ui->label_msg->setText(tr("密码和确认密码必须相同！"));
        return;
      }
    UIHandler::updateUser(user, pwd_2, disp_name, type);
    UIHandler::GoPage(UIHandler::PageId::Page_Setup_User);
}
