#include "logindlg.h"
#include "ui_logindlg.h"

#include "uihandler.h"
#include "components/twobtnmessagebox.h"

#include <QDebug>
#include <QListView>
#include <QPalette>

static LoginDlg *winptr = nullptr;

LoginDlg::LoginDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDlg)
{
    ui->setupUi(this);
    ui->LoginDlg_lbBG->setGeometry((UIHandler::screenWidth-811)/2,(UIHandler::screenHeight-UIHandler::headerHeight-485)/2,811,485);
    ui->LoginDlg_lbLogo->setGeometry((UIHandler::screenWidth-272)/2,ui->LoginDlg_lbBG->y()+49,272,64);
    ui->LoginDlg_lbLogo->setStyleSheet("background-color:rgba(255,255,255,100)");
    ui->LoginDlg_cbName->setGeometry((UIHandler::screenWidth-640)/2,ui->LoginDlg_lbBG->y()+141,640,71);
    ui->LoginDlg_txtPassword->setGeometry(ui->LoginDlg_cbName->x(),ui->LoginDlg_lbBG->y()+235,640,70);
    ui->LoginDlg_btLogin->setGeometry((UIHandler::screenWidth-315)/2,ui->LoginDlg_lbBG->y()+347,315,91);
    ui->LoginDlg_btLogin->setStyleSheet("background-color:rgba(255,255,255,100)");
    ui->LoginDlg_cbName->setView(new QListView);
    ui->LoginDlg_lbMessage->setGeometry(ui->LoginDlg_btLogin->x()+ui->LoginDlg_btLogin->width()+10,ui->LoginDlg_btLogin->y()-20,230,40);
    ui->LoginDlg_lbMessage->setAlignment(Qt::AlignLeft);
    ui->LoginDlg_lbMessage->setStyleSheet("background-color:rgba(255,255,255,100)");

    ui->LoginDlg_btQuit->setGeometry(UIHandler::screenWidth-299-100,UIHandler::screenHeight-UIHandler::headerHeight-106-30,299,106);
    ui->LoginDlg_btQuit->setText(tr("关机"));

    QPalette  plateUser = ui->LoginDlg_cbName->palette();
    QColor color(255,255,255);
    plateUser.setColor(QPalette::Normal,QPalette::PlaceholderText,color);
    ui->LoginDlg_cbName->setPalette(plateUser);

    QPalette  platePwd = ui->LoginDlg_txtPassword->palette();
    platePwd.setColor(QPalette::Normal,QPalette::PlaceholderText,color);
    ui->LoginDlg_txtPassword->setPalette(platePwd);

    QObjectList list =ui->LoginDlg_cbName->children();
    Q_FOREACH(QObject *obj,list)
    {
        if(obj->metaObject()->className() == QStringLiteral("QLineEdit"))
        {
            qobject_cast<QLineEdit *>(obj)->setPlaceholderText(tr("用户名"));
            qobject_cast<QLineEdit *>(obj)->setMaxLength(20);
        }
    }
}

LoginDlg::~LoginDlg()
{
    delete ui;
}

LoginDlg *LoginDlg::getPtr()
{
    if (winptr == nullptr)
        winptr = new LoginDlg;
    return winptr;
}

void LoginDlg::showEvent(QShowEvent *event){
    Q_UNUSED(event);
    ui->LoginDlg_cbName->clear();
    ui->LoginDlg_cbName->addItems(UIHandler::getLogUser());

    ui->LoginDlg_cbName->setCurrentIndex(-1);
    ui->LoginDlg_txtPassword->clear();

    //connect(TwoBtnMessageBox::getPtr(),&TwoBtnMessageBox::MessageAck,this,&LoginDlg::TwoBtnMessageBox_Ack);
}

void LoginDlg::hideEvent(QHideEvent *event){
    Q_UNUSED(event);
    //TwoBtnMessageBox::getPtr()->disconnect(this);
}

void LoginDlg::on_LoginDlg_btLogin_clicked()
{
    int result = UIHandler::Login(ui->LoginDlg_cbName->currentText(),ui->LoginDlg_txtPassword->text());
    if (result == 0)
    {
        ui->LoginDlg_lbMessage->setText("");
        emit UIHandler::getPtr()->EnterLogin(false);
    }
    else if (result == 1)
    {
        ui->LoginDlg_lbMessage->setText(tr("密码错误！"));
    }
    else
    {
        ui->LoginDlg_lbMessage->setText(tr("帐号不存在！"));
    }

}

void LoginDlg::on_LoginDlg_btQuit_clicked()
{
    TwoBtnMessageBox::display(tr("您将关机？"),tr("取消"),tr("确认"));
}

void LoginDlg::TwoBtnMessageBox_Ack(int ack)
{
    if (ack == 2)
        UIHandler::PowerOff();
}
