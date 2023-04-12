#include "hometest.h"
#include "ui_hometest.h"

#include <QPainter>

#include "components/twobtnmessagebox.h"
#include "components/onebtnmessagebox.h"
#include "uihandler.h"

#define OFFSET_X -200
#define OFFSET_Y -150
static HomeTest *winptr = nullptr;
HomeTest::HomeTest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HomeTest)
{
    ui->setupUi(this);
    int tempWidth = 60;
    int spacing = 20;
    ui->Home_HomeTest_btCancelTest->setGeometry(UIHandler::screenWidth-299-20,UIHandler::contentHeight*7/8-106-20,299,106);
    ui->Home_HomeTest_lbTestName->setGeometry(368+OFFSET_X,250+OFFSET_Y,348,tempWidth);
    ui->Home_HomeTest_lbTestSerial->setGeometry(368+OFFSET_X,ui->Home_HomeTest_lbTestName->y()+ui->Home_HomeTest_lbTestName->height()+spacing,348,tempWidth);
    ui->Home_HomeTest_lbTestType->setGeometry(368+OFFSET_X,ui->Home_HomeTest_lbTestSerial->y()+ui->Home_HomeTest_lbTestSerial->height()+spacing,348,tempWidth);
    ui->Home_HomeTest_lbSampleCode->setGeometry(368+OFFSET_X,ui->Home_HomeTest_lbTestType->y()+ui->Home_HomeTest_lbTestType->height()+spacing,348,tempWidth);
    ui->Home_HomeTest_lbSampleInfo->setGeometry(368+OFFSET_X,ui->Home_HomeTest_lbSampleCode->y()+ui->Home_HomeTest_lbSampleCode->height()+spacing,348,tempWidth);
    ui->Home_HomeTest_lbSampleRemark->setGeometry(368+OFFSET_X,ui->Home_HomeTest_lbSampleInfo->y()+ui->Home_HomeTest_lbSampleInfo->height()+spacing,348,tempWidth);
    ui->Home_HomeTest_lbTestName->setAlignment(Qt::AlignLeft);
    ui->Home_HomeTest_lbTestSerial->setAlignment(Qt::AlignLeft);
    ui->Home_HomeTest_lbTestType->setAlignment(Qt::AlignLeft);
    ui->Home_HomeTest_lbSampleCode->setAlignment(Qt::AlignLeft);
    ui->Home_HomeTest_lbSampleInfo->setAlignment(Qt::AlignLeft);
    ui->Home_HomeTest_lbSampleRemark->setAlignment(Qt::AlignLeft);

    ui->Home_HomeTest_lbSampleCode->setText("123456");
    ui->Home_HomeTest_lbSampleInfo->setText("人医");
    ui->Home_HomeTest_lbSampleRemark->setText("五联");
    ui->Home_HomeTest_lbTestProgress->setText(tr("正在测试预计剩余20分钟50秒"));


    ui->Home_HomeTest_lbTestProgress->setGeometry(150,0,600,80);
    //ui->Home_HomeTest_lbTestProgress->setStyleSheet("background-color:#ffffff;");
    setStyleSheet("background-color:#f5f5f5");
//    ui->Home_HomeTest_lbTestName->setStyleSheet("background-color:#ffffff;");
//    ui->Home_HomeTest_lbTestSerial->setStyleSheet("background-color:#ffffff;");
//    ui->Home_HomeTest_lbTestType->setStyleSheet("background-color:#ffffff;");
//    ui->Home_HomeTest_lbSampleCode->setStyleSheet("background-color:#ffffff;");
//    ui->Home_HomeTest_lbSampleInfo->setStyleSheet("background-color:#ffffff");
//    ui->Home_HomeTest_lbSampleRemark->setStyleSheet("background-color:#ffffff");


    ui->Home_HomeTest_lbTestName->setWordWrap(true);
    initUi();
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
//    QPainter paint(this);
//    paint.fillRect(1920/2-1+OFFSET_X,240+OFFSET_Y,2,400,QColor(0xd9,0xd9,0xd9));
}

void HomeTest::showEvent(QShowEvent *event){
    Q_UNUSED(event);    
    //qDebug()<<"hometest showEvent"<<UIHandler::PanelCode()<<UIHandler::BoxSerial();
    //connect(HomeMain::getPtr(),SIGNAL(sig_UpdateUI()),this,SLOT(UpdateUI()));
    connect(TwoBtnMessageBox::getPtr(),&TwoBtnMessageBox::MessageAck,this,&HomeTest::TwoBtnMessageBox_Ack);
    connect(OneBtnMessageBox::getPtr(),&OneBtnMessageBox::MessageAck,this,&HomeTest::on_OneBtnMessageBox_Ack);
    ui->Home_HomeTest_btCancelTest->setText(tr("取消测试"));
}

void HomeTest::hideEvent(QHideEvent *event){
    Q_UNUSED(event);
    TwoBtnMessageBox::getPtr()->disconnect(this);
    OneBtnMessageBox::getPtr()->disconnect(this);
    //HomeMain::getPtr()->disconnect(this);
    TwoBtnMessageBox::hide();
    OneBtnMessageBox::getPtr()->hide();
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
        //HomeLoading::display(str2q(data->tips));
    }
    if(data->oneBtnMsgFlag)
    {
        OneBtnMessageBox::display(str2q(data->oneMsginfo.tips),str2q(data->oneMsginfo.btnText),":/images/backTestbt2.png","hometest");
    }
    ui->Home_HomeTest_lbTestName->setText(UIHandler::PanelName()/*+UIHandler::PanelCode()*/);
    ui->Home_HomeTest_lbTestSerial->setText(UIHandler::BoxSerial());
    ui->Home_HomeTest_lbTestType->setText(UIHandler::getSampleTypeName(UIHandler::getSampleType()));
//    ui->Home_HomeTest_lbSampleCode->setText(UIHandler::getSampleCode());
//    ui->Home_HomeTest_lbSampleInfo->setText(UIHandler::getSampleInfo());
//    ui->Home_HomeTest_lbSampleRemark->setText(UIHandler::getSampleRemark());

    QString strMsg = UIHandler::getTwoBtnMsg();
    if(!strMsg.isEmpty())
    {
         TwoBtnMessageBox::display(QString("%1").arg(strMsg)+ tr("，是否继续测试？"),tr("继续测试"),tr("确定取消"), "HomeTest2");
    }
}

void HomeTest::initUi()
{
    chart = new QChart;
    axisX = new QValueAxis;
    axisX->setRange(0,50);
    QFont LabelFont;
    LabelFont.setPixelSize(25);
    axisX->setLabelsFont(LabelFont);
    //axisX->setTitleText("cycle");
    axisX->setTickCount(6);
    axisX->setMinorTickCount(9);
    axisX->setLabelFormat("%d");
    axisY = new QCategoryAxis;
    axisY->setLabelsFont(LabelFont);
    axisY->setRange(-10,50);
    //axisY->setTitleText("brightness");
    axisY->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
    chart->addAxis(axisX,Qt::AlignBottom);
    chart->addAxis(axisY,Qt::AlignLeft);
    chartView = new QChartView(chart,this);

    chartView->setGeometry(UIHandler::contentWidth/2-100,UIHandler::contentHeight/6+30,UIHandler::contentWidth/2,UIHandler::contentHeight*1/2);
    chart->setTitleFont(QFont("黑体",40));


    QStringList itemName;
    itemName<<"HRV/HEV"<<"RSV"<<"SARS-CoV-2"<<"PIV"<<"MP"<<"ADV"<<"Flu-B"<<"Flu-A";

    int tempWidth = 250;
    int tempHeight = 60 ;
    int xSpacing = 20;
    int ySpacing = 20;
    int tempx = chartView->geometry().x();
    int tempy = chartView->geometry().y() - 2*tempHeight -20;

    for (int i = 0; i < itemName.size(); i++){
        QPushButton *btn = new QPushButton(itemName[i], this);
        btn->setGeometry(tempx+(tempWidth+xSpacing)*int(i%4),tempy + (tempHeight+ySpacing)*int(i/4),tempWidth,tempHeight);
        btn->setObjectName(itemName[i]);
        btn->setText(itemName[i]);
        if(itemName[i] == TestModel::getCurrItemName())
        {
            btn->setStyleSheet("border-radius:10px;background-color:#3584E4;color:#FFFFFF;font:bold 10px");
        }
        else
        {
            btn->setStyleSheet("border-radius:10px;background-color:#cccccc;color:#000000");
        }
       // connect(btn,&QPushButton::clicked,this,&DataLine::on_Item_clicked);
        btn->show();
        //btnlist.append(btn);
    }
}
