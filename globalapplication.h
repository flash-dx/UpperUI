#ifndef GLOBALAPPLICATION_H
#define GLOBALAPPLICATION_H
#include <QApplication>
#include <QTimer>

class GlobalApplication : public QApplication
{
public:
    GlobalApplication(int &argc,char **argv);
    ~GlobalApplication();
    bool notify(QObject*,QEvent *);

private:
    int timerid;
    int timerkey;

protected:
    void timerEvent(QTimerEvent *event);
};

#endif // GLOBALAPPLICATION_H
