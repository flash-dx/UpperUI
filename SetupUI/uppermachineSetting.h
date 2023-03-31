#ifndef UPPERMACHINESETTING_H
#define UPPERMACHINESETTING_H

#include <QWidget>
#include <QStyledItemDelegate>
#include <QStyleOptionViewItem>
#include <QStandardItemModel>

namespace Ui {
class UpperMachineSetting;
}

class UpperMachineSetting : public QWidget
{
    Q_OBJECT

public:
    explicit UpperMachineSetting(QWidget *parent = nullptr);
    ~UpperMachineSetting();
    static UpperMachineSetting *getPtr();

protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

    void updataData();

private slots:
    void on_Setup_UpperMachineSetting_BtnModify_clicked();

    void on_Setup_UpperMachineSetting_BtnFlush_clicked();

    void TwoBtnMessageBox_Ack(int ack);


    void on_Setup_UpperMachineSetting_tbMachine_clicked(const QModelIndex &index);

    void on_Setup_UpperMachineSetting_BtnBack_clicked();

private:
    Ui::UpperMachineSetting *ui;
    int m_twoBtnFlag;
    QStandardItemModel  *m_pModel;
};

#endif // UPPERMACHINESETTING_H
