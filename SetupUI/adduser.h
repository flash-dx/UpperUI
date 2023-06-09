#ifndef ADDUSER_H
#define ADDUSER_H

#include <QDialog>

namespace Ui {
class AddUser;
}

class AddUser : public QDialog
{
    Q_OBJECT

public:
    explicit AddUser(QWidget *parent = nullptr);
    void show_data(void);
    ~AddUser();
    static AddUser* getPtr();

protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::AddUser *ui;
};

#endif // ADDUSER_H
