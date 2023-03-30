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

private slots:
    void on_LoginDlg_btLogin_clicked();

private:
    Ui::LoginDlg *ui;
};

#endif // LOGINDLG_H
