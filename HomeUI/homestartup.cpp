#include "homestartup.h"
#include "ui_homestartup.h"
#include "uihandler.h"
#include "components/onebtnmessagebox.h"

static int timerid = 0;

HomeStartup::HomeStartup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HomeStartup)
{
    ui->setupUi(this);
    ui->Home_Startup_lbLogo->setGeometry((UIHandler::screenWidth-804)/2,(UIHandler::contentHeight*7/8-190)/2,804,190);
    ui->Home_Startup_btOpenDoor->setGeometry((UIHandler::screenWidth-230)/2,(UIHandler::contentHeight*7/8-230)/2 - 100,230,230);
    ui->Home_Startup_btOpenDoor->setVisible(false);

    movie = new QMovie(":/images/opendoorAmi.gif");
    ui->Home_Startup_lbGif->setGeometry((UIHandler::screenWidth-230)/2,(UIHandler::contentHeight*7/8-230)/2 - 100,230,230);
    ui->Home_Startup_lbGif->setMovie(movie);
    ui->Home_Startup_lbGif->setVisible(false);

    ui->Home_Startup_lbDoorTips->setGeometry((UIHandler::screenWidth-600)/2,ui->Home_Startup_btOpenDoor->y()+250,600,400);
    ui->Home_Startup_lbDoorTips->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
    ui->Home_Startup_lbDoorTips->setVisible(false);
    ui->Home_Startup_lbDoorTips->setWordWrap(true);
}

HomeStartup::~HomeStartup()
{
    delete ui;
}

void HomeStartup::timerEvent(QTimerEvent *e)
{
    static int count;
    if (e->timerId() == timerid){
        QString header = tr("系统启动");
        if (++count > 5)
            count = 0;
        for (int i = 0; i < count; i++)
            header += ".";
    }
}

void HomeStartup::UpdateUI(int machineNo){
    const StartupData *data = UIHandler::getStartupData(machineNo);
    if (data == nullptr) return;
    qDebug()<<"startup UpdateUI,bOpenDoor"<<data->bOpenDoor;
    if (!data->tips.empty()){

        ui->Home_Startup_lbLogo->setVisible(false);
        ui->Home_Startup_btOpenDoor->setVisible(true);
        ui->Home_Startup_lbDoorTips->setVisible(true);
        ui->Home_Startup_lbDoorTips->setText(str2q(data->tips));
    }
    else {
        ui->Home_Startup_lbLogo->setVisible(true);
        ui->Home_Startup_btOpenDoor->setVisible(false);
        ui->Home_Startup_lbDoorTips->setVisible(false);
        timerid = startTimer(500);
    }

    if (data->bOpenDoor){
        ui->Home_Startup_btOpenDoor->setVisible(false);
        ui->Home_Startup_lbGif->setVisible(true);
        ui->Home_Startup_lbDoorTips->setVisible(true);
        movie->start();
    }
    else {
        movie->stop();
        ui->Home_Startup_lbGif->setVisible(false);
    }
}

void HomeStartup::on_Home_Startup_btOpenDoor_clicked()
{
    subDoorInfo info = UIHandler::judgeDoorStatus();
    if(info.status == 1)
    {
        OneBtnMessageBox::display( QString("%1").arg(str2q(info.machineName))+ tr("机器舱门出舱中！"),tr("返回"));
        return;
    }
    bool doorState = UIHandler::getDoorState();

    if(!doorState)
    {
        if(info.status == 2)
        {
            OneBtnMessageBox::display(tr("请先关闭")+QString("%1").arg(str2q(info.machineName))+tr("机器的舱门"),tr("返回"));
            return;
        }
    }

    UIHandler::StartupOpenDoor();
}
