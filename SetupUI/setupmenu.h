#ifndef SETUPMENU_H
#define SETUPMENU_H

#include <QDialog>
#include <QStandardItemModel>
#include "../uihandler.h"

struct SetupMenuItem
{
    QString Eid;
    QString icon;
    QString name;
    UIHandler::PageId page;
    bool show;
    bool testHide;
};

namespace Ui {
class SetupMenu;
}

class SetupMenu : public QDialog
{
    Q_OBJECT

public:
    explicit SetupMenu(QWidget *parent = nullptr);
    ~SetupMenu();
    static SetupMenu *getPtr();
protected:
    void showEvent(QShowEvent *event);
private:
    Ui::SetupMenu *ui;
    static SetupMenuItem item[];
    void LoadMenu();
    QString getItemInfo(QString eid);
    void InitItem();
    void hideItem(QString id);

private slots:
    void clickItem(QModelIndex index);
    void slot_StateUpdate(UIHandler::StateId id);
};

#endif // SETUPMENU_H
