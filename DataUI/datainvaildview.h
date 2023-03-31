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
    explicit DataInvaildView(QWidget *parent = nullptr);
    ~DataInvaildView();
    static DataInvaildView *getPtr(int ptrIndex = 0);

protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

private slots:
    void on_Data_InvalidView_btBack_clicked();

    void on_Data_InvalidView_btDelete_clicked();

    void updateUI();

private:
    Ui::DataInvaildView *ui;
};

#endif // DATAINVAILDVIEW_H
