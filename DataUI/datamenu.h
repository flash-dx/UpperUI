#ifndef DATAMENU_H
#define DATAMENU_H

#include <QDialog>
#include "Module/testmodel.h"
#include "datasearch.h"

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

    void on_Data_Menu_btnPre_clicked();

    void on_Data_Menu_btnNext_clicked();

    void on_Data_Menu_btnJump_clicked();

    void on_Data_Menu_btnFilter_clicked();

    void on_Data_Menu_btnAll_clicked();

private:
    Ui::DataMenu *ui;

    bool bAsc;
    TestModel testModel;
    DataSearch dataSearch;
    int pageNum;
    int currPage;
    int totalPage;
    int totalRecord;
    QString searchFilter;

    void initPage();
    void updatePage();
    void resetTableHead();
};

#endif // DATAMENU_H
