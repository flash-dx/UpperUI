#include "uppermachine.h"
#include "ui_uppermachine.h"

#include <QDebug>
#include "components/onebtnmessagebox.h"
#include <QListView>
#include "../uihandler.h"

static UpperMachine *winptr = nullptr;
UpperMachine::UpperMachine(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UpperMachine)
{
    ui->setupUi(this);

    QList<QWidget *> listWdiget =this->findChildren<QWidget *>();

    Q_FOREACH(QWidget *w,listWdiget)
    {
        w->setStyleSheet("border:1px solid gray");
    }

    QList<QLabel *> list =this->findChildren<QLabel *>();
    Q_FOREACH(QLabel *lb,list)
    {
        lb->setText("");
        lb->setWordWrap(true);
        lb->setStyleSheet("font:bold 18px;");
        lb->setAlignment(Qt::AlignCenter);
    }

    ui->lb_subInfo->setText(tr("机器mac+ip"));
    ui->lb_powerinfo->setText(tr("电源mac+ip"));


    QFont font(QStringLiteral("Arial"), 15);
    ui->listWidget_sub->setFont(font);
    ui->listWidget_powerMac->setFont(font);
    ui->widget->setWhatsThis("1");
    ui->widget_2->setWhatsThis("2");
    ui->widget_7->setWhatsThis("3");
    ui->widget_8->setWhatsThis("4");
    ui->widget_3->setWhatsThis("5");
    ui->widget_4->setWhatsThis("6");
    ui->widget_9->setWhatsThis("7");
    ui->widget_10->setWhatsThis("8");
    ui->widget_5->setWhatsThis("9");
    ui->widget_6->setWhatsThis("10");
    ui->widget_11->setWhatsThis("11");
    ui->widget_12->setWhatsThis("12");

    m_map.insert(ui->widget,true);
    m_map.insert(ui->widget_2,false);
    m_map.insert(ui->widget_7,false);
    m_map.insert(ui->widget_8,false);

    m_map.insert(ui->widget_3,false);
    m_map.insert(ui->widget_4,false);
    m_map.insert(ui->widget_9,false);
    m_map.insert(ui->widget_10,false);

    m_map.insert(ui->widget_5,false);
    m_map.insert(ui->widget_6,false);
    m_map.insert(ui->widget_11,false);
    m_map.insert(ui->widget_12,false);

    m_mutliMap.insert(ui->label_powermac1,ui->widget);
    m_mutliMap.insert(ui->label_powermac1,ui->widget_2);
    m_mutliMap.insert(ui->label_powermac1,ui->widget_7);
    m_mutliMap.insert(ui->label_powermac1,ui->widget_8);

    m_mutliMap.insert(ui->label_powermac1_2,ui->widget_3);
    m_mutliMap.insert(ui->label_powermac1_2,ui->widget_4);
    m_mutliMap.insert(ui->label_powermac1_2,ui->widget_9);
    m_mutliMap.insert(ui->label_powermac1_2,ui->widget_10);

    m_mutliMap.insert(ui->label_powermac1_3,ui->widget_5);
    m_mutliMap.insert(ui->label_powermac1_3,ui->widget_6);
    m_mutliMap.insert(ui->label_powermac1_3,ui->widget_11);
    m_mutliMap.insert(ui->label_powermac1_3,ui->widget_12);

    Q_FOREACH(QWidget *w,m_map.keys())
    {
        w->installEventFilter(this);
    }
}

UpperMachine::~UpperMachine()
{
    delete ui;
}

UpperMachine *UpperMachine::getPtr()
{
    if (winptr == nullptr)
        winptr = new UpperMachine;
    return winptr;
}

void UpperMachine::showEvent(QShowEvent *event){
    Q_UNUSED(event);

    static bool flag = false;
    if(!flag)
    {
        QWidget * w = m_map.key(true);
        w->setStyleSheet("border:3px solid red");
        flag = true;
    }
    showBroadcastMac();
    showPowerMac();

    updateUi();

    UIHandler::NotifyTitle("setup_submachine",5);
}

void UpperMachine::hideEvent(QHideEvent *event){
    Q_UNUSED(event);
    ui->listWidget_powerMac->clear();
    ui->listWidget_sub->clear();
    OneBtnMessageBox::getPtr()->disconnect(this);
}


void UpperMachine::showBroadcastMac()
{

    map<string, string> temmap = UIHandler::getBoardcastMac();
    for(auto it:temmap)
        ui->listWidget_sub->addItem(str2q(it.second)+"("+str2q(it.first)+")");

    if(ui->listWidget_sub->count() >0)
        ui->listWidget_sub->setCurrentRow(0);
}

void UpperMachine::showPowerMac()
{
    map<string, string> temmap = UIHandler::getPowerMac();
    for(auto it:temmap)
        ui->listWidget_powerMac->addItem(str2q(it.second)+"("+str2q(it.first)+")");
    ui->listWidget_powerMac->addItem("1111");
    ui->listWidget_powerMac->addItem("2222");
    ui->listWidget_powerMac->addItem("3333");
    if(ui->listWidget_powerMac->count() >0)
        ui->listWidget_powerMac->setCurrentRow(0);
}

void UpperMachine::updateUi()
{
    vector<WholeMachine_T  *> vecWholeMachine = UIHandler::getWholeMacArr();

    for (auto iter1: vecWholeMachine) {
        for (auto iter2: iter1->sub) {
            QMap<QWidget *,bool>::iterator iter3 = m_map.begin();
            while(iter3 != m_map.end())
            {
                if(iter3.key()->whatsThis().toInt() == iter2->machineNO)
                {
                    QList<QLineEdit *>listLe = iter3.key()->findChildren<QLineEdit *>();
                    Q_FOREACH(QLineEdit * le,listLe)
                    {
                        le->setText(str2q(iter2->name));
                    }

                    QList<QLabel *> listLb =  iter3.key()->findChildren<QLabel *>();
                    Q_FOREACH(QLabel *lb,listLb)
                    {
                        lb->setText(str2q(iter2->mac));
                    }

                    m_mutliMap.key(iter3.key())->setText(str2q(iter1->powerMac));
                }
                ++iter3;
            }
        }
    }
}

bool UpperMachine::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonRelease){

        QMap<QWidget *,bool>::iterator iter = m_map.begin();

        while(iter != m_map.end())
        {
            if(obj->objectName() == iter.key()->objectName())
            {
                iter.value() = true;
                iter.key()->setStyleSheet("border:3px solid red");
            }
            else
            {
                iter.value() = false;
                iter.key()->setStyleSheet("border:1px solid gray");
            }
            ++iter;
        }
        return true;
    }
    return false;
}

void UpperMachine::on_pBtn_addSub_clicked()
{
    if(ui->listWidget_sub->count() <= 0)
        return;

    QMap<QWidget *,bool>::iterator iter = m_map.begin();

    while(iter != m_map.end())
    {
        if(iter.value())
        {
            QList<QLabel *>listLb = iter.key()->findChildren<QLabel *>();
            Q_FOREACH(QLabel * lb,listLb)
            {
                UIHandler::setLabelWordWrap(lb,ui->listWidget_sub->currentItem()->text().split('(')[0]);
            }

            QList<QLineEdit *>listLe = iter.key()->findChildren<QLineEdit *>();
            Q_FOREACH(QLineEdit * le,listLe)
            {
                le->setText("111");
            }
        }
        ++iter;
    }
}

void UpperMachine::on_pBtn_addPower_clicked()
{
    if(ui->listWidget_powerMac->count() <= 0)
        return;

    QMap<QWidget *,bool>::iterator iter = m_map.begin();

    while(iter != m_map.end() )
    {
        if(iter.value())
        {
            m_mutliMap.key(iter.key())->setText(ui->listWidget_powerMac->currentItem()->text().split('(')[0]);
        }
        ++iter;
    }
}

void UpperMachine::on_pBtn_confirm_clicked()
{
    QList<QLabel *> templistLb = m_mutliMap.keys();

    QList<QLabel *> listLb;

    Q_FOREACH(QLabel *lb,templistLb)
    {
        if(!listLb.contains(lb))
        {
            listLb<<lb;
        }
    }

    QList<QString>  listStr;

    for (int var = 0; var < listLb.size(); ++var) {
        QString text = listLb[var]->text();
        if(!text.isEmpty())
        {
            if(listStr.contains(text))
            {
                OneBtnMessageBox::display("电源板mac重复",tr("关闭"),":/images/backTestbt3.png");
                return ;
            }
            else
            {
                listStr<<text;
            }
        }
    }

    if(listStr.size() <= 0)
    {
        OneBtnMessageBox::display("未添加电源板mac",tr("关闭"),":/images/backTestbt3.png");
        return;
    }

    listStr.clear();

    QMap<QWidget *,bool>::iterator iter = m_map.begin();

    static bool bClearTable = false;
    int bAddCount = 0;

    while(iter != m_map.end())
    {
        QList<QLabel *> list = iter.key()->findChildren<QLabel *>();
        for (int i = 0; i < list.size(); ++i) {
            QString text = list[i]->text();
            if(!list[i]->text().isEmpty())
            {
                QList<QLineEdit *> listLe = iter.key()->findChildren<QLineEdit *>();

                int total = listLe.size();

                for (int var = 0; var < total; ++var) {
                    QString LeText = listLe[var]->text();
                    if(LeText.isEmpty())
                    {
                        OneBtnMessageBox::display("机器名字不能为空",tr("关闭"),":/images/backTestbt3.png");
                        return ;
                    }
                }
                if(listStr.contains(text))
                {
                    OneBtnMessageBox::display("不同电源板添加相同的机器",tr("关闭"),":/images/backTestbt3.png");
                    return ;
                }
                else
                {
                    listStr<<text;
                }

                if(!bClearTable)
                {
                    if(!UIHandler::clearSubTable())
                    {
                        bClearTable = false;
                        OneBtnMessageBox::display("数据库清除错误",tr("关闭"),":/images/backTestbt3.png");
                        return ;
                    }
                    bClearTable = true;
                }

                QString strMac;
                Q_FOREACH(QString str,list[0]->text().split('\n'))
                {
                    strMac += str;
                }
                 bool flag = UIHandler::AddSubMachine(q2str(strMac),iter.key()->whatsThis().toInt(),q2str(listLe[0]->text()),
                        q2str(m_mutliMap.key(iter.key())->text()));

                 if(flag)
                 {
                     bAddCount++;
                 }
                 else {
                     OneBtnMessageBox::display("添加错误",tr("关闭"),":/images/backTestbt3.png");
                     return ;
                 }
            }
        }
        ++iter;
    }

    bClearTable = false;

    if(bAddCount <= 0)
    {
        OneBtnMessageBox::display("未添加机器",tr("关闭"),":/images/backTestbt3.png");
        return ;
    }

    OneBtnMessageBox::display("成功",tr("关闭"),":/images/backTestbt3.png");
}

void UpperMachine::on_pBtn_cancel_clicked()
{
    UIHandler::GoPage(UIHandler::PageId::Page_Setup_Menu);
}

void UpperMachine::on_pBtn_clear_clicked()
{
    QWidget * w= m_map.key(true);
    QList<QLineEdit *> listLe =  w->findChildren<QLineEdit *>();
    Q_FOREACH(QLineEdit *le,listLe)
    {
        le->setText("");
    }

    QList<QLabel *> listLb =  w->findChildren<QLabel *>();
    Q_FOREACH(QLabel *lb,listLb)
    {
        lb->setText("");
    }

    m_mutliMap.key(w)->setText("");;
}
