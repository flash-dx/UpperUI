#ifndef THREEQUERY_H
#define THREEQUERY_H

#include <QDialog>
namespace Ui {
class ThreeQuery;
}

class ThreeQuery : public QDialog
{
    Q_OBJECT

public:
    explicit ThreeQuery(QWidget *parent = nullptr);
    ~ThreeQuery();
    void setLabel(QString title, QString l1, QString l2, QString l3);
    void setValue(QString v1, QString v2, QString v3);
    QString getValue1(){return value1;}
    QString getValue2(){return value2;}
    QString getValue3(){return value3;}

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_Com_ThreeQuery_btConfirm_clicked();

    void on_Com_ThreeQuery_btCancel_clicked();

private:
    Ui::ThreeQuery *ui;
    QString value1;
    QString value2;
    QString value3;
};

#endif // THREEQUERY_H
