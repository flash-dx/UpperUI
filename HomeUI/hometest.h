#ifndef HOMETEST_H
#define HOMETEST_H

#include <QDialog>
#include "uihandler.h"
//#include <QtCharts>
#include <QtCharts/QChart>
#include <QValueAxis>
#include <QCategoryAxis>
#include <QChartView>
namespace Ui {
class HomeTest;
}

QT_CHARTS_USE_NAMESPACE

class HomeTest : public QDialog
{
    Q_OBJECT
public:
    explicit HomeTest(QWidget *parent = nullptr);
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
