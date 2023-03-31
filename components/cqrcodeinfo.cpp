#include "cqrcodeinfo.h"
#include "ui_cqrcodeinfo.h"
#include "uihandler.h"
#include "mainwin.h"
#include <QPainter>
#include "HomeUI/homeidle.h"
static CQrCodeInfo * _ptr;

CQrCodeInfo::CQrCodeInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CQrCodeInfo)
{
    ui->setupUi(this);
    setGeometry(0,0,UIHandler::contentWidth,UIHandler::screenHeight);
    int init_x = (UIHandler::contentWidth-698)/2;
    int init_y = (UIHandler::screenHeight-610)/2;
    ui->widget->setGeometry(init_x,init_y,698,610);
    ui->lb_title->setGeometry(0,0,698,76);
     ui->lb_title->setAlignment(Qt::AlignCenter);

    ui->lb_project->setGeometry(0,100,198,60);
    ui->lb_project->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    ui->lb_sample->setGeometry(0,180,198,60 );
    ui->lb_sample->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    ui->lb_validTime->setGeometry(0,260,198,60);
    ui->lb_validTime->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    ui->lb_serial->setGeometry(0,340,198,60 );
    ui->lb_serial->setAlignment(Qt::AlignRight | Qt::AlignVCenter);



    ui->lb_project_3->setGeometry(210,100,488,60);
    ui->lb_project_3->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    ui->lb_sample_2->setGeometry(210,180,488,60);
    ui->lb_sample_2->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    ui->lb_validTime_3->setGeometry(210,260,488,60);
    ui->lb_validTime_3->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    ui->lb_serial_3->setGeometry(210,340,488,60);
    ui->lb_serial_3->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);




    ui->lb_ErrMsg->setGeometry(0,420,698,60);
    ui->lb_ErrMsg->setAlignment(Qt::AlignCenter);
    ui->pBtn_Confirm->setGeometry((698-250)/2,500,250,85);
    ui->widget->setStyleSheet("background: url(:/images/datebg.png);");

    QList<QLabel *> list = ui->widget->findChildren<QLabel *>();
    foreach (QLabel * lb, list) {
        lb->setStyleSheet("background:transparent");
    }

//    ui->lb_title->setStyleSheet("background:transparent");
//    ui->lb_project->setStyleSheet("background:transparent");
//    ui->lb_sample->setStyleSheet("background:transparent");
//    ui->lb_serial->setStyleSheet("background:transparent");
//    ui->lb_validTime->setStyleSheet("background:transparent");
    ui->lb_ErrMsg->setStyleSheet("background:transparent;color:red");
    ui->pBtn_Confirm->setStyleSheet(" background-image: url(:/images/confirm.png);color: rgb(238, 238, 236);");
}

CQrCodeInfo *CQrCodeInfo::getPtr()
{
    if(_ptr == nullptr)
    {
        _ptr = new CQrCodeInfo(MainWin::getPtr());
    }
    return _ptr;
}


CQrCodeInfo::~CQrCodeInfo()
{
    delete ui;
}

void CQrCodeInfo::display(int result){
    getPtr()->show();
    ui->lb_title->setText("试剂盒信息");
    m_Type = result;
    connect(HomeIdle::getPtr(),&HomeIdle::sig_QrCodeChange,this,&CQrCodeInfo::slot_flushData);
    slot_flushData(result);
}

void CQrCodeInfo::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    p.fillRect(rect(),QColor(125,125,125,100));
}

void CQrCodeInfo::on_pBtn_Confirm_clicked()
{
    if(m_Type != 0)
    {
        UIHandler::resetQrInfo();
    }
    close();
}

void CQrCodeInfo::slot_flushData(int result)
{
    ui->lb_ErrMsg->setVisible(result != 0);
    ui->lb_project->setText(tr("测试项目:"));
    ui->lb_project_3->setText(UIHandler::PanelName());
    ui->lb_sample->setText(tr("样本号:") );
    ui->lb_sample_2->setText( UIHandler::getSampleCode());
    ui->lb_serial->setText(tr("批号:"));
    ui->lb_serial_3->setText(UIHandler::BoxSerial());
    ui->lb_validTime->setText(tr("有效期:"));
    ui->lb_validTime_3->setText(UIHandler::getValidTime());
    ui->pBtn_Confirm->setText(tr("确认"));
    if(result == 1 )
    {
        ui->lb_ErrMsg->setText(tr("试剂盒已过期"));
    }
    else if(result == 2 ) {
        ui->lb_ErrMsg->setText(tr("二维码错误"));
    }
    else if(result == 3 ) {
        ui->lb_ErrMsg->setText(tr("未找到对应点阵信息"));
    }
    else if(result == 4 ) {
        ui->lb_ErrMsg->setText(tr("未找到对应测试项"));
    }
    else if(result == 5 ) {
        ui->lb_ErrMsg->setText(tr("二维码时间格式错误"));
    }
}
