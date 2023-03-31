#ifndef UPPERMACHINE_H
#define UPPERMACHINE_H

#include <QWidget>
#include <QStyledItemDelegate>
#include <QStyleOptionViewItem>
#include <QStandardItemModel>
#include <QLabel>

namespace Ui {
class UpperMachine;
}

class CStyledItemDelegateEx : public QStyledItemDelegate
{
public:
    CStyledItemDelegateEx(){}
    ~CStyledItemDelegateEx(){}

public:
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        QStyleOptionViewItem opNew(option);

        opNew.displayAlignment =  Qt::AlignCenter;

        QStyledItemDelegate::paint(painter, opNew, index);

    }
};

class UpperMachine : public QWidget
{
    Q_OBJECT

public:
    explicit UpperMachine(QWidget *parent = nullptr);
    ~UpperMachine();
    static UpperMachine *getPtr();

protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);
private slots:


    void on_pBtn_addSub_clicked();

    void on_pBtn_addPower_clicked();

    void on_pBtn_confirm_clicked();

    void on_pBtn_cancel_clicked();

    void on_pBtn_clear_clicked();

private:
    Ui::UpperMachine *ui;

    void showBroadcastMac();
    void showPowerMac();
    QList<QWidget *> m_list;
    QMap<QWidget *,bool> m_map;
    QMultiMap<QLabel *,QWidget *> m_mutliMap;
    void updateUi();
};

#endif // UPPERMACHINE_H
