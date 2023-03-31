#ifndef PROGRESSBUTTON_H
#define PROGRESSBUTTON_H

#include <QPushButton>

class ProgressButton : public QPushButton {
    Q_OBJECT

    void paintEvent(QPaintEvent* event) override;
public:
    explicit ProgressButton(QWidget* parent); 
    void changeValue(int x);
    void setType();
    void setBottomColor(bool flag);
    void changeBkColor();
signals:
    void sig_finished();
private:
     bool m_bChecked;
     int m_value = 0;

 };

#endif // PROGRESSBUTTON_H
