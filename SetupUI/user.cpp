#include "user.h"
#include "ui_user.h"
#include "../uihandler.h"
//#include "updateuser.h"
#include "QMessageBox"
#include <QStandardItemModel>
#include "components/twobtnmessagebox.h"

static User *winptr = nullptr;

User *User::getPtr()
{
    if (winptr == nullptr)
        winptr = new User;
    return winptr;
}

User::User(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::User)
{
    ui->setupUi(this);
    //load_data();

    int btnW = 299;
    int btnH = 106;
    int btnRight = 100;
    int btnBottom = 30;
    int btnLeft = UIHandler::contentWidth - btnW - btnRight;
    int btnTop = UIHandler::contentHeight - btnBottom - btnH;
    int btnAdd = 20;

    ui->label_background->setGeometry(566,157,788,581);
    ui->label_name->setGeometry(579,178,205,60);
    ui->label_dis_name->setGeometry(809,178,286,60);
    ui->label_right->setGeometry(1105,178,250,60);
    ui->listWidget_2->setGeometry(566,253,789,346);

    ui->label_name->setAlignment(Qt::AlignCenter);
    ui->label_dis_name->setAlignment(Qt::AlignCenter);
    ui->label_right->setAlignment(Qt::AlignCenter);

    ui->pButton_user_add->setGeometry(1114,631,220,72);
    ui->pButton_user_edit->setGeometry(859,631,220,72);
    ui->pButton_user_del->setGeometry(607,631,220,72);
    ui->pButton_user_return->setGeometry(1500,740,250,80);
    ui->pButton_user_return->setVisible(false);
    ui->pushButton_back->setGeometry(btnLeft, btnTop, btnW,btnH);

    setStyleSheet("background-color:#f5f5f5;");
    initStyleSheet();
}

void User::load_data()
{
     ui->listWidget_2->setSpacing(5);
     ui->listWidget_2->setFixedSize(789,346);

     ui->listWidget_2->clear();

     ui->listWidget_2->setStyleSheet  ("QWidget{background:white;border:none}QListWidget::item:selected{background:rgb(230, 230, 230); color:rgb(112,194,203); border:1px solid rgb(139, 205, 104);}\
                                        QScrollBar:vertical {background-color:rgb(255,255,255);min-width:50px;}\
                                        QScrollBar::handle:vertical {background-color:rgb(193,193,193);border: 3px solid gray;border-radius:25px;min-height: 100px;min-width:20px;}\
                                        QScrollBar::handle:vertical:hover{background-colo:rgb(111,111,111);border: 3px solid gray;border-radius:25px;min-height: 100px;min-width:20px;");

    QList<USERINFO> userList = UIHandler::getUserList();
    for(int ii=0;ii<userList.count();ii++)
    {
        QString user_name,disp_name;

        user_name=str2q(userList[ii].name);
        disp_name=str2q(userList[ii].displayname);

        QListWidgetItem *plistItem = new QListWidgetItem();
        plistItem->setSizeHint(QSize(80,80));
        ui->listWidget_2->addItem(plistItem);
        QWidget *w = new QWidget(ui->listWidget_2);
        QString labelStyle = "font-size:36px;";
        int listLeft = ui->listWidget_2->geometry().left();
        int nLeft = ui->label_name->geometry().left();
        int nRight = ui->label_dis_name->geometry().left();
        int nMaxlen = nRight - nLeft;
        user_name = getElidedText(user_name, nMaxlen);
        QLabel *pUserItem = new QLabel(w);
        pUserItem->setGeometry(nLeft - listLeft,1,nMaxlen,78);
        pUserItem->setAlignment(Qt::AlignCenter);
        pUserItem->setStyleSheet(labelStyle);
        pUserItem->setText(user_name);

        nLeft = ui->label_dis_name->geometry().left();
        nRight = ui->label_right->geometry().left();
        nMaxlen = nRight - nLeft;
        disp_name = getElidedText(disp_name, nMaxlen);
        QLabel *pDisItem = new QLabel(w);
        pDisItem->setGeometry(nLeft - listLeft,1,nMaxlen,78);
        pDisItem->setAlignment(Qt::AlignCenter);
        pDisItem->setStyleSheet(labelStyle);
        pDisItem->setText(disp_name);

        if (userList[ii].usertype==3)
        {
          nLeft = ui->label_right->geometry().left();
          nRight = ui->listWidget_2->geometry().right();
          nMaxlen = nRight - nLeft;
          QLabel *pAItem = new QLabel(w);
          pAItem->setGeometry(nLeft - listLeft,1,nMaxlen,78);
          pAItem->setAlignment(Qt::AlignCenter);
          pAItem->setStyleSheet(labelStyle);
          pAItem->setText(tr("审核"));
        }
        ui->listWidget_2->setItemWidget(plistItem, w);
    }
    currIndex = -1;
    UIHandler::setCurrUserListIndex(currIndex);
}

User::~User()
{
    delete ui;
}

void User::showEvent(QShowEvent *event){
    Q_UNUSED(event);

    ui->label_name->setText(tr("帐号"));
    ui->label_dis_name->setText(tr("显示名"));
    ui->label_right->setText(tr("权限"));
    ui->pButton_user_del->setText(tr("    删除"));
    ui->pButton_user_edit->setText(tr("    修改"));
    ui->pButton_user_add->setText(tr("    添加"));
    ui->pButton_user_return->setText(tr("   返回"));
    ui->pushButton_back->setText(tr("   返回"));

    ui->pButton_user_del->setStyleSheet("background-image: url(:/images/deletebt.png);background-color:rgba(239,239,239,100);");
    ui->pButton_user_edit->setStyleSheet("background-image: url(:/images/updatebt.png);background-color:rgba(239,239,239,100);");
    ui->pButton_user_add->setStyleSheet("background-image: url(:/images/addbt.png);background-color:rgba(239,239,239,100);color:rgba(255,255,255,255);");

    load_data();

    UIHandler::setBtTextCenter(ui->pushButton_back, 48,"background-image: url(:/images/back.png);text-align:left;");
    connect(TwoBtnMessageBox::getPtr(),&TwoBtnMessageBox::MessageAck,this,&User::deleteUserBack,Qt::UniqueConnection);

    UIHandler::NotifyTitle("setup_user",5);
 }

void User::hideEvent(QHideEvent *event){
    Q_UNUSED(event);

    disconnect(TwoBtnMessageBox::getPtr(),&TwoBtnMessageBox::MessageAck,this,&User::deleteUserBack);
}


void User::on_pButton_user_del_clicked()
{
    currIndex=ui->listWidget_2->currentRow();
     qDebug()<<"del_pre_currIndex==="<<currIndex;
     QList<QListWidgetItem*> selectItem = ui->listWidget_2->selectedItems();
     if (currIndex >= 0 && selectItem.size() > 0)
     {
       TwoBtnMessageBox::display(tr("确定删除帐号")+"?",tr("取消"),tr("确认"));
      }
}

void User::deleteUserBack(int ack, QString text)
{
       if(ack == 2)
       {                                               
           if (currIndex>0)
           {
                qDebug()<<"del_after_currIndex==="<<currIndex;
                UIHandler::deleteUser(currIndex);
            }
           load_data();
       }
}

void User::on_pButton_user_add_clicked()
{
     currIndex=UIHandler::getCurrUserListIndex();
     UIHandler::GoPage(UIHandler::PageId::Page_User_AddUser);
}

void User::on_pButton_user_edit_clicked()
{
   QList<QListWidgetItem*> selectItem = ui->listWidget_2->selectedItems();
   if(selectItem.size() <=0)
      return;
   currIndex = ui->listWidget_2->currentRow();
   UIHandler::setCurrUserListIndex(currIndex);
   QList<USERINFO> userList = UIHandler::getUserList();
   if (userList.count()>0)
    UIHandler::GoPage(UIHandler::PageId::Page_User_UpdateUser);
}

void User::on_pButton_user_return_clicked()
{
    UIHandler::GoPage(UIHandler::PageId::Page_Setup_Menu);
}

void User::on_pushButton_back_clicked()
{
   UIHandler::GoPage(UIHandler::PageId::Page_Setup_Menu);
}



void User::on_listWidget_2_clicked(const QModelIndex &index)
{
   if(index.row() == -1)
       return;

   QModelIndex parent = index.model()->index(0,0);

   if(parent.row() == -1)
       return;

    for (int i = 0; i < ui->listWidget_2->count(); i++)
    {
        ui->listWidget_2->indexWidget(parent.siblingAtRow(i))->setStyleSheet("background:white;");
    }
    ui->listWidget_2->indexWidget(index)->setStyleSheet("QWidget{background:rgb(230, 230, 230); color:rgb(112,194,203); border:1px solid rgb(139, 205, 104);}\
                                                         QLabel{background:rgb(230, 230, 230); color:rgb(112,194,203);border:none;}");
}

void User::initStyleSheet()
{
    ui->label_name->setStyleSheet("background:transparent");
    ui->label_dis_name->setStyleSheet("background:transparent");
    ui->label_right->setStyleSheet("background:transparent");
}

QString User::getElidedText(QString str, int nMaxLen)
{
   QString strTemp;
   QFontMetrics fontMetrics(ui->listWidget_2->font());
   int nspaceWidth = fontMetrics.width(' ');
   int nStrWidth = fontMetrics.width(str);
   if(nStrWidth > (nMaxLen - nspaceWidth*3))
   {
       str = fontMetrics.elidedText(str, Qt::ElideRight, nMaxLen - nspaceWidth*3);
   }
   return str;
}

