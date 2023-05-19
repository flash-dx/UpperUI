#ifndef DATALINE_H
#define DATALINE_H

#include <QDialog>
//#include <QtCharts>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QChartView>
#include <QLabel>
namespace Ui {
class DataLine;
}

QT_CHARTS_USE_NAMESPACE

class DataLine : public QDialog
{
    Q_OBJECT

public:
    explicit DataLine(QWidget *parent = nullptr,int type =0);
    ~DataLine();
public:
    void updateUI(int machineNo = -1);
protected:
    void paintEvent(QPaintEvent *event);
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);
    void updateChart();
private slots:
    void on_btBack_clicked();
    void on_Item_clicked();



private:
    Ui::DataLine *ui;    
    QChart *chart;
    QChartView *chartView;
    QValueAxis *axisX;
    QCategoryAxis *axisY;

    QList<QLabel*> list;
    QList<QPushButton*> btnlist;
    int winIndex;
};

#endif // DATALINE_H
