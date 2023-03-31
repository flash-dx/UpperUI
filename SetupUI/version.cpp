#include "version.h"
#include "ui_version.h"

#include "../uihandler.h"
#include <QListView>
#include <QPainter>

#define LINE_HEIGHT 93
#define LINE_WIDTH 780
#define COL1_WIDTH 300
#define LINE_COUNT 5

static version *winptr = nullptr;
static int LINE_X = 584;
static int LINE_Y = 234;

static int count1,count2;
version *version::getPtr()
{
    if (winptr == nullptr)
        winptr = new version;
    return winptr;
}

version::version(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::version)
{
    QPainter painter(this);
    ui->setupUi(this);

    int btnW = 299;
    int btnH = 106;
    int btnRight = 100;
    int btnBottom = 30;
    int btnLeft = UIHandler::contentWidth - btnW - btnRight;
    int btnTop = UIHandler::contentHeight - btnBottom - btnH;
    int btnAdd = 20;

    ui->pushButton->setGeometry(btnLeft, btnTop, btnW,btnH);

    LINE_X = (UIHandler::contentWidth-LINE_WIDTH)/2;
    LINE_Y = (UIHandler::contentHeight-LINE_COUNT*LINE_HEIGHT)/2;

    ui->label_soft_v->setGeometry(LINE_X+2,LINE_Y,COL1_WIDTH,45);
    ui->label_soft_v->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->label_soft_v_2->setGeometry(LINE_X+COL1_WIDTH+10,LINE_Y,LINE_WIDTH-COL1_WIDTH-15,45);
    ui->label_soft_v_2->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->label_soft_v_all->setGeometry(LINE_X+2,ui->label_soft_v->y()+LINE_HEIGHT,COL1_WIDTH,45);
    ui->label_soft_v_all->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->label_soft_v_all_2->setGeometry(LINE_X+COL1_WIDTH+10,ui->label_soft_v->y()+LINE_HEIGHT,LINE_WIDTH-COL1_WIDTH-15,45);
    ui->label_soft_v_all_2->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->label_machine_type->setGeometry(LINE_X+2,ui->label_soft_v_all->y()+LINE_HEIGHT,COL1_WIDTH,45);
    ui->label_machine_type->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->label_machine_type_2->setGeometry(LINE_X+COL1_WIDTH+10,ui->label_soft_v_all->y()+LINE_HEIGHT,LINE_WIDTH-COL1_WIDTH-15,45);
    ui->label_machine_type_2->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->label_mac_address->setGeometry(LINE_X+2,ui->label_machine_type->y()+LINE_HEIGHT,COL1_WIDTH,45);
    ui->label_mac_address->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->label_mac_address_2->setGeometry(LINE_X+COL1_WIDTH+10,ui->label_machine_type->y()+LINE_HEIGHT,LINE_WIDTH-COL1_WIDTH-15,45);
    ui->label_mac_address_2->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->label_serail->setGeometry(LINE_X+2,ui->label_mac_address->y()+LINE_HEIGHT,COL1_WIDTH,45);
    ui->label_serail->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->label_serail_2->setGeometry(LINE_X+COL1_WIDTH+10,ui->label_mac_address->y()+LINE_HEIGHT,LINE_WIDTH-COL1_WIDTH-15,45);
    ui->label_serail_2->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

    setStyleSheet("QWidget{background-color:#f5f5f5;}QPushButton{text-align:center;padding-left: 30px;}");
}

version::~version()
{
    delete ui;
}

void version::load_data(void)
{
    ui->label_soft_v->setText(tr("软件发布版本："));
    ui->label_soft_v_all->setText(tr("软件完整版本："));
    ui->label_machine_type->setText(tr("仪器规格型号："));
    ui->label_serail->setText(tr("序列号："));
    ui->pushButton->setText(tr("返回"));

    ui->label_soft_v_2->setText(UIHandler::Version());//UIHandler::buildversion());
    ui->label_soft_v_all_2->setText(UIHandler::buildVersion());//UIHandler::tempversion());

    if (0==UIHandler::get_int_Param("MachineMode"))
       ui->label_machine_type_2->setText("FDx-500");
    else if (1==UIHandler::get_int_Param("MachineMode"))
        ui->label_machine_type_2->setText(tr("FDx-1000"));
    else
        ui->label_machine_type_2->setText(tr("FDx-1000"));
    ui->label_mac_address_2->setText(UIHandler::getMac());
    ui->label_serail_2->setText(UIHandler::getSerial());
}

void version::showEvent(QShowEvent *event){
    Q_UNUSED(event);
    load_data();
    UIHandler::setBtTextCenter(ui->pushButton, 48,"background-image: url(:/images/back.png);text-align:left;padding-bottom:10px;");

    UIHandler::NotifyTitle("setup_about",5);
}

void version::on_pushButton_clicked()
{
    UIHandler::GoPage(UIHandler::PageId::Page_Setup_Menu);
}

void version::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    for (int i = 0; i < LINE_COUNT; i++)
        painter.drawLine(LINE_X,LINE_Y+65+i*LINE_HEIGHT,LINE_X+LINE_WIDTH,LINE_Y+65+i*LINE_HEIGHT);
}
