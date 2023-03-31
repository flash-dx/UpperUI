#include "logview.h"
#include "ui_logview.h"

#include "../uihandler.h"

static LogView *winptr = nullptr;

LogView *LogView::getPtr()
{
    if (winptr == nullptr)
        winptr = new LogView;
    return winptr;
}

LogView::LogView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogView)
{
   ui->setupUi(this);
   ui->pButton_machine_back->setGeometry(1580,780,300,115);
   ui->ltWidget_log->setStyleSheet("QScrollBar::vertical{width:50px}");
   ui->cBox_log_selest->setStyleSheet(UIHandler::getStyleSheet("QComboBox"));
   setStyleSheet("background-color:#f5f5f5;");
}

LogView::~LogView()
{
    delete ui;
}

void LogView::showEvent(QShowEvent *event){
    Q_UNUSED(event);
    ui->retranslateUi(this);
    display_data();
    UIHandler::setBtTextCenter(ui->pButton_machine_back, 48,"background-image: url(:/images/back.png);text-align:left;padding-bottom:20px;");

    UIHandler::NotifyTitle("Log_view",5);

}
void LogView::display_data(void)
{
    int log_num;
    QString record;
    list<logdata> loglist = UIHandler::getLogDataList(0);
    log_num = loglist.size();
    for(auto it:loglist)
    {
       record=QString::number(it.Logid,10);
       record.resize(10,' ');
       record = record + str2q(it.LogType);
       record.resize(18,' ');
       record = record + str2q(it.Result);
        record.resize(26,' ');
       record = record + str2q(it.LogTime);
       record.resize(44,' ');

       record = record + str2q(it.LogMsg);
       record.resize(78,' ');
       ui->ltWidget_log->addItem(record);
    }
     ui->ltWidget_log->setCurrentRow(0);
}

void LogView::on_cBox_log_selest_currentIndexChanged(int index)
{
    QString record;
    ui->ltWidget_log->clear();

    list<logdata> loglist = UIHandler::getLogDataList(index);
    int log_num = loglist.size();
    int ii  = log_num-1;

    for(auto it:loglist)
    {
        record=QString::number(ii--,10);
        record.resize(10,' ');
        record = record + str2q(it.LogType);
        record.resize(18,' ');
        record = record + str2q(it.Result);
        record.resize(26,' ');
        record = record + str2q(it.LogTime);
        record.resize(46,' ');

        record=record + str2q(it.LogMsg);
        record.resize(74,' ');
        record=record.mid(0,70);
        ui->ltWidget_log->addItem(record);
    }
    ui->ltWidget_log->setCurrentRow(0);
}

void LogView::on_pButton_machine_back_clicked()
{
     UIHandler::GoPage(UIHandler::PageId::Page_Setup_Menu);
}
