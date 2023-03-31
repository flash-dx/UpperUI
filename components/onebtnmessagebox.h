#ifndef ONEBTNMESSAGEBOX_H
#define ONEBTNMESSAGEBOX_H

#include <QWidget>

namespace Ui {
class OneBtnMessageBox;
}

class OneBtnMessageBox : public QWidget
{
    Q_OBJECT

public:
    explicit OneBtnMessageBox(QWidget *parent = nullptr);
    ~OneBtnMessageBox();
    static OneBtnMessageBox *getPtr();
    static void display(QString message, QString btnString = tr("取消测试"), QString btnBkImg = ":/images/backTestbt2.png", QString name = "");

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::OneBtnMessageBox *ui;
    QString winName;
signals:
    void MessageAck(int ack, QString win);
private slots:
    void on_Com_OneBtnMessageBox_bt1_clicked();
};

#endif // ONEBTNMESSAGEBOX_H
