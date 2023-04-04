#ifndef HOMETEST_H
#define HOMETEST_H

#include <QDialog>
#include "uihandler.h"
#include <QtCharts>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QChartView>
namespace Ui {
class HomeTest;
}

class HomeTest : public QDialog
{
    Q_OBJECT
private:
    explicit HomeTest(QWidget *parent = nullptr);
public:
    ~HomeTest();
    static HomeTest *getPtr();

protected:
    void paintEvent(QPaintEvent *event);
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

private slots:
    void on_Home_HomeTest_btCancelTest_clicked();
    void TwoBtnMessageBox_Ack(int ack, QString winname);
    void on_OneBtnMessageBox_Ack(int ack,QString name);
    void UpdateUI();
private:
    Ui::HomeTest *ui;
    void initUi();
    QChart *chart;
    QChartView *chartView;
    QValueAxis *axisX;
    QCategoryAxis *axisY;

};

#endif // HOMETEST_H
