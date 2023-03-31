#include "e04.h"
#include "ui_e04.h"

#include "uihandler.h"
#include "HomeUI/homemain.h"
static E04 * E04Ptr;

E04::E04(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::E04)
{
    ui->setupUi(this);

    ui->Home_E04_lbError->setGeometry(0,(UIHandler::contentHeight*7/8-400)/2,UIHandler::contentWidth *5/6,400);
    ui->Home_E04_lbError->setAlignment(Qt::AlignCenter);
    ui->Home_E04_lbError->setWordWrap(true);
    ui->Home_E04_lbError->setStyleSheet("color:red;");
    ui->Home_E04_lbMessage->setGeometry(0,ui->Home_E04_lbError->y()+120,UIHandler::contentWidth*5/6,400);
    ui->Home_E04_lbMessage->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
    ui->Home_E04_lbMessage->setWordWrap(true);
    ui->Home_E04_lbMessage->setVisible(false);
}

E04 *E04::getPtr()
{
    if(E04Ptr == nullptr)
    {
        E04Ptr = new E04();
    }
    return E04Ptr;
}

E04::~E04()
{
    delete ui;
}

void E04::showEvent(QShowEvent *event){
    Q_UNUSED(event);

    connect(HomeMain::getPtr(),&HomeMain::sig_UpdateUI,this,&E04::slot_updateUi);

}

void E04::hideEvent(QHideEvent *event){
    Q_UNUSED(event);
    HomeMain::getPtr()->disconnect(this);
}

void E04::slot_updateUi()
{
    const ErrorInfo *info = UIHandler::getErrInfo();

    QString tips ;
    int type = info->type;
    tips = str2q(info->errInfo);
    if(tips.isEmpty())
        tips = tr("仪器未连接");

    ui->Home_E04_lbError->setText(tips);
    if(type == ErrType_NotConn)
        UIHandler::NotifyTitle("warning",5);
    else
        UIHandler::NotifyTitle("error",5);
}

