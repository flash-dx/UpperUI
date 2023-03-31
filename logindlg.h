#ifndef LOGINDLG_H
#define LOGINDLG_H

#include <QDialog>

namespace Ui {
class LoginDlg;
}

class LoginDlg : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDlg(QWidget *parent = nullptr);
    ~LoginDlg();
    static LoginDlg *getPtr();

protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

private slots:
    void on_LoginDlg_btLogin_clicked();

    void on_LoginDlg_btQuit_clicked();

    void TwoBtnMessageBox_Ack(int ack);

private:
    Ui::LoginDlg *ui;
};

#endif // LOGINDLG_H
