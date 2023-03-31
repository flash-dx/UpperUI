#ifndef DATAVIEW_H
#define DATAVIEW_H

#include <QDialog>


#include "uihandler.h"

namespace Ui {
class DataView;
}

class DataView : public QDialog
{
    Q_OBJECT

public:
    explicit DataView(QWidget *parent = nullptr);
    ~DataView();
    static DataView *getPtr(int ptrIndex = 0);

protected:
    void paintEvent(QPaintEvent *event);
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);
    void UpdataBtCheck();

private slots:
    void on_Data_View_btCheck_clicked();
    void Item_clicked();

    void on_Data_View_btBack_clicked();

    void on_Data_View_btPrint_clicked();

    void PrintFinish(QByteArray data);

    void on_Data_View_btDelete_clicked();

    void updateUI();  
private:
    Ui::DataView *ui;
    QList<QPushButton*> list;
};

#endif // DATAVIEW_H
