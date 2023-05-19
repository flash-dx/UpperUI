#ifndef DATAINVAILDVIEW_H
#define DATAINVAILDVIEW_H

#include <QDialog>


#include "uihandler.h"

namespace Ui {
class DataInvaildView;
}

class DataInvaildView : public QDialog
{
    Q_OBJECT

public:
    explicit DataInvaildView(QWidget *parent = nullptr,int type =0);
    ~DataInvaildView();
public:
    void updateUI(int machineNo = -1);
protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

private slots:
    void on_Data_InvalidView_btBack_clicked();

    void on_Data_InvalidView_btDelete_clicked();

private:
    Ui::DataInvaildView *ui;
    int winIndex;
};

#endif // DATAINVAILDVIEW_H
