#include "homeallmachine.h"
#include "ui_homeallmachine.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QMultiMap>
#include "homemain.h"
#include <uihandler.h>

#define WIDTH 480
#define HEIGHT 700
#define SPACING 2
static HomeAllMachine *winptr = nullptr;

HomeAllMachine::HomeAllMachine(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HomeAllMachine)
{
    ui->setupUi(this);

    int ypos = UIHandler::contentHeight - 90 - 30;
    ui->pBtn_PowerOff->setGeometry(UIHandler::screenWidth-279-50,ypos,279,90);
    ui->pBtn_loginOut->setGeometry(ui->pBtn_PowerOff->geometry().x(),ypos-ui->pBtn_PowerOff->geometry().height()-50,279,90);
    UIHandler::setBtTextCenter(ui->pBtn_loginOut, 1,"background-image: url(:/images/btclose_homemain.png);text-align:left;");
    UIHandler::setBtTextCenter(ui->pBtn_PowerOff, 35,"background-image: url(:/images/btexit_homemain.png);text-align:left;");

}

void HomeAllMachine::initUi()
{
    vector<WholeMachine_T *> vecWholeMachine = UIHandler::getWholeMacArr();

    int size = vecWholeMachine.size();

    for (int i = 0; i < size; ++i)
    {
        QRect rect;

        int tempx = i%3;

        if(size == 1)
        {
            rect = QRect((this->width()-WIDTH)/2,(this->height()-HEIGHT)/2,WIDTH,HEIGHT);
        }
        else if(size == 2)
        {
             rect = QRect(213+tempx*(WIDTH+213),(this->height()-HEIGHT)/2,WIDTH,HEIGHT);
        }
        else if(size == 3)
        {
             rect = QRect(20+tempx*(WIDTH+50),(this->height()-HEIGHT)/2,WIDTH,HEIGHT);
        }

         QWidget * tempWidget = new QWidget(this);
         tempWidget->setGeometry(rect);
         tempWidget->show();
         tempWidget->setStyleSheet("border:none;background:rgb(220,220,220,100)");
         vector<SubMachine_T *> vecSubmachine = vecWholeMachine.at(i)->sub;//__map.values(tempList[i]);
         QList<int > list_int;

         for(auto iter:vecSubmachine)
         {
             list_int<<iter->machineNO;
         }

         for (int j = 0; j < 4/*list_int.size()*/; ++j) {

             int x = j%2;
             int y = j/2;


             int tempNumber = -1;
             Q_FOREACH(int no,list_int)
             {
                 if(no != -1 && j == no%5 + no/5 -1)
                     tempNumber = no;
             }

             QWidget * w = new QWidget(tempWidget);

             w->setObjectName(QString::number(tempNumber));
             w->setStyleSheet("border:1px solid black");
             w->setAutoFillBackground(false);

             QWidget *nameWidget = new QWidget(this);
             nameWidget->show();


             QLabel * nameLb = new QLabel(nameWidget);
             QLabel * finishLb = new QLabel(nameWidget);
             QLabel * unfinishLb = new QLabel(nameWidget);

             finishLb->setObjectName(QString::number(tempNumber)+"^~&%finish");
             unfinishLb->setObjectName(QString::number(tempNumber)+"^~&%unfinish");

             QWidget *iconWidget = new QWidget(this);

             iconWidget->show();

             HomeStage stage = Stage_null;
             if(tempNumber != -1)
             {
                stage = UIHandler::getStage(tempNumber);
             }

             int value = 0;

             if(stage == Stage_test )
             {
                 value = UIHandler::getTestProgress(tempNumber);
                 if(value <= 5)
                     value = 5;
             }

             QLabel *lb2 = new QLabel(this);
             QLabel *lb3 = new QLabel(this);

             lb2->setObjectName(QString::number(tempNumber)+"^~&%sampleCode");
             lb3->setObjectName(QString::number(tempNumber)+"^~&%testProject");

             QString strSampleCode = UIHandler::getSampleCode(tempNumber);

             if(strSampleCode.isEmpty())
                 strSampleCode = tr("样本号: ") + tr("未设置");
             lb2->setText(strSampleCode);

             QString strPanelName = UIHandler::PanelName(tempNumber);
             if(strPanelName.isEmpty())
                 strPanelName = tr("测试项目: ") + tr("未设置");
             lb3->setText(strPanelName);

             lb2->setStyleSheet("font:bold 20px;color:black");
             lb3->setStyleSheet("font:bold 20px;color:black");

             lb2->setAlignment(Qt::AlignCenter);
             lb2->setWordWrap(true);
             lb3->setAlignment(Qt::AlignCenter);
             lb3->setWordWrap(true);

             lb2->show();
             lb3->show();

             for (int var = 0; var < 4; ++var) {

                 int tempPosX = var%4;
                 QLabel *label = new QLabel(iconWidget);
                 label->setGeometry(10+tempPosX*55,10,50,60);
                 QString strPath ;


                 QString strObjName;
                 ICONTYPE type;
                 if(var == 0)
                 {
                     strObjName = "^~&%tcpConStatus";
                     type = ICONTYPE::TYPE_TCPICON;
                 }
                 else if(var == 1) {
                     strObjName = "^~&%doorStatus";
                     type = ICONTYPE::TYPE_DOORICON;
                 }
                 else if(var == 2) {
                     strObjName = "^~&%boxStatus";
                     type = ICONTYPE::TYPE_BOXICON;
                 }
                 else if(var == 3) {
                     strObjName = "^~&%messageStatus";
                     type = ICONTYPE::TYPE_MESSAGEICON;
                 }

                 label->setObjectName(QString::number(tempNumber)+strObjName);

                 updateIcon(type,tempNumber);

                 label->setStyleSheet("border:none");
                 label->show();
             }

             nameWidget->setFixedHeight((HEIGHT-5)/2*1/4);

             iconWidget->setFixedHeight((HEIGHT-5)/2*1/4);

             lb2->setFixedHeight((HEIGHT-5)/2*1/4);

             lb3->setFixedHeight((HEIGHT-5)/2-lb2->height() - nameWidget->height() - iconWidget->height());

             unfinishLb->setGeometry(0,0,0,0);

             QString strName = str2q(UIHandler::get_subMac_Name()[tempNumber]);

             if(strName.isEmpty())
             {
                strName = "未添加机器";
             }
             nameLb->setText(strName);
             nameLb->setAlignment(Qt::AlignCenter);
             nameLb->setWordWrap(true);
             nameLb->setGeometry(0,0,(WIDTH-5)/2,(HEIGHT-5)/2*1/4);
             nameLb->setStyleSheet("color:black;border:none;");
             nameLb->raise();

             finishLb->setGeometry(0,0,(WIDTH-5)/2,(HEIGHT-5)/2*1/4);
             finishLb->setStyleSheet("background-color:rgb(89,205,223)");

             getPtr()->updateStatus(finishLb,tempNumber);

             unfinishLb->setStyleSheet("background:rgb(197,229,238)");

             unfinishLb->show();
             finishLb->show();

             nameLb->show();

             QVBoxLayout * lay = new QVBoxLayout();

             lay->addWidget(nameWidget);
             lay->addWidget(iconWidget);
             lay->addWidget(lb2);
             lay->addWidget(lb3);
             lay->setSpacing(0);
             lay->setContentsMargins(0,0,0,0);
             lay->setStretch(0,1);
             lay->setStretch(1,1);
             lay->setStretch(2,1);
             lay->setStretch(3,1);

             w->setLayout(lay);
             w->setGeometry(QRect(x*(WIDTH/2+SPACING),y*(HEIGHT/2+SPACING),WIDTH/2-SPACING,HEIGHT/2-SPACING));
             w->show();
             w->installEventFilter(this);


         }
    }
}

void HomeAllMachine::updateStatus(QLabel *lb1, int machineNo)
{
    if(machineNo == -1)
    {
        lb1->setStyleSheet("background:rgb(250,234,185)");
        return;
    }

    HomeStage stage = UIHandler::getStage(machineNo);

    if(stage == Stage_idle )
    {
        lb1->setStyleSheet("background:rgb(67,142,219);font:bold 25px;color:white");
    }
    else if(stage == Stage_ready)
    {
        if(UIHandler::getBoxState(machineNo))
            lb1->setStyleSheet("background:black");
        else
            lb1->setStyleSheet("background:rgb(67,142,219);color:white;font:bold 28px");
    }
    else if(stage == Stage_test )
    {
        //lb1->setStyleSheet("background:rgb(0,255,0);color:white");
    }
    else if(stage == Stage_error )
    {
        lb1->setStyleSheet("background:rgb(255,165,0);color:white;font:bold 28px");
    }
    else if(stage == Stage_null )
    {
        lb1->setStyleSheet("background:rgb(180,180,180);color:white");
    }
    else if(stage == Stage_selfcheck )
    {
        lb1->setStyleSheet("background:rgb(180,180,180);font:bold 25px;color:white");
    }
}

void HomeAllMachine::updateIcon(ICONTYPE type, int machineNo)
{
    QList<QLabel *> list =  this->findChildren<QLabel *>();
    for (int var = 0; var < list.size(); ++var) {

        QString strObjName;

        if(type == ICONTYPE::TYPE_TCPICON)
            strObjName = "^~&%tcpConStatus";
        else if (type == ICONTYPE::TYPE_DOORICON)
            strObjName = "^~&%doorStatus";
        else if (type == ICONTYPE::TYPE_BOXICON)
            strObjName = "^~&%boxStatus";
        else if (type == ICONTYPE::TYPE_MESSAGEICON)
            strObjName = "^~&%messageStatus";

         if(list[var]->objectName() == (QString::number(machineNo)+strObjName))
         {

             QString strPath;

             if(type == ICONTYPE::TYPE_TCPICON)
             {
                 if(UIHandler::isConnected(machineNo))
                 {
                    strPath = ":/images/tempnetcon.png";
                 }
                 else {
                    strPath = ":/images/tempnetdiscon.png";
                 }
             }
             else if (type == ICONTYPE::TYPE_DOORICON) {
                 if(UIHandler::getDoorState(machineNo))
                 {
                     strPath = ":/images/tempopendoor.png";
                 }
                 else {
                     strPath = ":/images/tempCloseDoor.png";
                 }
             }
             else if (type == ICONTYPE::TYPE_BOXICON) {
                 if(UIHandler::getBoxState(machineNo))
                 {
                     strPath = ":/images/tempHasBox.png";
                 }
                 else {
                     strPath = ":/images/tempnobox.png";
                 }
             }
             else if (type == ICONTYPE::TYPE_MESSAGEICON) {
                 HomeStage stage = UIHandler::getStage(machineNo);
                 strPath = ":/images/tempNoMsg.png";
                 if(stage == Stage_selfcheck && !UIHandler::getStartupData(machineNo)->tips.empty())
                 {
                    strPath = ":/images/tempHaveMsg.png";
                 }
                 else if (stage == Stage_error ) {
                     strPath = ":/images/tempHaveMsg.png";
                 }
             }

             list[var]->setPixmap(QPixmap::fromImage(QImage(strPath)).scaled(list[var]->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
         }
    }
}

HomeAllMachine *HomeAllMachine::getPtr()
{
    if (winptr == nullptr)
        winptr = new HomeAllMachine;
    return winptr;
}

HomeAllMachine::~HomeAllMachine()
{
    delete ui;
}

void HomeAllMachine::showEvent(QShowEvent *event)
{
    UIHandler::NotifyTitle("idle",5);

    ui->pBtn_loginOut->setText(tr("退出登录"));
    ui->pBtn_PowerOff->setText(tr("关机"));

    initUi();

    connect(UIHandler::getPtr(),&UIHandler::UpdateUI,this,[=](int machineNo){

        HomeStage stage = UIHandler::getStage(machineNo);

        if(stage != Stage_test)
        {
            QList<QLabel *> list =  this->findChildren<QLabel *>();

            for (int var = 0; var < list.size(); ++var) {
                if(list[var]->objectName() == QString::number(machineNo) + "^~&%unfinish" )
                {
                    list[var]->setGeometry(0,0,0,0);
                }
            }
        }

        QList<QLabel *> listLabel =  this->findChildren<QLabel *>();
        for (int var = 0; var < listLabel.size(); ++var) {
            if(listLabel[var]->objectName() == QString::number(machineNo) + "^~&%finish" )
            {
                listLabel[var]->setGeometry(0,0,(WIDTH-5)/2,(HEIGHT-5)/2*1/4);
                getPtr()->updateStatus(listLabel[var],machineNo);
            }

        }
    });

    connect(UIHandler::getPtr(),&UIHandler::TestProgress,this,[=](int complete, int total, int machineNo){

         QList<QLabel *> list =  this->findChildren<QLabel *>();

        for (int var = 0; var < list.size(); ++var) {


            int width = (WIDTH-5)/2;
            int height = (HEIGHT-5)/2*1/4;

            int  tempWidth =  width *complete/total;


            if(tempWidth*100/width <= 5)
            {
                tempWidth = width*20/100;
            }


            if(list[var]->objectName() == QString::number(machineNo) + "^~&%finish" )
            {
                list[var]->setGeometry(0,0,tempWidth,height);
            }

            if(list[var]->objectName() == QString::number(machineNo) + "^~&%unfinish" )
            {
                list[var]->setGeometry(tempWidth,0,width-tempWidth,height);
            }
        }

    });

    connect(UIHandler::getPtr(),&UIHandler::sig_senorUpdate,this,[=](int type, int machineNo)
    {
        if(type == 0 || type == 1)
            updateIcon(TYPE_DOORICON,machineNo);
        else if (type == 2)
            updateIcon(TYPE_BOXICON,machineNo);
    });


    connect(UIHandler::getPtr(),&UIHandler::sig_tcpStatus,this,[=](int status, int machineNo){
            updateIcon(TYPE_TCPICON,machineNo);
    });


    connect(UIHandler::getPtr(),&UIHandler::sig_updateMsgIcon,this,[=](int machineNo){

            updateIcon(TYPE_MESSAGEICON,machineNo);
    });

    connect(HomeMain::getPtr(),&HomeMain::sig_DoorKeyDown,this,&HomeAllMachine::slot_DoorKeyDown);
}

void HomeAllMachine::hideEvent(QHideEvent *event)
{
    UIHandler::getPtr()->disconnect(this);
    QList<QBoxLayout *> listLay = this->findChildren<QBoxLayout *>();

    for (int var = 0, count = listLay.size();var < count; ++var) {

        QBoxLayout *layout = listLay[var];
        if( layout ==  nullptr){
               return;
           }
           QLayoutItem *child;
           while(child=layout->takeAt(0)) {
               if(child->widget()){
                   child->widget()->setParent(nullptr);
               }
               layout->removeItem(child);
               delete child;
           }
           layout->update();
           delete layout;
    }

    QList<QObject *> listObj = this->findChildren<QObject *>();

    for(int i = 0;i < listObj.size();i++)
    {
       if(listObj[0] == nullptr)
           continue;
       else
       {
            if(!listObj[0]->objectName().isEmpty())
            {
                continue;
            }
            int count = listObj[0]->children().count();
            if(count > 0)
            {
                QList<QObject *>  list =  listObj[0]->findChildren<QObject *>();
                Q_FOREACH(QObject *tempObj ,list)
                {
                    listObj.removeOne(tempObj);
                    delete  tempObj;
                }
            }
            delete  listObj[0];
            listObj.removeOne(listObj[0]);
       }
   }
}

bool HomeAllMachine::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonRelease && obj->objectName() != "-1"){
        on_machine_Clicked(obj->objectName().toInt());
        return true;
    }
    return false;
}

void HomeAllMachine::on_machine_Clicked(int machineNo)
{
    UIHandler::GoPage(UIHandler::PageId::Page_Home_Main);
    HomeMain::getPtr()->switchDisplay(machineNo);
}

void HomeAllMachine::slot_DoorKeyDown(int machineNo)
{
    HomeMain::getPtr()->switchDisplay(machineNo);
}

void HomeAllMachine::on_pBtn_PowerOff_clicked()
{
    //TwoBtnMessageBox::display(tr("您将关机？"),tr("取消"),tr("确认"));
}

void HomeAllMachine::on_pBtn_loginOut_clicked()
{
     emit UIHandler::getPtr()->EnterLogin(true);
}
