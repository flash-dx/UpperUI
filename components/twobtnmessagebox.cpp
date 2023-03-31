#include "twobtnmessagebox.h"
#include "ui_twobtnmessagebox.h"
#include "../uihandler.h"

#include <QStyleOption>
#include <QPainter>
#include "mainwin.h"

static TwoBtnMessageBox *messageBox = nullptr;
TwoBtnMessageBox::TwoBtnMessageBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TwoBtnMessageBox)
{
    ui->setupUi(this);
    int init_x = (UIHandler::contentWidth-811)/2;
    int init_y = (UIHandler::screenHeight-485)/2;
    setGeometry(0,0,UIHandler::contentWidth,UIHandler::screenHeight);

    ui->Com_TwoBtnMessageBox_widget->setGeometry(init_x,init_y,811,485);
    //ui->Com_TwoBtnMessageBox_bt1->setGeometry(100,355,250,85);
    //ui->Com_TwoBtnMessageBox_bt2->setGeometry(811-350,355,250,85);
    ui->Com_TwoBtnMessageBox_bt1->setGeometry(50,355,280,85);
    ui->Com_TwoBtnMessageBox_bt2->setGeometry(811-330,355,280,85);
    ui->Com_TwoBtnMessageBox_lbMessage->setGeometry(0,62,811,250);
    ui->Com_TwoBtnMessageBox_lbEditname->hide();
    ui->Com_TwoBtnMessageBox_lbEdit->hide();
    ui->Com_TwoBtnMessageBox_lbEditname->setAlignment(Qt::AlignRight);
    ui->Com_TwoBtnMessageBox_lbEdit->setAlignment(Qt::AlignLeft);
    ui->Com_TwoBtnMessageBox_lbMessage->setAlignment(Qt::AlignCenter);
    ui->Com_TwoBtnMessageBox_lbMessage->setWordWrap(true);
    ui->Com_TwoBtnMessageBox_lbMessage->setStyleSheet("background:transparent");
}

TwoBtnMessageBox::~TwoBtnMessageBox()
{
    delete ui;
}

void TwoBtnMessageBox::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    p.fillRect(rect(),QColor(125,125,125,100));
}

TwoBtnMessageBox *TwoBtnMessageBox::getPtr(){
    if (messageBox == nullptr)
    {
        messageBox = new TwoBtnMessageBox(MainWin::getPtr());
    }
    return messageBox;
}

void TwoBtnMessageBox::display(QString message, QString bt1, QString bt2, QString name)
{
    getPtr()->ui->Com_TwoBtnMessageBox_lbEditname->hide();
    getPtr()->ui->Com_TwoBtnMessageBox_lbEdit->hide();
    getPtr()->ui->Com_TwoBtnMessageBox_lbMessage->setGeometry(0,62,811,250);
    getPtr()->ui->Com_TwoBtnMessageBox_lbMessage->setText(message);
    getPtr()->ui->Com_TwoBtnMessageBox_bt1->setText(bt1);
    getPtr()->ui->Com_TwoBtnMessageBox_bt2->setText(bt2);

    getPtr()->winName = name;
    getPtr()->show();
}

void TwoBtnMessageBox::display_edit(QString message, QString lb, QString edit, QString bt1, QString bt2, QString bt1Bkimg, QString bt2Bkimg)
{
    getPtr()->ui->Com_TwoBtnMessageBox_lbMessage->setGeometry(0,150,811,60);
    getPtr()->ui->Com_TwoBtnMessageBox_lbMessage->setText(message);

    getPtr()->ui->Com_TwoBtnMessageBox_lbEditname->setGeometry(60,230,195,60);
    getPtr()->ui->Com_TwoBtnMessageBox_lbEditname->setText(lb);
    getPtr()->ui->Com_TwoBtnMessageBox_lbEditname->show();

    getPtr()->ui->Com_TwoBtnMessageBox_lbEdit->setGeometry(260,230,300,60);
    getPtr()->ui->Com_TwoBtnMessageBox_lbEdit->setText(edit);
    getPtr()->ui->Com_TwoBtnMessageBox_lbEdit->setEchoMode(QLineEdit::Password);
    getPtr()->ui->Com_TwoBtnMessageBox_lbEdit->show();

    getPtr()->ui->Com_TwoBtnMessageBox_bt1->setText(bt1);
    getPtr()->ui->Com_TwoBtnMessageBox_bt2->setText(bt2);

    UIHandler::setBtTextCenter(getPtr()->ui->Com_TwoBtnMessageBox_bt1, 68,QString("color:#000000;background-image: url(%1);text-align:left;").arg(bt1Bkimg));
    UIHandler::setBtTextCenter(getPtr()->ui->Com_TwoBtnMessageBox_bt2, 68,QString("color:#000000;background-image: url(%2);text-align:left;").arg(bt2Bkimg));

    getPtr()->show();
}

void TwoBtnMessageBox::on_Com_TwoBtnMessageBox_bt1_clicked()
{
    messageBox->close();
    emit MessageAck(1,winName);
}

void TwoBtnMessageBox::on_Com_TwoBtnMessageBox_bt2_clicked()
{
    messageBox->close();
    emit MessageAck(2,winName);
}
