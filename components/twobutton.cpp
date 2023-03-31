#include "twobutton.h"
#include "ui_twobutton.h"
#include "../uihandler.h"
#include <QStyleOption>
#include <QPainter>
#include "mainwin.h"

static TwoButton *twobutton = nullptr;
static TwoButton *twobutton_no_edit = nullptr;
static TwoButton *onebutton = nullptr;
int TwoButton::init_x;
int TwoButton::init_y;
TwoButton::TwoButton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TwoButton)
{
    ui->setupUi(this);
    init_x = (UIHandler::contentWidth-799)/2;
    init_y = (UIHandler::contentHeight-469)/2+143;
    setGeometry(0,0,UIHandler::contentWidth,UIHandler::screenHeight);
    ui->label->setGeometry(init_x,init_y,799,469);
    ui->label_twobt_title->setGeometry(0+init_x,20+init_y,799,60);
    ui->label_twobt_title->setAlignment(Qt::AlignTop|Qt::AlignHCenter);
    ui->label_twobt_lb1->setGeometry(300+init_x,150+init_y,300,180);
    ui->label_twobt_lb1->setAlignment(Qt::AlignVCenter|Qt::AlignHCenter);
    //ui->label_twobt_lb2->setGeometry(300,150,400,60);
    ui->label_twobt_lb2->setGeometry(50+init_x,240+init_y,200,60);
    ui->label_twobt_lb2->setAlignment(Qt::AlignRight);
    ui->lEdit_twobt_edit1->setGeometry(260+init_x,240+init_y,360,60);
    ui->pButton_twobt_return->setGeometry(489+init_x,355+init_y,280,85);
    ui->pButton_twobt_return->setText(tr("   连接2"));
    ui->pButton_twobt_ok->setGeometry(43+init_x,355+init_y,280,85);
    ui->pButton_twobt_ok->setText(tr("   取消"));
   // ui->pButton_twobt_ok->setStyleSheet("QPushButton{border:3px black;background-color:rgb(200,200,200)}");
   // ui->pButton_twobt_return->setStyleSheet("QPushButton{border:3px black;background-color:rgb(200,200,200)}");
    ui->label->setStyleSheet("border-radius:25px;background-image: url(:/images/wifibg_white.png);");
    ui->label_twobt_title->setStyleSheet("background:transparent;font-size:40px");
    ui->label_twobt_lb2->setStyleSheet("background:transparent;font-size:40px");
    ui->label_twobt_lb1->setStyleSheet("background:transparent;font-size:40px;");
    ui->lEdit_twobt_edit1->setStyleSheet("border: 0px solid gray;font-size:30px;background-color:#E6E6E6;border-radius:5;");
    ui->label_twobt_lb1->setWordWrap(true);

    confirmBtBkImg = ":/images/confirm.png";
    cancelBtBkImg  = ":/images/cancel.png";
}

TwoButton::~TwoButton()
{
    delete ui;
}

void TwoButton::showEvent(QShowEvent *event){
    Q_UNUSED(event);

  //  qDebug()<<"ui->label_twobt_lb1->text().length()==="<<ui->label_twobt_lb1->text().length();
   // if (ui->label_twobt_lb1->text()!="")
  //    ui->label_twobt_lb1->setGeometry(400-(ui->label_twobt_lb1->text().length()*15)/2,150,300,60);
   // this->setWindowModality(Qt::ApplicationModal);

    UIHandler::setBtTextCenter(ui->pButton_twobt_return, 48,QString("background-image: url(%1);text-align:left;").arg(confirmBtBkImg));
    UIHandler::setBtTextCenter(ui->pButton_twobt_ok, 48,QString("background-image: url(%1);text-align:left;").arg(cancelBtBkImg));
}

void TwoButton::hideEvent(QHideEvent *event){
    Q_UNUSED(event);

}



TwoButton *TwoButton::getPtr(){
    if (twobutton == nullptr)
        twobutton = new TwoButton(MainWin::getPtr());
    return twobutton;
}

TwoButton *TwoButton::getPtr_no_edit(){
    if (twobutton_no_edit == nullptr)
        twobutton_no_edit = new TwoButton(MainWin::getPtr());
    return twobutton_no_edit;
}

TwoButton *TwoButton::getPtr_one_bt(){
    if (onebutton == nullptr)
        onebutton = new TwoButton(MainWin::getPtr());
    return onebutton;
}

void TwoButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    p.fillRect(rect(),QColor(125,125,125,100));
//    QStyleOption opt;
//    opt.init(this);
//    QPainter p(this);
//    style()->drawPrimitive(QStyle::PE_Widget,&opt,&p,this);
}


void TwoButton::display_two_bt(QString title, QString l1, QString l2, QString b1, QString b2,QString v1 )
{
    if (twobutton == nullptr)
        twobutton = new TwoButton(MainWin::getPtr());
     qDebug()<<"title:"<<title<<"+l1:"<<l1<<"+l2:"<<l2<<"+b1:"<<b1<<"+b2:"<<b2<<"+v1:"<<v1;
    twobutton->ui->label_twobt_title->setText(title);
    twobutton->ui->pButton_twobt_return->setText(b1);
    twobutton->ui->pButton_twobt_ok->setText(b2);
    //twobutton->ui->pButton_twobt_ok->setStyleSheet("background-image: url(:/images/cancel.png);text-align:left;padding-left: 95px;");    twobutton->ui->label_twobt_lb1->setText(l1);
    twobutton->ui->label_twobt_lb1->setText(l1);
    twobutton->ui->label_twobt_lb2->setText(l2);
    twobutton->ui->lEdit_twobt_edit1->setText("");
    twobutton->ui->lEdit_twobt_edit1->setText(v1);
    twobutton->ui->lEdit_twobt_edit1->setEchoMode(QLineEdit::Password);
    if (l2=="")
    {
      twobutton->ui->lEdit_twobt_edit1->hide();
      twobutton->ui->label_twobt_lb2->hide();
     // twobutton->ui->label_twobt_lb1->setGeometry(270,220,400,60);
      twobutton->ui->label_twobt_lb1->setGeometry(70+init_x,220+init_y,280,85);
      //twobutton->ui->label_twobt_lb1->setAlignment(Qt::AlignVCenter|Qt::AlignCenter);
      twobutton->ui->label_twobt_title->setAlignment(Qt::AlignVCenter|Qt::AlignCenter);
    }
    twobutton->ui->label_twobt_lb1->setAlignment(Qt::AlignVCenter|Qt::AlignCenter);
    if (twobutton->ui->label_twobt_lb1->text()!="")
      twobutton->ui->label_twobt_lb1->setGeometry(init_x,150+init_y,810,60);

    twobutton->show();

}

void TwoButton::display_two_bt_noedit(QString title, QString l1,QString b1, QString b2)
{
    if (twobutton_no_edit == nullptr)
        twobutton_no_edit = new TwoButton(MainWin::getPtr());
     qDebug()<<"title:"<<title<<"+l1:"<<l1<<"+b1:"<<b1<<"+b2:"<<b2;
    twobutton_no_edit->ui->label_twobt_title->setText(title);
    twobutton_no_edit->ui->pButton_twobt_return->setText(b1);
    twobutton_no_edit->ui->pButton_twobt_ok->setText(b2);
    //twobutton_no_edit->ui->pButton_twobt_ok->setStyleSheet("background-image: url(:/images/cancel.png);text-align:left;padding-left: 95px;");
    twobutton_no_edit->ui->label_twobt_lb1->setText(l1);
    twobutton_no_edit->ui->label_twobt_lb2->setText("");
    twobutton_no_edit->ui->lEdit_twobt_edit1->setText("");
    twobutton_no_edit->ui->lEdit_twobt_edit1->hide();
    twobutton_no_edit->ui->label_twobt_lb2->hide();
    twobutton_no_edit->ui->label_twobt_lb1->setGeometry(70+init_x,100+init_y,700,280);
    twobutton_no_edit->ui->label_twobt_lb1->setAlignment(Qt::AlignVCenter|Qt::AlignCenter);
    twobutton_no_edit->ui->label_twobt_title->setAlignment(Qt::AlignVCenter|Qt::AlignCenter);

    twobutton_no_edit->show();

}

  void TwoButton::display_one_bt(QString title, QString l1,QString b1, QString btBkImg)
{
      if (onebutton == nullptr)
          onebutton = new TwoButton(MainWin::getPtr());
       qDebug()<<"display_one_bt title:"<<title<<"+l1:"<<l1<<"+b1:"<<b1;

      // int init_x = (UIHandler::contentWidth-810)/2;
     //  int init_y = (UIHandler::contentHeight-565)/2+150;

     //  onebutton->setGeometry(init_x,init_y,810,465);
      onebutton->cancelBtBkImg = btBkImg;
      onebutton->ui->label_twobt_title->setText(title);
      onebutton->ui->pButton_twobt_return->setText(b1);
      onebutton->ui->label_twobt_lb1->setText(l1);
      onebutton->ui->label_twobt_lb2->setText("");
      onebutton->ui->lEdit_twobt_edit1->setText("");
      onebutton->ui->lEdit_twobt_edit1->hide();
      onebutton->ui->label_twobt_lb2->hide();
      onebutton->ui->pButton_twobt_return->hide();
      onebutton->ui->label_twobt_lb1->setGeometry(20+init_x,100+init_y,780,180);
      onebutton->ui->label_twobt_lb1->setAlignment(Qt::AlignVCenter|Qt::AlignCenter);
      //onebutton->setLabelAlignment(onebutton->ui->label_twobt_lb1, l1);
      onebutton->ui->label_twobt_title->setAlignment(Qt::AlignVCenter|Qt::AlignCenter);

     // onebutton->ui->label_twobt_lb1->setGeometry(220,180,550,60);
      onebutton->ui->pButton_twobt_ok->setGeometry(265+init_x,355+init_y,280,85);
      onebutton->ui->pButton_twobt_ok->setText(b1);

      onebutton->show();

  }

void TwoButton::on_pButton_twobt_ok_clicked()
{
     if (twobutton != nullptr)
       twobutton->close();
     if (twobutton_no_edit != nullptr)
       twobutton_no_edit->close();
     if (onebutton != nullptr)
       onebutton->close();

}

void TwoButton::on_pButton_twobt_return_clicked()
{
    qDebug()<<"lEdit_twobt_edit1:"<<ui->lEdit_twobt_edit1->text();

    if (twobutton != nullptr)
    {
      twobutton->close();
      emit queryAck_twobt(ui->lEdit_twobt_edit1->text());
    }
    if (twobutton_no_edit != nullptr)
    {
      twobutton_no_edit->close();
      emit queryAck_twobt_no_edit();
    }

}
