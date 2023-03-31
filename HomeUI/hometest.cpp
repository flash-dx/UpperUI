#include "hometest.h"
#include "ui_hometest.h"

#include <QPainter>

#include "components/twobtnmessagebox.h"
#include "components/onebtnmessagebox.h"
#include "uihandler.h"
#include "homemain.h"
#include "components/Homeloading.h"

#define OFFSET_X -200
#define OFFSET_Y -150
static HomeTest *winptr = nullptr;
HomeTest::HomeTest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HomeTest)
{
    ui->setupUi(this);
    ui->Home_HomeTest_btCancelTest->setGeometry(UIHandler::contentWidth*5/6-299-20,UIHandler::contentHeight*7/8-106-20,299,106);
    ui->Home_HomeTest_lbBK1->setGeometry(358+OFFSET_X,224+OFFSET_Y,368,457);
    ui->Home_HomeTest_lbBK2->setGeometry(1195+OFFSET_X,224+OFFSET_Y,368,457);
    ui->Home_HomeTest_lbTestName->setGeometry(368+OFFSET_X,250+OFFSET_Y,348,130);
    ui->Home_HomeTest_lbTestSerial->setGeometry(368+OFFSET_X,389+OFFSET_Y,348,130);
    ui->Home_HomeTest_lbTestType->setGeometry(368+OFFSET_X,534+OFFSET_Y,348,130);
    ui->Home_HomeTest_lbSampleCode->setGeometry(1205+OFFSET_X,250+OFFSET_Y,348,130);
    ui->Home_HomeTest_lbSampleInfo->setGeometry(1205+OFFSET_X,389+OFFSET_Y,348,130);
    ui->Home_HomeTest_lbSampleRemark->setGeometry(1205+OFFSET_X,534+OFFSET_Y,348,130);
    ui->Home_HomeTest_lbTestName->setAlignment(Qt::AlignCenter);
    ui->Home_HomeTest_lbTestSerial->setAlignment(Qt::AlignCenter);
    ui->Home_HomeTest_lbTestType->setAlignment(Qt::AlignCenter);
    ui->Home_HomeTest_lbSampleCode->setAlignment(Qt::AlignCenter);
    ui->Home_HomeTest_lbSampleInfo->setAlignment(Qt::AlignCenter);
    ui->Home_HomeTest_lbSampleRemark->setAlignment(Qt::AlignCenter);

    setStyleSheet("background-color:#f5f5f5");
    ui->Home_HomeTest_lbTestName->setStyleSheet("background-color:#ffffff;");
    ui->Home_HomeTest_lbTestSerial->setStyleSheet("background-color:#ffffff;");
    ui->Home_HomeTest_lbTestType->setStyleSheet("background-color:#ffffff;");
    ui->Home_HomeTest_lbSampleCode->setStyleSheet("background-color:#ffffff;");
    ui->Home_HomeTest_lbSampleInfo->setStyleSheet("background-color:#ffffff");
    ui->Home_HomeTest_lbSampleRemark->setStyleSheet("background-color:#ffffff");

    ui->Home_HomeTest_lbTestName->setWordWrap(true);
}

HomeTest::~HomeTest()
{
    delete ui;
}

HomeTest *HomeTest::getPtr()
{
    if (winptr == nullptr)
        winptr = new HomeTest;
    return winptr;
}

void HomeTest::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter paint(this);
    paint.fillRect(1920/2-1+OFFSET_X,240+OFFSET_Y,2,400,QColor(0xd9,0xd9,0xd9));
}

void HomeTest::showEvent(QShowEvent *event){
    Q_UNUSED(event);    
    //qDebug()<<"hometest showEvent"<<UIHandler::PanelCode()<<UIHandler::BoxSerial();
    connect(HomeMain::getPtr(),SIGNAL(sig_UpdateUI()),this,SLOT(UpdateUI()));
    connect(TwoBtnMessageBox::getPtr(),&TwoBtnMessageBox::MessageAck,this,&HomeTest::TwoBtnMessageBox_Ack);
    connect(OneBtnMessageBox::getPtr(),&OneBtnMessageBox::MessageAck,this,&HomeTest::on_OneBtnMessageBox_Ack);
    ui->Home_HomeTest_btCancelTest->setText(tr("取消测试"));

    if(HomeLoading::getPtr()->isVisible())
        HomeLoading::hide();
}

void HomeTest::hideEvent(QHideEvent *event){
    Q_UNUSED(event);
    TwoBtnMessageBox::getPtr()->disconnect(this);
    OneBtnMessageBox::getPtr()->disconnect(this);
    HomeMain::getPtr()->disconnect(this);
    TwoBtnMessageBox::hide();
    OneBtnMessageBox::getPtr()->hide();
    if(HomeLoading::getPtr()->isVisible())
        HomeLoading::getPtr()->hide();
}

void HomeTest::on_Home_HomeTest_btCancelTest_clicked()
{
    TwoBtnMessageBox::display(tr("测试进行中，取消后试剂盒作废\n是否取消测试？"),tr("返回测试"),tr("确定取消"),"HomeTest1");
}

void HomeTest::TwoBtnMessageBox_Ack(int ack, QString winname)
{
    //if (winname != "HomeTest") return;
    if (ack == 2)
    {
        if(winname == "HomeTest1" || winname == "HomeTest2")
        {
            //UIHandler::UpdateState(UIHandler::StateId::State_Loading_Open);
            UIHandler::clearMsg();
            UIHandler::CancelTest();
            //UIHandler::clear;
        }
    }
    else {
       if(winname == "HomeTest2")
       {
           UIHandler::clearMsg();
       }
    }
}

void HomeTest::on_OneBtnMessageBox_Ack(int ack ,QString name)
{
    if(name != "hometest")
        return;

    if( ack == 1 )
    {
        UIHandler::getPtr()->ContinueTest();
    }
}

void HomeTest::UpdateUI()
{
    const TestProcessData *data = UIHandler::getTestProcessData();
    if (data == nullptr) return;

    UIHandler::NotifyTitle("test",5);
    if(data->bLoading)
    {
        HomeLoading::display(str2q(data->tips));
    }
    if(data->oneBtnMsgFlag)
    {
        OneBtnMessageBox::display(str2q(data->oneMsginfo.tips),str2q(data->oneMsginfo.btnText),":/images/backTestbt2.png","hometest");
    }
    ui->Home_HomeTest_lbTestName->setText(UIHandler::PanelName()/*+UIHandler::PanelCode()*/);
    ui->Home_HomeTest_lbTestSerial->setText(UIHandler::BoxSerial());
    ui->Home_HomeTest_lbTestType->setText(UIHandler::getSampleTypeName(UIHandler::getSampleType()));
    ui->Home_HomeTest_lbSampleCode->setText(UIHandler::getSampleCode());
    ui->Home_HomeTest_lbSampleInfo->setText(UIHandler::getSampleInfo());
    ui->Home_HomeTest_lbSampleRemark->setText(UIHandler::getSampleRemark());

    QString strMsg = UIHandler::getTwoBtnMsg();
    if(!strMsg.isEmpty())
    {
         TwoBtnMessageBox::display(QString("%1").arg(strMsg)+ tr("，是否继续测试？"),tr("继续测试"),tr("确定取消"), "HomeTest2");
    }
}
