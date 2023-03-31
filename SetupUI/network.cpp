#include "network.h"
#include "ui_network.h"
#include "../uihandler.h"
#include <QMessageBox>
#include <QIntValidator>
#include "components/loading.h"
#include "components/onebtnmessagebox.h"
#include "components/twobtnmessagebox.h"

static NetWork *winptr = nullptr;

NetWork *NetWork::getPtr()
{
    if (winptr == nullptr)
        winptr = new NetWork;
    return winptr;
}

NetWork::NetWork(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NetWork)
{
    ui->setupUi(this);

    int btnW = 299;
    int btnH = 106;
    int btnRight = 100;
    int btnBottom = 30;
    int btnLeft = UIHandler::contentWidth - btnW - btnRight;
    int btnTop = UIHandler::contentHeight - btnBottom - btnH;
    int btnAdd = 20;

    ui->label_background->setGeometry(560,255,799,375);

    ui->label_4->setGeometry(585,280,184,54);
    ui->comboBox_macAddr->setGeometry(792,280,512,54);

    ui->label->setGeometry(648,344,121,54);
    ui->label_2->setGeometry(604,418,166,54);
    ui->label_3->setGeometry(585,492,184,54);
    ui->lineEdit_ip1->setGeometry(792,351,122,54);
    ui->lineEdit_ip2->setGeometry(923,351,122,54);
    ui->lineEdit_ip3->setGeometry(1054,351,122,54);
    ui->lineEdit_ip4->setGeometry(1185,351,122,54);
    ui->lineEdit_mask1->setGeometry(792,425,122,54);
    ui->lineEdit_mask2->setGeometry(923,425,122,54);
    ui->lineEdit_mask3->setGeometry(1054,425,122,54);
    ui->lineEdit_mask4->setGeometry(1185,425,122,54);

    ui->lineEdit_gate1->setGeometry(792,499,122,54);
    ui->lineEdit_gate2->setGeometry(923,499,122,54);
    ui->lineEdit_gate3->setGeometry(1054,499,122,54);
    ui->lineEdit_gate4->setGeometry(1185,499,122,54);

    ui->lineEdit_ip4->setFocus();

    ui->pushButton_ok->setGeometry(     btnLeft,  btnTop - (btnH + btnAdd),   btnW,btnH);
    ui->pushButton_cencel->setGeometry( btnLeft,  btnTop,                     btnW,btnH);

    ui->lineEdit_ip1->setValidator(new QIntValidator(0,256,this));
    ui->lineEdit_ip2->setValidator(new QIntValidator(0,256,this));
    ui->lineEdit_ip3->setValidator(new QIntValidator(0,256,this));
    ui->lineEdit_ip4->setValidator(new QIntValidator(0,256,this));
    ui->lineEdit_mask1->setValidator(new QIntValidator(0,256,this));
    ui->lineEdit_mask2->setValidator(new QIntValidator(0,256,this));
    ui->lineEdit_mask3->setValidator(new QIntValidator(0,256,this));
    ui->lineEdit_mask4->setValidator(new QIntValidator(0,256,this));
    ui->lineEdit_gate1->setValidator(new QIntValidator(0,256,this));
    ui->lineEdit_gate2->setValidator(new QIntValidator(0,256,this));
    ui->lineEdit_gate3->setValidator(new QIntValidator(0,256,this));
    ui->lineEdit_gate4->setValidator(new QIntValidator(0,256,this));
    setStyleSheet("QWidget{background-color:#f5f5f5;}QLabel{background:transparent}QLineEdit{background-color:#f5f5f5;}");
    ui->pushButton_cencel->setStyleSheet("background-image: url(:/images/back.png);text-align:left;padding-left:110px;");
}

NetWork::~NetWork()
{
    delete ui;
}

void NetWork::showEvent(QShowEvent *event){
    Q_UNUSED(event);


    ui->label->setText(tr("IP地址"));
    ui->label_2->setText(tr("子网掩码"));
    ui->label_3->setText(tr("网关"));
    ui->pushButton_ok->setText(tr("确定"));
    ui->pushButton_cencel->setText(tr("返回"));

    ui->comboBox_macAddr->blockSignals(true);
    ui->comboBox_macAddr->clear();
    UIHandler::getNetworkMap();
    ui->comboBox_macAddr->addItems(UIHandler::networkMap.keys());
    ui->comboBox_macAddr->setCurrentText(UIHandler::extNetMac);
    ui->comboBox_macAddr->blockSignals(false);

    if (UIHandler::get_int_Param("ProjectMode") != 0)
    {
        ui->label_4->hide();
        ui->comboBox_macAddr->hide();
    }

//    QStringList net = UIHandler::getPtr()->getNetWork();
//    ui->lineEdit_ip1->setText(net[0]);
//    ui->lineEdit_ip2->setText(net[1]);
//    ui->lineEdit_ip3->setText(net[2]);
//    ui->lineEdit_ip4->setText(net[3]);
//    ui->lineEdit_gate1->setText(net[4]);
//    ui->lineEdit_gate2->setText(net[5]);
//    ui->lineEdit_gate3->setText(net[6]);
//    ui->lineEdit_gate4->setText(net[7]);
//    ui->lineEdit_mask1->setText(net[8]);
//    ui->lineEdit_mask2->setText(net[9]);
//    ui->lineEdit_mask3->setText(net[10]);
//    ui->lineEdit_mask4->setText(net[11]);

    if(!UIHandler::isSetNetName())
    {
        if(ui->comboBox_macAddr->count() > 1)
        {
            ui->pushButton_ok->setEnabled(false);
            OneBtnMessageBox::display(tr("未选择外网网卡"),tr("返回"));
        }
        else if(UIHandler::networkMap.count() == 1)
        {
            UIHandler::setextNetMac(UIHandler::networkMap.keys()[0]);
            ui->comboBox_macAddr->setCurrentText(UIHandler::extNetMac);
        }
    }
    qDebug()<<UIHandler::extNetMac<<UIHandler::networkMap;
    updataNet(UIHandler::extNetMac);

    UIHandler::setBtTextCenter(ui->pushButton_ok, 48,"background-image: url(:/images/confirmbt.png);text-align:left;");
    UIHandler::setBtTextCenter(ui->pushButton_cencel, 48,"background-image: url(:/images/back.png);text-align:left;");

//    connect(UIHandler::getPtr(),&UIHandler::netFinish,this,&NetWork::ConnectFinish);
    connect(TwoBtnMessageBox::getPtr(),&TwoBtnMessageBox::MessageAck,this,&NetWork::TwoBtnMessageAck,Qt::QueuedConnection);

    UIHandler::NotifyTitle("setup_network",5);

}
void NetWork::hideEvent(QHideEvent *event){
    Q_UNUSED(event);

}

void NetWork::on_pushButton_ok_clicked()
{
    if ((ui->lineEdit_ip1->text()=="")||(ui->lineEdit_ip2->text()=="")||(ui->lineEdit_ip3->text()=="")||(ui->lineEdit_ip4->text()==""))
        {
           OneBtnMessageBox::display(tr("IP地址不能有空的项！"),tr("返回"));
        }
        else if ((ui->lineEdit_mask1->text()=="")||(ui->lineEdit_mask2->text()=="")||(ui->lineEdit_mask3->text()=="")||(ui->lineEdit_mask4->text()==""))
         {
            OneBtnMessageBox::display(tr("子网掩码不能有空的项！"),tr("返回"));
         }
        else if ((ui->lineEdit_gate1->text()=="")||(ui->lineEdit_gate2->text()=="")||(ui->lineEdit_gate3->text()=="")||(ui->lineEdit_gate4->text()==""))
         {
           OneBtnMessageBox::display(tr("网关不能有空的项！"),tr("返回"));
         }
        else
        {
            TwoBtnMessageBox::display(tr("是否修改IP？"),tr("取消"),tr("确认"));
        }
}

void NetWork::on_pushButton_cencel_clicked()
{
   UIHandler::GoPage(UIHandler::PageId::Page_Setup_Menu);
}

void NetWork::ConnectFinish(int val)
{
    Loading::hide();
    updataNet(UIHandler::extNetMac);
//    UIHandler::UpdateState(UIHandler::StateId::State_SetupMenu_Update);
}

void NetWork::on_comboBox_macAddr_currentIndexChanged(const QString &arg1)
{
    qDebug()<<"on_comboBox_macAddr_currentIndexChanged"<<arg1;
    if(UIHandler::networkMap.contains(arg1))
    {
        updataNet(arg1);
        UIHandler::setextNetMac(arg1);
        if(!UIHandler::isSetNetName())
        {
            ui->pushButton_ok->setEnabled(true);
        }
    }
}

void NetWork::updataNet(QString netName)
{
    qDebug()<<"updataNet"<<UIHandler::networkMap<<netName;
    if(UIHandler::networkMap.contains(netName))
    {
        QStringList list = UIHandler::networkMap[netName].split('^');
        QStringList net = list[1].split('.');
        if(list.count() != 4)
            return;

        qDebug()<<list<<net;

        if(net.count() == 4)
        {
            ui->lineEdit_ip1->setText(net[0]);
            ui->lineEdit_ip2->setText(net[1]);
            ui->lineEdit_ip3->setText(net[2]);
            ui->lineEdit_ip4->setText(net[3]);
        }
        net = list[2].split('.');
        if(net.count() == 4)
        {
            ui->lineEdit_mask1->setText(net[0]);
            ui->lineEdit_mask2->setText(net[1]);
            ui->lineEdit_mask3->setText(net[2]);
            ui->lineEdit_mask4->setText(net[3]);
        }
        net = list[3].split('.');
        if(net.count() == 4)
        {
            ui->lineEdit_gate1->setText(net[0]);
            ui->lineEdit_gate2->setText(net[1]);
            ui->lineEdit_gate3->setText(net[2]);
            ui->lineEdit_gate4->setText(net[3]);
        }
    }
}

void NetWork::TwoBtnMessageAck(int ack, QString text)
{
    if(ack == 2)
    {
        QString  ip = ui->lineEdit_ip1->text()+"."+ui->lineEdit_ip2->text()+"."+ui->lineEdit_ip3->text()+"."+ui->lineEdit_ip4->text();
        QString mask = ui->lineEdit_mask1->text()+"."+ui->lineEdit_mask2->text()+"."+ui->lineEdit_mask3->text()+"."+ui->lineEdit_mask4->text();
        QString gate = ui->lineEdit_gate1->text()+"."+ui->lineEdit_gate2->text()+"."+ui->lineEdit_gate3->text()+"."+ui->lineEdit_gate4->text();
        Loading::display(tr("正在设置") + tr("..."));
        UIHandler::setNetIp(ip,mask,gate);
        Loading::hide();
    }
}
