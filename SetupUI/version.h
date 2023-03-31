#ifndef VERSION_H
#define VERSION_H

#include <QDialog>

namespace Ui {
class version;
}

class version : public QDialog
{
    Q_OBJECT

protected:
    void showEvent(QShowEvent *event);
    void paintEvent(QPaintEvent *event);
    void load_data(void);

public:
    explicit version(QWidget *parent = nullptr);
    ~version();
    static version* getPtr();

private slots:
    void on_pushButton_clicked();

private:
    int caliMachineNo;

private:
    Ui::version *ui;
};

#endif // VERSION_H
