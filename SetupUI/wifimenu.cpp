#include "wifimenu.h"
#include "ui_wifimenu.h"

#include "../uihandler.h"
#include <QLabel>
#include <QListWidgetItem>
#include "components/onebtnmessagebox.h"
#include "components/twobtnmessagebox.h"
#include "components/twobutton.h"
#include "components/loading.h"

static WifiMenu* winptr = nullptr;

WifiMenu *WifiMenu::getPtr()
{
    if (winptr == nullptr)
        winptr = new WifiMenu;
    return winptr;
}

WifiMenu::WifiMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WifiMenu)
{
    ui->setupUi(this);

    int init_x = (UIHandler::contentWidth-810)/2;
    int init_y = (UIHandler::contentHeight-565)/2+150;

    int btnW = 299;
    int btnH = 106;
    int btnRight = 100;
    int btnBottom = 30;
    int btnLeft = UIHandler::contentWidth - btnW - btnRight;
    int btnTop = UIHandler::contentHeight - btnBottom - btnH;
    int btnAdd = 20;

    setGeometry(init_x,init_y,810,565);

    ui->label_background->setGeometry(560,208,799,469);
    ui->label->setGeometry(792,237,315,42);
    ui->tableWidget_wifi->setGeometry(562,304,797,363);

    ui->pButton_brock->setGeometry(btnLeft,   btnTop - 2*(btnH + btnAdd), btnW,btnH);
    ui->pButton_refresh->setGeometry(btnLeft, btnTop - (btnH + btnAdd),   btnW,btnH);
    ui->pButton_return->setGeometry(btnLeft,  btnTop,                     btnW,btnH);

    setStyleSheet("background-color:#f5f5f5;");
    ui->pButton_refresh->setStyleSheet("background-image: url(:/images/confirmbt.png);color: rgb(255, 255, 255)");
    ui->label->setStyleSheet("background:transparent");

    fun = -1;
}

WifiMenu::~WifiMenu()
{
    delete ui;
}

void WifiMenu::listview_refresh()
{

}
void WifiMenu::wifiShow()
{
    list<WifiItem> wifilist = UIHandler::getWifiList();
    QFont font_title=ui->pButton_refresh->font();
    int wifi_count=wifilist.size();//>rowCount();
    QPixmap pixmap_wifi_isconnect(":/images/wifiselect.png");
    QPixmap pixmap_wifi_signal0(":/images/sign0.png");
    QPixmap pixmap_wifi_signal1(":/images/sign1.png");
    QPixmap pixmap_wifi_signal2(":/images/sign2.png");
    QPixmap pixmap_wifi_signal3(":/images/sign3.png");
    QTableWidgetItem *item_SSID[100];
    QStringList str_title={"是否连接","wifi名称","信号强度"};

    ui->tableWidget_wifi->clear();
    ui->tableWidget_wifi->setSelectionBehavior(QAbstractItemView::SelectRows);  //行选择
    ui->tableWidget_wifi->setStyleSheet("background-color:#ffffff;");
    ui->tableWidget_wifi->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_wifi->setEditTriggers(QAbstractItemView::NoEditTriggers);   //不能编辑
    ui->tableWidget_wifi->horizontalHeader()->setStretchLastSection(true);  //表头自适应
    // ui->tableWidget_wifi->setFrameShape(QFrame::NoFrame); //无边框
    // ui->tableWidget_wifi->setFrameShape(QFrame::Box); //无边框
    // ui->tableWidget_wifi->setFrameShape(QFrame::WinPanel);
    ui->tableWidget_wifi->setFrameShape(QFrame::StyledPanel);
    ui->tableWidget_wifi->setShowGrid(false); //不显示网格

    ui->tableWidget_wifi->horizontalHeader()->setFont(font_title);        //QFont("song",40));
    ui->tableWidget_wifi->verticalHeader()->setHidden(true);  //隐藏行标题
    ui->tableWidget_wifi->horizontalHeader()->setHidden(true);
    // ui->tableWidget_wifi->horizontalHeader()->setHighlightSections(false); //表头不高亮

    ui->tableWidget_wifi->setIconSize(QSize(45,45));
    ui->tableWidget_wifi->setRowCount(wifi_count);
    ui->tableWidget_wifi->setColumnCount(3);

    ui->tableWidget_wifi->horizontalHeader()->setDefaultSectionSize(50); //设置缺省列宽度
    ui->tableWidget_wifi->verticalHeader()->setDefaultSectionSize(70); //设置缺省行高度
    // ui->tableWidget_wifi->horizontalHeaderItem(0)->setFont(font_title);
    // ui->tableWidget_wifi->horizontalHeaderItem(1)->setFont(font_title);

    //ui->tableWidget_wifi->setColumnWidth(0,30);
    ui->tableWidget_wifi->setColumnWidth(0,100);
    ui->tableWidget_wifi->setColumnWidth(1,500);
    ui->tableWidget_wifi->setColumnWidth(2,50);


    int ii=0;
    for(auto it:wifilist)
    {
        ui->tableWidget_wifi->setRowHeight(ii,90);
        QLabel *lbConnect = new QLabel;
        QLabel *lbSignal = new QLabel;
        item_SSID[ii]=new QTableWidgetItem();
        if (it.isConnected)
        {
            lbConnect->setPixmap(pixmap_wifi_isconnect);
            lbConnect->setAlignment(Qt::AlignCenter);
        }

        item_SSID[ii]->setText(it.SSID);

        if (it.Signal>80)
            lbSignal->setPixmap(pixmap_wifi_signal3);
        else if (it.Signal>60)
            lbSignal->setPixmap(pixmap_wifi_signal2);
        else if (it.Signal>10)
            lbSignal->setPixmap(pixmap_wifi_signal1);
        else
            lbSignal->setPixmap(pixmap_wifi_signal1);

        ui->tableWidget_wifi->setCellWidget(ii,0,lbConnect);
        ui->tableWidget_wifi->setItem(ii,1,item_SSID[ii]);
        ui->tableWidget_wifi->setCellWidget(ii,2,lbSignal);
        ii++;
    }


    ui->tableWidget_wifi->setWindowTitle(tr("可用WLAN列表"));
    ui->tableWidget_wifi->setHorizontalHeaderLabels(str_title);

    ui->tableWidget_wifi->selectRow(0);
}

void WifiMenu::showEvent(QShowEvent *event){
    Q_UNUSED(event);

    ui->label ->setText(tr("可用WLAN列表"));
    ui->pButton_brock->setText(tr("   断开连接"));
    ui->pButton_refresh->setText(tr("   刷新列表"));
    ui->pButton_return->setText(tr("   返回"));

    UIHandler::setBtTextCenter(ui->pButton_brock, 48,"background-image: url(:/images/CancelTest.png);text-align:left;");
    UIHandler::setBtTextCenter(ui->pButton_refresh, 48,"background-image: url(:/images/confirmbt.png);text-align:left;");
    UIHandler::setBtTextCenter(ui->pButton_return, 48,"background-image: url(:/images/back.png);text-align:left;");

    wifiShow();
    connect(&timer, &QTimer::timeout,this,&WifiMenu::timeout);
    connect(TwoButton::getPtr(),&TwoButton::queryAck_twobt,this,&WifiMenu::Connect_Wifi,Qt::QueuedConnection);
    connect(TwoBtnMessageBox::getPtr(),&TwoBtnMessageBox::MessageAck,this,&WifiMenu::disconnect_wifi,Qt::QueuedConnection);

    UIHandler::NotifyTitle("setup_wifi",5);
}

void WifiMenu::hideEvent(QHideEvent *event){
    Q_UNUSED(event);

    disconnect(TwoButton::getPtr(),&TwoButton::queryAck_twobt,this,&WifiMenu::Connect_Wifi);
    disconnect(TwoBtnMessageBox::getPtr(),&TwoBtnMessageBox::MessageAck,this,&WifiMenu::disconnect_wifi);

    Loading::hide();
    timer.stop();
    disconnect(&timer, &QTimer::timeout,this,&WifiMenu::timeout);
}

void WifiMenu::on_pButton_return_clicked()
{
//    UIHandler::UpdateState(UIHandler::StateId::State_SetupMenu_Update);
    UIHandler::GoPage(UIHandler::PageId::Page_Setup_Menu);
}

void WifiMenu::on_pButton_refresh_clicked()
{
    UIHandler::refreshWifi();
    wifiShow();
}

void WifiMenu::on_pButton_brock_clicked()
{
    fun = 2;
    TwoBtnMessageBox::display(tr("是否断开wifi连接？"),tr("取消"),tr("确认"));
}

void WifiMenu::disconnect_wifi(int ack, QString text)
{
    if(fun == 2 && ack == 2)
    {
        fun = -1;
        Loading::display(tr("正在断开..."));
        UIHandler::disconnectWifi();
        timer.start(2000);
    }

}

void WifiMenu::on_tableWidget_wifi_cellClicked(int row, int column)
{
    QAbstractItemModel *model=ui->tableWidget_wifi->model();
    QModelIndex index=model->index(row,1);
    QVariant data=model->data(index);
    current_SSID=data.toString();
    TwoButton::display_two_bt(tr("输入wifi密码"),current_SSID,tr("密码"),
                              tr("连接"),tr("取消"), UIHandler::getWifiPassword(current_SSID));
    fun = 1;

}

void WifiMenu::Connect_Wifi(QString real)
{
    //qDebug()<<"wifi_connect:"<<current_SSID<<"++++++++++++++++++++++++wifi_password:"<<res1;
    if(fun == 1)
    {
        fun = -1;
        if(real.isEmpty())
        {
            OneBtnMessageBox::display(tr("密码不能为空"),tr("关闭"),":/images/backTestbt3.png");
            return;
        }
        Loading::display(tr("正在连接..."));
        UIHandler::connectWifi(current_SSID,real);
        timer.start(2000);
    }
}


void WifiMenu::Connect_Finish(int val)
{
    Loading::hide();
    qDebug()<<"wifi_connect:finish"<<val;
//    UIHandler::UpdateState(UIHandler::StateId::State_Loading_Close);
    wifiShow();
    if(val == 0)
    {
        OneBtnMessageBox::display(tr("wifi连接失败"),tr("关闭"),":/images/backTestbt3.png");
        return ;
    }
}

void WifiMenu::on_WifiMenu_accepted()
{

}


void WifiMenu::timeout()
{
    Loading::hide();
    timer.stop();
    UIHandler::refreshWifi();
    wifiShow();
}
