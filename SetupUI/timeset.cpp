#include "timeset.h"
#include "ui_timeset.h"
#include <QListView>

#include "../uihandler.h"
#include <QTextCharFormat>
#include <QToolButton>
#include <QMenu>
#include "../components/loading.h"

static TimeSet *winptr = nullptr;

TimeSet *TimeSet::getPtr()
{
    if (winptr == nullptr)
        winptr = new TimeSet;
    return winptr;
}

TimeSet::TimeSet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TimeSet)
{
    ui->setupUi(this);

    int btnW = 299;
    int btnH = 106;
    int btnRight = 100;
    int btnBottom = 30;
    int btnLeft = UIHandler::contentWidth - btnW - btnRight;
    int btnTop = UIHandler::contentHeight - btnBottom - btnH;
    int btnAdd = 20;

    ui->pushButton_3->setGeometry(btnLeft, btnTop - (btnH + btnAdd),   btnW,btnH);
    ui->pushButton_2->setGeometry(btnLeft, btnTop,                     btnW,btnH);

    ui->label->setGeometry(1020,67,370,45);
    ui->pushButton->setGeometry(1400,67,90,58);
    ui->label_2->setGeometry(1020,197,370,45);
    ui->comboBox->setGeometry(1400,177,450,80);
    ui->timeScrollBarBk->setGeometry(770,67,370,340);
    ui->TimeScrollBar_Title->setGeometry(870,75,200,50);
    ui->calendarWidget->setGeometry(20,67,698,610);

    enableBtn();

    ui->comboBox->setView(new QListView());

    initStyleSheet();
    initTimeScrollBar();

    QToolButton *pmouthBtn = ui->calendarWidget->findChild<QToolButton*>(QLatin1String("qt_calendar_monthbutton"));
    connect(pmouthBtn,SIGNAL(pressed()),this,SLOT(slot_calendar_month_clicked()));
    connect(pWidgetAmPm,&TimeScrollBar::signal_currentValueChange,this,&TimeSet::slot_currentValueChange);
}

TimeSet::~TimeSet()
{
    delete ui;
}

void TimeSet::showEvent(QShowEvent *event){
    Q_UNUSED(event);

    ui->label->setText(tr("网络同步："));
    ui->label_2->setText(tr("选择时区："));
    ui->pushButton_3->setText(tr("  设置"));
    ui->pushButton_2->setText(tr("  返回"));
    ui->comboBox->setEnabled(false);
    ui->comboBox->clear();

    ui->comboBox->addItem(tr("(UTC+12)阿纳德尔"));
    ui->comboBox->addItem(tr("(UTC+11)马加丹"));
    ui->comboBox->addItem(tr("(UTC+10)关岛"));
    ui->comboBox->addItem(tr("(UTC+9)东京"));
    ui->comboBox->addItem(tr("(UTC+8)北京"));
    ui->comboBox->addItem(tr("(UTC+7)曼谷"));
    ui->comboBox->addItem(tr("(UTC+6)鄂木斯克"));
    ui->comboBox->addItem(tr("(UTC+5)塔什干"));
    ui->comboBox->addItem(tr("(UTC+4)迪拜"));
    ui->comboBox->addItem(tr("(UTC+3)莫斯科"));
    ui->comboBox->addItem(tr("(UTC+2)以色列"));
    ui->comboBox->addItem(tr("(UTC+1)巴黎"));
    ui->comboBox->addItem(tr("(UTC+0)伦敦"));
    ui->comboBox->addItem(tr("(UTC-1)佛得角群岛"));
    ui->comboBox->addItem(tr("(UTC-2)费尔南多"));
    ui->comboBox->addItem(tr("(UTC-3)贝伦"));
    ui->comboBox->addItem(tr("(UTC-4)加拉加斯"));
    ui->comboBox->addItem(tr("(UTC-5)纽约"));
    ui->comboBox->addItem(tr("(UTC-6)芝加哥"));
    ui->comboBox->addItem(tr("(UTC-7)丹佛"));
    ui->comboBox->addItem(tr("(UTC-8)洛杉矶"));
    ui->comboBox->addItem(tr("(UTC-9)安克雷奇"));
    ui->comboBox->addItem(tr("(UTC-10)火奴鲁鲁"));
    ui->comboBox->addItem(tr("(UTC-11)帕果帕果"));
    ui->comboBox->setEnabled(true);

    ui->comboBox->setStyleSheet(UIHandler::getStyleSheet("QComboBox"));

    ui->TimeScrollBar_Title->setText(tr("设置时间"));
    QDateTime curDateTime=QDateTime::currentDateTime();

    if (UIHandler::get_int_Param("LanguageCode") == 1)
    {
        ui->calendarWidget->setLocale(QLocale::English);
    }
    else
    {
        ui->calendarWidget->setLocale(QLocale::Chinese);
    }

    ui->calendarWidget->setSelectedDate(curDateTime.date());
    ui->comboBox->setCurrentIndex(UIHandler::get_int_Param("TimeZone"));

    updateTimeScrollBar();

    UIHandler::setBtTextCenter(ui->pushButton_3, 48,"background-image: url(:/images/confirmbt.png);text-align:left;");
    UIHandler::setBtTextCenter(ui->pushButton_2, 48,"background-image: url(:/images/back.png);text-align:left;");

    connect(&timer, &QTimer::timeout,this,&TimeSet::timeout);

    UIHandler::NotifyTitle("setup_datetime",5);
}

void TimeSet::hideEvent(QHideEvent *event){
    Q_UNUSED(event);

    Loading::hide();
    disconnect(&timer, &QTimer::timeout,this,&TimeSet::timeout);
}

void TimeSet::on_pushButton_2_clicked()
{
    UIHandler::GoPage(UIHandler::PageId::Page_Setup_Menu);
}

void TimeSet::on_pushButton_3_clicked()
{
    QString setStr;
    QDate qDate = ui->calendarWidget->selectedDate();
    int hour = pWidgetHour->getValue();
    int min  = pWidgetMin->getValue();
    if(pWidgetAmPm->getValue() == 1)
        hour += 12;
    setStr = qDate.toString("yyyy-MM-dd");
    setStr += QString(" %1:%2").arg(hour,2,10,QLatin1Char('0')).arg(min,2,10,QLatin1Char('0'));
    qDebug()<<"dateTime:="<<setStr;
    UIHandler::setTime(setStr);
}

void TimeSet::on_pushButton_clicked()
{    
    Loading::display(tr("请稍后..."));
    if (UIHandler::get_int_Param("TimeZoneOpen"))
        UIHandler::getPtr()->setTimezoneopen(false);
    else
        UIHandler::getPtr()->setTimezoneopen(true);

    timer.start(3000);
}

void TimeSet::on_comboBox_currentIndexChanged(int index)
{
    if(index >= 0 && ui->comboBox->isEnabled())
    {
        UIHandler::updatetimezone(index);
        updateTimeScrollBar();
    }
}

void TimeSet::initTimeScrollBar()
{
    QColor dColorCurrentText(0, 173, 215);
    QColor dColorLine("#0092FF");
    QColor dColorDisableText("#999999");
    QColor dColorBackground("#FFFFFF");

    pWidgetAmPm = new TimeScrollBar(ui->timeScrollBar_Ap);
    pWidgetAmPm->m_bAmPm = true;
    pWidgetAmPm->setRang(0, 1);
    pWidgetAmPm->setColor(dColorCurrentText);
    pWidgetAmPm->setColor(dColorLine, TimeScrollBar::ColorType::LINE);
    pWidgetAmPm->setColor(dColorDisableText, TimeScrollBar::ColorType::DISABLETEXT);
    pWidgetAmPm->setColor(dColorBackground, TimeScrollBar::ColorType::BACKHROUND);

   pWidgetHour = new TimeScrollBar(ui->timeScrollBar_hour);
   pWidgetHour->setRang(0, 12);
   pWidgetHour->setColor(dColorCurrentText);
   pWidgetHour->setColor(dColorLine, TimeScrollBar::ColorType::LINE);
   pWidgetHour->setColor(dColorDisableText, TimeScrollBar::ColorType::DISABLETEXT);
   pWidgetHour->setColor(dColorBackground, TimeScrollBar::ColorType::BACKHROUND);

   pWidgetMin = new TimeScrollBar(ui->timeScrollBar_min);
   pWidgetMin->setRang(0, 59);
   pWidgetMin->setColor(dColorCurrentText);
   pWidgetMin->setColor(dColorLine, TimeScrollBar::ColorType::LINE);
   pWidgetMin->setColor(dColorDisableText, TimeScrollBar::ColorType::DISABLETEXT);
   pWidgetMin->setColor(dColorBackground, TimeScrollBar::ColorType::BACKHROUND);

   updateTimeScrollBar();
}

void TimeSet::initStyleSheet()
{
    ui->calendarWidget->setStyleSheet(
    "QCalendarWidget{font:18pt;}"
    "QCalendarWidget QAbstractItemView {color: gray;}"
    "QCalendarWidget QAbstractItemView:enabled{color:#000000;background-color:#ffffff;selection-color:#ffffff;selection-background-color:rgb(48,140,198);}"
    "QToolButton#qt_calendar_prevmonth {qproperty-icon: url(:/images/row3.png);}"
    "QToolButton#qt_calendar_nextmonth {qproperty-icon:url(:/images/row1.png);}"
    "QCalendarWidget QToolButton{background-color:rgb(246,245,244);height:60px;width:300px;color:#000000;font:25pt;icon-size: 56px, 56px;}"
    "QCalendarView#qt_calendar_calendarview {background-color:#ffffff;alternate-background-color:#ffffff;}"
    "QCalendarWidget QSpinBox {width: 150px;font-size:34px;color: white;background-color:rgb(224,224,224);selection-background-color: blue;selection-color:#ffffff;}"
    "QCalendarWidget QSpinBox::up-button { subcontrol-origin: border;  subcontrol-position: top right;  width:65px; }"
    "QCalendarWidget QSpinBox::down-button {subcontrol-origin: border; subcontrol-position: bottom right;  width:65px;}"
    "QCalendarWidget QMenu{width:200px;color:#000000;font-size:30px; background-color:rgb(224,224,224);}"
    );

    QTextCharFormat textFormat = ui->calendarWidget->weekdayTextFormat(Qt::Monday);
    textFormat.setForeground(QBrush("#000000"));
    ui->calendarWidget->setWeekdayTextFormat(Qt::Saturday, textFormat);
    ui->calendarWidget->setWeekdayTextFormat(Qt::Sunday,   textFormat);

    ui->TimeScrollBar_Title->setStyleSheet("background:transparent");
    ui->timeScrollBarBk->setStyleSheet("border-image:url(:/images/timebg.png);");
}

void TimeSet::slot_calendar_month_clicked()
{
    QToolButton *senderObj=qobject_cast<QToolButton*>(sender());
    if(senderObj == nullptr)
    {
        return;
    }
    QPoint pt = cursor().pos();
    QList <QAction *> listAction = senderObj->findChildren<QAction *>();
    QList <QMenu *> pMenu = senderObj->findChildren<QMenu *>();
    if(pMenu.size() > 0)
    {
        QPoint menuPt = pMenu[0]->pos();
        int x = pt.x() - menuPt.x();
        int y = pt.y() - menuPt.y();
        for (int i = 0; i < listAction.size(); i++) {
            QRect rect = pMenu[0]->actionGeometry(listAction[i]);
            if(rect.contains(x, y))
            {
                QDate qDate = ui->calendarWidget->selectedDate();
                QToolButton *pBtnYear = ui->calendarWidget->findChild<QToolButton*>(QLatin1String("qt_calendar_yearbutton"));
                QDate tempDate(pBtnYear->text().toInt(), i, qDate.day());
                ui->calendarWidget->setSelectedDate(tempDate);
                senderObj->setText(listAction[i]->text());
            }
        }
    }
}
void TimeSet::updateTimeScrollBar()
{
    QTime time = QTime::currentTime();
    if (time.hour() > 12)
    {
        pWidgetAmPm->setValue(1);
        nAmPm = 1;
    }
    else
    {
        pWidgetAmPm->setValue(0);
        nAmPm = 0;
    }
    pWidgetAmPm->update();

    setWidgetHourRang(time.hour());

    pWidgetMin->setValue(time.minute());
    pWidgetMin->update();
}

void TimeSet::on_calendarWidget_currentPageChanged(int year, int month)
{
    QDate qDate = ui->calendarWidget->selectedDate();
    ui->calendarWidget->setSelectedDate(QDate(year, month, qDate.day()));
}

void TimeSet::slot_currentValueChange(int nValue, QWidget* pWidget)
{
    if(nAmPm != nValue)
    {
        nAmPm = nValue;
        setWidgetHourRang( pWidgetHour->getValue() );
    }
}

void TimeSet::setWidgetHourRang(int hour)
{
    if(nAmPm == 0)
    {
         pWidgetHour->setRang(0,12);
         pWidgetHour->setValue(hour);
    }
    else
    {
        pWidgetHour->setRang(1,11);

        if(hour >= 12)
        {
            hour -= 12;
        }
        if(hour <= 0)
        {
            hour = 1;
        }
        pWidgetHour->setValue(hour);
    }
    pWidgetHour->update();
}

void TimeSet::enableBtn()
{
    if (UIHandler::get_int_Param("TimeZoneOpen"))
    {
        ui->pushButton_3->setEnabled(false);
        ui->pushButton->setStyleSheet("background-image: url(:/images/lockscreenON.png);");
    }
    else
    {
        ui->pushButton_3->setEnabled(true);
        ui->pushButton->setStyleSheet("background-image: url(:/images/lockcreenOFF.png);");
    }
}

void TimeSet::timeout()
{
    Loading::hide();
    timer.stop();

    enableBtn();

    QDateTime dateTime = QDateTime::currentDateTime();
    ui->calendarWidget->setSelectedDate(dateTime.date());
    updateTimeScrollBar();
}
