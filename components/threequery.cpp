#include "threequery.h"
#include "ui_threequery.h"
#include <QStyleOption>
#include <QPainter>
#include <QScreen>
#include <QDebug>

ThreeQuery::ThreeQuery(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ThreeQuery)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground,true);
    int screenWidth = QGuiApplication::screens().at(0)->geometry().width();
    int screenHeight = QGuiApplication::screens().at(0)->geometry().height();
    int init_x = (screenWidth-810)/2;
    int init_y = (screenHeight-565)/2 - 60;
    setGeometry(0,0,screenWidth,screenHeight);
    ui->Com_ThreeQuery_wgContainer->setGeometry(init_x,init_y,810,565);
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

    ui->Com_ThreeQuery_lbTitle->setText(tr("样本信息录入"));
    ui->Com_ThreeQuery_lbL1->setText(tr("样本号："));
    ui->Com_ThreeQuery_lbL2->setText(tr("样本信息："));
    ui->Com_ThreeQuery_lbL3->setText(tr("样本备注："));
    ui->Com_ThreeQuery_btCancel->setText(tr("取消"));
    ui->Com_ThreeQuery_btConfirm->setText(tr("确认"));
}

ThreeQuery::~ThreeQuery()
{
    delete ui;
}

void ThreeQuery::setLabel(QString title, QString l1, QString l2, QString l3)
{
    ui->Com_ThreeQuery_lbTitle->setText(title);
    ui->Com_ThreeQuery_lbL1->setText(l1);
    ui->Com_ThreeQuery_lbL2->setText(l2);
    ui->Com_ThreeQuery_lbL3->setText(l3);
}

void ThreeQuery::setValue(QString v1, QString v2, QString v3)
{
    ui->Com_ThreeQuery_leR1->setText(v1);
    ui->Com_ThreeQuery_leR2->setText(v2);
    ui->Com_ThreeQuery_leR3->setText(v3);
}

void ThreeQuery::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    p.fillRect(rect(),QColor(125,125,125,100));
}

void ThreeQuery::on_Com_ThreeQuery_btConfirm_clicked()
{
    value1 = ui->Com_ThreeQuery_leR1->text();
    value2 = ui->Com_ThreeQuery_leR2->text();
    value3 = ui->Com_ThreeQuery_leR3->text();
    accept();
}

void ThreeQuery::on_Com_ThreeQuery_btCancel_clicked()
{
    close();
}
