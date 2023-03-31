#include "version2.h"
#include "ui_version2.h"


#include "../uihandler.h"
#include <QListView>
#include <QPainter>

static Version2 *winptr = nullptr;

Version2 *Version2::getPtr()
{
    if (winptr == nullptr)
        winptr = new Version2;
    return winptr;
}

Version2::Version2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Version2)
{
    ui->setupUi(this);

    int btnW = 299;
    int btnH = 106;
    int btnRight = 100;
    int btnBottom = 30;
    int btnLeft = UIHandler::contentWidth - btnW - btnRight;
    int btnTop = UIHandler::contentHeight - btnBottom - btnH;
    int btnAdd = 20;

    ui->pushButton->setGeometry(btnLeft, btnTop, btnW,btnH);

    ui->label_soft_v->setGeometry(586,234,300,40);
    ui->label_soft_v_2->setGeometry(890,234,480,40);
   // ui->label->setGeometry(584,289,780,20);
    ui->label_soft_v_all->setGeometry(586,327,600,40);
    ui->label_soft_v_all_2->setGeometry(1060,327,300,40);
   // ui->label_2->setGeometry(584,382,780,20);
    ui->label_machine_type->setGeometry(586,420,380,40);
    ui->label_machine_type_2->setGeometry(960,420,400,40);
    //ui->label_3->setGeometry(584,475,780,20);
    ui->label_mac_address->setGeometry(586,513,380,40);
    ui->label_mac_address_2->setGeometry(960,513,400,40);
   // ui->label_4->setGeometry(584,569,780,20);
    ui->label_serail->setGeometry(586,600,380,50);
    ui->label_serail_2->setGeometry(960,606,400,40);
   // ui->label_5->setGeometry(584,662,780,15);
    ui->label->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);

    setStyleSheet("background-color:#f5f5f5;");
}

Version2::~Version2()
{
    delete ui;
}

void Version2::load_data()
{
    //Sequence::getPtr()->setTitle("setup_about");

    ui->label_soft_v->setText(tr("系统版本："));
    ui->label_soft_v_all->setText(tr("温控板版本："));
    ui->label_machine_type->setText(tr("驱动板版本："));
    ui->label_serail->setText(tr("序列号："));
    ui->pushButton->setText(tr("返回"));

    ui->label_soft_v_2->setText(UIHandler::getBuildversion());
    ui->label_soft_v_all_2->setText(UIHandler::getTempversion());
    ui->label_machine_type_2->setText(UIHandler::getCtrlversion());
    ui->label_mac_address_2->setText(UIHandler::getMac());
    ui->label_serail_2->setText(UIHandler::getSerial());
}

void Version2::showEvent(QShowEvent *event){
    Q_UNUSED(event);

    load_data();

    UIHandler::setBtTextCenter(ui->pushButton, 48,"background-image: url(:/images/back.png);text-align:left;padding-bottom:10px;");

    UIHandler::NotifyTitle("setup_about",5);
}

void Version2::hideEvent(QHideEvent *event){
    Q_UNUSED(event);
}

void Version2::on_pushButton_clicked()
{
    UIHandler::GoPage(UIHandler::PageId::Page_Setup_Menu);
}

void Version2::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawLine(584,299,1364,299);
    painter.drawLine(584,392,1364,392);
    painter.drawLine(584,485,1364,485);
    painter.drawLine(584,579,1364,579);
    painter.drawLine(584,672,1364,672);
}
