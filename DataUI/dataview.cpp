#include "dataview.h"
#include "ui_dataview.h"
#include <QPainter>
#include "components/onebtnmessagebox.h"
#include "HomeUI/homemain.h"
#include "uihandler.h"
#include <Module/testmodel.h>
static DataView *winptr = nullptr;
static DataView *winptr2 = nullptr;
static int winIndex = 0;

DataView::DataView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataView)
{
    ui->setupUi(this);
    int contentWidth = UIHandler::contentWidth;
    int contentHeight = UIHandler::contentHeight;
    if (winIndex == 1){
        contentWidth = UIHandler::screenWidth;
        contentHeight = UIHandler::contentHeight*7/8;
    }


    ui->Data_View_lbPanelName->setGeometry(0,0,contentWidth/2,114);
    ui->Data_View_lbPanelName->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->Data_View_lbBoxSerial->setGeometry(contentWidth/2,0,contentWidth/4,114);
    ui->Data_View_lbBoxSerial->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    ui->Data_View_btPrint->setGeometry(contentWidth-200-80,15,90,94);
    ui->Data_View_lbReference->setGeometry(contentWidth-1100,114,300,114);
    ui->Data_View_btRef->setGeometry(contentWidth-700,114,200,114);

    int spacing = 0;
    if(winIndex == 1)
        spacing = 70;
    spacing =0 ;
    ui->Data_View_btBack->setGeometry(contentWidth-299-80+spacing,contentHeight-106-40,299,106);
    ui->Data_View_btCheck->setGeometry(ui->Data_View_btBack->x(),ui->Data_View_btBack->y()-106-30,299,106);

    ui->Data_View_btDelete->setGeometry(ui->Data_View_btBack->x(),ui->Data_View_btCheck->y()-106-30,299,106);
    ui->Data_View_btDelete->setVisible(false);

    this->setStyleSheet("QWidget{background-color:rgb(255,255,255)}");
}

DataView::~DataView()
{
    delete ui;
}

DataView *DataView::getPtr(int ptrIndex)
{
    winIndex = ptrIndex;
    if (ptrIndex == 1){
        if (winptr2 == nullptr)
            winptr2 = new DataView;
        return winptr2;
    }

    if (winptr == nullptr)
        winptr = new DataView;
    return winptr;
}

void DataView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter paint1(this);
    paint1.fillRect(0,0,UIHandler::contentWidth,114,QColor(0xDE,0xDE,0xDE));
    paint1.fillRect(0,114,UIHandler::contentWidth,114,QColor(0xF5,0xF5,0xF5));
}

void DataView::showEvent(QShowEvent *event){
    Q_UNUSED(event);


    ui->Data_View_btBack->setText(tr("返回"));

    ui->Data_View_btDelete->setText(tr("删除"));
    ui->Data_View_btDelete->setVisible(UIHandler::getHiddenFunction());

    UIHandler::setBtTextCenter(ui->Data_View_btDelete, 48,"background-image: url(:/images/CancelTest.png);text-align:left;");

    UIHandler::setBtTextCenter(ui->Data_View_btBack, 48,"background-image: url(:/images/back.png);text-align:left;");

//    connect(GlobalParam::pPrintmgr,&printmgr::finishPrint,this,&DataView::PrintFinish);

//    connect(GlobalParam::pPrintmgr,&printmgr::sig_printResult,this,[=](bool success){

//        if (success)
//        {
//            OneBtnMessageBox::display(tr("打印完成"),tr("关闭"),":/images/backTestbt3.png");
//        }
//        else
//        {
//            OneBtnMessageBox::display(tr("打印错误"),tr("关闭"),":/images/backTestbt3.png");
//        }

//    });

    if (winIndex == 1){
        if (UIHandler::dataEntry() == 1)
            UIHandler::NotifyTitle(tr("测试结束"));
        else
            UIHandler::NotifyTitle("dataview",5);
        connect(HomeMain::getPtr(),SIGNAL(sig_UpdateUI()),this,SLOT(updateUI()));
    }
    else {
        updateUI();
    }
}

void DataView::hideEvent(QHideEvent *event){
    Q_UNUSED(event);
    foreach (QPushButton *btn, list)
        delete btn;
    list.clear();
    HomeMain::getPtr()->disconnect(this);
    disconnect(ui->Data_View_btRef,&QPushButton::clicked,this,&DataView::Item_clicked);
    //disconnect(GlobalParam::pPrintmgr,&printmgr::finishPrint,this,&DataView::PrintFinish);
}

void DataView::on_Data_View_btCheck_clicked()
{
    if (ui->Data_View_btCheck->text() == tr("撤回审核"))
        UIHandler::pTestModel->uncheckTest();
    else
        UIHandler::pTestModel->checkTest();
    UpdataBtCheck();
    if (UIHandler::dataEntry() == 1)
        UIHandler::GoPage(UIHandler::PageId::Page_One_Idle);
//    else
//        UIHandler::GoPage(UIHandler::PageId::Page_Data_View);
}

void DataView::Item_clicked(){
    if (UIHandler::get_int_Param("MachineMode")==1){
        TestModel::setCurrItemName(focusWidget()->objectName());
        if (winIndex == 1)
            UIHandler::TestResultGoWin(2);
        else
            UIHandler::GoPage(UIHandler::PageId::Page_Data_Line);
    }
}

void DataView::on_Data_View_btBack_clicked()
{
    if (winIndex == 1){
        UIHandler::TestResultGoWin();
    }
    else {
        if (UIHandler::dataEntry() == 1)
            UIHandler::GoPage(UIHandler::PageId::Page_One_Idle);
        else
            UIHandler::GoPage(UIHandler::PageId::Page_Data_Menu);
    }
}

void DataView::on_Data_View_btPrint_clicked()
{
//    QPrinter printer;
//    QString printername = printer.printerName();
//    if(!printer.isValid() && printername.isEmpty()){
//        OneBtnMessageBox::display(tr("没有找到打印机"),tr("关闭"),":/images/backTestbt3.png");
//        return;
//    }

//    int testid ;
//    if (winIndex == 1)
//    {
//       testid = UIHandler::getSubCurTestId();
//    }
//    else
//    {
//        testid = TestModel::getCurrTestId();
//    }

//    if (GlobalParam::printTest(testid))
//    {
//        //UIHandler::UpdateState(UIHandler::StateId::State_Loading_Open);
//        qDebug()<<"GlobalParam::pSequence->printTest()";
//    }
}

void DataView::PrintFinish(QByteArray data)
{
    qDebug()<<"PrintFinish"<<data;
    if (data[7] == '\xB1')
    {
        if (data[8] == '\x00')
        {
            OneBtnMessageBox::display(tr("打印完成"),tr("关闭"),":/images/backTestbt3.png");
        }
        else
        {
            OneBtnMessageBox::display(tr("打印错误"),tr("关闭"),":/images/backTestbt3.png");
        }
        //UIHandler::UpdateState(UIHandler::StateId::State_Loading_Close);
    }
}

void DataView::UpdataBtCheck()
{
    if (UIHandler::pTestModel->mayCheck())
    {
        ui->Data_View_btCheck->setVisible(true);
        if (UIHandler::pTestModel->haveCheck())
        {
            ui->Data_View_btCheck->setText(tr("撤回审核"));
            //ui->Data_View_btCheck->setStyleSheet("background-image: url(:/images/CancelTest.png);color: #323232;text-align:left;padding-left:90px;padding-bottom: 10px;");
            UIHandler::setBtTextCenter(ui->Data_View_btCheck, 48,"background-image: url(:/images/CancelTest.png);color: #323232;text-align:left;");
        }
        else
        {
            ui->Data_View_btCheck->setText(tr("通过审核"));
            //ui->Data_View_btCheck->setStyleSheet("background-image: url(:/images/confirmbt.png);color: #ffffff;text-align:left;padding-left:90px;padding-bottom: 10px;");
            UIHandler::setBtTextCenter(ui->Data_View_btCheck, 48,"background-image: url(:/images/confirmbt.png);color: #ffffff;text-align:left;");
        }
    }
}

void DataView::on_Data_View_btDelete_clicked()
{
//    if(GlobalParam::pTestModel->delCurrTest())
//    {
//        UIHandler::GoPage(UIHandler::PageId::Page_Data_Menu);
//    }
}

void DataView::updateUI()
{

    foreach (QPushButton *btn, list)
        delete btn;
    list.clear();

    int testid ;
    if (winIndex == 1)
    {
       testid = UIHandler::getSubCurTestId();
    }
    else
    {
        testid = TestModel::getCurrTestId();
    }
//    ui->Data_View_lbPanelName->setText(TestModel::getTestPanelName(testid)+"   "+TestModel::getTestPanelCode(testid));
//    ui->Data_View_lbBoxSerial->setText(TestModel::getTestBoxSerial(testid));
    ui->Data_View_lbPanelName->setText("呼吸道病原体8联检测");
    ui->Data_View_lbBoxSerial->setText("Lot# 000001"+ QString(" 80021"));
    bool bValidcheck = TestModel::TestValidCheck(testid);
    if(bValidcheck)
    {
         ui->Data_View_lbReference->setText(tr("测试有效"));
         ui->Data_View_lbReference->setStyleSheet("font-size: 40px;color:#898989;background-color:#F5F5F5;");
    }
    else
    {
         ui->Data_View_lbReference->setText(tr("测试无效"));
         ui->Data_View_lbReference->setStyleSheet("font-size: 40px;color:#fc7050;background-color:#F5F5F5;");
    }


    ui->Data_View_btRef->setText(UIHandler::getItemName(2));
    ui->Data_View_btRef->setObjectName(UIHandler::getItemName(2));
    connect(ui->Data_View_btRef,&QPushButton::clicked,this,&DataView::Item_clicked);

    //QStringList itemName = TestModel::getTestName(testid);

    QStringList itemName;
    itemName<<"HRV/HEV"<<"RSV"<<"SARS-CoV-2"<<"PIV"<<"MP"<<"ADV"<<"Flu-B"<<"Flu-A";

    for (int i = 0; i < itemName.size(); i++){
        QPushButton *bt = new QPushButton(this);
        int x = i%4;
        int y = i/4;
        connect(bt,&QPushButton::clicked,this,&DataView::Item_clicked);
         if (winIndex == 1)
             bt->setGeometry(70+x*320,278+y*100,290,80);
         else {
             bt->setGeometry(70+x*370,278+y*100,340,80);
         }
        bt->setStyleSheet("text-align:left");
        bt->setObjectName(itemName[i]);
        bt->setText(itemName[i]);
        bt->setIconSize(QSize(40,40));

        QString strImg = ":/images/ud.png";
        if(bValidcheck)
            strImg = TestModel::getItemImgByName(testid,itemName[i]);

        bt->setIcon(QIcon(strImg));

        if(QString::compare(strImg,":/images/Positive.png") == 0)
        {
             bt->setStyleSheet("text-align:left;color:#40C7DC");
        }
        else
        {
             bt->setStyleSheet("text-align:left");
        }

        bt->show();
        list.append(bt);
    }

    if (UIHandler::pTestModel->mayCheck()){
        ui->Data_View_btCheck->setVisible(true);
        UpdataBtCheck();
    }
    else
        ui->Data_View_btCheck->setVisible(false);

}

