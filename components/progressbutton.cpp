#include "progressbutton.h"

#include <QBitmap>
#include <QPainter>
#include <QProxyStyle>
#include <QTimer>
class QtPushButtonStyleProxy : public QProxyStyle
{
public:
    QtPushButtonStyleProxy()
     : QProxyStyle()
    {
    }

    virtual void drawItemText(QPainter *painter, const QRect &rect,
     int flags, const QPalette &pal, bool enabled,
     const QString &text, QPalette::ColorRole textRole) const
    {
     flags |= Qt::TextWordWrap;
     QProxyStyle::drawItemText(painter, rect, flags, pal, enabled, text, textRole);
    }

private:
    Q_DISABLE_COPY(QtPushButtonStyleProxy)
};
void ProgressButton::paintEvent(QPaintEvent* event) {
//    if(m_value < 1 || m_value > 99) {
//        QPushButton::paintEvent(event);
//        return;
//    }
    QColor whiteColor(255, 255, 255);
    QColor backColor(43, 43, 43);
    QColor proColor(0, 222, 167);
    QColor btmColor(255, 0, 0);

    QRect IconRect(0,0,60,60);

    QRect tempRect(60,0,rect().width()-60,60);

    QPainter pt(this);
    pt.fillRect(tempRect,whiteColor);
    pt.setPen(proColor);
    pt.setBrush(QBrush(proColor));
    if(m_value > 0 &&  m_value <= 100)
    {
         pt.drawRect(60,0,(width()-IconRect.width())*m_value/100,height()-1);
    }


    pt.setPen(Qt::black);
    pt.drawText(tempRect,Qt::AlignCenter,text());
    QPixmap pixmap(":/images/ud.png");
    pt.drawPixmap(IconRect,pixmap);

    if(m_bChecked)
    {
        QPainter ptLine(this);
        ptLine.setPen(btmColor);
        ptLine.drawLine(0,height()-1,width(),height()-1);
    }
}

ProgressButton::ProgressButton(QWidget* parent) : QPushButton(parent){

    m_bChecked = false;
    m_value =0 ;
    setStyle(new QtPushButtonStyleProxy());
}

void ProgressButton::changeValue(int x)
{
    if(x <= 5)
        m_value = 5;
    else
        m_value = x;
    update();
}

void ProgressButton::setBottomColor(bool flag)
{
    m_bChecked = flag;
    update();
}

void ProgressButton::changeBkColor()
{
    //setStyleSheet("");
}
