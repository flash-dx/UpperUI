#include "projectparam.h"
#include "ui_projectparam.h"
#include <QListView>

#include "../uihandler.h"


static ProjectParam *winptr = nullptr;

ProjectParam *ProjectParam::getPtr()
{
    if (winptr == nullptr)
        winptr = new ProjectParam;
    return winptr;
}

ProjectParam::ProjectParam(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProjectParam)
{
    ui->setupUi(this);

    ui->rButton_c1->setStyleSheet("QRadioButton::indicator{width:35px;height:35px;}");
    ui->rButton_c2->setStyleSheet("QRadioButton::indicator{width:35px;height:35px;}");
    ui->rButton_c3->setStyleSheet("QRadioButton::indicator{width:35px;height:35px;}");
    ui->rButton_c4->setStyleSheet("QRadioButton::indicator{width:35px;height:35px;}");
    ui->rButton_c5->setStyleSheet("QRadioButton::indicator{width:35px;height:35px;}");
    ui->rButton_b1->setStyleSheet("QRadioButton::indicator{width:35px;height:35px;}");
    ui->rButton_b2->setStyleSheet("QRadioButton::indicator{width:35px;height:35px;}");
    ui->pButton_machine_back->setGeometry(UIHandler::contentWidth-299-100,UIHandler::contentHeight-106-30,299,106);
    setStyleSheet("background-color:#f5f5f5;");

    ui->comboBox_machine->setView(new QListView());
    ui->comboBox_machine->setGeometry(UIHandler::contentWidth - 200,10,200,75);
    ui->comboBox_machine->setStyleSheet(UIHandler::getStyleSheet("QComboBox"));

    caliMachineNo = -1;
}

ProjectParam::~ProjectParam()
{
    delete ui;
}

void ProjectParam::showEvent(QShowEvent *event){
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

    UIHandler::NotifyTitle("setup_projectparam",5);
}

void ProjectParam::hideEvent(QHideEvent *event)
{
    Q_UNUSED(event);
}

void ProjectParam::load_data(void)
{
    ui->spinBox_high->setValue(UIHandler::get_int_Param("LiquidsHeight",caliMachineNo));
    ui->spinBox_pre->setValue(UIHandler::get_int_Param("DryWet",caliMachineNo)/100.0);

    if (UIHandler::get_int_Param("ClearMode",caliMachineNo)==0)
      ui->rButton_c1->setChecked(true);
    else if (UIHandler::get_int_Param("ClearMode",caliMachineNo)==1)
      ui->rButton_c2->setChecked(true);
    else if (UIHandler::get_int_Param("ClearMode",caliMachineNo)==2)
      ui->rButton_c3->setChecked(true);
    else if (UIHandler::get_int_Param("ClearMode",caliMachineNo)==3)
      ui->rButton_c4->setChecked(true);
    else if (UIHandler::get_int_Param("ClearMode",caliMachineNo)==4)
      ui->rButton_c5->setChecked(true);

    if (UIHandler::get_int_Param("MachineMode")==0)
      ui->rButton_b1->setChecked(true);
    else if (UIHandler::get_int_Param("MachineMode")==1)
      ui->rButton_b2->setChecked(true);

    ui->rButton_b1->setEnabled(false);
    ui->rButton_b2->setEnabled(false);
    if(UIHandler::get_int_Param("TempCompensation") == 1)
        ui->checkBox_temp->setChecked(true);
    else
        ui->checkBox_temp->setChecked(false);
}

void ProjectParam::on_pButton_machine_back_clicked()
{
    UIHandler::GoPage(UIHandler::PageId::Page_Setup_Menu);
}


void ProjectParam::on_rButton_c1_clicked()
{
    if(caliMachineNo >= 0)
    {
        UIHandler::updata_int_Param("ClearMode",0,caliMachineNo);
    }
}

void ProjectParam::on_rButton_c2_clicked()
{
    if(caliMachineNo >= 0)
    {
        UIHandler::updata_int_Param("ClearMode",1,caliMachineNo);
    }
}

void ProjectParam::on_rButton_c3_clicked()
{
    if(caliMachineNo >= 0)
    {
        UIHandler::updata_int_Param("ClearMode",2,caliMachineNo);
    }
}

void ProjectParam::on_rButton_c4_clicked()
{
    if(caliMachineNo >= 0)
    {
        UIHandler::updata_int_Param("ClearMode",3,caliMachineNo);
    }
}

void ProjectParam::on_rButton_c5_clicked()
{
    if(caliMachineNo >= 0)
    {
        UIHandler::updata_int_Param("ClearMode",4,caliMachineNo);
    }
}

void ProjectParam::on_rButton_b1_clicked()
{
     UIHandler::updata_int_Param("MachineMode",0);
}

void ProjectParam::on_rButton_b2_clicked()
{
    UIHandler::updata_int_Param("MachineMode",1);
}

void ProjectParam::on_spinBox_high_valueChanged(int arg1)
{
    qDebug()<<arg1<<223344;
    if(caliMachineNo >= 0)
    {
        if (arg1 != UIHandler::get_int_Param("LiquidsHeight",caliMachineNo))
        {
            UIHandler::updata_int_Param("LiquidsHeight",arg1,caliMachineNo);
        }
    }
}

void ProjectParam::on_spinBox_pre_valueChanged(const QString &arg1)
{
    qDebug()<<arg1<<arg1.toFloat()<<445566<<caliMachineNo;
    if(caliMachineNo >= 0)
    {
        if (arg1 != UIHandler::get_int_Param("DryWet",caliMachineNo))
        {
            UIHandler::updata_int_Param("DryWet",int((arg1.toDouble()+0.005)*100.0),caliMachineNo);
        }
    }
}

void ProjectParam::on_comboBox_machine_currentIndexChanged(int index)
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

void ProjectParam::on_checkBox_temp_clicked(bool checked)
{
    qDebug()<<"ProjectParam::on_checkBox_temp_clicked"<<checked;
    UIHandler::updata_int_Param("TempCompensation",checked,caliMachineNo);
    if(checked)
        UIHandler::settingParam("TempCompensation:1", caliMachineNo);
    else
        UIHandler::settingParam("TempCompensation:0", caliMachineNo);
}
