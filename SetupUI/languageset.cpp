#include "languageset.h"
#include "ui_languageset.h"

#include "../uihandler.h"
#include <QLabel>
#include <QScroller>


static LanguageSet *winptr = nullptr;

LanguageSet *LanguageSet::getPtr()
{
    if (winptr == nullptr)
        winptr = new LanguageSet;
    return winptr;
}

LanguageSet::LanguageSet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LanguageSet)
{
    ui->setupUi(this);

    ui->radioButton->setGeometry(750,300,500,60);
    ui->radioButton_2->setGeometry(750,400,500,60);
    ui->pushButton->setGeometry(1580,740,300,115);

    ui->radioButton->setIconSize(QSize(40,40));
    ui->radioButton_2->setIconSize(QSize(40,40));
    ui->radioButton->setStyleSheet("QRadioButton::indicator{width:35px;height:35px;}");
    ui->radioButton_2->setStyleSheet("QRadioButton::indicator{width:35px;height:35px;}");
    if (UIHandler::get_int_Param("LanguageCode") == 0)
        ui->radioButton->setChecked(true);
    else
        ui->radioButton_2->setChecked(true);

    ui->listWidget->setGeometry(0,0,UIHandler::contentWidth,UIHandler::contentHeight);
    ui->radioButton->setVisible(false);
    ui->radioButton_2->setVisible(false);
    ui->pushButton->setVisible(false);
    setStyleSheet("background-color:#f5f5f5;border:none;");

}

LanguageSet::~LanguageSet()
{
    delete ui;
}

void LanguageSet::clickItem(QModelIndex index)
{
    UIHandler::updata_int_Param("LanguageCode", index.row());
    addLang();
}
void LanguageSet::showEvent(QShowEvent *event){
    Q_UNUSED(event);
    addLang();
    UIHandler::NotifyTitle("setup_language",5);
}

void LanguageSet::hideEvent(QHideEvent *event){
    Q_UNUSED(event);

}


void LanguageSet::addLang()
{
    ui->listWidget->clear();
    for (unsigned int i = 0; i < 2; i++){
        QListWidgetItem *list = new QListWidgetItem;
        list->setSizeHint(QSize(UIHandler::contentWidth,120));
        ui->listWidget->addItem(list);

        QWidget *w = new QWidget(ui->listWidget);
        QLabel *a = new QLabel(w);
        if (i==0)
            a->setText("中文");
        else
            a->setText("English");

        a->setGeometry(160,35,200,50);
        a->setAlignment(Qt::AlignVCenter|Qt::AlignHCenter);
        a->setStyleSheet("font-size: 40px;");

        QLabel *row = new QLabel(w);
        row->setGeometry(UIHandler::contentWidth-140,40,39,39);
        if (UIHandler::get_int_Param("LanguageCode")==0)
        {
            if (i==0)
            {
                row->setPixmap(QPixmap(":/images/check.png"));
                w->setStyleSheet("background-color:#dedede");
            }

        }
        else
        {
            if (i==1)
            {
                row->setPixmap(QPixmap(":/images/check.png"));
                w->setStyleSheet("background-color:#dedede");
            }
        }

        ui->listWidget->setItemWidget(list,w);
    }

}


void LanguageSet::on_radioButton_clicked()
{
    UIHandler::updata_int_Param("LanguageCode", 0);
}

void LanguageSet::on_radioButton_2_clicked()
{
    UIHandler::updata_int_Param("LanguageCode", 1);
}

void LanguageSet::on_pushButton_clicked()
{
    UIHandler::GoPage(UIHandler::PageId::Page_Setup_Menu);
}

void LanguageSet::on_listWidget_clicked(const QModelIndex &index)
{
    UIHandler::updata_int_Param("LanguageCode", index.row());
    //UIHandler::UpdateState(UIHandler::StateId::State_SetupMenu_Update);
    UIHandler::GoPage(UIHandler::PageId::Page_Setup_Menu);

}
