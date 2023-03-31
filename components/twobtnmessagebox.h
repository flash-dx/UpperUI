#ifndef TWOBTNMESSAGEBOX_H
#define TWOBTNMESSAGEBOX_H

#include <QWidget>

namespace Ui {
class TwoBtnMessageBox;
}

class TwoBtnMessageBox : public QWidget
{
    Q_OBJECT

public:
    explicit TwoBtnMessageBox(QWidget *parent = nullptr);
    ~TwoBtnMessageBox();
    static TwoBtnMessageBox *getPtr();
    static void display(QString message, QString bt1 = tr("确定"), QString bt2 = tr("取消"), QString name = "");
    static void display_edit(QString message, QString lb = "", QString edit = "", QString bt1 = tr("确定"), QString bt2 = tr("取消"),QString bt1Bkimg = ":/images/backTestbt3.png", QString bt2Bkimg = ":/images/confirm280X85.png");
    static void hide(){getPtr()->close();}

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_Com_TwoBtnMessageBox_bt1_clicked();

    void on_Com_TwoBtnMessageBox_bt2_clicked();

private:
    Ui::TwoBtnMessageBox *ui;
    QString winName;

signals:
    void MessageAck(int ack, QString win);
};

#endif // TWOBTNMESSAGEBOX_H
