#ifndef E04_H
#define E04_H

#include <QDialog>


namespace Ui {
class E04;
}

class E04 : public QDialog
{
    Q_OBJECT
private:
     explicit E04(QWidget *parent = nullptr);

public:
   static E04 * getPtr();
    ~E04();

protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);
private slots:
    void slot_updateUi();
private:
    Ui::E04 *ui;
};

#endif // E04_H
