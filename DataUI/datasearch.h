#ifndef DATASEARCH_H
#define DATASEARCH_H

#include <QDialog>
#include <QMouseEvent>

namespace Ui {
class DataSearch;
}

class DataSearch : public QDialog
{
    Q_OBJECT

public:
    explicit DataSearch(QWidget *parent = nullptr);
    ~DataSearch();

    void Init();

    QString searchFilter;

private slots:
    void paintEvent(QPaintEvent *event);
    void showEvent(QShowEvent *event);
    void on_btn_Cancel_clicked();
    void on_radioButton_resultAll_clicked();
    void on_radioButton_resultValid_clicked();
    void on_radioButton_resultInvalid_clicked();
    void on_btn_ok_clicked();
    void on_btn_all_clicked();

private:
    Ui::DataSearch *ui;
};

#endif // DATASEARCH_H
