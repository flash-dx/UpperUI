#ifndef NETWORK_H
#define NETWORK_H

#include <QDialog>

namespace Ui {
class NetWork;
}

class NetWork : public QDialog
{
    Q_OBJECT

public:
    explicit NetWork(QWidget *parent = nullptr);
    ~NetWork();
    static NetWork* getPtr();

protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);


private slots:
    void on_pushButton_ok_clicked();

    void on_pushButton_cencel_clicked();

    void ConnectFinish(int val);

    void on_comboBox_macAddr_currentIndexChanged(const QString &arg1);
    void TwoBtnMessageAck(int ack, QString text);

private:
    Ui::NetWork *ui;

    void updataNet(QString netName);
};

#endif // NETWORK_H
