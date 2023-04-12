#include "machinecalibration.h"
#include "ui_machinecalibration.h"
#include "../uihandler.h"
#include <QListView>

static MachineCalibration *winptr = nullptr;

MachineCalibration *MachineCalibration::getPtr()
{
    if (winptr == nullptr)
        winptr = new MachineCalibration;
    return winptr;
}

MachineCalibration::MachineCalibration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MachineCalibration)
{
    ui->setupUi(this);
    qDebug()<<"label_V1"<<ui->label_V1->geometry();

    int btnW = 299;
    int btnH = 106;
    int btnRight = 100;
    int btnBottom = 30;
    int btnLeft = UIHandler::contentWidth - btnW - btnRight;
    int btnTop = UIHandler::contentHeight - btnBottom - btnH;

    ui->pButton_machine_back->setGeometry(btnLeft, btnTop, btnW,btnH);

    setStyleSheet("background-color:#f5f5f5;");
   // load_data();

    ui->frame->setStyleSheet(".QFrame{border-width:2px;border-style:solid;border-color:#e3e3e3;}");
    ui->comboBox_machine->setView(new QListView());
    ui->comboBox_machine->setGeometry(UIHandler::contentWidth - 300,10,200,75);
   ui->comboBox_machine->setStyleSheet(UIHandler::getStyleSheet("QComboBox"));

    caliMachineNo = -1;
    ui->spinBox_door_work_offset->setMinimum(100);
    ui->spinBox_door_work_offset->setMaximum(2000);
}


void MachineCalibration::showEvent(QShowEvent *event){
    Q_UNUSED(event);
    ui->retranslateUi(this);

    ui->rButton_step_1->setStyleSheet("QRadioButton::indicator{width:35px;height:35px;}");
    ui->rButton_step_10->setStyleSheet("QRadioButton::indicator{width:35px;height:35px;}");
    ui->rButton_step_100->setStyleSheet("QRadioButton::indicator{width:35px;height:35px;}");
    ui->rButton_step_500->setStyleSheet("QRadioButton::indicator{width:35px;height:35px;}");
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
    load_data(caliMachineNo);
    //connect(HomeMain::getPtr(),SIGNAL(sig_UpdateUI()),this,SLOT(UpdateUI()));
    UIHandler::setBtTextCenter(ui->pButton_machine_back, 48,"background-image: url(:/images/back.png);text-align:left;padding-bottom:20px;");

    UIHandler::NotifyTitle("Cali",5);

    qDebug()<<"label_V1"<<ui->label_V1->geometry();
}
void MachineCalibration::hideEvent(QHideEvent *event){
    Q_UNUSED(event);

    //HomeMain::getPtr()->disconnect(this);
}


MachineCalibration::~MachineCalibration()
{
    delete ui;
}

void MachineCalibration::load_data(int MachineNo)
{
    ui->rButton_step_1->setChecked(false);
    ui->rButton_step_10->setChecked(false);
    ui->rButton_step_100->setChecked(true);
    ui->rButton_step_500->setChecked(false);

    ui->spinBox_V1->setSingleStep(100);
    ui->spinBox_V2->setSingleStep(100);
    ui->spinBox_V3->setSingleStep(100);
    ui->spinBox_V4->setSingleStep(100);
    ui->spinBox_Door->setSingleStep(100);
    ui->spinBox_Pump->setSingleStep(100);
    ui->spinBox_split->setSingleStep(100);
    ui->spinBox_door_step->setSingleStep(100);

    ui->label_V1_data->setNum(UIHandler::get_int_Param("V1ToolHomeX",MachineNo));
    ui->label_V2_data->setNum(UIHandler::get_int_Param("V2ToolHomeX",MachineNo));
    ui->label_V3_data->setNum(UIHandler::get_int_Param("V3ToolHomeX",MachineNo));
    ui->label_V4_data->setNum(UIHandler::get_int_Param("VPToolHomeX",MachineNo));
    ui->label_door_data->setNum(UIHandler::get_int_Param("VDWorkX",MachineNo));
    ui->label_push_data->setNum(UIHandler::get_int_Param("PumpToolHomeX",MachineNo));
    ui->label_split_data->setNum(UIHandler::get_int_Param("SplitToolHomeX",MachineNo));
    ui->label_door_work_data->setNum(UIHandler::get_int_Param("DoorOut",MachineNo));

    ui->spinBox_V1->setValue(0);
    ui->spinBox_V2->setValue(0);
    ui->spinBox_V3->setValue(0);
    ui->spinBox_V4->setValue(0);
    ui->spinBox_Door->setValue(0);
    ui->spinBox_Pump->setValue(0);
    ui->spinBox_split->setValue(0);

    ui->spinBox_door_step->setValue(0);
    ui->spinBox_speed->setValue(6);

    ui->spinBox_door_work_offset->setValue(UIHandler::get_int_Param("DoorOffset",MachineNo));
}

void MachineCalibration::on_pButton_machine_back_clicked()
{
    UIHandler::GoPage(UIHandler::PageId::Page_Setup_Menu);

}

void MachineCalibration::on_pButton_v1_hard_clicked()
{
    ui->spinBox_V1->setValue(0);

    UIHandler::ActionDo("V1",1,0,0,0,caliMachineNo);
}

void MachineCalibration::on_pButton_v1_soft_clicked()
{
    ui->spinBox_V1->setValue(UIHandler::get_int_Param("V1SoftHomeX",caliMachineNo));
    UIHandler::ActionDo("V1",2,0,0,0,caliMachineNo);
}

void MachineCalibration::on_pButton_v1_work_clicked()
{
     ui->spinBox_V1->setValue(UIHandler::get_int_Param("V1ToolHomeX",caliMachineNo));
     ui->label_V1_data->setNum(UIHandler::get_int_Param("V1ToolHomeX",caliMachineNo));
    UIHandler::ActionDo("V1",9,ui->spinBox_V1->value(),0,0,caliMachineNo);
}


void MachineCalibration::on_pButton_v1_set_clicked()
{
    UIHandler::ActionDo("V1",9,ui->spinBox_V1->value(),0,0,caliMachineNo);
}

void MachineCalibration::on_pButton_v1_save_clicked()
{
    int v1Value = ui->spinBox_V1->value();
    int V1WorkX = v1Value-UIHandler::get_int_Param("V1SoftHomeOffset",caliMachineNo)+UIHandler::get_int_Param("V1WorkOffset",caliMachineNo);
    int V1SoftHomeX = v1Value-UIHandler::get_int_Param("V1SoftHomeOffset");

    UIHandler::updata_int_Param("V1ToolHomeX",v1Value,caliMachineNo);
    UIHandler::updata_int_Param("V1WorkX",V1WorkX,caliMachineNo);
    UIHandler::updata_int_Param("V1SoftHomeX",V1SoftHomeX,caliMachineNo);
    ui->spinBox_V1->setValue(UIHandler::get_int_Param("V1ToolHomeX",caliMachineNo));

    ui->label_V1_data->setNum(UIHandler::get_int_Param("V1ToolHomeX",caliMachineNo));
    ui->label_V2_data->setNum(UIHandler::get_int_Param("V2ToolHomeX",caliMachineNo));
    ui->label_V3_data->setNum(UIHandler::get_int_Param("V3ToolHomeX",caliMachineNo));
    ui->label_V4_data->setNum(UIHandler::get_int_Param("VPToolHomeX",caliMachineNo));
    ui->label_door_data->setNum(UIHandler::get_int_Param("VDWorkX",caliMachineNo));
    ui->label_push_data->setNum(UIHandler::get_int_Param("PumpToolHomeX",caliMachineNo));

    QString param;
    param = "V1ToolHomeX:" + QString::number(v1Value) + "^";
    param += "V1WorkX:" + QString::number(V1WorkX) + "^";
    param += "V1SoftHomeX:" + QString::number(V1SoftHomeX);
    UIHandler::settingParam(param, caliMachineNo);
}


void MachineCalibration::on_pButton_v2_hard_clicked()
{
    ui->spinBox_V2->setValue(0);
    UIHandler::ActionDo("V2",1,0,0,0,caliMachineNo);
 }

void MachineCalibration::on_pButton_v2_soft_clicked()
{
    ui->spinBox_V2->setValue(UIHandler::get_int_Param("V2SoftHomeX",caliMachineNo));

    UIHandler::ActionDo("V2",2,0,0,0,caliMachineNo);
}

void MachineCalibration::on_pButton_v2_work_clicked()
{
    ui->spinBox_V2->setValue(UIHandler::get_int_Param("V2ToolHomeX",caliMachineNo));
    ui->label_V2_data->setNum(UIHandler::get_int_Param("V2ToolHomeX",caliMachineNo));
   UIHandler::ActionDo("V2",9,ui->spinBox_V2->value(),0,0,caliMachineNo);
}


void MachineCalibration::on_pButton_v2_set_clicked()
{
    UIHandler::ActionDo("V2",9,ui->spinBox_V2->value(),0,0,caliMachineNo);
}

void MachineCalibration::on_pButton_v2_save_clicked()
{
    int v2Value = ui->spinBox_V2->value();
    int V2WorkX = v2Value-UIHandler::get_int_Param("V2SoftHomeOffset",caliMachineNo)+UIHandler::get_int_Param("V2WorkOffset",caliMachineNo);

    int V2SoftHomeX = v2Value-UIHandler::get_int_Param("V2SoftHomeOffset",caliMachineNo);
    UIHandler::updata_int_Param("V2ToolHomeX",v2Value,caliMachineNo);
    UIHandler::updata_int_Param("V2WorkX",V2WorkX,caliMachineNo);
    UIHandler::updata_int_Param("V2SoftHomeX",V2SoftHomeX,caliMachineNo);
    ui->spinBox_V2->setValue(UIHandler::get_int_Param("V2ToolHomeX",caliMachineNo));

    ui->label_V1_data->setNum(UIHandler::get_int_Param("V1ToolHomeX",caliMachineNo));
    ui->label_V2_data->setNum(UIHandler::get_int_Param("V2ToolHomeX",caliMachineNo));
    ui->label_V3_data->setNum(UIHandler::get_int_Param("V3ToolHomeX",caliMachineNo));
    ui->label_V4_data->setNum(UIHandler::get_int_Param("VPToolHomeX",caliMachineNo));
    ui->label_door_data->setNum(UIHandler::get_int_Param("VDWorkX",caliMachineNo));
    ui->label_push_data->setNum(UIHandler::get_int_Param("PumpToolHomeX",caliMachineNo));

    QString param;
    param = "V2ToolHomeX:" + QString::number(v2Value) + "^";
    param += "V2WorkX:" + QString::number(V2WorkX) + "^";
    param += "V2SoftHomeX:" + QString::number(V2SoftHomeX);
    UIHandler::settingParam(param, caliMachineNo);
}



void MachineCalibration::on_pButton_v3_hard_clicked()
{
    ui->spinBox_V3->setValue(0);
    UIHandler::ActionDo("V3",1,0,0,0,caliMachineNo);
 }

void MachineCalibration::on_pButton_v3_soft_clicked()
{
    ui->spinBox_V3->setValue(UIHandler::get_int_Param("V3SoftHomeX",caliMachineNo));
    UIHandler::ActionDo("V3",2,0,0,0,caliMachineNo);
}

void MachineCalibration::on_pButton_v3_work_clicked()
{
   ui->spinBox_V3->setValue(UIHandler::get_int_Param("V3ToolHomeX",caliMachineNo));
   ui->label_V3_data->setNum(UIHandler::get_int_Param("V3ToolHomeX",caliMachineNo));
   UIHandler::ActionDo("V3",9,ui->spinBox_V3->value(),0,0,caliMachineNo);
}


void MachineCalibration::on_pButton_v3_set_clicked()
{
    UIHandler::ActionDo("V3",9,ui->spinBox_V3->value(),0,0,caliMachineNo);

}

void MachineCalibration::on_pButton_v3_save_clicked()
{
    int v3Value = ui->spinBox_V3->value();
    int V3WorkX = v3Value-UIHandler::get_int_Param("V3SoftHomeOffset",caliMachineNo)+UIHandler::get_int_Param("V3WorkOffset",caliMachineNo);
    int V3SoftHomeX = v3Value-UIHandler::get_int_Param("V3SoftHomeOffset",caliMachineNo);

    UIHandler::updata_int_Param("V3ToolHomeX",v3Value,caliMachineNo);
    UIHandler::updata_int_Param("V3WorkX",V3WorkX,caliMachineNo);
    UIHandler::updata_int_Param("V3SoftHomeX",V3SoftHomeX,caliMachineNo);
    ui->spinBox_V3->setValue(UIHandler::get_int_Param("V3ToolHomeX",caliMachineNo));

    ui->label_V1_data->setNum(UIHandler::get_int_Param("V1ToolHomeX",caliMachineNo));
    ui->label_V2_data->setNum(UIHandler::get_int_Param("V2ToolHomeX",caliMachineNo));
    ui->label_V3_data->setNum(UIHandler::get_int_Param("V3ToolHomeX",caliMachineNo));
    ui->label_V4_data->setNum(UIHandler::get_int_Param("VPToolHomeX",caliMachineNo));
    ui->label_door_data->setNum(UIHandler::get_int_Param("VDWorkX",caliMachineNo));
    ui->label_push_data->setNum(UIHandler::get_int_Param("PumpToolHomeX",caliMachineNo));

    QString param;
    param = "V3ToolHomeX:" + QString::number(v3Value) + "^";
    param += "V3WorkX:" + QString::number(V3WorkX) + "^";
    param += "V3SoftHomeX:" + QString::number(V3SoftHomeX);
    UIHandler::settingParam(param, caliMachineNo);
}

void MachineCalibration::on_pButton_v4_hard_clicked()
{
    ui->spinBox_V4->setValue(0);
    UIHandler::ActionDo("VP",1,0,0,0,caliMachineNo);
 }

void MachineCalibration::on_pButton_v4_soft_clicked()
{
    ui->spinBox_V4->setValue(UIHandler::get_int_Param("VPSoftHomeX",caliMachineNo));
    UIHandler::ActionDo("VP",2,0,0,0,caliMachineNo);
}

void MachineCalibration::on_pButton_v4_work_clicked()
{
   ui->spinBox_V4->setValue(UIHandler::get_int_Param("VPToolHomeX",caliMachineNo));
   ui->label_V4_data->setNum(UIHandler::get_int_Param("VPToolHomeX",caliMachineNo));
   UIHandler::ActionDo("VP",9,ui->spinBox_V4->value(),0,0,caliMachineNo);
}


void MachineCalibration::on_pButton_v4_set_clicked()
{
    UIHandler::ActionDo("VP",9,ui->spinBox_V4->value(),0,0,caliMachineNo);
}

void MachineCalibration::on_pButton_v4_save_clicked()
{
    int v4Value = ui->spinBox_V4->value();
    int VPWorkX = v4Value-UIHandler::get_int_Param("VPSoftHomeOffset",caliMachineNo)+UIHandler::get_int_Param("VPWorkOffset",caliMachineNo);
    int VPSoftHomeX = v4Value-UIHandler::get_int_Param("VPSoftHomeOffset",caliMachineNo);

    UIHandler::updata_int_Param("VPToolHomeX",v4Value,caliMachineNo);
    UIHandler::updata_int_Param("VPWorkX",VPWorkX,caliMachineNo);
    UIHandler::updata_int_Param("VPSoftHomeX",VPSoftHomeX,caliMachineNo);
    ui->spinBox_V4->setValue(UIHandler::get_int_Param("VPToolHomeX",caliMachineNo));
    //Sequence::getPtr()->checkParam(true);

    ui->label_V1_data->setNum(UIHandler::get_int_Param("V1ToolHomeX",caliMachineNo));
    ui->label_V2_data->setNum(UIHandler::get_int_Param("V2ToolHomeX",caliMachineNo));
    ui->label_V3_data->setNum(UIHandler::get_int_Param("V3ToolHomeX",caliMachineNo));
    ui->label_V4_data->setNum(UIHandler::get_int_Param("VPToolHomeX",caliMachineNo));
    ui->label_door_data->setNum(UIHandler::get_int_Param("VDWorkX",caliMachineNo));
    ui->label_push_data->setNum(UIHandler::get_int_Param("PumpToolHomeX",caliMachineNo));

    QString param;
    param = "VPToolHomeX:" + QString::number(v4Value) + "^";
    param += "VPWorkX:" + QString::number(VPWorkX) + "^";
    param += "VPSoftHomeX:" + QString::number(VPSoftHomeX);
    UIHandler::settingParam(param, caliMachineNo);
 }


void MachineCalibration::on_pButton_door_hard_clicked()
{
    ui->spinBox_Door->setValue(0);
    UIHandler::ActionDo("Door",5,0,0,0,caliMachineNo);
    predoorpos =ui->spinBox_Door->value();
 }

void MachineCalibration::on_pButton_door_soft_clicked()
{
    ui->spinBox_Door->setValue(0);
    UIHandler::ActionDo("Door",1,0,0,0,caliMachineNo);
    predoorpos = ui->spinBox_Door->value();
}

void MachineCalibration::on_pButton_door_work_clicked()
{
    ui->spinBox_Door->setValue(UIHandler::get_int_Param("VDWorkX",caliMachineNo));
    ui->label_door_data->setNum(UIHandler::get_int_Param("VDWorkX",caliMachineNo));
    predoorpos = ui->spinBox_Door->value();
    UIHandler::ActionDo("Door",2,0,0,0,caliMachineNo);
}


void MachineCalibration::on_pButton_door_set_clicked()
{
     if (predoorpos < ui->spinBox_Door->value())
        UIHandler::ActionDo("Door",4,ui->spinBox_Door->value()-predoorpos,0,0,caliMachineNo);
    else
        UIHandler::ActionDo("Door",3,predoorpos-ui->spinBox_Door->value(),0,0,caliMachineNo);

    predoorpos = ui->spinBox_Door->value();
}

void MachineCalibration::on_pButton_door_save_clicked()
{
    UIHandler::updata_int_Param("VDWorkX",ui->spinBox_Door->value(),caliMachineNo);
    ui->spinBox_Door->setValue(UIHandler::get_int_Param("VDWorkX",caliMachineNo));

    ui->label_door_data->setNum(UIHandler::get_int_Param("VDWorkX",caliMachineNo));

    UIHandler::settingParam("VDWorkX:"+ui->spinBox_Door->text(), caliMachineNo);
 }


void MachineCalibration::on_pButton_push_hard_clicked()
{
    ui->spinBox_Pump->setValue(0);
    UIHandler::ActionDo("Pump",1,0,0,0,caliMachineNo);
 }

void MachineCalibration::on_pButton_push_soft_clicked()
{
    ui->spinBox_Pump->setValue(UIHandler::get_int_Param("PumpSoftHomeX",caliMachineNo));
    UIHandler::ActionDo("Pump",9,ui->spinBox_Pump->value(),0,0,caliMachineNo);
    predoorpos = ui->spinBox_Pump->value();
}

void MachineCalibration::on_pButton_push_work_clicked()
{
    ui->spinBox_Pump->setValue(UIHandler::get_int_Param("PumpToolHomeX",caliMachineNo));
    ui->label_push_data->setNum(UIHandler::get_int_Param("PumpToolHomeX",caliMachineNo));
    UIHandler::ActionDo("Pump",9,ui->spinBox_Pump->value(),0,0,caliMachineNo);
}


void MachineCalibration::on_pButton_push_set_clicked()
{
    UIHandler::ActionDo("Pump",9,ui->spinBox_Pump->value(),0,0,caliMachineNo);
}

void MachineCalibration::on_pButton_push_save_clicked()
{
    int PumpToolHomeX = ui->spinBox_Pump->value();
    int PumpSoftHomeX = PumpToolHomeX - UIHandler::get_int_Param("PumpSoftHomeOffset",caliMachineNo);

    UIHandler::updata_int_Param("PumpToolHomeX",PumpToolHomeX,caliMachineNo);
    UIHandler::updata_int_Param("PumpSoftHomeX",PumpSoftHomeX,caliMachineNo);
    ui->spinBox_Pump->setValue(UIHandler::get_int_Param("PumpToolHomeX",caliMachineNo));
    //Sequence::getPtr()->checkParam(true);

    ui->label_push_data->setNum(UIHandler::get_int_Param("PumpToolHomeX",caliMachineNo));

    QString param;
    param = "PumpToolHomeX:" + QString::number(PumpToolHomeX) + "^";
    param += "PumpSoftHomeX:" + QString::number(PumpSoftHomeX);
    UIHandler::settingParam(param, caliMachineNo);
}


void MachineCalibration::on_pButton_door_in_clicked()
{
    UIHandler::ActionDo("Door",4,ui->spinBox_door_step->value(),ui->spinBox_speed->value(),0,caliMachineNo);
 }

void MachineCalibration::on_pButton_door_out_clicked()
{
    UIHandler::ActionDo("Door",3,ui->spinBox_door_step->value(),ui->spinBox_speed->value(),0,caliMachineNo);
}

void MachineCalibration::on_rButton_step_1_clicked()
{
    ui->spinBox_V1->setSingleStep(1);
    ui->spinBox_V2->setSingleStep(1);
    ui->spinBox_V3->setSingleStep(1);
    ui->spinBox_V4->setSingleStep(1);
    ui->spinBox_Door->setSingleStep(1);
    ui->spinBox_Pump->setSingleStep(1);
    ui->spinBox_split->setSingleStep(1);
    ui->spinBox_door_step->setSingleStep(1);
}

void MachineCalibration::on_rButton_step_10_clicked()
{
    ui->spinBox_V1->setSingleStep(10);
    ui->spinBox_V2->setSingleStep(10);
    ui->spinBox_V3->setSingleStep(10);
    ui->spinBox_V4->setSingleStep(10);
    ui->spinBox_Door->setSingleStep(10);
    ui->spinBox_Pump->setSingleStep(10);
    ui->spinBox_split->setSingleStep(10);
    ui->spinBox_door_step->setSingleStep(10);
}

void MachineCalibration::on_rButton_step_100_clicked()
{
    ui->spinBox_V1->setSingleStep(100);
    ui->spinBox_V2->setSingleStep(100);
    ui->spinBox_V3->setSingleStep(100);
    ui->spinBox_V4->setSingleStep(100);
    ui->spinBox_Door->setSingleStep(100);
    ui->spinBox_Pump->setSingleStep(100);
    ui->spinBox_split->setSingleStep(100);
    ui->spinBox_door_step->setSingleStep(100);
}

void MachineCalibration::on_rButton_step_500_clicked()
{
    ui->spinBox_V1->setSingleStep(500);
    ui->spinBox_V2->setSingleStep(500);
    ui->spinBox_V3->setSingleStep(500);
    ui->spinBox_V4->setSingleStep(500);
    ui->spinBox_Door->setSingleStep(500);
    ui->spinBox_Pump->setSingleStep(500);
    ui->spinBox_split->setSingleStep(500);
    ui->spinBox_door_step->setSingleStep(500);
}

void MachineCalibration::on_comboBox_machine_currentIndexChanged(int index)
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

        //UIHandler::setCurrMachineId(caliMachineNo);
        qDebug()<<"caliMachineNo"<<caliMachineNo;
        load_data(caliMachineNo);
    }
}

void MachineCalibration::UpdateUI(){
    qDebug()<<"MachineCalibration::UpdateUI";
    load_data(caliMachineNo);
}


void MachineCalibration::on_pButton_door_work_set_clicked()
{
    UIHandler::ActionDo("Door",1,ui->spinBox_door_work_data->value(),0,0,caliMachineNo);
}

void MachineCalibration::on_pButton_door_work_save_clicked()
{
    UIHandler::updata_int_Param("DoorOut",ui->spinBox_door_work_data->value(),caliMachineNo);

    UIHandler::settingParam("DoorOut:"+ui->spinBox_door_work_data->text(), caliMachineNo);
}

void MachineCalibration::on_pButton_door_work_soft_clicked()
{
    ui->spinBox_door_work_data->setValue(UIHandler::get_int_Param("DoorOut",caliMachineNo));
    ui->label_door_work_data->setNum(UIHandler::get_int_Param("DoorOut",caliMachineNo));
    UIHandler::ActionDo("Door",1,ui->spinBox_door_work_data->value(),0,0,caliMachineNo);
}
void MachineCalibration::on_pButton_split_hard_clicked()
{
    ui->spinBox_split->setValue(0);
    UIHandler::ActionDo("Split",1,0,0,0,caliMachineNo);
}

void MachineCalibration::on_pButton_split_soft_clicked()
{
    ui->spinBox_split->setValue(UIHandler::get_int_Param("SliptSoftHomeX",caliMachineNo));
    UIHandler::ActionDo("Split",1,ui->spinBox_split->value(),0,0,caliMachineNo);
}

void MachineCalibration::on_pButton_split_work_clicked()
{
    ui->spinBox_split->setValue(UIHandler::get_int_Param("SplitToolHomeX",caliMachineNo));
    ui->label_split_data->setNum(UIHandler::get_int_Param("SplitToolHomeX",caliMachineNo));
    UIHandler::ActionDo("Split",2,ui->spinBox_split->value(),0,0,caliMachineNo);
}

void MachineCalibration::on_pButton_split_set_clicked()
{
    UIHandler::ActionDo("Split",3,ui->spinBox_split->value(),0,0,caliMachineNo);
}

void MachineCalibration::on_pButton_split_save_clicked()
{
    int splitValue = ui->spinBox_split->value();
    int SplitWorkX = splitValue-UIHandler::get_int_Param("Split1SoftHomeOffset",caliMachineNo)+UIHandler::get_int_Param("SplitWorkOffset",caliMachineNo);
    int SplitSoftHomeX = splitValue-UIHandler::get_int_Param("SplitSoftHomeOffset");

    UIHandler::updata_int_Param("SplitToolHomeX",splitValue,caliMachineNo);
    UIHandler::updata_int_Param("SplitWorkX",SplitWorkX,caliMachineNo);
    UIHandler::updata_int_Param("SplitSoftHomeX",SplitSoftHomeX,caliMachineNo);
    ui->spinBox_split->setValue(UIHandler::get_int_Param("SplitToolHomeX",caliMachineNo));
    ui->label_split_data->setNum(UIHandler::get_int_Param("SplitWorkX",caliMachineNo));

    QString param;
    param = "SplitToolHomeX:" + QString::number(splitValue) + "^";
    param += "SplitWorkX:" + QString::number(SplitWorkX) + "^";
    param += "SplitSoftHomeX:" + QString::number(SplitSoftHomeX);
    UIHandler::settingParam(param, caliMachineNo);
}

void MachineCalibration::on_pButton_door_work_offset_clicked()
{
    UIHandler::updata_int_Param("DoorOffset",ui->spinBox_door_work_offset->value(),caliMachineNo);
    UIHandler::ActionDo("Door",14,ui->spinBox_door_work_offset->value(),0,0,caliMachineNo);
    UIHandler::settingParam("DoorOffset:"+ui->spinBox_door_work_offset->text(), caliMachineNo);
}
