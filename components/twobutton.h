#ifndef TWOBUTTON_H
#define TWOBUTTON_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class TwoButton;
}

class TwoButton : public QWidget
{
    Q_OBJECT
private:
    explicit TwoButton(QWidget *parent = nullptr);
public:
    ~TwoButton();
    static TwoButton *getPtr();
    static TwoButton *getPtr_no_edit();
    static TwoButton *getPtr_one_bt();
    static void display_two_bt(QString title, QString l1, QString l2, QString b1, QString b2,QString v1 );
    static void display_two_bt_noedit(QString title, QString l1,QString b1, QString b2);
    static void display_one_bt(QString title, QString l1,QString b1, QString btBkImg = ":/images/cancel2.png");
protected:
    void paintEvent(QPaintEvent *event);
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

private slots:
    void on_pButton_twobt_ok_clicked();

    void on_pButton_twobt_return_clicked();

private:
    Ui::TwoButton *ui;
    static int init_x ;
    static int init_y ;
    QString cancelBtBkImg;
    QString confirmBtBkImg;

signals:
    void queryAck_twobt(QString res1);
    void queryAck_twobt_no_edit();
};

#endif // TWOBUTTON_H
