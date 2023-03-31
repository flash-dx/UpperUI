#include "Homeloading.h"
#include "ui_Homeloading.h"
#include "../uihandler.h"
#include "HomeUI/homemain.h"

static HomeLoading *messageBox = nullptr;

HomeLoading::HomeLoading(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeLoading)
{
    ui->setupUi(this);

    int init_x = (HomeMain::getPtr()->getMaskWidget()->width()-675)/2;
    int init_y = (HomeMain::getPtr()->getMaskWidget()->height()-409)/2;
    setGeometry(0,0,UIHandler::contentWidth,UIHandler::screenHeight);
    ui->Com_Loading_lbBack->setGeometry(init_x,init_y,675,409);
    ui->Com_Loading_lbBack->setStyleSheet("background: url(:/images/lockbg.png) transparent");

    movie = new QMovie(":/images/loading.gif");
    ui->Com_Loading_lbAmi->setGeometry((HomeMain::getPtr()->getMaskWidget()->width()-230)/2,(HomeMain::getPtr()->getMaskWidget()->height()-230)/2-30,230,230);
    ui->Com_Loading_lbAmi->setMovie(movie);
    ui->Com_Loading_lbAmi->setVisible(false);

    ui->Com_Loading_lbMessage->setGeometry(init_x,ui->Com_Loading_lbAmi->y()+ui->Com_Loading_lbAmi->height()+30,675,60);
    ui->Com_Loading_lbMessage->setAlignment(Qt::AlignCenter);
    ui->Com_Loading_lbBack->setStyleSheet("transparent");
}

HomeLoading::~HomeLoading()
{
    delete ui;
}

void HomeLoading::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    p.fillRect(rect(),QColor(125,125,125,100));
}

HomeLoading *HomeLoading::getPtr(){
    if (messageBox == nullptr)
    {
        messageBox = new HomeLoading(HomeMain::getPtr()->getMaskWidget());
    }
    return messageBox;
}

void HomeLoading::display(QString message)
{
    getPtr()->ui->Com_Loading_lbMessage->setText(message);
    getPtr()->ui->Com_Loading_lbAmi->setVisible(true);
    getPtr()->movie->start();
    getPtr()->show();
}

void HomeLoading::hide(){
    getPtr()->movie->stop();
    getPtr()->ui->Com_Loading_lbAmi->setVisible(false);
    getPtr()->close();
}
