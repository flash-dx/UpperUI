#include "homeidle.h"
#include "ui_homeidle.h"
#include "components/twobtnmessagebox.h"
#include "uihandler.h"
#include "components/threequery.h"
#include "components/onebtnmessagebox.h"

#include <QListView>

HomeIdle::HomeIdle(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HomeIdle)
{
    ui->setupUi(this);
    ui->Home_Idle_btOpenDoor->setGeometry((UIHandler::screenWidth-230)/2-50,(UIHandler::contentHeight*7/8-230)/2-100,230,230);
    movie = new QMovie(":/images/opendoorAmi.gif");
    ui->Home_Idle_lbGif->setGeometry(ui->Home_Idle_btOpenDoor->x(),ui->Home_Idle_btOpenDoor->y(),230,230);
    ui->Home_Idle_lbGif->setMovie(movie);
    ui->Home_Idle_lbGif->setVisible(false);

    ui->Home_Idle_lbTips->setGeometry((UIHandler::screenWidth-450)/2-50,ui->Home_Idle_btOpenDoor->y()+300,450,100);
    ui->Home_Idle_lbTips->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
    ui->Home_Idle_lbTips->setWordWrap(true);

    ui->Home_Idle_lbBK1->setGeometry(ui->Home_Idle_btOpenDoor->x()-368-150,(UIHandler::contentHeight*7/8-457)/2-50,368,457);
    ui->Home_Idle_lbBK2->setGeometry(ui->Home_Idle_btOpenDoor->x()+219+150,(UIHandler::contentHeight*7/8-457)/2-50,368,457);
    ui->Home_Idle_btPen->setGeometry(ui->Home_Idle_lbBK2->x()+368+100,(UIHandler::contentHeight*7/8-76)/2-50,75,76);

    ui->Home_Idle_lbTestName->setGeometry(ui->Home_Idle_lbBK1->x()+10,ui->Home_Idle_lbBK1->y()+26,348,130);
    ui->Home_Idle_lbTestName->setAlignment(Qt::AlignCenter);
    ui->Home_Idle_lbTestName->setWordWrap(true);

    ui->Home_Idle_lbTestSerial->setGeometry(ui->Home_Idle_lbBK1->x()+10,ui->Home_Idle_lbBK1->y()+165,348,130);
    ui->Home_Idle_lbTestSerial->setAlignment(Qt::AlignCenter);
    ui->Home_Idle_cbTestType->setGeometry(ui->Home_Idle_lbBK1->x()+32,ui->Home_Idle_lbBK1->y()+346,300,60);
    ui->Home_Idle_cbTestType->setView(new QListView());
    ui->Home_Idle_lbSampleCode->setGeometry(ui->Home_Idle_lbBK2->x()+10,ui->Home_Idle_lbBK2->y()+26,348,130);
    ui->Home_Idle_lbSampleInfo->setGeometry(ui->Home_Idle_lbBK2->x()+10,ui->Home_Idle_lbBK2->y()+165,348,130);
    ui->Home_Idle_lbSampleRemark->setGeometry(ui->Home_Idle_lbBK2->x()+10,ui->Home_Idle_lbBK2->y()+310,348,130);


    ui->Home_Idle_lbSampleCode->setWordWrap(true);
    ui->Home_Idle_lbSampleCode->setAlignment(Qt::AlignCenter);
    ui->Home_Idle_lbSampleInfo->setAlignment(Qt::AlignCenter);
    ui->Home_Idle_lbSampleRemark->setAlignment(Qt::AlignCenter);

    ui->Home_Idle_lbOpen->setGeometry(ui->Home_Idle_lbBK1->x()+150,ui->Home_Idle_lbBK1->y()+ui->Home_Idle_lbBK1->height()+100,250,60);
    ui->Home_Idle_lbBarCode->setGeometry(ui->Home_Idle_lbOpen->x()+ui->Home_Idle_lbOpen->width()+100,ui->Home_Idle_lbOpen->y()-ui->Home_Idle_lbOpen->height()-20,250,60);
    ui->Home_Idle_lbQrCode->setGeometry(ui->Home_Idle_lbBarCode->x(),ui->Home_Idle_lbBarCode->y()+ui->Home_Idle_lbBarCode->height()+80,250,60);
    ui->Home_Idle_lbBox->setGeometry(ui->Home_Idle_lbQrCode->x()+ui->Home_Idle_lbQrCode->width()+100,ui->Home_Idle_lbOpen->y(),250,60);

    setStyleSheet("background-color:#f5f5f5");
    ui->Home_Idle_btOpenDoor->setStyleSheet("QPushButton {background-image: url(:/images/doorclose.png)}");
    ui->Home_Idle_lbTestName->setStyleSheet("background-color:#ffffff");
    ui->Home_Idle_lbTestSerial->setStyleSheet("background-color:#ffffff");
    ui->Home_Idle_lbSampleCode->setStyleSheet("background-color:#ffffff");
    ui->Home_Idle_lbSampleInfo->setStyleSheet("background-color:#ffffff");
    ui->Home_Idle_lbSampleRemark->setStyleSheet("background-color:#ffffff");

    ui->Home_Idle_cbTestType->clear();
    ui->Home_Idle_cbTestType->addItems(UIHandler::getSampleTypeArr());

    ui->Home_Idle_lbOpen->setText(tr("开仓"));
    ui->Home_Idle_lbBarCode->setText(tr("扫条形码"));
    ui->Home_Idle_lbQrCode->setText(tr("扫二维码"));
    ui->Home_Idle_lbBox->setText(tr("放试剂盒"));
}

HomeIdle::~HomeIdle()
{
    delete ui;
}

void HomeIdle::UpdateUI(int machineNo){
    const IdleData *data = UIHandler::getIdleData(machineNo);
    if (data == nullptr) return;    
    qDebug()<<"HomeIdle,UpdateUI"<<"err="<<data->errMessage<<"tips="<<data->tips<<UIHandler::getBoxState();

    if (UIHandler::getBoxState() && UIHandler::PanelCode().isEmpty()){
        OneBtnMessageBox::display(tr("请先取出残留试剂盒！"),tr("返回"));
        return;
    }

    qDebug()<<"HomeIdle,UpdateUI"<<"err="<<data->errMessage<<"tips="<<data->tips<<UIHandler::getBoxState();

    DisplayStep(true);
    ui->Home_Idle_lbTestName->setText(UIHandler::PanelName());
    ui->Home_Idle_lbTestSerial->setText(UIHandler::BoxSerial());
    ui->Home_Idle_lbSampleCode->setText(UIHandler::getSampleCode());
    ui->Home_Idle_lbSampleInfo->setText(UIHandler::getSampleInfo());
    ui->Home_Idle_lbSampleRemark->setText(UIHandler::getSampleRemark());

    if (data->tips > 0){
        if(data->tips == 1)
            ui->Home_Idle_lbTips->setText(tr("请打开舱门"));
        else if(data->tips == 2)
            ui->Home_Idle_lbTips->setText(tr("请扫条形码"));
        else if(data->tips == 3)
            ui->Home_Idle_lbTips->setText(tr("请扫二维码"));
        else if(data->tips == 4)
            ui->Home_Idle_lbTips->setText(tr("请放入试剂盒"));
    }

    if (data->errMessage > 0){
        QString strErr;
        if (data->errMessage == 1)
            strErr = tr("请先打开舱门！");
        else if (data->errMessage == 2)
            strErr = tr("请先取出试剂盒！");
        else if (data->errMessage == 3)
            strErr = tr("请先输入样本号！");
        else if (data->errMessage == 4)
            strErr = tr("请先扫描二维码！");
        OneBtnMessageBox::display(strErr,tr("返回"));
    }
    else
    {
        qDebug()<<"BoxState:"<<UIHandler::getBoxState()<<"DoorState:"<<UIHandler::getDoorState();
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
        ui->Home_Idle_btPen->setEnabled(!data->bOpenDoor);
    }
}

void HomeIdle::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    if (UIHandler::getBoxState() && UIHandler::PanelCode().isEmpty()){
        OneBtnMessageBox::display(tr("请先取出残留试剂盒！"),tr("返回"));
        DisplayStep(false);
    }
}

void HomeIdle::on_Home_Idle_btOpenDoor_clicked()
{
    if (!UIHandler::getDoorState()){
        subDoorInfo info = UIHandler::judgeDoorStatus();
        if(info.status == 1)
        {
            OneBtnMessageBox::display( QString("%1").arg(str2q(info.machineName))+ tr("机器舱门出舱中！"),tr("返回"));
            return;
        }
        else if(info.status == 2){
            OneBtnMessageBox::display(tr("请先关闭")+QString("%1").arg(str2q(info.machineName))+tr("机器的舱门"),tr("返回"));
            return;
        }
    }

    UIHandler::IdleSwitchDoor();
}

void HomeIdle::on_Home_Idle_btPen_clicked()
{
    ThreeQuery query;
    query.setValue(UIHandler::getSampleCode(),UIHandler::getSampleInfo(),UIHandler::getSampleRemark());
    if (query.exec() == QDialog::Accepted){
        UIHandler::setSampleCode(query.getValue1());
        UIHandler::setSampleInfo(query.getValue2());
        UIHandler::setSampleRemark(query.getValue3());
        ui->Home_Idle_lbSampleCode->setText(UIHandler::getSampleCode());
        ui->Home_Idle_lbSampleInfo->setText(UIHandler::getSampleInfo());
        ui->Home_Idle_lbSampleRemark->setText(UIHandler::getSampleRemark());
    }
}

void HomeIdle::DisplayStep(bool bDisplay)
{
    ui->Home_Idle_lbOpen->setVisible(bDisplay);
    ui->Home_Idle_lbBarCode->setVisible(bDisplay);
    ui->Home_Idle_lbQrCode->setVisible(bDisplay);
    ui->Home_Idle_lbBox->setVisible(bDisplay);
}
