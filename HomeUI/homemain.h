#ifndef HOMEMAIN_H
#define HOMEMAIN_H

#include <QDialog>
#include <QMap>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QButtonGroup>
namespace Ui {
class HomeMain;
}

class HomeMain : public QDialog
{
    Q_OBJECT

private:
     explicit HomeMain(QWidget *parent = nullptr);

public:
    ~HomeMain();
    static HomeMain *getPtr();
    QWidget * getMaskWidget();
    static int getStackCurIndex();

    void switchDisplay(int machiNo);
signals:
    void sig_UpdateUI();
    void sig_DoorKeyDown(int machineNo);

protected:
    void showEvent(QShowEvent *event);
    virtual void hideEvent(QHideEvent *event) Q_DECL_OVERRIDE ;
    virtual void timerEvent(QTimerEvent *e) Q_DECL_OVERRIDE;

private slots:
    void on_HomeMain_pb_PowerOff_clicked();
    void on_HomeMain_pb_quit_clicked();
    void UpdateUI(int machineNo);
    void TestProgress(int complete, int total, int machineNo);
    void slot_btnGrpClicked(QAbstractButton*);
    void slot_clearTestProcess( int machineNo);
    void slot_DoorKeyDown(int machineNo);

    void on_HomeMain_pb_allMac_clicked();

private:
    Ui::HomeMain *ui;

    QStackedWidget * m_StackWidget;
    QVBoxLayout *m_layout;
    QWidget *m_BtnWidget;
    QHBoxLayout * m_btnLayout;

    void addSubMachineBtn();
    QButtonGroup *m_btnGroup;
    QPushButton *m_btnPre;
    QPushButton *m_btnNext;
    QStackedWidget * m_StackBtnWidget;

    void changePage();
    void initStyle();
    QWidget * maskWidget;
    QHBoxLayout *maskWidgetLay;
};

#endif // HOMEMAIN_H
