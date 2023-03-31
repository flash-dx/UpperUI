﻿#include "homeidle.h"
#include "ui_homeidle.h"
#include "components/twobtnmessagebox.h"
#include "uihandler.h"
#include "components/threequery.h"
#include "components/onebtnmessagebox.h"
#include "homemain.h"
#include "components/cqrcodeinfo.h"
static HomeIdle *winptr = nullptr;
HomeIdle::HomeIdle(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HomeIdle)
{
    ui->setupUi(this);
    setStyleSheet("background-color:#f5f5f5");
    ui->Home_Idle_btOpenDoor->setGeometry((UIHandler::contentWidth*5/6-230)/2,(UIHandler::contentHeight*7/8-230)/2-100,230,230);
    ui->Home_Idle_lbBoxState->setGeometry((UIHandler::contentWidth*5/6-600)/2,ui->Home_Idle_btOpenDoor->y()+250,600,400);
    ui->Home_Idle_lbBoxState->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
    ui->Home_Idle_lbBoxState->setWordWrap(true);
    ui->Home_Idle_lbBoxState->setText(tr("未检测到试剂盒"));
    ui->Home_Idle_btReady->setGeometry(UIHandler::contentWidth*5/6-299-171,UIHandler::contentHeight*7/8-106-40-106-30-106-30,299,106);
    ui->Home_Idle_btReady->setText(tr("试剂盒就绪"));
    ui->Home_Idle_btPen->setGeometry(ui->Home_Idle_btOpenDoor->x()+350,ui->Home_Idle_btOpenDoor->y()+(224-70)/2,75,76);
    movie = new QMovie(":/images/opendoorAmi.gif");
    ui->Home_Idle_lbGif->setGeometry((UIHandler::contentWidth*5/6-230)/2,(UIHandler::contentHeight*7/8-230)/2-100,230,230);
    ui->Home_Idle_lbGif->setMovie(movie);
    ui->Home_Idle_lbGif->setVisible(false);

    ui->Home_Idle_btOpenDoor->setStyleSheet("QPushButton {background-image: url(:/images/doorclose.png)}");
}

HomeIdle::~HomeIdle()
{
    delete ui;
}

HomeIdle *HomeIdle::getPtr()
{
    if (winptr == nullptr)
        winptr = new HomeIdle;
    return winptr;
}

void HomeIdle::showEvent(QShowEvent *event){
    Q_UNUSED(event);


    connect(HomeMain::getPtr(),SIGNAL(sig_UpdateUI()),this,SLOT(UpdateUI()));
    //connect(TwoBtnMessageBox::getPtr(),&TwoBtnMessageBox::MessageAck,this,&HomeIdle::TwoBtnMessageBox_Ack);
    connect(OneBtnMessageBox::getPtr(),&OneBtnMessageBox::MessageAck,this,&HomeIdle::OneBtnMessageBox_Ack);
    connect(ThreeQuery::getPtr(),&ThreeQuery::queryAck,this,&HomeIdle::Sample_Changed);
    connect(ThreeQuery::getPtr(),&ThreeQuery::queryClose,this,&HomeIdle::InputBox_Close);
    connect(HomeMain::getPtr(),&HomeMain::sig_DoorKeyDown,this,&HomeIdle::slot_DoorKeyDown);
    connect(UIHandler::getPtr(),&UIHandler::sig_QrCodeChange,this,[=](QString code){

        if(!UIHandler::getDoorState() || UIHandler::getIdleData()->bOpenDoor)
        {
            return ;
        }

        qDebug()<<code<<"QrCode";
        int result = 0;
        code.remove('\r');

        if(/*code.length() == 42 &&*/ (code.startsWith("FLASHDX") || code.startsWith("FlashDx") )&& code.endsWith("X"))
        {
            result = UIHandler::decodeQr(code);
        }
        else
        {
            UIHandler::setSampleCode(code);
        }
        //Log::LogByFile("recodeQr.txt",code);
        if(CQrCodeInfo::getPtr()->isHidden())
        {
            CQrCodeInfo::getPtr()->display(result);
        }
        else
        {
            emit sig_QrCodeChange(result);
        }
    });

    bool mode = false;
    if(UIHandler::get_int_Param("ProjectMode") == 0)
    {
        mode = true;
        QString panelcode = UIHandler::get_string_Param("DefaultPanelCode");
        QStringList testlist = UIHandler::getPanelList();
        ui->Home_Idle_cbSequence->clear();
        ui->Home_Idle_cbSequence->addItems(testlist);
        for (int i = 0; i < testlist.count(); i++)
        {
            QStringList list = testlist[i].split('_');
            if(list.count() > 0)
            {
                if(list[0] == panelcode)
                {
                    ui->Home_Idle_cbSequence->setCurrentIndex(i);
                    break;
                }
            }
        }
    }
    else
    {
        //UIHandler::setParam("");
        UIHandler::setPanelName("");
        UIHandler::setPanelCode("");
        UIHandler::setBoxSerial("");
        UIHandler::setBoxCode("");
    }

    ui->Home_Idle_btReady->setVisible(mode);
    ui->Home_Idle_lbSequence->setVisible(mode);
    ui->Home_Idle_cbSequence->setVisible(mode);
    ui->Home_Idle_btSequence->setVisible(mode);
}

void HomeIdle::hideEvent(QHideEvent *event){
    Q_UNUSED(event);
    UIHandler::getPtr()->disconnect(this);
    TwoBtnMessageBox::getPtr()->disconnect(this);
    OneBtnMessageBox::getPtr()->disconnect(this);
    ThreeQuery::getPtr()->disconnect(this);
    HomeMain::getPtr()->disconnect(this);
}

void HomeIdle::UpdateUI(){
    UIHandler::NotifyTitle("idle",5);
    const IdleData *data = UIHandler::getIdleData();
    if (data == nullptr) return;
    qDebug()<<"HomeIdle,UpdateUI"<<str2q(data->errMessage)<<UIHandler::getBoxState();
    /*
    if (!data->errMessage.isEmpty()){

    }
    else
    */
    {
        if (UIHandler::getBoxState())
            ui->Home_Idle_lbBoxState->setText(tr("试剂盒就绪"));
        else
            ui->Home_Idle_lbBoxState->setText(tr("未检测到试剂盒"));


        if (data->bOpenDoor){
            ui->Home_Idle_btOpenDoor->setVisible(false);
            ui->Home_Idle_lbGif->setVisible(true);
            ui->Home_Idle_btOpenDoor->setStyleSheet("QPushButton {background-image: url(:/images/doorclose.png)}");
            movie->start();
        }
        else {
            movie->stop();
            ui->Home_Idle_btOpenDoor->setVisible(true);
            ui->Home_Idle_lbGif->setVisible(false);
            ui->Home_Idle_btOpenDoor->setStyleSheet("QPushButton {background-image: url(:/images/dooropen.png)}");
        }
        ui->Home_Idle_btReady->setEnabled(!data->bOpenDoor);
        ui->Home_Idle_btPen->setEnabled(!data->bOpenDoor);
    }
}

void HomeIdle::on_Home_Idle_btOpenDoor_clicked()
{
    subDoorInfo info = UIHandler::judgeDoorStatus();
    if(info.status == 1)
    {
        OneBtnMessageBox::display( QString("%1").arg(str2q(info.machineName))+ tr("机器舱门出舱中！"),tr("返回"));
        return;
    }

    qDebug()<<UIHandler::getCurrMachineId()<<9999;

    bool doorState = UIHandler::getDoorState();
    bool boxState = UIHandler::getBoxState();

    qDebug()<<"UIHandler::PanelCode()"<<UIHandler::PanelCode()<<UIHandler::getSampleCode()<<doorState<<boxState;
    if(doorState)
    {
        if(UIHandler::getSampleCode().isEmpty() && boxState)
        {
            OneBtnMessageBox::display(tr("请先输入样本号！"),tr("返回"));
            return;
        }
        else  if(UIHandler::PanelCode().isEmpty() && boxState)
        {
            OneBtnMessageBox::display(tr("请先扫描二维码！"),tr("返回"));
            return;
        }
    }
    else
    {
       subDoorInfo info = UIHandler::judgeDoorStatus();
       if(info.status == 2)
       {
           OneBtnMessageBox::display(tr("请先关闭")+QString("%1").arg(str2q(info.machineName))+tr("机器的舱门"),tr("返回"));
           return;
       }
    }

    UIHandler::IdleSwitchDoor();
}

//void HomeIdle::TwoBtnMessageBox_Ack(int ack)
//{
//    if (ack == 1)
//        UIHandler::GoPage(UIHandler::PageId::Page_Home_Main);
//    else{
//        //UIHandler::setErrorOpenDoor(true,GlobalParam::currentMachineNo);
//        UIHandler::SequenceDo(SequenceId::Sequence_OpenBox);
//    }
//}

void HomeIdle::OneBtnMessageBox_Ack(int ack)
{
    Q_UNUSED(ack);

    //UIHandler::SequenceDo(SequenceId::Sequence_OpenBox);
}

void HomeIdle::on_Home_Idle_btPen_clicked()
{
    ThreeQuery::display(tr("样本信息录入"),tr("样本号"),tr("样本信息"),tr("样本备注"),UIHandler::getSampleCode(),UIHandler::getSampleInfo(),UIHandler::getSampleRemark());
}

void HomeIdle::InputBox_Close()
{
    ui->Home_Idle_btPen->setEnabled(true);
    ui->Home_Idle_btOpenDoor->setEnabled(true);
    UIHandler::getPtr()->sig_FooterSetEnabled(true);
}

void HomeIdle::Sample_Changed(QString res1, QString res2, QString res3)
{
    //qDebug()<<"Sample_Changed"<<res1<<res2<<res3;
    UIHandler::setSampleCode(res1);
    UIHandler::setSampleInfo(res2);
    UIHandler::setSampleRemark(res3);
}

void HomeIdle::on_Home_Idle_btReady_clicked()
{
    UIHandler::setStage(HomeStage::Stage_ready);
    UIHandler::getPtr()->UpdateUI(UIHandler::getCurrMachineId());
}

void HomeIdle::on_Home_Idle_btSequence_clicked()
{
    QString panelCode = "";
    QString panelName = ui->Home_Idle_cbSequence->currentText();

    QStringList list = panelName.split("_");
    if(list.count() > 1)
    {
        panelCode = list[0];
        panelName = panelName.remove(0,panelCode.length()+1);

        UIHandler::setPanelName(panelName);
        UIHandler::setPanelCode(panelCode);
        UIHandler::setBoxCode(UIHandler::getBoxCode(panelCode));
//        qDebug()<<panelName<<panelCode<<GlobalParam::DefaultBoxSerial<<GlobalParam::getBoxCode(panelCode);
    }
}

void HomeIdle::slot_DoorKeyDown(int machineNo)
{
    on_Home_Idle_btOpenDoor_clicked();
}
