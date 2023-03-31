#include "homeready.h"
#include "ui_homeready.h"

#include "components/threequery.h"
#include "components/twobtnmessagebox.h"
#include "components/onebtnmessagebox.h"
#include "uihandler.h"

#include <QListView>

static HomeReady *winptr = nullptr;

HomeReady::HomeReady(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HomeReady)
{
    ui->setupUi(this);
    ui->Home_HomeReady_btStart->setGeometry((UIHandler::contentWidth*5/6-219)/2-100,(UIHandler::contentHeight*7/8-224)/2-100,219,224);
    ui->Home_HomeReady_lbTips->setGeometry((UIHandler::contentWidth*5/6-350)/2-100,ui->Home_HomeReady_btStart->y()+250,350,200);
    ui->Home_HomeReady_lbTips->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
    ui->Home_HomeReady_lbTips->setWordWrap(true);

    ui->Home_HomeReady_btCancelTest->setGeometry(UIHandler::contentWidth*5/6-299-20,UIHandler::contentHeight*7/8-106-20,299,106);
    ui->Home_HomeReady_lbBK1->setGeometry(ui->Home_HomeReady_btStart->x()-368-80,(UIHandler::contentHeight*7/8-457)/2-50,368,457);
    ui->Home_HomeReady_lbBK2->setGeometry(ui->Home_HomeReady_btStart->x()+219+80,(UIHandler::contentHeight*7/8-457)/2-50,368,457);
    ui->Home_HomeReady_btPen->setGeometry(ui->Home_HomeReady_lbBK2->x()+368+100,(UIHandler::contentHeight*7/8-76)/2-50,75,76);
    ui->Home_HomeReady_lbTestName->setGeometry(ui->Home_HomeReady_lbBK1->x()+10,ui->Home_HomeReady_lbBK1->y()+26,348,130);
    ui->Home_HomeReady_lbTestName->setAlignment(Qt::AlignCenter);
    ui->Home_HomeReady_lbTestName->setWordWrap(true);

    ui->Home_HomeReady_lbTestSerial->setGeometry(ui->Home_HomeReady_lbBK1->x()+10,ui->Home_HomeReady_lbBK1->y()+165,348,130);
    ui->Home_HomeReady_lbTestSerial->setAlignment(Qt::AlignCenter);
    ui->Home_HomeReady_cbTestType->setGeometry(ui->Home_HomeReady_lbBK1->x()+32,ui->Home_HomeReady_lbBK1->y()+346,300,60);
    ui->Home_HomeReady_cbTestType->setView(new QListView);
    ui->Home_HomeReady_lbSampleCode->setGeometry(ui->Home_HomeReady_lbBK2->x()+10,ui->Home_HomeReady_lbBK2->y()+26,348,130);
    ui->Home_HomeReady_lbSampleInfo->setGeometry(ui->Home_HomeReady_lbBK2->x()+10,ui->Home_HomeReady_lbBK1->y()+165,348,130);
    ui->Home_HomeReady_lbSampleRemark->setGeometry(ui->Home_HomeReady_lbBK2->x()+10,ui->Home_HomeReady_lbBK1->y()+310,348,130);

    ui->Home_HomeReady_lbSampleCode->setWordWrap(true);
    ui->Home_HomeReady_lbSampleCode->setAlignment(Qt::AlignCenter);
    ui->Home_HomeReady_lbSampleInfo->setAlignment(Qt::AlignCenter);
    ui->Home_HomeReady_lbSampleRemark->setAlignment(Qt::AlignCenter);

    setStyleSheet("background-color:#f5f5f5");
    ui->Home_HomeReady_lbTestName->setStyleSheet("background-color:#ffffff");
    ui->Home_HomeReady_lbTestSerial->setStyleSheet("background-color:#ffffff");

    ui->Home_HomeReady_cbTestType->setView(new QListView());

    ui->Home_HomeReady_lbSampleCode->setStyleSheet("background-color:#ffffff");
    ui->Home_HomeReady_lbSampleInfo->setStyleSheet("background-color:#ffffff");
    ui->Home_HomeReady_lbSampleRemark->setStyleSheet("background-color:#ffffff");

    ui->Home_HomeReady_lbBK2->installEventFilter(this);
    ui->Home_HomeReady_lbSampleCode->installEventFilter(this);
    ui->Home_HomeReady_lbSampleInfo->installEventFilter(this);
    ui->Home_HomeReady_lbSampleRemark->installEventFilter(this);
}

HomeReady::~HomeReady()
{
    delete ui;
}

HomeReady *HomeReady::getPtr()
{
    if (winptr == nullptr)
        winptr = new HomeReady;
    return winptr;
}

void HomeReady::showEvent(QShowEvent *event){
    Q_UNUSED(event);
    //UIHandler::setStage(HomeStage::Stage_ready);
    UIHandler::NotifyTitle("boxready",5);
    ui->Home_HomeReady_lbTestName->setText(UIHandler::PanelName()/*+UIHandler::PanelCode()*/);
    ui->Home_HomeReady_lbTestSerial->setText(UIHandler::BoxSerial());
    ui->Home_HomeReady_cbTestType->clear();
    ui->Home_HomeReady_cbTestType->addItems(UIHandler::getSampleTypeArr());

    UIHandler::setLabelWordWrap(ui->Home_HomeReady_lbSampleCode,UIHandler::getSampleCode());
    //ui->Home_HomeReady_lbSampleCode->setText(UIHandler::getSampleCode());
    ui->Home_HomeReady_lbSampleInfo->setText(UIHandler::getSampleInfo());
    ui->Home_HomeReady_lbSampleRemark->setText(UIHandler::getSampleRemark());
    ui->Home_HomeReady_btCancelTest->setText(tr("取消测试"));

    ChangedTips();
    connect(ThreeQuery::getPtr(),&ThreeQuery::queryAck,this,&HomeReady::Sample_Changed);
    connect(TwoBtnMessageBox::getPtr(),&TwoBtnMessageBox::MessageAck,this,&HomeReady::TwoBtnMessageBox_Ack,Qt::UniqueConnection);
    connect(UIHandler::getPtr(),&UIHandler::sig_errorSql,this,[=](int machiNo){
        OneBtnMessageBox::display(tr("测试创建失败，请检查是否含有非法字符！"),tr("返回"));
        return;
    });
}

void HomeReady::hideEvent(QHideEvent *event){
    Q_UNUSED(event);
    ThreeQuery::getPtr()->disconnect(this);
    TwoBtnMessageBox::getPtr()->disconnect(this);
    OneBtnMessageBox::getPtr()->disconnect(this);
    UIHandler::getPtr()->disconnect(this);
}

bool HomeReady::eventFilter(QObject *obj, QEvent *event)
{
    Q_UNUSED(obj);
    if (event->type() == QEvent::MouseButtonRelease){
        on_Home_HomeReady_btPen_clicked();
        return true;
    }
    return false;
}

void HomeReady::ChangedTips()
{
    if (UIHandler::getSampleCode().isEmpty()){
        ui->Home_HomeReady_btStart->setStyleSheet("background-image:url(:/images/UStartTest.png)");
        ui->Home_HomeReady_lbTips->setText(tr("样本号不能为空 请输入样本号"));
        ui->Home_HomeReady_lbTips->setStyleSheet("color: #FC7052");
        ui->Home_HomeReady_btStart->setEnabled(false);

    }
    else{
        ui->Home_HomeReady_btStart->setStyleSheet("background-image:url(:/images/StartTest.png)");
        ui->Home_HomeReady_lbTips->setText(tr("开始测试"));
        ui->Home_HomeReady_lbTips->setStyleSheet("color: #4c4c4c");
        ui->Home_HomeReady_btStart->setEnabled(true);
    }
}

void HomeReady::Sample_Changed(QString res1, QString res2, QString res3)
{
    UIHandler::setSampleCode(res1);
    UIHandler::setSampleInfo(res2);
    UIHandler::setSampleRemark(res3);
    UIHandler::setLabelWordWrap(ui->Home_HomeReady_lbSampleCode,res1);
    //ui->Home_HomeReady_lbSampleCode->setText(res1);
    ui->Home_HomeReady_lbSampleInfo->setText(res2);
    ui->Home_HomeReady_lbSampleRemark->setText(res3);
    ChangedTips();
}

void HomeReady::TwoBtnMessageBox_Ack(int ack, QString winName)
{
    if (winName != "HomeReady") return;
    if (ack == 2)
        UIHandler::CancelTest();
}

void HomeReady::on_Home_HomeReady_btPen_clicked()
{
    int id = UIHandler::getCurrMachineId();
    ThreeQuery::display(tr("样本信息录入"),tr("样本号"),tr("样本信息"),tr("样本备注"),
                        UIHandler::getSampleCode(),UIHandler::getSampleInfo(),UIHandler::getSampleRemark());
}

void HomeReady::on_Home_HomeReady_btCancelTest_clicked()
{
    TwoBtnMessageBox::display(tr("是否取消测试？"),tr("返回测试"),tr("确定取消"),"HomeReady");
}

void HomeReady::on_Home_HomeReady_btStart_clicked()
{
    UIHandler::ReadyStartTest();
}

void HomeReady::on_Home_HomeReady_cbTestType_currentIndexChanged(int index)
{
    UIHandler::setSampleType(index);
}
