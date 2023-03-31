#ifndef HomeLoading_H
#define HomeLoading_H

#include <QWidget>
#include <QMovie>
#include <QPainter>

namespace Ui {
class HomeLoading;
}

class HomeLoading : public QWidget
{
    Q_OBJECT

private:
    explicit HomeLoading(QWidget *parent = nullptr);
public:  
    ~HomeLoading();
    static HomeLoading *getPtr();
    static void display(QString message);
    static void hide();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::HomeLoading *ui;
    QMovie *movie;
};

#endif // HomeLoading_H
