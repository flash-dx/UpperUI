#include "camerasetup.h"
#include "ui_camerasetup.h"
#include "../uihandler.h"
#include <QListView>

static int timerid_cap = 0;
static CameraSetup *winptr = nullptr;

CameraSetup *CameraSetup::getPtr()
{
    if (winptr == nullptr)
        winptr = new CameraSetup;
    return winptr;
}

CameraSetup::CameraSetup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CameraSetup)
{
    ui->setupUi(this);

    int btnW = 299;
    int btnH = 106;
    int btnRight = 100;
    int btnBottom = 30;
    int btnLeft = UIHandler::contentWidth - btnW - btnRight;
    int btnTop = UIHandler::contentHeight - btnBottom - btnH;

    ui->pButton_backl->setGeometry(btnLeft, btnTop, btnW,btnH);

    ui->Setup_CameraSetup_lbCam->setGeometry(20,20,931,621);
    ui->Setup_CameraSetup_lbCam->setAlignment(Qt::AlignCenter);

    ui->comboBox_lightLevel->setStyleSheet(UIHandler::getStyleSheet("QComboBox"));

    setStyleSheet("background-color:#f5f5f5;");

    ui->comboBox_machine->setView(new QListView());
    ui->comboBox_machine->setGeometry(UIHandler::contentWidth - 200,10,200,75);
    ui->comboBox_machine->setStyleSheet(UIHandler::getStyleSheet("QComboBox"));

    caliMachineNo = -1;

    qRegisterMetaType<string>("string");

    ui->cBox_open_auto->setVisible(false);
    ui->label_temp->setVisible(false);
    ui->sBox_temp->setVisible(false);
    ui->pButton_temp->setVisible(false);
}

CameraSetup::~CameraSetup()
{
    delete ui;
}

void CameraSetup::showEvent(QShowEvent *event){
    Q_UNUSED(event);
    ui->retranslateUi(this);

    bView = false;
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

    ui->comboBox_lightLevel->blockSignals(true);
    ui->comboBox_lightLevel->addItem("2");
    ui->comboBox_lightLevel->addItem("3");
    ui->comboBox_lightLevel->addItem("4");
    ui->comboBox_lightLevel->addItem("5");
    ui->comboBox_lightLevel->blockSignals(false);

    load_data();

    ui->cBox_open_auto->setStyleSheet("QCheckBox::indicator{width:40px;height:40px;}");
    ui->cBox_show_box->setStyleSheet("QCheckBox::indicator{width:40px;height:40px;}");
    UIHandler::setBtTextCenter(ui->pButton_backl, 48,"background-image: url(:/images/back.png);text-align:left;padding-bottom:10px;");

//X    connect(UIHandler::getPtr(),&UIHandler::sig_callRefeshView,this,&CameraSetup::CameraView);
    connect(UIHandler::getPtr(),&UIHandler::sig_autoFocusNotify,this,&CameraSetup::slot_autoFocusNotify);
    connect(UIHandler::getPtr(),&UIHandler::sig_CamerView,this,&CameraSetup::slot_CamerView);

    UIHandler::NotifyTitle("setup_camera",5);
}

void CameraSetup::hideEvent(QHideEvent *event){
    Q_UNUSED(event);
    UIHandler::getPtr()->disconnect(this);
    on_pButton_stop_view_clicked();
}

void CameraSetup::on_pButton_backl_clicked()
{
    UIHandler::GoPage(UIHandler::PageId::Page_Setup_Menu);
}

void CameraSetup::on_pButton_open_view_clicked()
{
    if (!bView && caliMachineNo >= 0 && UIHandler::isConnected(caliMachineNo)){
        ui->Setup_CameraSetup_lbCam->setText(tr("图像加载中..."));
        UIHandler::StartView(ui->cBox_show_box->checkState()?1:0,ui->comboBox_lightLevel->currentText().toInt(),caliMachineNo);
        bView = true;
    }
}

void CameraSetup::on_pButton_stop_view_clicked()
{
    if (bView){
        bView = false;
        ui->Setup_CameraSetup_lbCam->setText(tr("预览停止"));
        UIHandler::StopView(caliMachineNo);
    }
    else {
        UIHandler::ActionDo("Light",1,0,0,0,caliMachineNo);
    }
}

void CameraSetup::on_pButton_open_light_clicked()
{
    int lightLevel = ui->comboBox_lightLevel->currentIndex() + 2;    
    UIHandler::ActionDo("Light",lightLevel,0,0,0,caliMachineNo);
}

void CameraSetup::on_pButton_close_light_clicked()
{
    UIHandler::ActionDo("Light",1,0,0,0,caliMachineNo);
}

void CameraSetup::on_pButton_auto_focus_clicked()
{
    if (!bView && caliMachineNo >= 0 && UIHandler::isConnected(caliMachineNo)){
        ui->Setup_CameraSetup_lbCam->setText(tr("图像加载中..."));
        UIHandler::settingParam("autoFocus:0", caliMachineNo);
        bView = true;
    }
}

void CameraSetup::on_pButton_time_clicked()
{
    if(caliMachineNo >= 0)
    {
        qDebug()<<"CameraSetup UIHandler::setAbs"<<ui->sBox_time->value()<<caliMachineNo;
        UIHandler::updata_int_Param("CamAbs",ui->sBox_time->value(),caliMachineNo);
        UIHandler::settingParam("CamAbs:"+ui->sBox_time->text(), caliMachineNo);
    }
}

void CameraSetup::on_pButton_gain_clicked()
{
    if(caliMachineNo >= 0)
    {
        qDebug()<<"CameraSetup UIHandler::CamGain"<<ui->sBox_gain->value()<<caliMachineNo;
        UIHandler::updata_int_Param("CamGain",ui->sBox_gain->value(),caliMachineNo);
        UIHandler::settingParam("CamGain:"+ui->sBox_gain->text(), caliMachineNo);
    }
}

void CameraSetup::on_pButton_focus_clicked()
{
    if(caliMachineNo >= 0)
    {
        qDebug()<<"CameraSetup UIHandler::Focus"<<ui->sBox_focus->value()<<caliMachineNo;
        UIHandler::updata_int_Param("CamFocus",ui->sBox_focus->value(), caliMachineNo);
        UIHandler::settingParam("CamFocus:"+ui->sBox_focus->text(), caliMachineNo);
        UIHandler::ActionDo("Focus",2,ui->sBox_focus->value()+2600,0,0,caliMachineNo);
    }
}

void CameraSetup::on_pButton_reset_clicked()
{
    if(caliMachineNo >= 0)
    {
        ui->sBox_focus->setValue(0);
        qDebug()<<"CameraSetup UIHandler::CamFocus"<<ui->sBox_focus->value()<<caliMachineNo;
        UIHandler::updata_int_Param("CamFocus",0, caliMachineNo);
        UIHandler::settingParam("CamFocus:0", caliMachineNo);
        UIHandler::ActionDo("Focus",1,0,0,0,caliMachineNo);
    }
}

void CameraSetup::on_pButton_temp_clicked()
{
    if(caliMachineNo >= 0)
    {
        qDebug()<<"CameraSetup UIHandler::CamWhiteBlance"<<(ui->cBox_open_auto->checkState()?0:ui->sBox_temp->value())<<caliMachineNo;
        UIHandler::updata_int_Param("CamWhiteBlance",ui->cBox_open_auto->checkState()?0:ui->sBox_temp->value(),caliMachineNo);
        UIHandler::settingParam("CamWhiteBlance:"+ui->sBox_temp->text(), caliMachineNo);
    }
}

void CameraSetup::on_pButton_area_clicked()
{
    if(caliMachineNo >= 0)
    {
        UIHandler::updata_int_Param("FocusX",ui->lineEdit_x->text().toInt(), caliMachineNo);
        UIHandler::updata_int_Param("FocusY",ui->lineEdit_y->text().toInt(), caliMachineNo);
        UIHandler::updata_int_Param("FocusWidth",ui->lineEdit_w->text().toInt(), caliMachineNo);
        UIHandler::updata_int_Param("FocusHeight",ui->lineEdit_h->text().toInt(), caliMachineNo);

        QString param;
        param = "FocusX:" +  ui->lineEdit_x->text() + "^";
        param += "FocusY:" +  ui->lineEdit_y->text() + "^";
        param += "FocusWidth:" +  ui->lineEdit_w->text() + "^";
        param += "FocusHeight:" +  ui->lineEdit_h->text() + "^";
        param += "setFocus:0";
        UIHandler::settingParam(param, caliMachineNo);
    }
}

void CameraSetup::on_cBox_show_box_clicked()
{
    if (ui->cBox_show_box->checkState())
        UIHandler::settingParam("setViewType:1", caliMachineNo);
    else
        UIHandler::settingParam("setViewType:0", caliMachineNo);
}

void CameraSetup::CameraView(QImage img,int machineNo)
{
    qDebug()<<"CameraSetup::CameraView"<<bView;
    if (bView && machineNo == caliMachineNo)
    {
       ui->Setup_CameraSetup_lbCam->setPixmap(QPixmap::fromImage(img.scaled(ui->Setup_CameraSetup_lbCam->width(),ui->Setup_CameraSetup_lbCam->height())));
    }

}

void CameraSetup::on_pButton_picture_clicked()
{
    if(caliMachineNo >= 0)
    {
        timerid_cap = startTimer(1000);
//X         UIHandler::UpdateState(UIHandler::StateId::State_Loading_Open);
        UIHandler::settingParam("Pictrure:0", caliMachineNo);
    }
     //Sequence::getPtr()->saveView();
}

void CameraSetup::on_cBox_show_box_stateChanged(int arg1)
{
    //UIHandler::settingParam(Param_setViewType, arg1, true, caliMachineNo);
}


void CameraSetup::timerEvent(QTimerEvent *e)
{
    if (e->timerId() == timerid_cap){
//X         UIHandler::UpdateState(UIHandler::StateId::State_Loading_Close);
        if (timerid_cap != 0){
            killTimer(timerid_cap);
            timerid_cap = 0;
        }
    }
    else
        killTimer(e->timerId());
}

void CameraSetup::slot_autoFocusNotify(int status, int value, int machineNo)
{
     qDebug()<<"autoFocusNotify"<<status<<value<<machineNo<<caliMachineNo<<UIHandler::get_int_Param("CamFocus", caliMachineNo);
     if(machineNo == caliMachineNo)
         ui->sBox_focus->setValue(value);
}

void CameraSetup::on_comboBox_machine_currentIndexChanged(int index)
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

void CameraSetup::load_data(void)
{
    ui->sBox_time->setValue(UIHandler::get_int_Param("CamAbs",caliMachineNo));  //曝光时间 Sequence::getPtr()->getAbs()
    ui->sBox_gain->setValue(UIHandler::get_int_Param("CamGain",caliMachineNo));  //增益
    ui->sBox_focus->setValue(UIHandler::get_int_Param("CamFocus",caliMachineNo)); //焦距
    if (UIHandler::get_int_Param("CamWhiteBlance",caliMachineNo)==0)   //是否打开自动白平衡
        ui->cBox_open_auto->setChecked(true);
    else
        ui->cBox_open_auto->setChecked(false);
    ui->sBox_temp->setValue(UIHandler::get_int_Param("CamWhiteBlance",caliMachineNo)); //白平衡温度

    ui->lineEdit_x->setText(QString::number(UIHandler::get_int_Param("FocusX",caliMachineNo)));
    ui->lineEdit_y->setText(QString::number(UIHandler::get_int_Param("FocusY",caliMachineNo)));
    ui->lineEdit_w->setText(QString::number(UIHandler::get_int_Param("FocusWidth",caliMachineNo)));
    ui->lineEdit_h->setText(QString::number(UIHandler::get_int_Param("FocusHeight",caliMachineNo)));
    ui->Setup_CameraSetup_lbCam->setText(tr("预览停止"));
}

void CameraSetup::slot_CamerView(string imgstr, int machineNo)
{
    qDebug()<<"CameraSetup::CamerView "<<imgstr.length()<<"bView="<<bView<<"machineNo="<<machineNo<<"caliMachineNo="<<caliMachineNo;
    if (bView && machineNo == caliMachineNo){
        int pos = imgstr.rfind("AAAAAAAA");
        QByteArray imgbuf(imgstr.c_str(), pos);
        if (imgbuf.startsWith(QByteArray("CameraView")) && pos > 0){
            QByteArray jpgBuff = qUncompress(imgbuf.mid(10,pos - 10));
            QImage img;
            img.loadFromData(jpgBuff,"jpeg");
            imgbuf.clear();

            ui->Setup_CameraSetup_lbCam->setPixmap(QPixmap::fromImage(img.scaled(ui->Setup_CameraSetup_lbCam->width(),ui->Setup_CameraSetup_lbCam->height())));
        }
    }
}

void CameraSetup::on_comboBox_lightLevel_currentIndexChanged(int index)
{
    qDebug()<<"on_comboBox_lightLevel_currentIndexChanged"<<index;
    UIHandler::ActionDo("Light",index + 2,0,0,0,caliMachineNo);
}

void CameraSetup::on_pButton_shutter_on_clicked()
{    
    UIHandler::ActionDo("Shutter",0,0,1,0,caliMachineNo);
}

void CameraSetup::on_pButton_shutter_off_clicked()
{
    UIHandler::ActionDo("Shutter",0,0,0,0,caliMachineNo);
}
