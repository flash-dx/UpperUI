#include "homeidle.h"
#include "ui_homeidle.h"
#include "components/twobtnmessagebox.h"
#include "uihandler.h"
#include "components/threequery.h"
#include "components/onebtnmessagebox.h"

#include <QListView>
static HomeIdle *winptr = nullptr;
HomeIdle::HomeIdle(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HomeIdle)
{
    ui->setupUi(this);
    setStyleSheet("background-color:#f5f5f5");
    ui->Home_Idle_btOpenDoor->setGeometry((UIHandler::screenWidth-230)/2,(UIHandler::contentHeight*7/8-230)/2-100,230,230);
    ui->Home_Idle_lbBoxState->setGeometry((UIHandler::screenWidth-600)/2,ui->Home_Idle_btOpenDoor->y()+250,600,400);
    ui->Home_Idle_lbBoxState->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
    ui->Home_Idle_lbBoxState->setWordWrap(true);
    ui->Home_Idle_lbBoxState->setText(tr("未检测到试剂盒"));
    ui->Home_Idle_btReady->setGeometry(UIHandler::screenWidth-299-171,UIHandler::contentHeight*7/8-106-40-106-30-106-30,299,106);
    ui->Home_Idle_btReady->setText(tr("试剂盒就绪"));
    ui->Home_Idle_btPen->setGeometry(ui->Home_Idle_btOpenDoor->x()+350,ui->Home_Idle_btOpenDoor->y()+(224-70)/2,75,76);
    movie = new QMovie(":/images/opendoorAmi.gif");
    ui->Home_Idle_lbGif->setGeometry((UIHandler::screenWidth-230)/2,(UIHandler::contentHeight*7/8-230)/2-100,230,230);
    ui->Home_Idle_lbGif->setMovie(movie);
    ui->Home_Idle_lbGif->setVisible(false);


//    ui->Home_Idle_lbTestName->setStyleSheet("background-color:#ffffff");
//    ui->Home_Idle_lbTestSerial->setStyleSheet("background-color:#ffffff");
//    ui->Home_Idle_lbSampleCode->setStyleSheet("background-color:#ffffff");
//    ui->Home_Idle_lbSampleInfo->setStyleSheet("background-color:#ffffff");
//    ui->Home_Idle_lbSampleRemark->setStyleSheet("background-color:#ffffff");
//    ui->Home_Idle_lbValidTime->setStyleSheet("background-color:#ffffff");
    ui->Home_Idle_lbBoxTips->setStyleSheet("color:red");

    ui->Home_Idle_cbTestType->setView(new QListView());

    int tempX = ui->Home_Idle_btOpenDoor->x();
    int tempY = ui->Home_Idle_btOpenDoor->y();
    int tempWidth = ui->Home_Idle_btOpenDoor->width();
    int tempHeight = ui->Home_Idle_btOpenDoor->height();
    int spaceing = 20;

    ui->Home_Idle_lbTestName->setGeometry(tempX-348-300,tempY-30,448,50);
    ui->Home_Idle_lbTestSerial->setGeometry(ui->Home_Idle_lbTestName->x(),ui->Home_Idle_lbTestName->y()+ui->Home_Idle_lbTestName->height()+spaceing,348,50);
    ui->Home_Idle_lbValidTime->setGeometry(ui->Home_Idle_lbTestName->x(),ui->Home_Idle_lbTestSerial->y()+ui->Home_Idle_lbTestSerial->height()+spaceing,348,50);

    ui->Home_Idle_cbTestType->setGeometry(ui->Home_Idle_lbValidTime->x(),ui->Home_Idle_lbValidTime->y()+ui->Home_Idle_lbValidTime->height()+spaceing,300,60);
    ui->Home_Idle_lbBoxTips->setGeometry(ui->Home_Idle_cbTestType->x(),ui->Home_Idle_cbTestType->y()+ui->Home_Idle_cbTestType->height()+spaceing,348,50);

    ui->Home_Idle_lbTestName->setText(tr("四项呼吸道病毒核酸检测"));
    ui->Home_Idle_lbValidTime->setText("2022-09-10");
    ui->Home_Idle_lbTestSerial->setText(tr("GMS007C302"));
    ui->Home_Idle_lbBoxTips->setText(tr("试剂盒已过期"));

    ui->Home_Idle_lbSampleCode->setText("123456");
    ui->Home_Idle_lbSampleInfo->setText("人医");
    ui->Home_Idle_lbSampleRemark->setText("五联");

    ui->Home_Idle_lbSampleCode->setGeometry(tempX+tempHeight+300,tempY-30,348,50);
    ui->Home_Idle_lbSampleInfo->setGeometry(ui->Home_Idle_lbSampleCode->x(),ui->Home_Idle_lbSampleCode->y()+ui->Home_Idle_lbSampleCode->height()+spaceing,348,50);
    ui->Home_Idle_lbSampleRemark->setGeometry(ui->Home_Idle_lbSampleCode->x(),ui->Home_Idle_lbSampleInfo->y()+ui->Home_Idle_lbSampleInfo->height()+spaceing,348,50);
    ui->Home_Idle_btOpenDoor->setStyleSheet("QPushButton {background-image: url(:/images/doorclose.png)}");

//    ui->Home_Idle_lbOpen->setStyleSheet("background-color:red");
//    ui->Home_Idle_lbBarCode->setStyleSheet("background-color:#ffffff");
//    ui->Home_Idle_lbQrCode->setStyleSheet("background-color:#ffffff");
//    ui->Home_Idle_lbBox->setStyleSheet("background-color:#ffffff");
//    ui->Home_Idle_lbClose->setStyleSheet("background-color:#ffffff");

    ui->Home_Idle_lbBoxState->setVisible(false);

    ui->Home_Idle_lbOpen->setText(tr("开仓"));
    ui->Home_Idle_lbBarCode->setText(tr("扫条形码"));
    ui->Home_Idle_lbQrCode->setText(tr("扫二维码"));
    ui->Home_Idle_lbBox->setText(tr("放试剂盒"));
    ui->Home_Idle_lbClose->setText(tr("合仓"));

    ui->Home_Idle_lbOpen->setGeometry(tempX-580,tempY+tempHeight+200,250,60);
    ui->Home_Idle_lbBarCode->setGeometry(ui->Home_Idle_lbOpen->x()+ui->Home_Idle_lbOpen->width()+100,ui->Home_Idle_lbOpen->y()-ui->Home_Idle_lbOpen->height()-20,250,60);
    ui->Home_Idle_lbQrCode->setGeometry(ui->Home_Idle_lbBarCode->x(),ui->Home_Idle_lbBarCode->y()+ui->Home_Idle_lbBarCode->height()+80,250,60);
    ui->Home_Idle_lbBox->setGeometry(ui->Home_Idle_lbQrCode->x()+ui->Home_Idle_lbQrCode->width()+100,ui->Home_Idle_lbOpen->y(),250,60);
    ui->Home_Idle_lbClose->setGeometry(ui->Home_Idle_lbBox->x()+ui->Home_Idle_lbBox->width()+100,ui->Home_Idle_lbBox->y(),250,60);
}

HomeIdle::~HomeIdle()
{
    delete ui;
}

void HomeIdle::showEvent(QShowEvent *event){
    Q_UNUSED(event);

    ui->Home_Idle_cbTestType->clear();
    ui->Home_Idle_cbTestType->addItems(UIHandler::getSampleTypeArr());

    //connect(HomeMain::getPtr(),SIGNAL(sig_UpdateUI()),this,SLOT(UpdateUI()));
    //connect(TwoBtnMessageBox::getPtr(),&TwoBtnMessageBox::MessageAck,this,&HomeIdle::TwoBtnMessageBox_Ack);
    connect(OneBtnMessageBox::getPtr(),&OneBtnMessageBox::MessageAck,this,&HomeIdle::OneBtnMessageBox_Ack);
    connect(ThreeQuery::getPtr(),&ThreeQuery::queryAck,this,&HomeIdle::Sample_Changed);
    connect(ThreeQuery::getPtr(),&ThreeQuery::queryClose,this,&HomeIdle::InputBox_Close);
    //connect(HomeMain::getPtr(),&HomeMain::sig_DoorKeyDown,this,&HomeIdle::slot_DoorKeyDown);
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
    ui->Home_Idle_lbSequence->setVisible(false);
    ui->Home_Idle_cbSequence->setVisible(false);
    ui->Home_Idle_btSequence->setVisible(false);
}

void HomeIdle::hideEvent(QHideEvent *event){
    Q_UNUSED(event);
    TwoBtnMessageBox::getPtr()->disconnect(this);
    OneBtnMessageBox::getPtr()->disconnect(this);
    ThreeQuery::getPtr()->disconnect(this);
    //HomeMain::getPtr()->disconnect(this);
}

void HomeIdle::UpdateUI(int machineNo){
    const IdleData *data = UIHandler::getIdleData(machineNo);
    if (data == nullptr) return;
    qDebug()<<"HomeIdle,UpdateUI"<<str2q(data->errMessage)<<UIHandler::getBoxState();
    /*
    if (!data->errMessage.isEmpty()){

    }
    else
    */
    {       
        ui->Home_Idle_lbClose->setStyleSheet("padding-left:70px;border-image: url(:/images/tip_ notDone.png);");
        if (UIHandler::getBoxState())
            ui->Home_Idle_lbBox->setStyleSheet("padding-left:30px;border-image: url(:/images/tip_done.png);");
        else
            ui->Home_Idle_lbBox->setStyleSheet("padding-left:30px;border-image: url(:/images/tip_ notDone.png);");
        if (UIHandler::getDoorState())
            ui->Home_Idle_lbOpen->setStyleSheet("padding-left:70px;border-image: url(:/images/tip_done.png);");
        else
            ui->Home_Idle_lbOpen->setStyleSheet("padding-left:70px;border-image: url(:/images/tip_ notDone.png);");
        if (UIHandler::getSampleCode().isEmpty())
            ui->Home_Idle_lbBarCode->setStyleSheet("padding-left:30px;border-image: url(:/images/tip_ notDone.png);");
        else
            ui->Home_Idle_lbBarCode->setStyleSheet("padding-left:30px;border-image: url(:/images/tip_done.png);");
        if (UIHandler::PanelCode().isEmpty())
            ui->Home_Idle_lbQrCode->setStyleSheet("padding-left:30px;border-image: url(:/images/tip_ notDone.png);");
        else
            ui->Home_Idle_lbQrCode->setStyleSheet("padding-left:30px;border-image: url(:/images/tip_done.png);");

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
    UIHandler::setStage(HomeStage::Stage_result);
    UIHandler::getPtr()->UpdateUI(UIHandler::getCurrMachineId());
    //emit UIHandler::getPtr()->TestProgress(50,100,UIHandler::getCurrMachineId());
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
