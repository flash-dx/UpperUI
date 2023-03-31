#include "uppermachineSetting.h"
#include "ui_uppermachineSetting.h"

#include <QDebug>
#include "components/onebtnmessagebox.h"
#include "components/twobtnmessagebox.h"
#include <QListView>
#include "../uihandler.h"

static UpperMachineSetting *winptr = nullptr;
UpperMachineSetting::UpperMachineSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UpperMachineSetting)
{
    ui->setupUi(this);

    ui->Setup_UpperMachineSetting_lbBg->setGeometry(560,58,799,469);
    ui->Setup_UpperMachineSetting_lbMachine->setGeometry(792,87,315,42);
    ui->Setup_UpperMachineSetting_tbMachine->setGeometry(562,154,797,363);

    ui->Setup_UpperMachineSetting_lbNo->setGeometry(660,560,100,40);
    ui->Setup_UpperMachineSetting_lbNo->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->Setup_UpperMachineSetting_leNo->setGeometry(780,560,400,40);
    ui->Setup_UpperMachineSetting_leNo->setEnabled(false);

    ui->Setup_UpperMachineSetting_lbName->setGeometry(660,620,100,40);
    ui->Setup_UpperMachineSetting_lbName->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->Setup_UpperMachineSetting_leName->setGeometry(780,620,400,40);

    ui->Setup_UpperMachineSetting_BtnModify->setGeometry(1400,494,220,72);
    ui->Setup_UpperMachineSetting_BtnFlush->setGeometry(1400,586,220,72);
    ui->Setup_UpperMachineSetting_BtnBack->setGeometry(1400,678,220,72);

    m_pModel = new QStandardItemModel(ui->Setup_UpperMachineSetting_tbMachine);
    ui->Setup_UpperMachineSetting_tbMachine->setModel(m_pModel);
    ui->Setup_UpperMachineSetting_tbMachine->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->Setup_UpperMachineSetting_tbMachine->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->Setup_UpperMachineSetting_tbMachine->horizontalHeader()->setStretchLastSection(true);
    ui->Setup_UpperMachineSetting_tbMachine->verticalHeader()->setVisible(false);
    ui->Setup_UpperMachineSetting_tbMachine->horizontalHeader()->setMinimumSectionSize(350);
    ui->Setup_UpperMachineSetting_tbMachine->horizontalHeader()->setMaximumSectionSize(400);
    m_pModel->setColumnCount(2);
    m_pModel->setHeaderData(1,Qt::Horizontal,tr("编号"));
    m_pModel->setHeaderData(2,Qt::Horizontal,tr("名称"));
    m_twoBtnFlag = 0;
}

UpperMachineSetting::~UpperMachineSetting()
{
    delete ui;
}

UpperMachineSetting *UpperMachineSetting::getPtr()
{
    if (winptr == nullptr)
        winptr = new UpperMachineSetting;
    return winptr;
}

void UpperMachineSetting::showEvent(QShowEvent *event){
    Q_UNUSED(event);

    updataData();

    connect(TwoBtnMessageBox::getPtr(),&TwoBtnMessageBox::MessageAck,this,&UpperMachineSetting::TwoBtnMessageBox_Ack);

    UIHandler::NotifyTitle("setup_submachine",5);
}

void UpperMachineSetting::hideEvent(QHideEvent *event){
    Q_UNUSED(event);
    TwoBtnMessageBox::getPtr()->disconnect(this);
    m_twoBtnFlag = 0;
}

void UpperMachineSetting::on_Setup_UpperMachineSetting_BtnModify_clicked()
{
    if(!ui->Setup_UpperMachineSetting_tbMachine->currentIndex().isValid())
    {
        OneBtnMessageBox::display(tr("请选中需要修改的行！"),tr("关闭"),":/images/backTestbt3.png");
        return ;
    }

    QString strNo  = ui->Setup_UpperMachineSetting_leNo->text();
    QString strName = ui->Setup_UpperMachineSetting_leName->text();
    if(!strNo.isEmpty() && !strName.isEmpty())
    {
        m_twoBtnFlag = 2;
        TwoBtnMessageBox::display(tr("确定修改选中行？"),tr("取消"),tr("确认"));
    }
    else
    {
        OneBtnMessageBox::display(tr("MAC，编号和名称都不能为空！"),tr("关闭"),":/images/backTestbt3.png");
        return;
    }
}

void UpperMachineSetting::on_Setup_UpperMachineSetting_BtnFlush_clicked()
{
    updataData();
}

void UpperMachineSetting::TwoBtnMessageBox_Ack(int ack)
{
    if(ack == 2 )
    {
        if(m_twoBtnFlag == 2) {
            QString strNo  = ui->Setup_UpperMachineSetting_leNo->text();
            QString strName = ui->Setup_UpperMachineSetting_leName->text();

            map<int, string> NameMap = UIHandler::get_subMac_Name();
            map<int, string> MacMap = UIHandler::get_subMac_Mac();
            map<int, string> powerMap = UIHandler::get_subMac_PowerMac();
            for(auto it:NameMap)
            {
                if(str2q(it.second) == strName)
                {
                    OneBtnMessageBox::display(tr("该名称已存在"),tr("关闭"),":/images/backTestbt3.png");
                    return;
                }
            }

            QString mac = str2q(MacMap.at(strNo.toInt()));
            QString power = str2q(powerMap.at(strNo.toInt()));
            int index =ui->Setup_UpperMachineSetting_tbMachine->currentIndex().row();
            QString oldMac = m_pModel->item(index,0)->text();
            int ret = UIHandler::modifySubMachine(oldMac, mac, strNo.toInt(), strName, power);
            if(ret == -1) {
               OneBtnMessageBox::display(tr("修改失败"),tr("关闭"),":/images/backTestbt3.png");
               return ;
           }
           else{
                OneBtnMessageBox::display(tr("修改成功"),tr("关闭"),":/images/backTestbt3.png");
                ui->Setup_UpperMachineSetting_leNo->text().clear();
                ui->Setup_UpperMachineSetting_leName->text().clear();
                updataData();
                return ;
            }
        }
    }
}

void UpperMachineSetting::on_Setup_UpperMachineSetting_tbMachine_clicked(const QModelIndex &index)
{
    ui->Setup_UpperMachineSetting_leNo->setText(m_pModel->item(index.row(),0)->text());
    ui->Setup_UpperMachineSetting_leName->setText(m_pModel->item(index.row(),1)->text());

}

void UpperMachineSetting::on_Setup_UpperMachineSetting_BtnBack_clicked()
{
    UIHandler::GoPage(UIHandler::PageId::Page_Setup_Menu);
}

void UpperMachineSetting::updataData()
{
    map<int, string> Name = UIHandler::get_subMac_Name();
    m_pModel->removeRows(0,m_pModel->rowCount());
    int row = 0;
    for(auto it : Name) {
        m_pModel->setItem(row, 0, new QStandardItem(QString::number(it.first)));
        m_pModel->setItem(row++, 1, new QStandardItem(str2q(it.second)));
    }
}
