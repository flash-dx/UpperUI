#include "hometest.h"
#include "ui_hometest.h"

#include <QLineSeries>
#include <QPainter>

#include "components/twobtnmessagebox.h"
#include "components/onebtnmessagebox.h"
#include "uihandler.h"

HomeTest::HomeTest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HomeTest)
{
    ui->setupUi(this);
    setStyleSheet("background-color:#f5f5f5");

    ui->Home_HomeTest_lbTestProgress->setGeometry(60,0,700,80);

    ui->Home_HomeTest_lbTestName->setGeometry(60,120,700,60);
    ui->Home_HomeTest_lbTestSerial->setGeometry(60,ui->Home_HomeTest_lbTestName->y()+80,700,60);
    ui->Home_HomeTest_lbTestType->setGeometry(60,ui->Home_HomeTest_lbTestSerial->y()+80,700,60);
    ui->Home_HomeTest_lbSampleCode->setGeometry(60,ui->Home_HomeTest_lbTestType->y()+80,700,60);
    ui->Home_HomeTest_lbSampleInfo->setGeometry(60,ui->Home_HomeTest_lbSampleCode->y()+80,700,60);
    ui->Home_HomeTest_lbSampleRemark->setGeometry(60,ui->Home_HomeTest_lbSampleInfo->y()+80,700,60);
    ui->Home_HomeTest_lbTestName->setAlignment(Qt::AlignHCenter);
    ui->Home_HomeTest_lbTestSerial->setAlignment(Qt::AlignHCenter);
    ui->Home_HomeTest_lbTestType->setAlignment(Qt::AlignHCenter);
    ui->Home_HomeTest_lbSampleCode->setAlignment(Qt::AlignHCenter);
    ui->Home_HomeTest_lbSampleInfo->setAlignment(Qt::AlignHCenter);
    ui->Home_HomeTest_lbSampleRemark->setAlignment(Qt::AlignHCenter);

    ui->Home_HomeTest_btCancelTest->setGeometry(UIHandler::screenWidth-299-20,UIHandler::contentHeight*7/8-106-20,299,106);

    initUi();
}

HomeTest::~HomeTest()
{
    delete ui;
}

void HomeTest::showEvent(QShowEvent *event){
    Q_UNUSED(event);

    TestModel::setCurrTestById(UIHandler::getSubCurTestId());

    ui->Home_HomeTest_lbTestName->setText(UIHandler::PanelName());
    ui->Home_HomeTest_lbTestSerial->setText(UIHandler::BoxSerial());
    ui->Home_HomeTest_lbTestType->setText(UIHandler::getSampleTypeName(UIHandler::getSampleType()));
    ui->Home_HomeTest_lbSampleCode->setText(UIHandler::getSampleCode());
    ui->Home_HomeTest_lbSampleInfo->setText(UIHandler::getSampleInfo());
    ui->Home_HomeTest_lbSampleRemark->setText(UIHandler::getSampleRemark());

    ui->Home_HomeTest_btCancelTest->setText(tr("取消测试"));

    updateItem();

    connect(UIHandler::getPtr(),&UIHandler::TestProgress,this,[=](int complete, int total, int machineNo){

         if (machineNo != UIHandler::getCurrMachineId())
             return;


         ui->Home_HomeTest_lbTestProgress->setText(tr("正在测试，预计剩余")+QString::number(total-complete)+tr("秒"));
     });
}

void HomeTest::hideEvent(QHideEvent *event){
    Q_UNUSED(event);
    TwoBtnMessageBox::getPtr()->disconnect(this);
    OneBtnMessageBox::getPtr()->disconnect(this);
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

void HomeTest::on_Item_clicked()
{
    qDebug()<<"on_Item_clicked"<<focusWidget()->objectName();
    TestModel::setCurrItemName(focusWidget()->objectName());
    foreach (QPushButton *pBtn, list)
    {
        if(pBtn->objectName() == TestModel::getCurrItemName())
        {
            pBtn->setStyleSheet("border-radius:10px;background-color:#3584E4;color:#FFFFFF");
        }
        else
        {
            pBtn->setStyleSheet("border-radius:10px;background-color:#cccccc;color:#000000");
        }
    }

    foreach (QString label, axisY->categoriesLabels())
        axisY->remove(label);


    updateChart();
}

void HomeTest::UpdateUI(int machineNo)
{
    updateChart();
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
}

void HomeTest::updateChart()
{
    chart->setTitle(TestModel::getCurrItemName());
    chart->removeAllSeries();
    axisY->setRange(-10,50);
    QString itemName = TestModel::getCurrItemName();
    int testid = TestModel::getCurrTestId();
    int ct = TestModel::getItemCT(testid,itemName);
    qDebug()<<"HomeTest showEvent testid="<<testid<<"ct="<<ct<<"itemName"<<itemName;
    axisY->append(QString::number(ct),ct);
    TestData *data = TestModel::getTestData(testid);
    if (data == nullptr)
        return;
    for(auto it : data->PosId){
        int itemid = it.second/*data->PosId[it.first]*/;
        if (UIHandler::getItemName(itemid) == itemName){
            QLineSeries *line = new QLineSeries;
            line->setName(QString("P%1").arg(it.first));
            chart->addSeries(line);
            line->attachAxis(axisX);
            line->attachAxis(axisY);

            for (size_t i = 0; i < data->posArr[it.first].size(); i++){
                if (data->posArr[it.first][i].y() > axisX->max() - 10)
                    axisY->setMax(data->posArr[it.first][i].y()+10);
                line->append(data->posArr[it.first][i].x(),data->posArr[it.first][i].y());
            }
        }
    }
}

void HomeTest::updateItem()
{
    foreach (QPushButton *btn, list)
        delete btn;
    list.clear();

    QStringList itemName = TestModel::getTestName(UIHandler::getSubCurTestId());
    //itemName<<"HRV/HEV"<<"RSV"<<"SARS-CoV-2"<<"PIV"<<"MP"<<"ADV"<<"Flu-B"<<"Flu-A";

    int tempWidth = 250;
    int tempHeight = 60 ;
    int xSpacing = 20;
    int ySpacing = 20;
    int tempx = chartView->geometry().x();
    int tempy = chartView->geometry().y() - 2*tempHeight -20;

    for (int i = 0; i < itemName.size(); i++){
        QPushButton *btn = new QPushButton(itemName[i], this);
        connect(btn,&QPushButton::clicked,this,&HomeTest::on_Item_clicked);
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

        btn->show();
        list.append(btn);
    }

    const TestProcessData *data = UIHandler::getTestProcessData(UIHandler::getCurrMachineId());
    if (data == nullptr) return;
    ui->Home_HomeTest_lbTestProgress->setText(tr("正在测试，预计剩余")+QString::number(data->nTotal-data->nComplete)+tr("秒"));

    if(data->bLoading)
    {
        //HomeLoading::display(str2q(data->tips));
    }
    if(data->oneBtnMsgFlag)
    {
        OneBtnMessageBox::display(str2q(data->oneMsginfo.tips),str2q(data->oneMsginfo.btnText),":/images/backTestbt2.png","hometest");
    }

    QString strMsg = UIHandler::getTwoBtnMsg();
    if(!strMsg.isEmpty())
    {
         TwoBtnMessageBox::display(QString("%1").arg(strMsg)+ tr("，是否继续测试？"),tr("继续测试"),tr("确定取消"), "HomeTest2");
    }
}
