#include "globalapplication.h"
#include "uihandler.h"

#include <QKeyEvent>
#include <QDebug>
GlobalApplication::GlobalApplication(int &argc, char **argv):QApplication (argc,argv)
{
    timerid = -1;
}

GlobalApplication::~GlobalApplication(){

}

static QString sampleCode = "";
static QString simpleKey = "";
static time_t timel = 0;

bool GlobalApplication::notify(QObject *obj, QEvent *e){
    if(e->type() == QEvent::MouseButtonRelease){
        const QMetaObject* objMeta = obj->metaObject();
        QString clName = objMeta->className();
        if (clName == "QWidgetWindow"){
            if (timerid != -1)
                this->killTimer(timerid);
            int timerout = UIHandler::get_int_Param("lockscreen_time");
            if (timerout != 0)
                timerid = this->startTimer(timerout*1000);
        }
    }
    else if(e->type() == QEvent::KeyPress){
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);
        //qDebug()<<"QEvent::KeyPress"<<QString::number(keyEvent->key(),16)<<keyEvent->text()<<keyEvent->text().isEmpty();
        if (keyEvent->text() != "")
            simpleKey = keyEvent->text();
        if (keyEvent->key() == Qt::Key_Return)
            return true;
        else if (keyEvent->key() == Qt::Key_Escape)
            UIHandler::GlobalMessage(2);
    }
    else if(e->type() == QEvent::KeyRelease){
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);
        //qDebug()<<"QEvent::KeyRelease"<<QString::number(keyEvent->key(),16)<<keyEvent->text()<<keyEvent->key();
        if (/*!simpleKey.isEmpty() &&*/ ( keyEvent->key() >= 0x20)  &&  (keyEvent->key()< 0x5A) )
        {
            sampleCode += simpleKey;
            simpleKey = "";
        }
        timerkey = startTimer(100);
        return true;
    }

    return QApplication::notify(obj,e);
}

void GlobalApplication::timerEvent(QTimerEvent *event){    
    if (event->timerId() == timerid)
    {
        this->killTimer(event->timerId());
        timerid = -1;
        if (UIHandler::get_int_Param("LockScreenOpen") == 1)
            UIHandler::GlobalMessage(1);
    }
    else if(event->timerId() == timerkey)
    {
        killTimer(timerkey);
        timerkey = -1;
        qDebug()<<sampleCode<<"sampleCode";
        if(sampleCode.length() > 5)
        {
            UIHandler::QrCodeUpdate(sampleCode);
        }
        sampleCode = "";
    }
}
