#include "systemname.h"
#include "ui_systemname.h"
#include "../uihandler.h"
#include <QListView>

static SystemName *winptr = nullptr;

SystemName *SystemName::getPtr()
{
    if (winptr == nullptr)
        winptr = new SystemName;
    return winptr;
}

SystemName::SystemName(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SystemName)
{
    ui->setupUi(this);

    int init_x = (UIHandler::contentWidth-798)/2;
    int init_y = (UIHandler::contentHeight-375)/2;

    ui->label->setGeometry(init_x,init_y,798,375);
    ui->label_hospital->setGeometry(init_x+20,init_y+60,260,64);
    ui->label_hospital->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->lineEdit_hospital->setGeometry(init_x+320,init_y+60,400,64);
    ui->label_device->setGeometry(init_x+20,ui->label_hospital->y()+94,260,64);
    ui->label_device->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->lineEdit_device->setGeometry(init_x+320,ui->label_hospital->y()+94,400,64);
    ui->label_print->setGeometry(init_x+20,ui->label_device->y()+94,260,64);
    ui->label_print->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->comboBox_print->setGeometry(init_x+320,ui->label_device->y()+94,400,64);

    ui->pushButton_2->setGeometry(UIHandler::contentWidth-299-100,UIHandler::contentHeight-106-30,299,106);
    ui->pushButton->setGeometry(UIHandler::contentWidth-299-100,ui->pushButton_2->y()-106-20,299,106);

    ui->comboBox_print->setView(new QListView());
    ui->label_device->setStyleSheet("background-color:#ffffff");
    setStyleSheet("QWidget{background-color:#f5f5f5;}QLabel{background:transparent}\
                  QPushButton{text-align:center;padding-left: 30px;}");
}

SystemName::~SystemName()
{
    delete ui;
}

void SystemName::showEvent(QShowEvent *event){
    Q_UNUSED(event);
    ui->lineEdit_hospital->setText(UIHandler::get_string_Param("HospitalName"));
    ui->lineEdit_device->setText(UIHandler::get_string_Param("SysName"));

    ui->comboBox_print->clear();
    ui->comboBox_print->addItem(tr("便携式打印机"));
    ui->comboBox_print->addItem(tr("台式打印机"));
    ui->comboBox_print->setCurrentIndex(UIHandler::get_int_Param("PrintType"));

    ui->label_hospital->setText(tr("医院名称"));
    ui->label_device->setText(tr("仪器名称"));
    ui->label_print->setText(tr("打印机设置"));
    ui->pushButton_2->setText(tr("取消"));
    ui->pushButton->setText(tr("确认"));

    UIHandler::NotifyTitle("setup_system",5);
}

void SystemName::hideEvent(QHideEvent *event){
    Q_UNUSED(event);

}

void SystemName::on_pushButton_clicked()
{
    qDebug()<<ui->lineEdit_hospital->text()<<ui->lineEdit_device->text()<<ui->comboBox_print->currentIndex();
    UIHandler::updata_string_Param("HospitalName", ui->lineEdit_hospital->text());
    if(ui->lineEdit_device->text() != UIHandler::get_string_Param("SysName"))
    {
        UIHandler::updata_string_Param("SysName", ui->lineEdit_device->text());
        UIHandler::UpdateState(UIHandler::StateId::State_MachineName_Update);
    }
    UIHandler::UpdateState(UIHandler::StateId::State_SetupMenu_Update);
    UIHandler::updata_int_Param("PrintType", ui->comboBox_print->currentIndex());
    UIHandler::GoPage(UIHandler::PageId::Page_Setup_Menu);
}

void SystemName::on_pushButton_2_clicked()
{
    UIHandler::GoPage(UIHandler::PageId::Page_Setup_Menu);
}
