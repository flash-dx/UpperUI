#ifndef DATAMENU_H
#define DATAMENU_H

#include <QDialog>
#include "Module/testmodel.h"

namespace Ui {
class DataMenu;
}

class DataMenu : public QDialog
{
    Q_OBJECT

public:
    explicit DataMenu(QWidget *parent = nullptr);
    ~DataMenu();
    static DataMenu *getPtr();

protected:
    void showEvent(QShowEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::DataMenu *ui;

    bool bAsc;
    TestModel testModel;
};

#endif // DATAMENU_H
