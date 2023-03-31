#ifndef TIMESLIDER_H
#define TIMESLIDER_H

#include <QWidget>
#include <QMouseEvent>
#include <QColor>
#include<QPainter>
#include<QTime>
#include<QTimer>

class TimeScrollBar : public QWidget
{
    Q_OBJECT
public:
    enum ScrollType{
      VERTICAL = 1,
      HORIZONTAL
    };
    enum ColorType{
        BACKHROUND = 1,
        LINE,
        CURRENTTEXT,
        DISABLETEXT
    };
    bool m_bAmPm;
public:
    explicit TimeScrollBar(QWidget *parent = 0, ScrollType nType = VERTICAL);
    ~TimeScrollBar();
public:
    void setColor(QColor &pColor, ColorType nType = CURRENTTEXT);
    inline int getValue() { return m_nCurrentValue;}
    inline void setValue(int nValue) { m_nCurrentValue = nValue;}
    inline void setStep(int nStep) { m_nStep = nStep;}
    inline void setDevice(int nDevice) {m_nDevice = nDevice;}
    inline void setScrollType(ScrollType nType) {m_nType = nType;}
    inline void setRang(int nMin, int nMax)
    {
        m_nMin = nMin;
        m_nMax = nMax;
        m_nCurrentValue = m_nCurrentValue > m_nMax ? m_nMax : m_nCurrentValue;
        m_nCurrentValue = m_nCurrentValue < m_nMin ? m_nMin : m_nCurrentValue;
    }

protected:
    void wheelEvent(QWheelEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent* event);

private:
    void paintBackground(QPainter* pPainter);
    void paintLine(QPainter* pPainter);
    void paintText(QPainter* pPainter, int nValue, int nOffSet, int nFontSize);

signals:
    void signal_currentValueChange(int nValue, QWidget* pWidget);

private slots:
    void slot_ShowAction();

private:
    int m_nCurrentValue;
    int m_nOffSet;        	//偏离值
    int m_nMax;           	//滚动的最大值
    int m_nMin;           	//滚动的最小值
    int m_nMousePos;		//鼠标点击的位置
    int m_nDevice;      	//显示的数量
    int m_nStep;        	//滚动的步长
    ScrollType  m_nType;    //垂直还是水平
    QColor  m_cBackground;	//背景颜色
    QColor  m_cCurrentText;	//当前值颜色
    QColor  m_cDisableText;	//其他字体颜色
    QColor  m_cLine;		//线条颜色
    QColor  m_cSelBackground;//选中的文字背景

    QPoint m_LMousePressPoint;
    QTime  m_LMousePresstime;
    QTimer m_ActionTimer;
    int    m_ActionDirect;
};


#endif // TIMESLIDER_H
