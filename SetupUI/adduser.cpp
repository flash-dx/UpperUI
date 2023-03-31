#include "adduser.h"
#include "ui_adduser.h"
#include "../uihandler.h"


static AddUser *winptr = nullptr;

AddUser *AddUser::getPtr()
{
    if (winptr == nullptr)
        winptr = new AddUser;
    return winptr;
}

AddUser::AddUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUser)
{
    ui->setupUi(this);
    //show_data();

    int btnW = 299;
    int btnH = 106;
    int btnRight = 100;
    int btnBottom = 30;
    int btnLeft = UIHandler::contentWidth - btnW - btnRight;
    int btnTop = UIHandler::contentHeight - btnBottom - btnH;
    int btnAdd = 20;

    ui->label_background->setGeometry(566,180,811,485);

    ui->label_adduser_user->setGeometry(609,272,225,60);
    ui->lEdit_adduser_user->setGeometry(848,258,404,64);
    ui->label_adduser_disp_name->setGeometry(575,353,255,60);
    ui->lEdit_adduser_disp_name->setGeometry(848,339,404,64);
    ui->label_adduser_pwd->setGeometry(581,434,250,60);
    ui->lEdit_adduser_pwd->setGeometry(848,420,404,64);
    ui->label_adduser_pwd_2->setGeometry(575,514,258,60);
    ui->lEdit_adduser_pwd_2->setGeometry(848,500,404,64);
    ui->cBox_adduser_type->setGeometry(850,581,400,40);
    ui->lEdit_adduser_pwd_2->setEchoMode(QLineEdit::Password);
    ui->lEdit_adduser_pwd->setEchoMode(QLineEdit::Password);
    ui->label_adduser_hint->setGeometry(566,680,811,64);
    ui->label_adduser_hint->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
    ui->label_adduser_hint->setWordWrap(true);

    ui->pushButton->setGeometry(btnLeft, btnTop - (btnH + btnAdd),   btnW,btnH);
    ui->pushButton_2->setGeometry(btnLeft,  btnTop,                     btnW,btnH);

    setStyleSheet("QWidget{background-color:#f5f5f5;}QLabel{background:transparent;}QCheckBox{background-color:#ffffff;}");
    ui->label_adduser_hint->setStyleSheet("QWidget{background-color:#f5f5f5;}");
}

void AddUser::show_data()
{

}

AddUser::~AddUser()
{
    delete ui;
}

void AddUser::showEvent(QShowEvent *event){
    Q_UNUSED(event);
    show_data();

    ui->cBox_adduser_type->setIconSize(QSize(40,40));
    ui->cBox_adduser_type->setStyleSheet("QCheckBox::indicator{width:35px;height:35px;}");

    ui->lEdit_adduser_user->setText("");
    ui->lEdit_adduser_disp_name->setText("");
    ui->lEdit_adduser_pwd->setText("");
    ui->lEdit_adduser_pwd_2->setText("");
    ui->cBox_adduser_type->setChecked(false);

    ui->label_adduser_user->setText(tr("帐号"));
    ui->label_adduser_disp_name->setText(tr("显示名"));
    ui->label_adduser_pwd->setText(tr("密码"));
    ui->label_adduser_pwd_2->setText(tr("确认密码"));
    ui->pushButton->setText(tr("   确认添加"));
    ui->pushButton_2->setText(tr("  返回"));
    ui->cBox_adduser_type->setText(tr("审核权限"));
    ui->label_adduser_hint->setVisible(false);
    ui->label_adduser_hint->text().clear();

    UIHandler::setBtTextCenter(ui->pushButton, 48,"background-image: url(:/images/confirmbt.png);text-align:left;");
    UIHandler::setBtTextCenter(ui->pushButton_2, 48,"background-image: url(:/images/back.png);text-align:left;");

    UIHandler::NotifyTitle("setup_useradd",5);
}

void AddUser::hideEvent(QHideEvent *event){
    Q_UNUSED(event);
 qDebug()<<"AddUser::hideEvent";
}

void AddUser::on_pushButton_clicked()
{
    ui->label_adduser_hint->setVisible(true);
    if (ui->lEdit_adduser_user->text()=="")
    {
        ui->label_adduser_hint->setText(tr("帐号不能为空！"));
        return;
    }
    if (ui->lEdit_adduser_disp_name->text()=="")
    {
        ui->label_adduser_hint->setText(tr("显示名不能为空！"));
        return;
    }

    if (ui->lEdit_adduser_pwd->text()=="")
    {
        ui->label_adduser_hint->setText(tr("密码不能为空！"));
        return;
    }

    if (ui->lEdit_adduser_pwd->text()!=ui->lEdit_adduser_pwd_2->text())
    {
        ui->label_adduser_hint->setText(tr("密码和确认密码必须相同！"));
        return;
    }
    if(UIHandler::isUserNameExist( ui->lEdit_adduser_user->text() ))
    {
        ui->label_adduser_hint->setText(tr("帐号已存在!"));
        return;
    }
    ui->label_adduser_hint->setVisible(false);
    bool bRes = UIHandler::addUser( ui->lEdit_adduser_user->text(),ui->lEdit_adduser_pwd_2->text(),ui->lEdit_adduser_disp_name->text(),ui->cBox_adduser_type->checkState()?3:1);
    if(bRes == false)
    {
        ui->label_adduser_hint->setText(tr("添加帐号失败!"));
        return;
    }
    UIHandler::GoPage(UIHandler::PageId::Page_Setup_User);
}

void AddUser::on_pushButton_2_clicked()
{
    UIHandler::GoPage(UIHandler::PageId::Page_Setup_User);
}
