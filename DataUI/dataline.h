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
    explicit DataLine(QWidget *parent = nullptr);
    ~DataLine();
    static DataLine *getPtr(int ptrIndex = 0);

protected:
    void paintEvent(QPaintEvent *event);
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);
    void updateChart();
private slots:
    void on_btBack_clicked();
    void on_Item_clicked();
    void updateUI();


private:
    Ui::DataLine *ui;    
    QChart *chart;
    QChartView *chartView;
    QValueAxis *axisX;
    QCategoryAxis *axisY;

    QList<QLabel*> list;
    QList<QPushButton*> btnlist;
};

#endif // DATALINE_H
