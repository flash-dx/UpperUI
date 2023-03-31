#include "pidparam.h"
#include "ui_pidparam.h"

#include "../uihandler.h"
#include "components/onebtnmessagebox.h"
#include <QListView>

static PIDParam *winptr = nullptr;

PIDParam *PIDParam::getPtr()
{
    if (winptr == nullptr)
        winptr = new PIDParam;
    return winptr;
}

PIDParam::PIDParam(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PIDParam)
{
    ui->setupUi(this);

    int btnW = 299;
    int btnH = 106;
    int btnRight = 100;
    int btnBottom = 30;
    int btnLeft = UIHandler::contentWidth - btnW - btnRight;
    int btnTop = UIHandler::contentHeight - btnBottom - btnH;
    int btnAdd = 20;

    ui->pushButton->setGeometry(btnLeft, btnTop - (btnH + btnAdd),   btnW,btnH);
    ui->pButton_machine_back->setGeometry(btnLeft, btnTop, btnW,btnH);

    ui->comboBox_machine->setView(new QListView());
    ui->comboBox_machine->setGeometry(UIHandler::contentWidth - 200,10,200,75);
    ui->comboBox_machine->setStyleSheet(UIHandler::getStyleSheet("QComboBox"));

    caliMachineNo = -1;

    setStyleSheet("background-color:#f5f5f5;");
}

PIDParam::~PIDParam()
{
    delete ui;
}

void PIDParam::showEvent(QShowEvent *event){
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

    UIHandler::setBtTextCenter(ui->pushButton, 48,"background-image: url(:/images/confirmbt.png);text-align:left;");
    UIHandler::setBtTextCenter(ui->pButton_machine_back, 48,"background-image: url(:/images/back.png);text-align:left;");

    UIHandler::NotifyTitle("Pid_view",5);
}

void PIDParam::hideEvent(QHideEvent *event){
    Q_UNUSED(event);
}

void PIDParam::load_data(void)
{
    ui->label_PID1_P_TXT->setVisible(false);
    ui->label_PID1_I_TXT->setVisible(false);
    ui->label_PID1_D_TXT->setVisible(false);

    ui->label_PID2_P_TXT->setVisible(false);
    ui->label_PID2_I_TXT->setVisible(false);
    ui->label_PID2_D_TXT->setVisible(false);

    ui->label_PID3_P_TXT->setVisible(false);
    ui->label_PID3_I_TXT->setVisible(false);
    ui->label_PID3_D_TXT->setVisible(false);

    ui->label_PID4_P_TXT->setVisible(false);
    ui->label_PID4_I_TXT->setVisible(false);
    ui->label_PID4_D_TXT->setVisible(false);

    ui->label_PID5_P_TXT->setVisible(false);
    ui->label_PID5_I_TXT->setVisible(false);
    ui->label_PID5_D_TXT->setVisible(false);

    ui->label_PID6_P_TXT->setVisible(false);
    ui->label_PID6_I_TXT->setVisible(false);
    ui->label_PID6_D_TXT->setVisible(false);

    ui->label_PID7_P_TXT->setVisible(false);
    ui->label_PID7_I_TXT->setVisible(false);
    ui->label_PID7_D_TXT->setVisible(false);

    ui->label_PID8_P_TXT->setVisible(false);
    ui->label_PID8_I_TXT->setVisible(false);
    ui->label_PID8_D_TXT->setVisible(false);

    ui->label_PID9_P_TXT->setVisible(false);
    ui->label_PID9_I_TXT->setVisible(false);
    ui->label_PID9_D_TXT->setVisible(false);

    ui->label_PID10_P_TXT->setVisible(false);
    ui->label_PID10_I_TXT->setVisible(false);
    ui->label_PID10_D_TXT->setVisible(false);

    ui->label_PID11_P_TXT->setVisible(false);
    ui->label_PID11_I_TXT->setVisible(false);
    ui->label_PID11_D_TXT->setVisible(false);

    ui->label_PID12_P_TXT->setVisible(false);
    ui->label_PID12_I_TXT->setVisible(false);
    ui->label_PID12_D_TXT->setVisible(false);

    ui->label_PID13_P_TXT->setVisible(false);
    ui->label_PID13_I_TXT->setVisible(false);
    ui->label_PID13_D_TXT->setVisible(false);

    ui->label_PID14_P_TXT->setVisible(false);
    ui->label_PID14_I_TXT->setVisible(false);
    ui->label_PID14_D_TXT->setVisible(false);

    ui->label_PID15_P_TXT->setVisible(false);
    ui->label_PID15_I_TXT->setVisible(false);
    ui->label_PID15_D_TXT->setVisible(false);

    ui->spinBox_PID1_P_TXT->setValue(UIHandler::get_int_Param("PID_P1",caliMachineNo));
    ui->spinBox_PID1_I_TXT->setValue(UIHandler::get_int_Param("PID_I1",caliMachineNo));
    ui->spinBox_PID1_D_TXT->setValue(UIHandler::get_int_Param("PID_D1",caliMachineNo));

    ui->spinBox_PID2_P_TXT->setValue(UIHandler::get_int_Param("PID_P2",caliMachineNo));
    ui->spinBox_PID2_I_TXT->setValue(UIHandler::get_int_Param("PID_I2",caliMachineNo));
    ui->spinBox_PID2_D_TXT->setValue(UIHandler::get_int_Param("PID_D2",caliMachineNo));

    ui->spinBox_PID3_P_TXT->setValue(UIHandler::get_int_Param("PID_P3",caliMachineNo));
    ui->spinBox_PID3_I_TXT->setValue(UIHandler::get_int_Param("PID_I3",caliMachineNo));
    ui->spinBox_PID3_D_TXT->setValue(UIHandler::get_int_Param("PID_D3",caliMachineNo));

    ui->spinBox_PID4_P_TXT->setValue(UIHandler::get_int_Param("PID_P4",caliMachineNo));
    ui->spinBox_PID4_I_TXT->setValue(UIHandler::get_int_Param("PID_I4",caliMachineNo));
    ui->spinBox_PID4_D_TXT->setValue(UIHandler::get_int_Param("PID_D4",caliMachineNo));

    ui->spinBox_PID5_P_TXT->setValue(UIHandler::get_int_Param("PID_P5",caliMachineNo));
    ui->spinBox_PID5_I_TXT->setValue(UIHandler::get_int_Param("PID_I5",caliMachineNo));
    ui->spinBox_PID5_D_TXT->setValue(UIHandler::get_int_Param("PID_D5",caliMachineNo));

    ui->spinBox_PID6_P_TXT->setValue(UIHandler::get_int_Param("PID_P6",caliMachineNo));
    ui->spinBox_PID6_I_TXT->setValue(UIHandler::get_int_Param("PID_I6",caliMachineNo));
    ui->spinBox_PID6_D_TXT->setValue(UIHandler::get_int_Param("PID_D6",caliMachineNo));

    ui->spinBox_PID7_P_TXT->setValue(UIHandler::get_int_Param("PID_P7",caliMachineNo));
    ui->spinBox_PID7_I_TXT->setValue(UIHandler::get_int_Param("PID_I7",caliMachineNo));
    ui->spinBox_PID7_D_TXT->setValue(UIHandler::get_int_Param("PID_D7",caliMachineNo));

    ui->spinBox_PID8_P_TXT->setValue(UIHandler::get_int_Param("PID_P8",caliMachineNo));
    ui->spinBox_PID8_I_TXT->setValue(UIHandler::get_int_Param("PID_I8",caliMachineNo));
    ui->spinBox_PID8_D_TXT->setValue(UIHandler::get_int_Param("PID_D8",caliMachineNo));

    ui->spinBox_PID9_P_TXT->setValue(UIHandler::get_int_Param("PID_P9",caliMachineNo));
    ui->spinBox_PID9_I_TXT->setValue(UIHandler::get_int_Param("PID_I9",caliMachineNo));
    ui->spinBox_PID9_D_TXT->setValue(UIHandler::get_int_Param("PID_D9",caliMachineNo));

    ui->spinBox_PID10_P_TXT->setValue(UIHandler::get_int_Param("PID_P10",caliMachineNo));
    ui->spinBox_PID10_I_TXT->setValue(UIHandler::get_int_Param("PID_I10",caliMachineNo));
    ui->spinBox_PID10_D_TXT->setValue(UIHandler::get_int_Param("PID_D10",caliMachineNo));

    ui->spinBox_PID11_P_TXT->setValue(UIHandler::get_int_Param("PID_P11",caliMachineNo));
    ui->spinBox_PID11_I_TXT->setValue(UIHandler::get_int_Param("PID_I11",caliMachineNo));
    ui->spinBox_PID11_D_TXT->setValue(UIHandler::get_int_Param("PID_D11",caliMachineNo));

    ui->spinBox_PID12_P_TXT->setValue(UIHandler::get_int_Param("PID_P12",caliMachineNo));
    ui->spinBox_PID12_I_TXT->setValue(UIHandler::get_int_Param("PID_I12",caliMachineNo));
    ui->spinBox_PID12_D_TXT->setValue(UIHandler::get_int_Param("PID_D12",caliMachineNo));

    ui->spinBox_PID13_P_TXT->setValue(UIHandler::get_int_Param("PID_P13",caliMachineNo));
    ui->spinBox_PID13_I_TXT->setValue(UIHandler::get_int_Param("PID_I13",caliMachineNo));
    ui->spinBox_PID13_D_TXT->setValue(UIHandler::get_int_Param("PID_D13",caliMachineNo));

    ui->spinBox_PID14_P_TXT->setValue(UIHandler::get_int_Param("PID_P14",caliMachineNo));
    ui->spinBox_PID14_I_TXT->setValue(UIHandler::get_int_Param("PID_I14",caliMachineNo));
    ui->spinBox_PID14_D_TXT->setValue(UIHandler::get_int_Param("PID_D14",caliMachineNo));

    ui->spinBox_PID15_P_TXT->setValue(UIHandler::get_int_Param("PID_P15",caliMachineNo));
    ui->spinBox_PID15_I_TXT->setValue(UIHandler::get_int_Param("PID_I15",caliMachineNo));
    ui->spinBox_PID15_D_TXT->setValue(UIHandler::get_int_Param("PID_D15",caliMachineNo));
}

void PIDParam::on_PIDParam_accepted()
{

}

void PIDParam::on_pButton_machine_back_clicked()
{
    UIHandler::GoPage(UIHandler::PageId::Page_Setup_Menu);
}

void PIDParam::on_pushButton_clicked()
{
    SetCaliParam();
    if(caliMachineNo >= 0)
    {
        QString param;
        param = "PID_P1:" +  ui->spinBox_PID1_P_TXT->text() + "^";
        param += "PID_I1:" +  ui->spinBox_PID1_I_TXT->text() + "^";
        param += "PID_D1:" +  ui->spinBox_PID1_D_TXT->text() + "^";
        param += "PID_P2:" +  ui->spinBox_PID2_P_TXT->text() + "^";
        param += "PID_I2:" +  ui->spinBox_PID2_I_TXT->text() + "^";
        param += "PID_D2:" +  ui->spinBox_PID2_D_TXT->text() + "^";
        param += "PID_P3:" +  ui->spinBox_PID3_P_TXT->text() + "^";
        param += "PID_I3:" +  ui->spinBox_PID3_I_TXT->text() + "^";
        param += "PID_D3:" +  ui->spinBox_PID3_D_TXT->text() + "^";
        param += "PID_P4:" +  ui->spinBox_PID4_P_TXT->text() + "^";
        param += "PID_I4:" +  ui->spinBox_PID4_I_TXT->text() + "^";
        param += "PID_D4:" +  ui->spinBox_PID4_D_TXT->text() + "^";
        param += "PID_P5:" +  ui->spinBox_PID5_P_TXT->text() + "^";
        param += "PID_I5:" +  ui->spinBox_PID5_I_TXT->text() + "^";
        param += "PID_D5:" +  ui->spinBox_PID5_D_TXT->text() + "^";
        param += "PID_P6:" +  ui->spinBox_PID6_P_TXT->text() + "^";
        param += "PID_I6:" +  ui->spinBox_PID6_I_TXT->text() + "^";
        param += "PID_D6:" +  ui->spinBox_PID6_D_TXT->text() + "^";
        param += "PID_P7:" +  ui->spinBox_PID7_P_TXT->text() + "^";
        param += "PID_I7:" +  ui->spinBox_PID7_I_TXT->text() + "^";
        param += "PID_D7:" +  ui->spinBox_PID7_D_TXT->text() + "^";
        param += "PID_P8:" +  ui->spinBox_PID8_P_TXT->text() + "^";
        param += "PID_I8:" +  ui->spinBox_PID8_I_TXT->text() + "^";
        param += "PID_D8:" +  ui->spinBox_PID8_D_TXT->text() + "^";
        param += "PID_P9:" +  ui->spinBox_PID9_P_TXT->text() + "^";
        param += "PID_I9:" +  ui->spinBox_PID9_I_TXT->text() + "^";
        param += "PID_D9:" +  ui->spinBox_PID9_D_TXT->text() + "^";
        param += "PID_P10:" +  ui->spinBox_PID10_P_TXT->text() + "^";
        param += "PID_I10:" +  ui->spinBox_PID10_I_TXT->text() + "^";
        param += "PID_D10:" +  ui->spinBox_PID10_D_TXT->text() + "^";
        param += "PID_P11:" +  ui->spinBox_PID11_P_TXT->text() + "^";
        param += "PID_I11:" +  ui->spinBox_PID11_I_TXT->text() + "^";
        param += "PID_D11:" +  ui->spinBox_PID11_D_TXT->text() + "^";
        param += "PID_P12:" +  ui->spinBox_PID12_P_TXT->text() + "^";
        param += "PID_I12:" +  ui->spinBox_PID12_I_TXT->text() + "^";
        param += "PID_D12:" +  ui->spinBox_PID12_D_TXT->text() + "^";
        param += "PID_P13:" +  ui->spinBox_PID13_P_TXT->text() + "^";
        param += "PID_I13:" +  ui->spinBox_PID13_I_TXT->text() + "^";
        param += "PID_D13:" +  ui->spinBox_PID13_D_TXT->text() + "^";
        param += "PID_P14:" +  ui->spinBox_PID14_P_TXT->text() + "^";
        param += "PID_I14:" +  ui->spinBox_PID14_I_TXT->text() + "^";
        param += "PID_D14:" +  ui->spinBox_PID14_D_TXT->text() + "^";
        param += "PID_P15:" +  ui->spinBox_PID15_P_TXT->text() + "^";
        param += "PID_I15:" +  ui->spinBox_PID15_I_TXT->text() + "^";
        param += "PID_D15:" +  ui->spinBox_PID15_D_TXT->text();
        UIHandler::settingParam(param, caliMachineNo);

       OneBtnMessageBox::display(tr("PID数据保存完成！"),tr("返回"));
    }
}

void PIDParam::on_comboBox_machine_currentIndexChanged(int index)
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

void PIDParam::SetCaliParam()
{
    UIHandler::updata_int_Param("PID_P1",ui->spinBox_PID1_P_TXT->value(),caliMachineNo);
    UIHandler::updata_int_Param("PID_I1",ui->spinBox_PID1_I_TXT->value(),caliMachineNo);
    UIHandler::updata_int_Param("PID_D1",ui->spinBox_PID1_D_TXT->value(),caliMachineNo);

    UIHandler::updata_int_Param("PID_P2",ui->spinBox_PID2_P_TXT->value(),caliMachineNo);
    UIHandler::updata_int_Param("PID_I2",ui->spinBox_PID2_I_TXT->value(),caliMachineNo);
    UIHandler::updata_int_Param("PID_D2",ui->spinBox_PID2_D_TXT->value(),caliMachineNo);

    UIHandler::updata_int_Param("PID_P3",ui->spinBox_PID3_P_TXT->value(),caliMachineNo);
    UIHandler::updata_int_Param("PID_I3",ui->spinBox_PID3_I_TXT->value(),caliMachineNo);
    UIHandler::updata_int_Param("PID_D3",ui->spinBox_PID3_D_TXT->value(),caliMachineNo);

    UIHandler::updata_int_Param("PID_P4",ui->spinBox_PID4_P_TXT->value(),caliMachineNo);
    UIHandler::updata_int_Param("PID_I4",ui->spinBox_PID4_I_TXT->value(),caliMachineNo);
    UIHandler::updata_int_Param("PID_D4",ui->spinBox_PID4_D_TXT->value(),caliMachineNo);

    UIHandler::updata_int_Param("PID_P5",ui->spinBox_PID5_P_TXT->value(),caliMachineNo);
    UIHandler::updata_int_Param("PID_I5",ui->spinBox_PID5_I_TXT->value(),caliMachineNo);
    UIHandler::updata_int_Param("PID_D5",ui->spinBox_PID5_D_TXT->value(),caliMachineNo);

    UIHandler::updata_int_Param("PID_P6",ui->spinBox_PID6_P_TXT->value(),caliMachineNo);
    UIHandler::updata_int_Param("PID_I6",ui->spinBox_PID6_I_TXT->value(),caliMachineNo);
    UIHandler::updata_int_Param("PID_D6",ui->spinBox_PID6_D_TXT->value(),caliMachineNo);

    UIHandler::updata_int_Param("PID_P7",ui->spinBox_PID7_P_TXT->value(),caliMachineNo);
    UIHandler::updata_int_Param("PID_I7",ui->spinBox_PID7_I_TXT->value(),caliMachineNo);
    UIHandler::updata_int_Param("PID_D7",ui->spinBox_PID7_D_TXT->value(),caliMachineNo);

    UIHandler::updata_int_Param("PID_P8",ui->spinBox_PID8_P_TXT->value(),caliMachineNo);
    UIHandler::updata_int_Param("PID_I8",ui->spinBox_PID8_I_TXT->value(),caliMachineNo);
    UIHandler::updata_int_Param("PID_D8",ui->spinBox_PID8_D_TXT->value(),caliMachineNo);

    UIHandler::updata_int_Param("PID_P9",ui->spinBox_PID9_P_TXT->value(),caliMachineNo);
    UIHandler::updata_int_Param("PID_I9",ui->spinBox_PID9_I_TXT->value(),caliMachineNo);
    UIHandler::updata_int_Param("PID_D9",ui->spinBox_PID9_D_TXT->value(),caliMachineNo);

    UIHandler::updata_int_Param("PID_P10",ui->spinBox_PID10_P_TXT->value(),caliMachineNo);
    UIHandler::updata_int_Param("PID_I10",ui->spinBox_PID10_I_TXT->value(),caliMachineNo);
    UIHandler::updata_int_Param("PID_D10",ui->spinBox_PID10_D_TXT->value(),caliMachineNo);

    UIHandler::updata_int_Param("PID_P11",ui->spinBox_PID11_P_TXT->value(),caliMachineNo);
    UIHandler::updata_int_Param("PID_I11",ui->spinBox_PID11_I_TXT->value(),caliMachineNo);
    UIHandler::updata_int_Param("PID_D11",ui->spinBox_PID11_D_TXT->value(),caliMachineNo);

    UIHandler::updata_int_Param("PID_P12",ui->spinBox_PID12_P_TXT->value(),caliMachineNo);
    UIHandler::updata_int_Param("PID_I12",ui->spinBox_PID12_I_TXT->value(),caliMachineNo);
    UIHandler::updata_int_Param("PID_D12",ui->spinBox_PID12_D_TXT->value(),caliMachineNo);

    UIHandler::updata_int_Param("PID_P13",ui->spinBox_PID13_P_TXT->value(),caliMachineNo);
    UIHandler::updata_int_Param("PID_I13",ui->spinBox_PID13_I_TXT->value(),caliMachineNo);
    UIHandler::updata_int_Param("PID_D13",ui->spinBox_PID13_D_TXT->value(),caliMachineNo);

    UIHandler::updata_int_Param("PID_P14",ui->spinBox_PID14_P_TXT->value(),caliMachineNo);
    UIHandler::updata_int_Param("PID_I14",ui->spinBox_PID14_I_TXT->value(),caliMachineNo);
    UIHandler::updata_int_Param("PID_D14",ui->spinBox_PID14_D_TXT->value(),caliMachineNo);

    UIHandler::updata_int_Param("PID_P15",ui->spinBox_PID15_P_TXT->value(),caliMachineNo);
    UIHandler::updata_int_Param("PID_I15",ui->spinBox_PID15_I_TXT->value(),caliMachineNo);
    UIHandler::updata_int_Param("PID_D15",ui->spinBox_PID15_D_TXT->value(),caliMachineNo);

    //Sequence::getPtr()->checkParam(true);
}
