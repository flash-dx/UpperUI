#include "loading.h"
#include "ui_loading.h"

#include "../uihandler.h"
#include "mainwin.h"

static Loading *messageBox = nullptr;

Loading::Loading(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Loading)
{
    ui->setupUi(this);
    int init_x = (UIHandler::contentWidth-675)/2;
    int init_y = (UIHandler::screenHeight-409)/2;
    setGeometry(0,0,UIHandler::contentWidth,UIHandler::screenHeight);
    ui->Com_Loading_lbBack->setGeometry(init_x,init_y,675,409);
    ui->Com_Loading_lbBack->setStyleSheet("background: url(:/images/lockbg.png) transparent");

    movie = new QMovie(":/images/loading.gif");
    ui->Com_Loading_lbAmi->setGeometry((UIHandler::contentWidth-230)/2,(UIHandler::screenHeight-230)/2-30,230,230);
    ui->Com_Loading_lbAmi->setMovie(movie);
    ui->Com_Loading_lbAmi->setVisible(false);

    ui->Com_Loading_lbMessage->setGeometry(init_x,ui->Com_Loading_lbAmi->y()+ui->Com_Loading_lbAmi->height()+30,675,60);
    ui->Com_Loading_lbMessage->setAlignment(Qt::AlignCenter);
    ui->Com_Loading_lbBack->setStyleSheet("transparent");
}

Loading::~Loading()
{
    delete ui;
}

void Loading::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    p.fillRect(rect(),QColor(125,125,125,100));
}

Loading *Loading::getPtr(){
    if (messageBox == nullptr)
    {
        messageBox = new Loading(MainWin::getPtr());
    }
    return messageBox;
}

void Loading::display(QString message)
{
    getPtr()->ui->Com_Loading_lbMessage->setText(message);
    getPtr()->ui->Com_Loading_lbAmi->setVisible(true);
    getPtr()->movie->start();
    getPtr()->show();
}

void Loading::hide(){
    getPtr()->movie->stop();
    getPtr()->ui->Com_Loading_lbAmi->setVisible(false);
    getPtr()->close();
}
