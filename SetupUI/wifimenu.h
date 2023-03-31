#ifndef WIFIMENU_H
#define WIFIMENU_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class WifiMenu;
}

class WifiMenu : public QDialog
{
    Q_OBJECT

protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

public:
    explicit WifiMenu(QWidget *parent = nullptr);
    ~WifiMenu();

    void listview_refresh();
    void wifiShow();
    static WifiMenu* getPtr();

    QString current_SSID;

private slots:
    void on_pButton_return_clicked();

    void on_pButton_refresh_clicked();

    void on_pButton_brock_clicked();

    void on_tableWidget_wifi_cellClicked(int row, int column);

    void Connect_Wifi(QString real);
    void Connect_Finish(int val);
    void disconnect_wifi(int ack, QString text);

    void on_WifiMenu_accepted();
    void timeout();

private:
    Ui::WifiMenu *ui;
    int fun;
    QTimer timer;

};

#endif // WIFIMENU_H
