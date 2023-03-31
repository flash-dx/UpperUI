#ifndef USER_H
#define USER_H

#include <QDialog>

namespace Ui {
class User;
}

class User : public QDialog
{
    Q_OBJECT

protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);


public:
    explicit User(QWidget *parent = nullptr);
    ~User();
    void load_data(void);
    int currIndex=0;

    void mode_data();
    static User* getPtr();


private slots:
    void on_pButton_user_del_clicked();

    void on_pButton_user_add_clicked();

    void on_pButton_user_edit_clicked();

    void on_pButton_user_return_clicked();

    void deleteUserBack(int ack, QString text);


    void on_pushButton_back_clicked();


    void on_listWidget_2_clicked(const QModelIndex &index);

private:
    void initStyleSheet();
    QString getElidedText(QString str, int nMaxLen);

private:
    Ui::User *ui;
};

#endif // USER_H
