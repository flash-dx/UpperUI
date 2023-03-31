#include "pumpparam.h"
#include "ui_pumpparam.h"
#include "../uihandler.h"
#include <QListView>

static PumpParam *winptr = nullptr;

PumpParam *PumpParam::getPtr()
{
    if (winptr == nullptr)
        winptr = new PumpParam;
    return winptr;
}

PumpParam::PumpParam(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PumpParam)
{
    ui->setupUi(this);

    int btnW = 299;
    int btnH = 106;
    int btnRight = 100;
    int btnBottom = 30;
    int btnLeft = UIHandler::contentWidth - btnW - btnRight;
    int btnTop = UIHandler::contentHeight - btnBottom - btnH;
    int btnAdd = 20;

    ui->pushButton->setGeometry(  btnLeft - btnW - btnAdd, btnTop, btnW, btnH);
    ui->pushButton_2->setGeometry(btnLeft,                 btnTop, btnW, btnH);

    setStyleSheet("background-color:#f5f5f5;");

    ui->comboBox_machine->setView(new QListView());
    ui->comboBox_machine->setGeometry(UIHandler::contentWidth - 200,10,200,75);
    ui->comboBox_machine->setStyleSheet(UIHandler::getStyleSheet("QComboBox"));

    caliMachineNo = -1;
}

void PumpParam::showEvent(QShowEvent *event){
    Q_UNUSED(event);
    ui->retranslateUi(this);

    QMap<int, QString> list;
    for(auto it : UIHandler::getPtr()->get_subMac_Name()) {
       list[it.first] = str2q(it.second);
    }
    ui->comboBox_machine->blockSignals(true);
    ui->comboBox_machine->clear();
    if( list.count() > 0){
        ui->comboBox_machine->addItems(list.values());
        //        if(caliMachineNo == -1)
        //            caliMachineNo = list.firstKey();
        caliMachineNo = UIHandler::getCurrMachineId();
        ui->comboBox_machine->setCurrentText(list.value(caliMachineNo));
    }
    ui->comboBox_machine->blockSignals(false);
    load_data();

    UIHandler::setBtTextCenter(ui->pushButton, 48,"background-image: url(:/images/confirmbt.png);text-align:left;padding-bottom:10px;");
    UIHandler::setBtTextCenter(ui->pushButton_2, 48,"background-image: url(:/images/back.png);text-align:left;padding-bottom:10px;");

    UIHandler::NotifyTitle("FluidParam",5);
}

void PumpParam::hideEvent(QHideEvent *event){
    Q_UNUSED(event);
}

PumpParam::~PumpParam()
{
    delete ui;
}

void PumpParam::load_data()
{
    ui->label_pump1_data->setNum(UIHandler::get_int_Param("VPump1",caliMachineNo));
    ui->lEdit_pump1->setText(QString::number(UIHandler::get_int_Param("VPump1",caliMachineNo),10));
    ui->label_pump2_data->setNum(UIHandler::get_int_Param("VPump2",caliMachineNo));
    ui->lEdit_pump2->setText(QString::number(UIHandler::get_int_Param("VPump2",caliMachineNo),10));
    ui->label_pump3_data->setNum(UIHandler::get_int_Param("VPump3",caliMachineNo));
    ui->lEdit_pump3->setText(QString::number(UIHandler::get_int_Param("VPump3",caliMachineNo),10));
    ui->label_pump4_data->setNum(UIHandler::get_int_Param("VPump4",caliMachineNo));
    ui->lEdit_pump4->setText(QString::number(UIHandler::get_int_Param("VPump4",caliMachineNo),10));
    ui->label_pump5_data->setNum(UIHandler::get_int_Param("VPump5",caliMachineNo));
    ui->lEdit_pump5->setText(QString::number(UIHandler::get_int_Param("VPump5",caliMachineNo),10));

    ui->label_pump6_data->setNum(UIHandler::get_int_Param("VPump6",caliMachineNo));
    ui->lEdit_pump6->setText(QString::number(UIHandler::get_int_Param("VPump6",caliMachineNo),10));
    ui->label_pump7_data->setNum(UIHandler::get_int_Param("VPump7",caliMachineNo));
    ui->lEdit_pump7->setText(QString::number(UIHandler::get_int_Param("VPump7",caliMachineNo),10));
    ui->label_pump8_data->setNum(UIHandler::get_int_Param("VPump8",caliMachineNo));
    ui->lEdit_pump8->setText(QString::number(UIHandler::get_int_Param("VPump8",caliMachineNo),10));
    ui->label_pump9_data->setNum(UIHandler::get_int_Param("VPump9",caliMachineNo));
    ui->lEdit_pump9->setText(QString::number(UIHandler::get_int_Param("VPump9",caliMachineNo),10));
    ui->label_pump10_data->setNum(UIHandler::get_int_Param("VPump10",caliMachineNo));
    ui->lEdit_pump10->setText(QString::number(UIHandler::get_int_Param("VPump10",caliMachineNo),10));


    ui->label_pump11_data->setNum(UIHandler::get_int_Param("VPump11",caliMachineNo));
    ui->lEdit_pump11->setText(QString::number(UIHandler::get_int_Param("VPump11",caliMachineNo),10));
    ui->label_pump12_data->setNum(UIHandler::get_int_Param("VPump12",caliMachineNo));
    ui->lEdit_pump12->setText(QString::number(UIHandler::get_int_Param("VPump12",caliMachineNo),10));
    ui->label_pump13_data->setNum(UIHandler::get_int_Param("VPump13",caliMachineNo));
    ui->lEdit_pump13->setText(QString::number(UIHandler::get_int_Param("VPump13",caliMachineNo),10));
    ui->label_pump14_data->setNum(UIHandler::get_int_Param("VPump14",caliMachineNo));
    ui->lEdit_pump14->setText(QString::number(UIHandler::get_int_Param("VPump14",caliMachineNo),10));
    ui->label_pump15_data->setNum(UIHandler::get_int_Param("VPump15",caliMachineNo));
    ui->lEdit_pump15->setText(QString::number(UIHandler::get_int_Param("VPump15",caliMachineNo),10));

  //  ui->rButton_step_1->setStyleSheet("QRadioButton::indicator{width:35px;height:35px;}");
   // ui->rButton_step_10->setStyleSheet("QRadioButton::indicator{width:35px;height:35px;}");
  //  ui->rButton_step_100->setStyleSheet("QRadioButton::indicator{width:35px;height:35px;}");
  //  ui->rButton_step_500->setStyleSheet("QRadioButton::indicator{width:35px;height:35px;}");
}

void PumpParam::on_pushButton_clicked()
{
    if(caliMachineNo >= 0)
    {
        UIHandler::updata_int_Param("VPump1",(ui->lEdit_pump1->text()).toInt(),caliMachineNo);
        UIHandler::updata_int_Param("VPump2",(ui->lEdit_pump2->text()).toInt(),caliMachineNo);
        UIHandler::updata_int_Param("VPump3",(ui->lEdit_pump3->text()).toInt(),caliMachineNo);
        UIHandler::updata_int_Param("VPump4",(ui->lEdit_pump4->text()).toInt(),caliMachineNo);
        UIHandler::updata_int_Param("VPump5",(ui->lEdit_pump5->text()).toInt(),caliMachineNo);
        UIHandler::updata_int_Param("VPump6",(ui->lEdit_pump6->text()).toInt(),caliMachineNo);
        UIHandler::updata_int_Param("VPump7",(ui->lEdit_pump7->text()).toInt(),caliMachineNo);
        UIHandler::updata_int_Param("VPump8",(ui->lEdit_pump8->text()).toInt(),caliMachineNo);
        UIHandler::updata_int_Param("VPump9",(ui->lEdit_pump9->text()).toInt(),caliMachineNo);
        UIHandler::updata_int_Param("VPump10",(ui->lEdit_pump10->text()).toInt(),caliMachineNo);
        UIHandler::updata_int_Param("VPump11",(ui->lEdit_pump11->text()).toInt(),caliMachineNo);
        UIHandler::updata_int_Param("VPump12",(ui->lEdit_pump12->text()).toInt(),caliMachineNo);
        UIHandler::updata_int_Param("VPump13",(ui->lEdit_pump13->text()).toInt(),caliMachineNo);
        UIHandler::updata_int_Param("VPump14",(ui->lEdit_pump14->text()).toInt(),caliMachineNo);
        UIHandler::updata_int_Param("VPump15",(ui->lEdit_pump15->text()).toInt(),caliMachineNo);

        load_data();

        QString param;
        param = "VPump1:" +  ui->lEdit_pump1->text() + "^";
        param += "VPump2:" +  ui->lEdit_pump2->text() + "^";
        param += "VPump3:" +  ui->lEdit_pump3->text() + "^";
        param += "VPump4:" +  ui->lEdit_pump4->text() + "^";
        param += "VPump5:" +  ui->lEdit_pump5->text() + "^";
        param += "VPump6:" +  ui->lEdit_pump6->text() + "^";
        param += "VPump7:" +  ui->lEdit_pump7->text() + "^";
        param += "VPump8:" +  ui->lEdit_pump8->text() + "^";
        param += "VPump9:" +  ui->lEdit_pump9->text() + "^";
        param += "VPump10:" +  ui->lEdit_pump10->text() + "^";
        param += "VPump11:" +  ui->lEdit_pump11->text() + "^";
        param += "VPump12:" +  ui->lEdit_pump12->text() + "^";
        param += "VPump13:" +  ui->lEdit_pump13->text() + "^";
        param += "VPump14:" +  ui->lEdit_pump14->text() + "^";
        param += "VPump15:" +  ui->lEdit_pump15->text();
        UIHandler::settingParam(param, caliMachineNo);
    }
}

void PumpParam::on_pushButton_2_clicked()
{
     UIHandler::GoPage(UIHandler::PageId::Page_Setup_Menu);
}

void PumpParam::on_comboBox_machine_currentIndexChanged(int index)
{
    if(index >= 0)
    {
        map<int, string> mac = UIHandler::get_subMac_Name();
        for(auto it:mac) {
           if(str2q(it.second) == ui->comboBox_machine->currentText())
           {
               caliMachineNo = it.first;
           }
        }
        qDebug()<<"caliMachineNo"<<caliMachineNo;
        load_data();
    }
}
