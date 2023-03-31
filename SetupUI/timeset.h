#ifndef TIMESET_H
#define TIMESET_H

#include <QDialog>
#include "../components/TimeScrollBar.h"

namespace Ui {
class TimeSet;
}

class TimeSet : public QDialog
{
    Q_OBJECT

protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

public:
    explicit TimeSet(QWidget *parent = nullptr);
    ~TimeSet();
    static TimeSet* getPtr();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_clicked();
    void on_comboBox_currentIndexChanged(int index);
    void slot_calendar_month_clicked();
    void on_calendarWidget_currentPageChanged(int year, int month);
    void slot_currentValueChange(int nValue, QWidget* pWidget);
    void timeout();

private:
    void initTimeScrollBar();
    void initStyleSheet();
    void updateTimeScrollBar();
    void setWidgetHourRang(int hour);
    void enableBtn();

private:
    Ui::TimeSet *ui;

    TimeScrollBar* pWidgetAmPm;
    TimeScrollBar* pWidgetHour;
    TimeScrollBar* pWidgetMin;
    int nAmPm;
    QTimer timer;
};

#endif // TIMESET_H
