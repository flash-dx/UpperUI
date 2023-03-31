#include "light.h"
#include "ui_light.h"
#include "../uihandler.h"
#include <QListView>

static Light *winptr = nullptr;

Light *Light::getPtr()
{
    if (winptr == nullptr)
        winptr = new Light;
    return winptr;
}


Light::Light(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Light)
{
    ui->setupUi(this);

    int btnW = 299;
    int btnH = 106;
    int btnRight = 100;
    int btnBottom = 30;
    int btnLeft = UIHandler::contentWidth - btnW - btnRight;
    int btnTop = UIHandler::contentHeight - btnBottom - btnH;
    int btnAdd = 20;

    ui->pButton_backl->setGeometry(btnLeft, btnTop, btnW,btnH);

    setStyleSheet("background-color:#f5f5f5;");
    ui->comboBox_machine->setView(new QListView());
    ui->comboBox_machine->setGeometry(UIHandler::contentWidth - 200,10,200,75);
    ui->comboBox_machine->setStyleSheet(UIHandler::getStyleSheet("QComboBox"));

    caliMachineNo = -1;
}

Light::~Light()
{
    delete ui;
}

void Light::on_pButton_backl_clicked()
{
     UIHandler::GoPage(UIHandler::PageId::Page_Setup_Menu);
}

void Light::on_pButton_work_clicked()
{
   // doingBox.show(qsTr("舱门移动到工作位"))
    //UIHandler::UpdateState(UIHandler::StateId::State_Loading_Open);
    UIHandler::ActionDo("Door",2,0,0,0,caliMachineNo);
}

void Light::on_pButton_hard_clicked()
{
   // doingBox.show(qsTr("舱门回到硬件零点"))
    //UIHandler::UpdateState(UIHandler::StateId::State_Loading_Open);
    UIHandler::ActionDo("Door",5,0,0,0,caliMachineNo);
}

void Light::on_pButton_set_clicked()
{
    QString panelCode = "";
     QString panelName = ui->cBox_panel->currentText();

     QStringList list = panelName.split("_");
     if(list.count() > 1)
     {
         panelCode = list[0];
         panelName = panelName.remove(0,panelCode.length()+1);

         UIHandler::setPanelName(panelName);
         UIHandler::setPanelCode(panelCode);
         UIHandler::setBoxCode(UIHandler::getBoxCode(panelCode));
     }
}

void Light::on_pButton_set_xy_clicked()
{
    UIHandler::updata_int_Param("LightCX",ui->lEdit_X->text().toInt(),caliMachineNo);
    UIHandler::updata_int_Param("LightCY",ui->lEdit_Y->text().toInt(),caliMachineNo);
    UIHandler::updata_int_Param("LightR",ui->lEdit_rad->text().toInt(),caliMachineNo);
    QString param;
    param = "LightCX:" +  ui->lEdit_X->text() + "^";
    param += "LightCY:" +  ui->lEdit_Y->text() + "^";
    param += "LightR:" +  ui->lEdit_rad->text() + "^";
    param += "setLight:0";
    UIHandler::settingParam(param, caliMachineNo);
}

void Light::on_pButton_get_light_clicked()
{
  //  doingBox.show(qsTr("获取荧光亮度"))
    //UIHandler::UpdateState(UIHandler::StateId::State_Loading_Open);
    UIHandler::settingParam("startLight:0", caliMachineNo);
}

void Light::CameraView(string imgstr, int machineNo)
{
    qDebug()<<"CameraView"<<imgstr.length()<<machineNo<<caliMachineNo;

    if (machineNo == caliMachineNo){

        int pos = imgstr.rfind("AAAAAAAA");
        QByteArray imgbuf(imgstr.c_str(), pos);

        if (imgbuf.startsWith(QByteArray("CameraView")) && pos > 0){
            QByteArray jpgBuff = qUncompress(imgbuf.mid(10,pos - 10));
            QImage img;
            img.loadFromData(jpgBuff,"jpeg");
            imgbuf.clear();

            ui->label->setScaledContents(true);
            ui->label->setPixmap(QPixmap::fromImage(img.scaled(img.width(),img.height())));
        }
    }
}

void Light::RefreshLight(int lightvalue, int machineNo){
    qDebug()<<"Light::RefreshLight"<<lightvalue<<machineNo<<caliMachineNo;
    if(machineNo == caliMachineNo)
    {
      ui->label_light_num->setText(QString::number(lightvalue/100.0,'0',2));
     //UIHandler::UpdateState(UIHandler::StateId::State_Loading_Close);
    }
}

void Light::showEvent(QShowEvent *event){
    Q_UNUSED(event);
    ui->retranslateUi(this);

    ui->cBox_panel->clear();
    list<string> testlist = UIHandler::onePointTestList(UIHandler::get_int_Param("LanguageCode"));
    for (auto it = testlist.begin();  it != testlist.end(); it++){
        ui->cBox_panel->addItem(str2q(*it));
    }
    ui->pButton_get_light->setText(tr("获取亮度"));
    ui->label_light->setText(tr("荧光亮度"));

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

//X    connect(UIHandler::getPtr(),&UIHandler::sig_callRefeshView,this,&Light::CameraView);
    connect(UIHandler::getPtr(),&UIHandler::sig_refreshLightValue,this,&Light::RefreshLight);
    connect(UIHandler::getPtr(),&UIHandler::sig_CamerView,this,&Light::CameraView);

    UIHandler::setBtTextCenter(ui->pButton_get_light, 48,"background-image: url(:/images/confirmbt.png);text-align:left;padding-bottom:20px;");
    UIHandler::setBtTextCenter(ui->pButton_backl, 48,"background-image: url(:/images/back.png);text-align:left;padding-bottom:10px;");

    UIHandler::NotifyTitle("setup_light",5);
}

void Light::hideEvent(QHideEvent *event){
    Q_UNUSED(event);

    UIHandler::getPtr()->disconnect(this);
}

void Light::on_comboBox_machine_currentIndexChanged(int index)
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
    }
}

void Light::load_data()
{
    ui->lEdit_X->setText(QString::number(UIHandler::get_int_Param("LightCX",caliMachineNo)));
    ui->lEdit_Y->setText(QString::number(UIHandler::get_int_Param("LightCY",caliMachineNo)));
    ui->lEdit_rad->setText(QString::number(UIHandler::get_int_Param("LightR",caliMachineNo)));
    ui->label_light_num->setText("");
}
