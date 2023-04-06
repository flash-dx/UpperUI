#include "setupmenu.h"
#include "ui_setupmenu.h"

#include <QLabel>
#include <QScrollBar>
#include <QScroller>
#include <QListWidgetItem>

/*
struct SetupMenuItem
{
    QString Eid;
    QString icon;
    QString name;
    UIHandler::PageId page;
    bool show;
    bool testHide;
};
*/

SetupMenuItem SetupMenu::item[] = {
    {"SystemName",":/images/setupmenu_system.png", QObject::tr("系统设置"), UIHandler::PageId::Page_Setup_SystemName,true,false},
    {"LockTime",":/images/setupmenu_lock.png", QObject::tr("锁屏时间"), UIHandler::PageId::Page_Setup_LockScreen,true,false},
    //  {"Blacklight",":/images/setupmenu_system.png", QObject::tr("背光设置"), UIHandler::PageId::Page_Setup_Backlight,true,false},
    {"Language",":/images/setupmenu_lauguage.png", QObject::tr("语言"),UIHandler::PageId::Page_Setup_Language,true,false},
    {"AdminPassword",":/images/setupmenu_password.png", QObject::tr("修改密码"), UIHandler::PageId::Page_Setup_Password,true,false},
    {"Wlan",":/images/setupmenu_wifi.png", QObject::tr("无线网络"), UIHandler::PageId::Page_Setup_Wifi,true,false},
    {"Network",":/images/setupmenu_net.png", QObject::tr("有线网络"), UIHandler::PageId::Page_Setup_Network,true,false},
    {"TimeSet",":/images/setupmenu_time.png", QObject::tr("时间设置"), UIHandler::PageId::Page_Setup_Time,true,true},
    {"User",":/images/setupmenu_user.png", QObject::tr("用户帐号"), UIHandler::PageId::Page_Setup_User,true,false},
    {"Cali",":/images/setupmenu_system.png", QObject::tr("机械校准"), UIHandler::PageId::Page_Setup_Machine,true,true},
    {"Camera",":/images/setupmenu_system.png", QObject::tr("摄像头参数设置"), UIHandler::PageId::Page_Setup_Camera,true,true},
    {"TestSetup",":/images/setupmenu_system.png", QObject::tr("测试设置"), UIHandler::PageId::Page_Setup_TestSetup,true,true},
    {"TestLoop",":/images/setupmenu_system.png", QObject::tr("循环测试"), UIHandler::PageId::Page_Setup_TestLoop,true,true},
    {"SystemParam",":/images/setupmenu_system.png", QObject::tr("系统参数"),UIHandler::PageId::Page_Setup_SystemParam,true,true},
    {"ProjectParam",":/images/setupmenu_system.png", QObject::tr("工程参数"), UIHandler::PageId::Page_Setup_ProjectParam,true,true},
    {"Usb",":/images/setupmenu_system.png", QObject::tr("数据维护"), UIHandler::PageId::Page_Setup_UsbFile,true,true},
    {"Light",":/images/setupmenu_system.png", QObject::tr("荧光强度"), UIHandler::PageId::Page_Setup_Light,true,true},
    {"FluidParam",":/images/setupmenu_system.png", QObject::tr("流体参数"), UIHandler::PageId::Page_Setup_PumpParam,true,true},
    {"Log_view",":/images/setupmenu_system.png", QObject::tr("查看Log信息"), UIHandler::PageId::Page_Setup_Log,true,false},
    {"Pid_view",":/images/setupmenu_system.png", QObject::tr("查看PID参数"),UIHandler::PageId::Page_Setup_PID,true,true},
    // {"Lis_inter",":/images/setupmenu_system.png", QObject::tr("Lis系统接口"),UIHandler::PageId::Page_Setup_Lis,true,true},
    {"UpperMachine",":/images/setupmenu_system.png", QObject::tr("中位机管理"),UIHandler::PageId::Page_Setup_UpperMachine,true,true},
    {"UpperMachineSetting",":/images/setupmenu_system.png", QObject::tr("中位机设置"),UIHandler::PageId::Page_Setup_UpperMachineSetting,true,true},
    {"Version",":/images/setupmenu_about.png", QObject::tr("关于"), UIHandler::PageId::Page_Setup_Version,true,false}
};

static SetupMenu *winptr = nullptr;

SetupMenu::SetupMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetupMenu)
{
    ui->setupUi(this);

    int contentWidth = UIHandler::contentWidth;
    int contentHeight = UIHandler::contentHeight;

    connect(ui->listWidget,SIGNAL(clicked(QModelIndex)),this,SLOT(clickItem(QModelIndex)));
    ui->listWidget->setGeometry(0,0,contentWidth,contentHeight);
    ui->listWidget->verticalScrollBar()->setStyleSheet("QScrollBar:vertical {background:rgb(255,255,255);min-width:50px;}"
                                                       "QScrollBar::handle:vertical {background:rgb(193,193,193);border: 3px solid gray;border-radius:25px;min-height: 100px;min-width:20px;}"
                                                       "QScrollBar::handle:vertical:hover {background:rgb(111,111,111);}");
    ui->listWidget->setVerticalScrollMode(QListWidget::ScrollMode::ScrollPerPixel);
    QScroller::grabGesture(ui->listWidget->viewport(),QScroller::LeftMouseButtonGesture);
    this->setStyleSheet("background-color: #f5f5f5;border:none;");

    connect(UIHandler::getPtr(),&UIHandler::State,this,&SetupMenu::slot_StateUpdate);
}

void SetupMenu::slot_StateUpdate(UIHandler::StateId id){
    if (id == UIHandler::StateId::State_SetupMenu_Update){
        InitItem();
        LoadMenu();
    }
}

SetupMenu::~SetupMenu()
{
    delete ui;
}

SetupMenu *SetupMenu::getPtr()
{
    if (winptr == nullptr)
        winptr = new SetupMenu;
    return winptr;
}

void SetupMenu::showEvent(QShowEvent *event){
    Q_UNUSED(event);
    InitItem();
    LoadMenu();
    UIHandler::NotifyTitle("setup",5);
}

void SetupMenu::clickItem(QModelIndex index)
{
    int currIndex = 0;
    for (unsigned int i = 0; i < sizeof(item)/sizeof(item[0]); i++){
        if (item[i].show){
            if (index.row() == currIndex){
//                if (item[i].testHide && UIHandler::isTesting())
//                    break;
                UIHandler::GoPage(item[i].page);
                break;
            }
            if (++currIndex > index.row())
                break;
        }
    }
}

void SetupMenu::InitItem(){
    for (unsigned int i = 0; i < sizeof(item)/sizeof(item[0]); i++)
        item[i].show = true;
    hideItem("Lis_inter");
    if (UIHandler::getUserType(UIHandler::getUser()) == 4)
        hideItem("SystemParam");

    if (UIHandler::getUserType(UIHandler::getUser()) == 5){
        hideItem("SystemName");
        hideItem("Wlan");
        hideItem("Network");
        hideItem("TimeSet");
        hideItem("LockTime");
        hideItem("User");
        hideItem("Usb");
    }

    if (UIHandler::get_int_Param("ProjectMode") != 0){
        hideItem("TestSetup");
        hideItem("Cali");
        hideItem("Camera");
        hideItem("TestSetup");
        hideItem("TestLoop");
        hideItem("ProjectParam");
        hideItem("FluidParam");
        hideItem("Log_view");
        hideItem("Pid_view");
        hideItem("Light");
        hideItem("Blacklight");
        hideItem("UpperMachine");
    }
    else
        hideItem("UpperMachineSetting");

    hideItem("TestSetup");
}

void SetupMenu::hideItem(QString id){
    for (unsigned int i = 0; i < sizeof(item)/sizeof(item[0]); i++){
        if (item[i].Eid == id){
            item[i].show = false;
            break;
        }
    }
}

QString SetupMenu::getItemInfo(QString eid)
{
    QString itemInfo = "";
    if (eid == "SystemName")
        itemInfo = UIHandler::get_string_Param("SysName");
    else if (eid == "Language"){
        itemInfo = tr("中文");
        if(UIHandler::get_int_Param("LanguageCode") == 1)
          itemInfo = "English";
    }
    else if (eid == "Version")
        itemInfo = UIHandler::get_string_Param("Version");
    else if (eid == "Network")
        itemInfo = UIHandler::getIP();
    else if (eid == "Wlan")
        itemInfo = UIHandler::getWIFIIP();
    else if (eid == "LockTime"){
        itemInfo = tr("关闭");
        int lockscreentime = UIHandler::get_int_Param("LockScreenTime");
        if (UIHandler::get_int_Param("LockScreenOpen") == 0)
            itemInfo = tr("关闭");
        else if (lockscreentime == 0)
            itemInfo = "1   min";//+tr("分钟");
        else if (lockscreentime == 1)
            itemInfo = "3   min";//+tr("分钟");
        else if (lockscreentime == 2)
            itemInfo = "5   min";//+tr("分钟");
        else if (lockscreentime == 3)
            itemInfo = "10   min";//+tr("分钟");
        else if (lockscreentime == 4)
            itemInfo = "15   min";//+tr("分钟");
        else
            itemInfo = "30   min";//+tr("分钟");
    }

    return itemInfo;
}

void SetupMenu::LoadMenu()
{
    ui->listWidget->clear();
    for (unsigned int i = 0; i < sizeof(item)/sizeof(item[0]); i++){
        if (!item[i].show)
            continue;
        QListWidgetItem *list = new QListWidgetItem;
        list->setSizeHint(QSize(UIHandler::contentWidth,80));
        ui->listWidget->addItem(list);

        QWidget *w = new QWidget(ui->listWidget);

        QLabel *icon = new QLabel(w);
        icon->setGeometry(106,15,50,50);
        icon->setPixmap(QPixmap(item[i].icon));

        QLabel *a = new QLabel(w);
        a->setText(tr(item[i].name.toStdString().c_str()));
        a->setGeometry(175,0,500,80);
        a->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
        a->setStyleSheet("font-size: 35px");

        QLabel *row = new QLabel(w);
        row->setGeometry(UIHandler::contentWidth-21-120+45-50,38,21,37);
        row->setPixmap(QPixmap(":/images/row1.png"));

        QLabel *info = new QLabel(w);
        info->setGeometry(UIHandler::contentWidth-21-120-350-30-50,15,380,80);
        info->setStyleSheet("font-size: 35px;color: #636363");
        QFont font_info;
        font_info.setPixelSize(35);
        info->setFont(font_info);
        info->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
        QFontMetrics fontWidth(info->font());
        QString elideNote = fontWidth.elidedText(getItemInfo(item[i].Eid), Qt::ElideRight,380);
        info->setText(elideNote);

        ui->listWidget->setItemWidget(list,w);
    }
}
