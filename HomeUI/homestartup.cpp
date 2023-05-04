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

    ui->Home_Startup_lbDoorTips->setGeometry(UIHandler::screenWidth/2-100,ui->Home_Startup_lbLogo->y()+250,400,400);
    ui->Home_Startup_lbDoorTips->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    ui->Home_Startup_lbDoorTips->setWordWrap(true);
    ui->Home_Startup_lbDoorTips->setText(tr("系统启动中 "));
}

HomeStartup::~HomeStartup()
{
    delete ui;
}

void HomeStartup::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    timerid = startTimer(500);
}

void HomeStartup::hideEvent(QHideEvent *event)
{
    Q_UNUSED(event);
    killTimer(timerid);
}

void HomeStartup::timerEvent(QTimerEvent *e)
{
    static int count;
    if (e->timerId() == timerid){
        QString header = tr("系统启动中 ");
        if (++count > 5)
            count = 0;
        for (int i = 0; i < count; i++)
            header += ".";
        ui->Home_Startup_lbDoorTips->setText(header);
    }
}
