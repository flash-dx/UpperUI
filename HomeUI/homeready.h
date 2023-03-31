#ifndef HOMEREADY_H
#define HOMEREADY_H

#include <QDialog>


namespace Ui {
class HomeReady;
}

class HomeReady : public QDialog
{
    Q_OBJECT
private:
    explicit HomeReady(QWidget *parent = nullptr);
public:
    ~HomeReady();
    static HomeReady *getPtr();

protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void TwoBtnMessageBox_Ack(int ack, QString winName);
    void on_Home_HomeReady_btPen_clicked();
    void on_Home_HomeReady_btCancelTest_clicked();
    void on_Home_HomeReady_btStart_clicked();
    void Sample_Changed(QString res1, QString res2, QString res3);
    void on_Home_HomeReady_cbTestType_currentIndexChanged(int index);

private:
    Ui::HomeReady *ui;
    void ChangedTips();
};

#endif // HOMEREADY_H
