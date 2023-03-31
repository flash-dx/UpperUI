#include "lockscreenset.h"
#include "ui_lockscreenset.h"
#include "../uihandler.h"
#include "setupmenu.h"
#include <QListView>

static LockScreenSet *winptr = nullptr;

LockScreenSet *LockScreenSet::getPtr()
{
    if (winptr == nullptr)
        winptr = new LockScreenSet;
    return winptr;
}

LockScreenSet::LockScreenSet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LockScreenSet)
{
    ui->setupUi(this);

    int init_x = (UIHandler::contentWidth-584)/2;
    int init_y = (UIHandler::contentHeight-306)/2;

    ui->label_background->setGeometry(init_x,init_y,584,306);
    ui->label_switch->setGeometry(init_x+30,init_y+20,360,58);
    ui->label_switch->setAlignment(Qt::AlignVCenter);
    ui->pushButton_switch->setGeometry(init_x+420,init_y+20,90,58);
    ui->label_time->setGeometry(init_x+30,init_y+160,200,64);
    ui->label_time->setAlignment(Qt::AlignVCenter);
    ui->comboBox_time->setGeometry(init_x+250,init_y+160,293,64);
    ui->pushButton_return->setGeometry(UIHandler::contentWidth-299-100,UIHandler::contentHeight-106-30,299,106);
    ui->comboBox_time->setView(new QListView());

    initStyleSheet();
}

LockScreenSet::~LockScreenSet()
{
    delete ui;
}

void LockScreenSet::showEvent(QShowEvent *event){
    Q_UNUSED(event);

    ui->label_switch->setText(tr("启用锁屏功能"));
    ui->label_time->setText(tr("锁屏时间"));
    ui->pushButton_return->setText(tr("返回"));

    ui->comboBox_time->blockSignals(true);
    ui->comboBox_time->clear();
    ui->comboBox_time->addItem(tr("1min"));
    ui->comboBox_time->addItem(tr("3min"));
    ui->comboBox_time->addItem(tr("5min"));
    ui->comboBox_time->addItem(tr("10min"));
    ui->comboBox_time->addItem(tr("15min"));
    ui->comboBox_time->addItem(tr("30min"));

    ui->comboBox_time->setStyleSheet(UIHandler::getStyleSheet("QComboBox"));
    if (UIHandler::get_int_Param("LockScreenOpen") == 1)
    {
      ui->pushButton_switch->setStyleSheet("background-image: url(:/images/lockscreenON.png);background-color:rgba(209,209,209,100);");
      ui->comboBox_time->setEnabled(true);
      ui->label_time->setEnabled(true);
    }
    else
    {
      ui->pushButton_switch->setStyleSheet("background-image: url(:/images/lockcreenOFF.png);background-color:rgba(209,209,209,100);");
      ui->comboBox_time->setEnabled(false);
      ui->label_time->setEnabled(false);
    }
    ui->comboBox_time->setCurrentIndex(UIHandler::get_int_Param("LockScreenTime"));
    ui->comboBox_time->blockSignals(false);
    UIHandler::setBtTextCenter(ui->pushButton_return, 48,"background-image: url(:/images/back.png);text-align:left;");

    UIHandler::NotifyTitle("setup_lockscreen",5);
}

void LockScreenSet::hideEvent(QHideEvent *event){
    Q_UNUSED(event);

}

void LockScreenSet::on_pushButton_switch_clicked()
{
    if (UIHandler::get_int_Param("LockScreenOpen") == 1)
    {
         UIHandler::updata_int_Param("LockScreenOpen", 0);
         ui->comboBox_time->setEnabled(false);         
         ui->label_time->setEnabled(false);
         ui->pushButton_switch->setStyleSheet("background-image: url(:/images/lockcreenOFF.png);background-color:rgba(209,209,209,100);");
    }
    else
    {
        UIHandler::updata_int_Param("LockScreenOpen", 1);
        ui->comboBox_time->setEnabled(true);
        ui->label_time->setEnabled(true);
        ui->pushButton_switch->setStyleSheet("background-image: url(:/images/lockscreenON.png);background-color:rgba(209,209,209,100);");
    }
}

void LockScreenSet::on_comboBox_time_currentIndexChanged(int index)
{
    if (UIHandler::get_int_Param("LockScreenTime") != index)
    {
        UIHandler::updata_int_Param("LockScreenTime", index);

        int lockscreen_time = 0;
        if (UIHandler::get_int_Param("LockScreenOpen") == 0)
            lockscreen_time = 0;
        else if(index == 0)
            lockscreen_time = 60;
        else if(index == 1)
            lockscreen_time = 180;
        else if(index == 2)
            lockscreen_time = 300;
        else if(index == 3)
            lockscreen_time = 600;
        else if(index == 4)
            lockscreen_time = 900;
        else if(index == 5)
            lockscreen_time = 1800;
        else
            lockscreen_time = 0;
        UIHandler::updata_int_Param("lockscreen_time", lockscreen_time);
    }
}

void LockScreenSet::on_pushButton_return_clicked()
{
    //UIHandler::UpdateState(UIHandler::StateId::State_SetupMenu_Update);
    UIHandler::GoPage(UIHandler::PageId::Page_Setup_Menu);
}


void LockScreenSet::initStyleSheet()
{
    setStyleSheet("QWidget{background-color:#f5f5f5;}QPushButton{text-align:center;padding-left: 30px;}");
    ui->label_switch->setStyleSheet("background:transparent");
    ui->label_time->setStyleSheet("QLabel{background:transparent;color:rgb(10,10,10)}QLabel:!enabled{color:rgb(209,209,209)}");

}
