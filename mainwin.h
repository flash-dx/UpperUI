#ifndef MAINWIN_H
#define MAINWIN_H

#include <QDialog>
#include "uihandler.h"

namespace Ui {
class MainWin;
}

class DataView;
class DataInvaildView;
class DataLine;

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

    void FooterSetEnabled(bool enable);

    void GoPage(UIHandler::PageId id);

private:
    Ui::MainWin *ui;

    DataView *dataViewWin;
    DataInvaildView *invalidWin;
    DataLine *lineWin;
};

#endif // MAINWIN_H
