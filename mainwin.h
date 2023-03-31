#ifndef MAINWIN_H
#define MAINWIN_H

#include <QDialog>

namespace Ui {
class MainWin;
}

class MainWin : public QDialog
{
    Q_OBJECT

public:
    explicit MainWin(QWidget *parent = nullptr);
    ~MainWin();
    static MainWin *getPtr();

private slots:
    void on_MainWin_btSetup_clicked();

    void on_MainWin_btHome_clicked();

    void on_MainWin_btData_clicked();

private:
    Ui::MainWin *ui;
};

#endif // MAINWIN_H
