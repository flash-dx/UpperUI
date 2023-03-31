#include "homemain.h"
#include "ui_homemain.h"
#include "uihandler.h"
#include "components/twobtnmessagebox.h"
#include "components/progressbutton.h"
#include <QDateTime>
#include "homeidle.h"
#include "homestartup.h"
#include "homeready.h"
#include "hometest.h"
#include "homeallmachine.h"
#include "DataUI/dataview.h"
#include "DataUI/datainvaildview.h"
#include "DataUI/dataline.h"
#include "components/e04.h"
#include "components/cqrcodeinfo.h"
#include "components/onebtnmessagebox.h"
#include <map>
static HomeMain *winptr = nullptr;

HomeMain::HomeMain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HomeMain)
{
    ui->setupUi(this);

    m_btnPre = new QPushButton();
    connect(m_btnPre,&QPushButton::clicked,this,[=](){

       int index = m_StackBtnWidget->currentIndex();
       int count = m_StackBtnWidget->count();
       if(index == 0)
       {
           //m_StackBtnWidget->setCurrentIndex(count - 1);
       }
       else
       {
           m_StackBtnWidget->setCurrentIndex(index-1);
       }
       changePage();

    });
    m_btnNext= new QPushButton();
    connect(m_btnNext,&QPushButton::clicked,this,[=](){

       int index = m_StackBtnWidget->currentIndex();
       int count = m_StackBtnWidget->count();
       if(index+1 == count)
       {
           //m_StackBtnWidget->setCurrentIndex(0);
       }
       else
       {
           m_StackBtnWidget->setCurrentIndex(index+1);
       }
        changePage();
    });

    initStyle();

    addSubMachineBtn();

    changePage();

    this->startTimer(1);
}

HomeMain::~HomeMain()
{
    delete ui;
}

HomeMain *HomeMain::getPtr()
{
    if (winptr == nullptr)
        winptr = new HomeMain;
    return winptr;
}

QWidget *HomeMain::getMaskWidget()
{
    return  maskWidget;
}

int HomeMain::getStackCurIndex()
{
    return getPtr()->ui->stackedWidget->currentIndex();
}

void HomeMain::switchDisplay(int machiNo)
{
    Q_FOREACH(QAbstractButton *btn,m_btnGroup->buttons())
    {
        if(btn->objectName().toInt() == machiNo)
        {
           btn->setFocus();
           ui->stackedWidget->setCurrentWidget(ui->page_main);
           bool flag = focusWidget()->objectName().toInt() == UIHandler::getCurrMachineId() ? true:false;
           slot_btnGrpClicked(btn);
           if(flag)
               UpdateUI(UIHandler::getCurrMachineId());
        }
    }

    for (int i =0 ; i< m_StackWidget->count(); i++) {

         QList<QPushButton *> list =  m_StackBtnWidget->widget(i)->findChildren<QPushButton *>();

         for (int var = 0; var < list.size(); ++var) {

             if(list[var]->objectName().toInt() == machiNo)
             {
                 m_StackBtnWidget->setCurrentIndex(i);
             }
         }
    }
    changePage();


}

void HomeMain::showEvent(QShowEvent *event){
    Q_UNUSED(event);
    UIHandler::NotifyTitle("idle",5);
    ui->HomeMain_lb_user->setText(UIHandler::getDisplayUser());
    qDebug()<<"HomeMain showEvent"<<this->geometry();
    connect(TwoBtnMessageBox::getPtr(),&TwoBtnMessageBox::MessageAck,this,[=](int result, const QString &win){
        if (win != "HomeMain" || result!=2) return;

        qDebug()<<"poweroff"<<win<<result;
        UIHandler::PowerOff();

    },Qt::UniqueConnection);

    connect(UIHandler::getPtr(),&UIHandler::UpdateUI,this,&HomeMain::UpdateUI);
    connect(UIHandler::getPtr(),&UIHandler::TestProgress,this,&HomeMain::TestProgress);
    connect(UIHandler::getPtr(),&UIHandler::sig_clearProcess,this,&HomeMain::slot_clearTestProcess);
    connect(m_btnGroup,SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(slot_btnGrpClicked(QAbstractButton*)));
    connect(UIHandler::getPtr(),&UIHandler::sig_DoorKeyDown,this,&HomeMain::slot_DoorKeyDown);

    int tempId = UIHandler::getCurrMachineId();
    if (tempId != -1){

        Q_FOREACH(QAbstractButton *btn,m_btnGroup->buttons())
        {
            if(btn->objectName().toInt() == tempId)
            {
               btn->setFocus();
               slot_btnGrpClicked(btn);
               UpdateUI(UIHandler::getCurrMachineId());
            }
        }
    }

    UIHandler::setBtTextCenter(ui->HomeMain_pb_allMac, 75,"background-image: url(:/images/btexit_homemain.png);text-align:left;");
    UIHandler::setBtTextCenter(ui->HomeMain_pb_PowerOff, 75,"background-image: url(:/images/btclose_homemain.png);text-align:left;");
    UIHandler::setBtTextCenter(ui->HomeMain_pb_quit, 55,"background-image: url(:/images/btexit_homemain.png);text-align:left;");
}

void HomeMain::hideEvent(QHideEvent *event)
{
   Q_UNUSED(event);
   TwoBtnMessageBox::getPtr()->disconnect(this);
   UIHandler::getPtr()->disconnect(this);
}

void HomeMain::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);
    QDateTime dt = QDateTime::currentDateTime();
    ui->HomeMain_lb_time ->setText(dt.time().toString("hh:mm:ss"));
    ui->HomeMain_lb_data->setText(dt.date().toString(tr("yyyy年MM月dd日")));
}

void HomeMain::addSubMachineBtn()
{
    //size_t count = UIHandler::getSubCount();

    vector<WholeMachine_T *> vec = UIHandler::getWholeMacArr();

    size_t count = vec.size();

    if (count < 1)
        return;

    for (size_t i = 0; i < count; ++i) {
        QWidget * w = new QWidget(m_StackBtnWidget);
        QHBoxLayout * lay = new QHBoxLayout(m_StackBtnWidget);
        lay->setContentsMargins(0,0,0,0);
        w->setLayout(lay);
        m_StackBtnWidget->addWidget(w);
    }

    int index = 0;

    for (auto iter1 : vec) {
        for (auto iter2 : iter1->sub) {
            ProgressButton *btn = new ProgressButton(this);
            btn->setFixedSize(200,60);
            //btn->setMaximumWidth(50);
            btn->setText(str2q(iter2->name));
            btn->setObjectName(QString::number(iter2->machineNO));
            m_btnGroup->addButton(btn);
            m_StackBtnWidget->widget(index%3)->layout()->addWidget(btn);
        }
        ++index;
    }

    if(m_btnGroup->buttons().size()>0)
    {
        QAbstractButton * btn = m_btnGroup->buttons().at(0);
        btn->setFocus();
        slot_btnGrpClicked(btn);
    }
}

void HomeMain::changePage()
{
    int index = m_StackBtnWidget->currentIndex();
    int count = m_StackBtnWidget->count();

    if(count <= 1)
    {
        m_btnPre->setEnabled(false);
        m_btnNext->setEnabled(false);
    }
    else
    {
        if(index == 0)
        {
            m_btnPre->setEnabled(false);
            m_btnNext->setEnabled(true);
        }
        else if(index == count -1)
        {
            m_btnPre->setEnabled(true);
            m_btnNext->setEnabled(false);
        }
        else
        {
            m_btnPre->setEnabled(true);
            m_btnNext->setEnabled(true);
        }
    }
}

void HomeMain::initStyle()
{
    m_btnGroup = new QButtonGroup(this);


    //ui->HomeMain_pb_PowerOff->setFont(QFont("song", 30));

    ui->HomeMain_pb_PowerOff->setText(tr("关机"));
    ui->HomeMain_pb_quit->setText(tr("退出登录"));
    ui->HomeMain_pb_allMac->setText(tr("首页"));


    ui->HomeMain_pb_PowerOff->setFixedSize(279,90);
    ui->HomeMain_pb_quit->setFixedSize(279,90);
    ui->HomeMain_pb_allMac->setFixedSize(279,90);

    ui->HomeMain_lb_time->setAlignment(Qt::AlignCenter);
    ui->HomeMain_lb_data->setAlignment(Qt::AlignCenter);
    ui->HomeMain_lb_user->setAlignment(Qt::AlignCenter);

    ui->HomeMain_lb_data->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
    ui->HomeMain_lb_data->setStyleSheet("font-size: 30px;color: #b5b5b5;background: transparent;");
    ui->HomeMain_lb_time->setAlignment(Qt::AlignCenter);
    ui->HomeMain_lb_time->setStyleSheet("font-size: 60px;color: #b5b5b5;background: transparent;");
    ui->HomeMain_lb_user->setStyleSheet("font-size: 60px;color: #b5b5b5;background: transparent;");

    m_StackWidget = new QStackedWidget(ui->page_main);
    m_layout = new QVBoxLayout(ui->page_main) ;
    m_BtnWidget = new QWidget(ui->page_main);
    m_btnLayout = new QHBoxLayout(m_BtnWidget);

    m_StackBtnWidget = new QStackedWidget(ui->page_main);

    m_btnPre->setFixedSize(200,60);
    m_btnPre->setMaximumWidth(50);
    m_btnPre->setText("<<<<<");

    m_btnNext->setFixedSize(200,60);
    m_btnNext->setMaximumWidth(50);
    m_btnNext->setText(">>>>");

    m_StackBtnWidget->setMaximumHeight(60);
    //m_StackBtnWidget->setStyleSheet("background:red");


    m_btnLayout->addWidget(m_btnPre);
    m_btnLayout->addWidget(m_StackBtnWidget);

    m_btnLayout->addWidget(m_btnNext);


    m_btnLayout->setContentsMargins(0,0,20,0);
    m_BtnWidget->setLayout(m_btnLayout);


    m_StackWidget->addWidget(DataView::getPtr(1));
    m_StackWidget->addWidget(DataInvaildView::getPtr(1));
    m_StackWidget->addWidget(DataLine::getPtr(1));
    m_StackWidget->addWidget(HomeStartup::getPtr());
    m_StackWidget->addWidget(HomeIdle::getPtr());
    m_StackWidget->addWidget(HomeReady::getPtr());
    m_StackWidget->addWidget(HomeTest::getPtr());
    m_StackWidget->addWidget(E04::getPtr());

    qDebug()<<m_StackWidget->currentWidget()->objectName();


    m_layout->addWidget(m_BtnWidget);

    maskWidget = new QWidget;
    maskWidgetLay = new QHBoxLayout;
    maskWidget->setLayout(maskWidgetLay);
    maskWidgetLay->addWidget(m_StackWidget);


    m_layout->addWidget(maskWidget);
    m_layout->setStretch(0,1);
    m_layout->setStretch(1,7);
    m_layout->setContentsMargins(0,0,0,0);

    ui->page_main->setLayout(m_layout);

    ui->vLay_allMachine->addWidget(HomeAllMachine::getPtr());

    ui->stackedWidget->setCurrentWidget(ui->page_allMachine);
}

void HomeMain::on_HomeMain_pb_PowerOff_clicked()
{
#ifdef QT_DEBUG
    UIHandler::DebugMedianMachine(1,489);
    return;
#endif
    if(UIHandler::hasTesting())
    {
        OneBtnMessageBox::display(tr("请等待测试完成或取消测试才可关机"),tr("关闭"),":/images/backTestbt3.png");
        return;
    }

    QList<int> list = UIHandler::getHasBoxNoList();


    int size = list.size();

    if( size > 0)
    {
        QString str;
        for (int var = 0; var < size; ++var)
        {
            str += QString::number(list[var]) ;
            if(var != size -1)
                str += ",";
        }

        OneBtnMessageBox::display(tr("请取出以下机器")+str+tr("里的试剂盒才可关机"),tr("关闭"),":/images/backTestbt3.png");
        return;
    }

    TwoBtnMessageBox::display(tr("您将关机？"),tr("取消"),tr("确认"),"HomeMain");
}

void HomeMain::on_HomeMain_pb_quit_clicked()
{

    if(UIHandler::hasTesting())
    {
        OneBtnMessageBox::display(tr("请等待测试完成或取消测试才可退出登录"),tr("关闭"),":/images/backTestbt3.png");
        return;
    }
    UIHandler::GoPage(UIHandler::PageId::Page_Home_Login);
}

void HomeMain::UpdateUI(int machineNo){
    if (machineNo != UIHandler::getCurrMachineId())
        return;
    HomeStage stage = UIHandler::getStage();
    qDebug()<<"homemain UpdateUI,machineNo="<<machineNo<<"CurrMachineId="<<UIHandler::getCurrMachineId()<<"stage="<<stage;
    if(stage == Stage_selfcheck && m_StackWidget->currentWidget() != HomeStartup::getPtr())
        m_StackWidget->setCurrentWidget(HomeStartup::getPtr());
    else if (stage == Stage_idle && m_StackWidget->currentWidget() != HomeIdle::getPtr())
        m_StackWidget->setCurrentWidget(HomeIdle::getPtr());
    else if (stage == Stage_ready && m_StackWidget->currentWidget() != HomeReady::getPtr())
        m_StackWidget->setCurrentWidget(HomeReady::getPtr());
    else if (stage == Stage_test && m_StackWidget->currentWidget() != HomeTest::getPtr())
        m_StackWidget->setCurrentWidget(HomeTest::getPtr());
    else if (stage == Stage_result && m_StackWidget->currentWidget() != DataView::getPtr(1)){
        m_StackWidget->setCurrentWidget(DataView::getPtr(1));
    }
    else if (stage == Stage_eresult && m_StackWidget->currentWidget() != DataInvaildView::getPtr(1))
        m_StackWidget->setCurrentWidget(DataInvaildView::getPtr(1));
    else if (stage == Stage_line && m_StackWidget->currentWidget() != DataLine::getPtr(1))
        m_StackWidget->setCurrentWidget(DataLine::getPtr(1));
    else if (stage == Stage_error && m_StackWidget->currentWidget() != E04::getPtr())
        m_StackWidget->setCurrentWidget(E04::getPtr());
    else if (stage == Stage_null && m_StackWidget->currentWidget() != E04::getPtr())
        m_StackWidget->setCurrentWidget(E04::getPtr());
    emit sig_UpdateUI();
}

void HomeMain::TestProgress(int complete, int total, int machineNo){
    for (int var = 0; var < m_btnGroup->buttons().size(); ++var) {
       if(QString::compare(m_btnGroup->buttons().at(var)->objectName() ,QString::number(machineNo)) == 0 )
           dynamic_cast<ProgressButton *>(m_btnGroup->buttons().at(var))->changeValue(complete*100/total);
    }
    //qDebug()<<"HomeMain,TestProgress,machineNo="<<machineNo<<"complete="<<complete<<"total="<<total;
}

void HomeMain::slot_btnGrpClicked(QAbstractButton* btn)
{
    int machineNo = focusWidget()->objectName().toInt();
    UIHandler::setCurrMachineId(machineNo);
    for (int var = 0; var < m_btnGroup->buttons().size(); ++var) {
       if(m_btnGroup->buttons().at(var)->objectName() == btn->objectName())
       {
           dynamic_cast<ProgressButton *>(btn)->setBottomColor(true);
           if(UIHandler::getLogin())
              UIHandler::setLedBlink(machineNo);
       }
       else
       {
           dynamic_cast<ProgressButton *>(m_btnGroup->buttons().at(var))->setBottomColor(false);
       }
    }
}

void HomeMain::slot_clearTestProcess(int machineNo)
{
    for (int var = 0; var < m_btnGroup->buttons().size(); ++var) {
       if(QString::compare(m_btnGroup->buttons().at(var)->objectName() ,QString::number(machineNo)) == 0 )
           dynamic_cast<ProgressButton *>(m_btnGroup->buttons().at(var))->changeValue(0);
    }
}


void HomeMain::on_HomeMain_pb_allMac_clicked()
{
   ui->stackedWidget->setCurrentWidget(ui->page_allMachine);
}

void HomeMain::slot_DoorKeyDown(int machineNo)
{
    qDebug()<<"HomeMain::slot_DoorKeyDown"<<machineNo<<UIHandler::getCurrMachineId();

    if(machineNo != UIHandler::getCurrMachineId())
    {
        UIHandler::setCurrMachineId(machineNo);
        switchDisplay(machineNo);
    }
    emit sig_DoorKeyDown(machineNo);
}
