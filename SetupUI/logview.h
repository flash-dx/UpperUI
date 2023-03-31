#ifndef LOGVIEW_H
#define LOGVIEW_H

#include <QDialog>

namespace Ui {
class LogView;
}

class LogView : public QDialog
{
    Q_OBJECT

public:
    explicit LogView(QWidget *parent = nullptr);
    ~LogView();
    void display_data(void);
    static LogView* getPtr();

private slots:
    void on_cBox_log_selest_currentIndexChanged(int index);

    void on_pButton_machine_back_clicked();

protected:
    void showEvent(QShowEvent *event);

private:
    Ui::LogView *ui;
};

#endif // LOGVIEW_H
