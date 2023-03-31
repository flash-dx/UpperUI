#ifndef CQRCODEINFO_H
#define CQRCODEINFO_H

#include <QWidget>

namespace Ui {
class CQrCodeInfo;
}

class CQrCodeInfo : public QWidget
{
    Q_OBJECT
private:
    explicit CQrCodeInfo(QWidget *parent = nullptr);
public:
    static CQrCodeInfo *getPtr();
    ~CQrCodeInfo();
    void display(int  result);

protected:
    void paintEvent(QPaintEvent *event);
private slots:
    void on_pBtn_Confirm_clicked();
    void slot_flushData(int result);

private:
    Ui::CQrCodeInfo *ui;
    int m_Type;
};

#endif // CQRCODEINFO_H
