#include "usbfile.h"
#include "ui_usbfile.h"
#include "components/twobtnmessagebox.h"
#include "../uihandler.h"

#include <QLabel>
#include <QCheckBox>
#include <QScrollBar>
#include <QScroller>
#include <QListView>
#include <QFileInfo>
#include "components/onebtnmessagebox.h"
#include "components/loading.h"


static UsbFile *winptr = nullptr;
static QList<QString> upFilelist;

UsbFile *UsbFile::getPtr()
{
    if (winptr == nullptr)
        winptr = new UsbFile;
    return winptr;
}

UsbFile::UsbFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UsbFile)
{
    ui->setupUi(this);

    int x = UIHandler::contentWidth/6 ;
    ui->pushButton->setGeometry(1*x + x/2 - 150,690,299,106);
    ui->pushButton_2->setGeometry(2*x + x/2 - 150,690,299,106);
    ui->pushButton_3->setGeometry(3*x + x/2 - 150,690,299,106);
    ui->pushButton_4->setGeometry(4*x + x/2 - 150,690,299,106);
    ui->pushButton_5->setGeometry(5*x + x/2 - 150,690,299,106);
   // ui->tableWidget_usbfile->setVisible(false);

   // ui->tableWidget_usbfile->setGeometry(0,0,1920,710);
    ui->tableWidget_usbfile->setGeometry(0,0,1920,680);
    ui->gridLayoutWidget->setVisible(false);

    ui->comboBox_machine->setView(new QListView());
    ui->comboBox_machine->setGeometry(x/2 - 100,690,200,75);
    ui->comboBox_machine->setStyleSheet(UIHandler::getStyleSheet("QComboBox"));
    caliMachineNo = -1;
    setStyleSheet("QWidget{background-color:#f5f5f5;}QPushButton{text-align:left;padding-left:90px;padding-bottom: 30px;}");
}

UsbFile::~UsbFile()
{
    delete ui;
}

void UsbFile::Checkbox_clicked(int index)
{

  //UIHandler::pUsbModel->switchSelect(index);
  //qDebug()<<"Checkbox_clicked----index=="<<index;

}

void UsbFile::show_file(void)
{
    /*
    int count;
    QPixmap pixmap_dir(":/images/dir.png");
    QPixmap pixmap_file(":/images/file.png");
    QFont font_1=ui->pushButton->font();

    count = UIHandler::pUsbModel->getCount();
    //qDebug()<<"UsbFile::show_file ==count=="<<count;
    if (count==0) return ;
    QCheckBox * CheckboxFile[count];
    QLabel * LabelFile[count];


    boxList.clear();



    ui->tableWidget_usbfile->clear();
    ui->tableWidget_usbfile->setRowCount(0);
    ui->tableWidget_usbfile->clearContents();
    ui->tableWidget_usbfile->setSelectionBehavior(QAbstractItemView::SelectItems);  //行选择
    ui->tableWidget_usbfile->setStyleSheet("QScrollBar:vertical {background-color:rgb(255,255,255);min-width:50px;}\
                                 QScrollBar::handle:vertical {background-color:rgb(193,193,193);border: 3px solid gray;border-radius:25px;min-height: 100px;min-width:20px;}\
                                 QScrollBar::handle:vertical:hover{background-colo:rgb(111,111,111);border: 3px solid gray;border-radius:25px;min-height: 100px;min-width:20px;}\
                                 ");
    ui->tableWidget_usbfile->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_usbfile->setEditTriggers(QAbstractItemView::NoEditTriggers);   //不能编辑
    ui->tableWidget_usbfile->horizontalHeader()->setStretchLastSection(true);  //表头自适应
    ui->tableWidget_usbfile->setFrameShape(QFrame::StyledPanel);
    ui->tableWidget_usbfile->setShowGrid(false); //不显示网格

    ui->tableWidget_usbfile->horizontalHeader()->setFont(font_1);        //QFont("song",40));
    ui->tableWidget_usbfile->verticalHeader()->setHidden(true);  //隐藏行标题
    ui->tableWidget_usbfile->horizontalHeader()->setHidden(true);


    ui->tableWidget_usbfile->setIconSize(QSize(45,45));
    ui->tableWidget_usbfile->setRowCount(count/4+1);
    ui->tableWidget_usbfile->setColumnCount(8);

    ui->tableWidget_usbfile->horizontalHeader()->setDefaultSectionSize(480); //设置缺省列宽度
    ui->tableWidget_usbfile->verticalHeader()->setDefaultSectionSize(80); //设置缺省行高度

    ui->tableWidget_usbfile->setColumnWidth(0,40);
    ui->tableWidget_usbfile->setColumnWidth(1,400);
    ui->tableWidget_usbfile->setColumnWidth(2,40);
    ui->tableWidget_usbfile->setColumnWidth(3,400);
    ui->tableWidget_usbfile->setColumnWidth(4,40);
    ui->tableWidget_usbfile->setColumnWidth(5,400);
    ui->tableWidget_usbfile->setColumnWidth(6,40);
    ui->tableWidget_usbfile->setColumnWidth(7,400);
    ui->tableWidget_usbfile->verticalScrollBar()->setStyleSheet("QScrollBar{width:60px;}");

    for(int ii=0;ii<count;ii++)
      {
        ui->tableWidget_usbfile->setRowHeight(ii/4,120);

        CheckboxFile[ii]=new QCheckBox(this);
        connect(CheckboxFile[ii],&QCheckBox::clicked,[=](int index)
        {
            index = ii;
            Checkbox_clicked(ii);
        });
        LabelFile[ii] = new QLabel(this);

        boxList.append(CheckboxFile[ii]);

        UIHandler::pUsbModel->setCurrIndex(ii);

        boxList[ii]->setFont(font_1);
        boxList[ii]->setText(UIHandler::pUsbModel->getCurName());
        boxList[ii]->setChecked(UIHandler::pUsbModel->getCurSelect());
        boxList[ii]->setIconSize(QSize(40,40));
        boxList[ii]->setStyleSheet("QCheckBox::indicator{width:35px;height:35px;}");


        LabelFile[ii]->setPixmap(UIHandler::pUsbModel->getCurDir()?pixmap_dir:pixmap_file);

        ui->tableWidget_usbfile->setCellWidget(ii/4,(ii%4)*2,LabelFile[ii]);
        ui->tableWidget_usbfile->setCellWidget(ii/4,(ii%4)*2+1,boxList[ii]);
   }
    qDebug()<<"count="<<count;

    */
}

void UsbFile::showEvent(QShowEvent *event){
    Q_UNUSED(event);

    ui->pushButton->setText(tr("删除"));
    ui->pushButton_2->setText(tr("拷出"));
    ui->pushButton_3->setText(tr("升级"));
    ui->pushButton_4->setText(tr("重启"));
    ui->pushButton_5->setText(tr("返回"));


    UIHandler::setBtTextCenter(ui->pushButton,   17,"background-image: url(:/images/cancel.png);text-align:left;");
    UIHandler::setBtTextCenter(ui->pushButton_2, 17,"background-image: url(:/images/confirm.png);color:#ffffff;text-align:left;");
    UIHandler::setBtTextCenter(ui->pushButton_3, 17,"background-image: url(:/images/confirm.png);color:#ffffff;text-align:left;");
    UIHandler::setBtTextCenter(ui->pushButton_4, 17,"background-image: url(:/images/confirm.png);color:#ffffff;text-align:left;");
    UIHandler::setBtTextCenter(ui->pushButton_5, 48,"background-image: url(:/images/backTestbt2.png);text-align:left;");

    QMap<int, QString> list;
    for(auto it : UIHandler::getPtr()->get_subMac_Name()) {
       list[it.first] = str2q(it.second);
    }
    ui->comboBox_machine->blockSignals(true);
    ui->comboBox_machine->clear();
    if( list.count() > 0){
        ui->comboBox_machine->addItems(list.values());
        //        if(caliMachineNo == -1)
        //            caliMachineNo = list.firstKey();
        caliMachineNo = UIHandler::getCurrMachineId();
        ui->comboBox_machine->setCurrentText(list.value(caliMachineNo));
    }
    ui->comboBox_machine->blockSignals(false);

   fun=0;
   //UIHandler::pUsbModel->refresh();
   show_file();
   //connect(UIHandler::pUsbModel,&UsbModel::copyFinish,this,&UsbFile::copyFinish);
   connect(TwoBtnMessageBox::getPtr(),&TwoBtnMessageBox::MessageAck,this,&UsbFile::deleteFile);
   connect(TwoBtnMessageBox::getPtr(),&TwoBtnMessageBox::MessageAck,this,&UsbFile::rebootSystem);
   connect(UIHandler::getPtr(),&UIHandler::sig_sendFileResult,this,&UsbFile::slot_sendFileResult);

   UIHandler::NotifyTitle("setup_usbfile",5);
}

void UsbFile::hideEvent(QHideEvent *event){
    Q_UNUSED(event);
    //disconnect(UIHandler::pUsbModel,&UsbModel::copyFinish,this,&UsbFile::copyFinish);
    TwoBtnMessageBox::getPtr()->disconnect(this);
}

void UsbFile::deleteGridItem(QLayout * layout)
{
    QLayoutItem *item;//*child,*item;

    while((item=ui->gridLayout->takeAt(0))!=0)
    {
        if(item->widget())
        {
            ui->gridLayout->removeWidget(item->widget());
            item->widget()->setParent(0);
            delete item->widget();
         }
    delete item;
    }
}

void UsbFile::deleteFile(int ack, QString text)
{
    // qDebug()<<"deleteFile fun =============="<<fun;
    if (fun==1 && ack ==2)
    {
        //int count ;
        //count=UIHandler::pUsbModel->getCount();

        fun = 0;

//        if(!UIHandler::pUsbModel->deleteDir())
//        {
//            OneBtnMessageBox::display(tr("删除失败"),tr("返回"));
//            return;
//        }
        show_file();
   }
}

void UsbFile::rebootSystem(int ack, QString text)
{
    // qDebug()<<"rebootSystem fun =============="<<fun;
    if (fun==2 && ack == 2)
    {
      fun=0;

      system("shutdown -r now");
      //UIHandler::pUsbModel->restart(); //重启
    }
}


void UsbFile::on_pushButton_clicked()
{
    bool flag = false;
    Q_FOREACH(QCheckBox *checkbox,boxList)
    {
        if(checkbox->isChecked())
        {
            flag = true;
            break;
        }
    }

    if(!flag)
    {
        OneBtnMessageBox::display(tr("未选中文件!"),tr("返回"));
        return ;
    }

    fun=1;

    TwoBtnMessageBox::display(tr("是否删除选中的文件？"),tr("取消"),tr("确认"));
}

void UsbFile::on_pushButton_2_clicked()
{
    bool flag = false;
    Q_FOREACH(QCheckBox *checkbox,boxList)
    {
        if(checkbox->isChecked())
        {
            flag = true;
            break;
        }
    }

    if(!flag)
    {
        OneBtnMessageBox::display(tr("未选中文件!"),tr("返回"));
        return ;
    }

    //int count ;
    //count=UIHandler::pUsbModel->getCount();

  //  TwoButton::display_one_bt(tr("提示"),tr("文件拷贝中"),tr("返回"));
    //Sequence::getPtr()->updateFooter(false,false,false);
    //UIHandler::UpdateState(UIHandler::StateId::State_Loading_Open);
    //UIHandler::pUsbModel->copyDir();
}

void UsbFile::on_pushButton_3_clicked()
{
    upFilelist.clear();
    upFilelist =  UIHandler::updateSoft();

    if(upFilelist.count() == 1)
    {
        OneBtnMessageBox::display(upFilelist[0], tr("返回"));
        upFilelist.clear();
    }
    else if(upFilelist.count() > 1)
    {
        upFilelist.removeFirst();
        Loading::display(tr("正在升级:")+upFilelist[0]);

        QFileInfo info(upFilelist[0]);
        QString strSend = QString("%1^%2").arg(info.size()).arg(info.fileName());
        UIHandler::sendFile(info.filePath(), strSend, sendFileFinish, caliMachineNo);
    }
}

void UsbFile::on_pushButton_4_clicked()
{
    fun=2;
   // UIHandler::pUsbModel->restart(); //重启

   TwoBtnMessageBox::display(tr("是否重启系统？"),tr("取消"),tr("确认"));


   // QString key="bbb7ad3f4d19c6a7ba9a08f156c40dd8";
   // QString filename="/en_US.qm";
   // UIHandler::pUsbModel->unMdz5Sum(filename,key);
   //int key=345895;
   // UIHandler::pUsbModel->EncryptFile("/time.txt","/time1.txt",key);

}

void UsbFile::on_pushButton_5_clicked()
{
//    int count = UIHandler::pUsbModel->getCount();
//    for(int ii=0;ii<count;ii++)
//    {
//       if (boxList[ii]->isChecked())
//       {
//           UIHandler::pUsbModel->setCurrIndex(ii);
//           UIHandler::pUsbModel->switchSelect(ii);
//       }
//    }
    UIHandler::GoPage(UIHandler::PageId::Page_Setup_Menu);
}

void UsbFile::copyFinish(int val)
{
//X    UIHandler::UpdateState(UIHandler::StateId::State_Loading_Close);
    if (val==0){
     OneBtnMessageBox::display(tr("拷贝完成！"),tr("返回"));
    }
    else if (val==1){
      OneBtnMessageBox::display(tr("未检测到U盘！"),tr("返回"));
    }
    else if (val==2){
      OneBtnMessageBox::display(tr("U盘格式不对！应该要FAT32类型"),tr("返回"));
    }

    //Sequence::getPtr()->updateFooter(true,true,true);
}

void UsbFile::sendFileFinish(int res, int MachineNo)
{
    qDebug()<<"UsbFile::sendFileFinish"<<res<<MachineNo<<UsbFile::getPtr()->caliMachineNo;

    QString filename;

    if(res == 1)
    {
        if(upFilelist.count() > 0)
        {
            filename = upFilelist[0];
            upFilelist.removeFirst();
        }

        if(upFilelist.count() > 0)
        {
            Loading::display(tr("正在升级:")+upFilelist[0]);

            QFileInfo info(upFilelist[0]);
            QString strSend = QString("%1^%2").arg(info.size()).arg(info.fileName());
            UIHandler::sendFile(info.filePath(), strSend, sendFileFinish, UsbFile::getPtr()->caliMachineNo);
        }
        else
        {
            Loading::hide();
            OneBtnMessageBox::display(tr("升级完成！"),tr("返回"));
        }
    }
    else if(res == 2)
    {
        OneBtnMessageBox::display(filename + tr("文件升级失败"),tr("返回"));
    }

    qDebug()<<"sendFileFinish"<<filename<<upFilelist.count();
}

void UsbFile::on_comboBox_machine_currentIndexChanged(int index)
{
    if(index >= 0)
    {
        map<int, string> mac = UIHandler::get_subMac_Name();
        for(auto it:mac) {
           if(str2q(it.second) == ui->comboBox_machine->currentText())
           {
               caliMachineNo = it.first;
           }
        }
        qDebug()<<"caliMachineNo"<<caliMachineNo;
    }
}

void UsbFile::slot_sendFileResult(int param, int machineNo)
{
    qDebug()<<"UsbFile::slot_sendFileResult"<<param<<machineNo<<UsbFile::getPtr()->caliMachineNo;

    QString filename;

    if(param == 1)
    {
        if(upFilelist.count() > 0)
        {
            filename = upFilelist[0];
            upFilelist.removeFirst();
        }

        if(upFilelist.count() > 0)
        {
            Loading::display(tr("正在升级:")+upFilelist[0]);

            QFileInfo info(upFilelist[0]);
            QString strSend = QString("%1^%2").arg(info.size()).arg(info.fileName());
            UIHandler::sendFile(info.filePath(), strSend, sendFileFinish, UsbFile::getPtr()->caliMachineNo);
        }
        else
        {
            Loading::hide();
            OneBtnMessageBox::display(tr("升级完成！"),tr("返回"));
        }
    }
    else if(param == 2)
    {
        OneBtnMessageBox::display(filename + tr("文件升级失败"),tr("返回"));
    }

    qDebug()<<"sendFileFinish"<<filename<<upFilelist.count();
}
