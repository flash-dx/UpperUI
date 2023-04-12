#include "datainvaildview.h"
#include "ui_datainvaildview.h"

static DataInvaildView *winptr = nullptr;
static DataInvaildView *winptr2 = nullptr;
static int winIndex = 0;

DataInvaildView *DataInvaildView::getPtr(int ptrIndex)
{
    winIndex = ptrIndex;
    if (ptrIndex == 1){
        if (winptr2 == nullptr)
            winptr2 = new DataInvaildView;
        return winptr2;
    }
    if (winptr == nullptr)
        winptr = new DataInvaildView;
    return winptr;
}

DataInvaildView::DataInvaildView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataInvaildView)
{
    ui->setupUi(this);
    setStyleSheet("background-color:#f5f5f5");
    int contentWidth = UIHandler::contentWidth;
    int contentHeight = UIHandler::contentHeight;
    if (winIndex == 1){
        contentWidth = UIHandler::screenWidth;
        contentHeight = UIHandler::contentHeight*7/8;
    }

    ui->Data_InvalidView_lbTestMsg->setGeometry(0,0,contentWidth,114);
    ui->Data_InvalidView_lbTestMsg->setStyleSheet("background: #dddddd");
    ui->Data_InvalidView_lbTestName->setGeometry(0,0,contentWidth*2/3,114);
    ui->Data_InvalidView_lbTestName->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->Data_InvalidView_lbTestName->setStyleSheet("background: #dddddd");
    ui->Data_InvalidView_lbSerial->setGeometry(contentWidth*2/3,0,contentWidth/3,114);
    ui->Data_InvalidView_lbSerial->setAlignment(Qt::AlignVCenter|Qt::AlignHCenter);
    ui->Data_InvalidView_lbSerial->setStyleSheet("background: #dddddd");

    ui->Data_InvalidView_lbIco->setGeometry((contentWidth-61)/2,(contentHeight-250)/2,61,55);
    ui->Data_InvalidView_lbMessage->setGeometry(300,ui->Data_InvalidView_lbIco->y()+55+40,contentWidth-600,200);
    ui->Data_InvalidView_lbMessage->setAlignment(Qt::AlignHCenter|Qt::AlignTop);


    ui->Data_InvalidView_btBack->setGeometry(contentWidth-299-80,contentHeight-106-40,299,106);
    ui->Data_InvalidView_btDelete->setGeometry(contentWidth-299-80,ui->Data_InvalidView_btBack->y()-106-40,299,106);
    ui->Data_InvalidView_btDelete->setVisible(false);

}

DataInvaildView::~DataInvaildView()
{
    delete ui;
}

void DataInvaildView::showEvent(QShowEvent *event){
    Q_UNUSED(event);

    ui->Data_InvalidView_btDelete->setText(tr("删除"));
    ui->Data_InvalidView_btDelete->setVisible(UIHandler::getHiddenFunction());
    UIHandler::setBtTextCenter(ui->Data_InvalidView_btDelete, 48,"background-image: url(:/images/CancelTest.png);text-align:left;");

    UIHandler::setBtTextCenter(ui->Data_InvalidView_btBack, 48,"background-image: url(:/images/back.png);text-align:left;");

    qDebug()<<winIndex<<"winIndex";
    if (winIndex == 1){
        if (UIHandler::dataEntry() == 1)
            UIHandler::NotifyTitle(tr("测试结束"));
        else
            UIHandler::NotifyTitle("dataview",5);
        //connect(HomeMain::getPtr(),SIGNAL(sig_UpdateUI()),this,SLOT(updateUI()));
    }
    else {
        updateUI();
    }
}

void DataInvaildView::hideEvent(QHideEvent *event)
{
    Q_UNUSED(event);
    if(!UIHandler::abNormalInfo.isEmpty())
    {
        UIHandler::abNormalInfo = "";
    }
    //HomeMain::getPtr()->disconnect(this);
}

void DataInvaildView::on_Data_InvalidView_btBack_clicked()
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

void DataInvaildView::on_Data_InvalidView_btDelete_clicked()
{
//    if(GlobalParam::pTestModel->delCurrTest())
//    {
//        UIHandler::GoPage(UIHandler::PageId::Page_Data_Menu);
//    }
}

void DataInvaildView::updateUI()
{
     int testId ;
     if (winIndex == 1)
     {
        //testId = UIHandler::getSubCurTestId();
     }
     else
     {
         testId = TestModel::getCurrTestId();
     }
    qDebug()<<"DataInvaildView showEvent"<<testId;
    ui->Data_InvalidView_lbTestName->setText(TestModel::getTestPanelName(testId)+"   "+TestModel::getTestPanelCode(testId));
    ui->Data_InvalidView_lbSerial->setText(TestModel::getTestBoxSerial(testId));
    //Sequence::getPtr()->changeTitle(GlobalParam::pTestModel->getCurrTestCode()+" | "+GlobalParam::pTestModel->getCurrTestInfo());
    int ErrorCode = TestModel::getTestErrCode(testId);
    QString  strErrInfo;
    if(ErrorCode == 1)
    {
        strErrInfo = tr("吸液异常");
    }
    else if(ErrorCode == 2)
    {
        strErrInfo = tr("点阵异常");
    }

    if (TestModel::getTestResultType(testId) == 1)
        ui->Data_InvalidView_lbMessage->setText(tr("测试无效\n内部参考品结果异常\n")+ strErrInfo);
    else
        ui->Data_InvalidView_lbMessage->setText(tr("测试无效\n测试过程被终止\n") + strErrInfo);
    ui->Data_InvalidView_btBack->setText(tr("返回"));
}
