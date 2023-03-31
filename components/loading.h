#ifndef LOADING_H
#define LOADING_H

#include <QWidget>
#include <QMovie>
#include <QPainter>

namespace Ui {
class Loading;
}

class Loading : public QWidget
{
    Q_OBJECT

private:
    explicit Loading(QWidget *parent = nullptr);
public:  
    ~Loading();
    static Loading *getPtr();
    static void display(QString message);
    static void hide();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::Loading *ui;
    QMovie *movie;
};

#endif // LOADING_H
