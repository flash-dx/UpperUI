#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void timerEvent(QTimerEvent *e);
private:
    Ui::MainWindow *ui;
    void UISetup();

private slots:
    void EnterLogin(bool bEnter);
};

#endif // MAINWINDOW_H
