#include "onebtnmessagebox.h"
#include "ui_onebtnmessagebox.h"
#include "../uihandler.h"

#include <QStyleOption>
#include <QPainter>
#include "mainwin.h"

static OneBtnMessageBox *messageBox = nullptr;
OneBtnMessageBox::OneBtnMessageBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OneBtnMessageBox)
{
    ui->setupUi(this);
    int init_x = (UIHandler::contentWidth-811)/2;
    int init_y = (UIHandler::screenHeight-485)/2;
    setGeometry(0,0,UIHandler::contentWidth,UIHandler::screenHeight);
    ui->Com_OneBtnMessageBox_widget->setGeometry(init_x,init_y,811,485);
    ui->Com_OneBtnMessageBox_bt1->setGeometry((811-280)/2,355,280,85);
    ui->Com_OneBtnMessageBox_bt1->setStyleSheet("text-align:left;padding-left: 95px;");
    ui->Com_OneBtnMessageBox_lbMessage->setGeometry(10,100,791,250);
    ui->Com_OneBtnMessageBox_lbMessage->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->Com_OneBtnMessageBox_lbMessage->setWordWrap(true);
    ui->Com_OneBtnMessageBox_lbMessage->setStyleSheet("background:transparent");
}

OneBtnMessageBox::~OneBtnMessageBox()
{
    delete ui;
}

void OneBtnMessageBox::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    p.fillRect(rect(),QColor(125,125,125,100));
}

OneBtnMessageBox *OneBtnMessageBox::getPtr(){
    if (messageBox == nullptr)
    {
        messageBox = new OneBtnMessageBox(MainWin::getPtr());
    }
    return messageBox;
}

void OneBtnMessageBox::display(QString message, QString btnString, QString btnBkImg, QString name ){
    getPtr()->ui->Com_OneBtnMessageBox_lbMessage->setText(message);
    getPtr()->ui->Com_OneBtnMessageBox_bt1->setText(btnString);
    UIHandler::setBtTextCenter(getPtr()->ui->Com_OneBtnMessageBox_bt1, 48,QString("background-image: url(%1);color:#000000;text-align:left;").arg(btnBkImg));
    getPtr()->winName = name;
    getPtr()->show();
}

void OneBtnMessageBox::on_Com_OneBtnMessageBox_bt1_clicked()
{
    messageBox->close();
    emit MessageAck(1,winName);
}
