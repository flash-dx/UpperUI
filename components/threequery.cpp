#include "threequery.h"
#include "ui_threequery.h"
#include <QStyleOption>
#include <QPainter>
#include "uihandler.h"
#include "mainwin.h"
static ThreeQuery *threeQuery = nullptr;

ThreeQuery::ThreeQuery(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ThreeQuery)
{
    ui->setupUi(this);
    int init_x = (UIHandler::contentWidth-810)/2;
    int init_y = (UIHandler::contentHeight-565)/2+150 - 60;
    setGeometry(0,0,UIHandler::contentWidth,UIHandler::screenHeight);
    ui->Com_ThreeQuery_wgContainer->setGeometry(0+init_x,20+init_y,810,565);
    ui->Com_ThreeQuery_lbTitle->setGeometry(0,20,810,60);
    ui->Com_ThreeQuery_lbTitle->setAlignment(Qt::AlignTop|Qt::AlignHCenter);

    ui->Com_ThreeQuery_leR1->setGeometry(300,150,400,60);
    ui->Com_ThreeQuery_leR2->setGeometry(300,240,400,60);
    ui->Com_ThreeQuery_leR3->setGeometry(300,330,400,60);

    ui->Com_ThreeQuery_lbL1->setGeometry(30,150,250,90);
    ui->Com_ThreeQuery_lbL1->setAlignment(Qt::AlignRight);

    ui->Com_ThreeQuery_lbL2->setGeometry(30,240,250,90);
    ui->Com_ThreeQuery_lbL2->setAlignment(Qt::AlignRight);

    ui->Com_ThreeQuery_lbL3->setGeometry(30,330,250,90);
    ui->Com_ThreeQuery_lbL3->setAlignment(Qt::AlignRight);

    ui->Com_ThreeQuery_btCancel->setGeometry(42,434,250,85);
    ui->Com_ThreeQuery_btConfirm->setGeometry(518,434,250,85);

    ui->Com_ThreeQuery_leR1->setMaxLength(20);

    ui->Com_ThreeQuery_lbTitle->setStyleSheet("background:transparent");
    ui->Com_ThreeQuery_lbL1->setStyleSheet("background:transparent");
    ui->Com_ThreeQuery_lbL2->setStyleSheet("background:transparent");
    ui->Com_ThreeQuery_lbL3->setStyleSheet("background:transparent");
    QString lineStyle = "border: 0px solid gray;font-size:30px;background-color:#E6E6E6;border-radius:5";
    ui->Com_ThreeQuery_leR1->setStyleSheet(lineStyle);
    ui->Com_ThreeQuery_leR2->setStyleSheet(lineStyle);
    ui->Com_ThreeQuery_leR3->setStyleSheet(lineStyle);
    ui->Com_ThreeQuery_btCancel->setStyleSheet("text-align:left;padding-left:90px;padding-bottom:10px;");
}

ThreeQuery::~ThreeQuery()
{
    delete ui;
}

ThreeQuery *ThreeQuery::getPtr(){
    if (threeQuery == nullptr)
    {
        threeQuery = new ThreeQuery(MainWin::getPtr());
    }
    return threeQuery;
}

void ThreeQuery::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    p.fillRect(rect(),QColor(125,125,125,100));
}

void ThreeQuery::display(QString title, QString l1, QString l2, QString l3, QString v1, QString v2, QString v3)
{
    getPtr()->ui->Com_ThreeQuery_lbTitle->setText(title);
    getPtr()->ui->Com_ThreeQuery_lbL1->setText("<em style=\"color:red;font-size:40px;\">* &nbsp;</em>"+l1);
    getPtr()->ui->Com_ThreeQuery_lbL2->setText(l2);
    getPtr()->ui->Com_ThreeQuery_lbL3->setText(l3);
    getPtr()->ui->Com_ThreeQuery_leR1->setText(v1);
    getPtr()->ui->Com_ThreeQuery_leR2->setText(v2);
    getPtr()->ui->Com_ThreeQuery_leR3->setText(v3);
    getPtr()->ui->Com_ThreeQuery_btCancel->setText(tr("取消"));
    getPtr()->ui->Com_ThreeQuery_btConfirm->setText(tr("确认"));
    UIHandler::setBtTextCenter(getPtr()->ui->Com_ThreeQuery_btConfirm, 79,"background-image: url(:/images/confirm.png);text-align:left;");
    UIHandler::setBtTextCenter(getPtr()->ui->Com_ThreeQuery_btCancel, 48,"background-image: url(:/images/cancel.png);text-align:left;");
    getPtr()->show();
}

void ThreeQuery::on_Com_ThreeQuery_btConfirm_clicked()
{    
    emit queryAck(ui->Com_ThreeQuery_leR1->text(),ui->Com_ThreeQuery_leR2->text(),ui->Com_ThreeQuery_leR3->text());
    getPtr()->close();
    emit queryClose();
}

void ThreeQuery::on_Com_ThreeQuery_btCancel_clicked()
{
    getPtr()->close();
    emit queryClose();
}
