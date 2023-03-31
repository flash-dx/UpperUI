#include "dataline.h"
#include "ui_dataline.h"
#include <QtCharts/QLineSeries>

#include "uihandler.h"
#include "Module/testmodel.h"
#include "HomeUI/homemain.h"
#include "list"
using namespace std;
static DataLine *winptr = nullptr;
static DataLine *winptr2 = nullptr;
static int winIndex = 0;

DataLine *DataLine::getPtr(int ptrIndex)
{
    winIndex = ptrIndex;
    if (ptrIndex == 1){
        if (winptr2 == nullptr)
            winptr2 = new DataLine;
        return winptr2;
    }

    if (winptr == nullptr)
        winptr = new DataLine;
    return winptr;
}

DataLine::DataLine(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataLine)
{
    ui->setupUi(this);
    int contentWidth = UIHandler::contentWidth;
    int contentHeight = UIHandler::contentHeight;
    if (winIndex == 1){
        contentWidth = UIHandler::screenWidth;
        contentHeight = UIHandler::contentHeight*7/8;
    }
    chart = new QChart;
    axisX = new QValueAxis;
    axisX->setRange(0,50);
    QFont LabelFont;
    LabelFont.setPixelSize(30);
    axisX->setLabelsFont(LabelFont);
    //axisX->setTitleText("cycle");
    axisX->setTickCount(6);
    axisX->setMinorTickCount(9);
    axisX->setLabelFormat("%d");
    axisY = new QCategoryAxis;
    axisY->setLabelsFont(LabelFont);
    axisY->setRange(-10,50);
    //axisY->setTitleText("brightness");
    axisY->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
    chart->addAxis(axisX,Qt::AlignBottom);
    chart->addAxis(axisY,Qt::AlignLeft);
    chartView = new QChartView(chart,this);

    chartView->setGeometry(contentWidth/3,contentHeight/8,contentWidth*2/3,contentHeight*2/3);
    chart->setTitleFont(QFont("黑体",40));
    //chart->legend()->setVisible(false);
    ui->btBack->setGeometry(contentWidth-299-80,contentHeight-106-40,299,106);

    setStyleSheet("background-color:#ffffff;");
}

DataLine::~DataLine()
{
    delete ui;
}

void DataLine::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    int yPos = 200;
    int ySpacing = 40;
    if(winIndex == 1)
    {
        yPos = 200;
        ySpacing = 35;
    }


    QPainter paint(this);
    paint.setFont(QFont("黑体",20));
    paint.drawText(130,yPos,tr("靶标"));
    paint.drawText(360,yPos,tr("Ct"));
    QString itemName = TestModel::getCurrItemName();
    int testid = TestModel::getCurrTestId();
    TestData *data = TestModel::getTestData(testid);
    if (data == nullptr)
        return;


    QBrush oldBrush = paint.brush();

    int lineNo = 0;

    for(auto it1:data->ItemidOfName[q2str(itemName)]){

        //GlobalParam::ItemCode[itemid]);
        for(auto it2: data->PosId){
            if (/*data->PosId[it2.first*/it2.second == (it1)){
                paint.drawText(130,yPos+50+lineNo*ySpacing,UIHandler::getItemCode(it1));
                if (data->CT[it2.first] > 0)
                    paint.drawText(360,yPos+50+lineNo*ySpacing,QString::number(static_cast<double>(data->CT[it2.first])/10));
                else
                    paint.drawText(360,yPos+50+lineNo*ySpacing,"ND");

                QString seriesName = QString("P%1").arg(it2.first);
                foreach (QAbstractSeries *series, chart->series()){
                    if (series->name() == seriesName){
                        QLineSeries *line = static_cast<QLineSeries *>(series);
                        QBrush *brush = new QBrush(line->color());
                        paint.fillRect(440,yPos+50+lineNo*ySpacing-20,20,20,*brush);
                        break;
                    }
                }
                lineNo++;
            }
        }
    }
    paint.setBrush(oldBrush);
}

void DataLine::showEvent(QShowEvent *event){
    Q_UNUSED(event);

    UIHandler::NotifyTitle("dataline",5);

    if (winIndex == 1){
        connect(HomeMain::getPtr(),SIGNAL(sig_UpdateUI()),this,SLOT(updateUI()));
    }
    else {
        updateUI();
    }
}

void DataLine::hideEvent(QHideEvent *event){
    Q_UNUSED(event);
    foreach (QString label, axisY->categoriesLabels())
        axisY->remove(label);
    foreach (QLabel *label, list)
        delete label;
    list.clear();
    foreach (QPushButton *btn, btnlist)
        delete btn;
    btnlist.clear();
}

void DataLine::updateChart()
{
    chart->setTitle(TestModel::getCurrItemName());
    chart->removeAllSeries();
    axisY->setRange(-10,50);
    QString itemName = TestModel::getCurrItemName();
    int testid = TestModel::getCurrTestId();
    int ct = TestModel::getItemCT(testid,itemName);
    qDebug()<<"DataLine showEvent testid="<<testid<<"ct="<<ct<<"itemName"<<itemName;
    axisY->append(QString::number(ct),ct);
    ui->btBack->setText(tr("返回"));
    TestData *data = TestModel::getTestData(testid);
    if (data == nullptr)
        return;
    for(auto it : data->PosId){
        int itemid = it.second/*data->PosId[it.first]*/;
        if (UIHandler::getItemName(itemid) == itemName){
            QLineSeries *line = new QLineSeries;
            line->setName(QString("P%1").arg(it.first));
            chart->addSeries(line);
            line->attachAxis(axisX);
            line->attachAxis(axisY);

            for (size_t i = 0; i < data->posArr[it.first].size(); i++){
                if (data->posArr[it.first][i].y() > axisX->max() - 10)
                    axisY->setMax(data->posArr[it.first][i].y()+10);
                line->append(data->posArr[it.first][i].x(),data->posArr[it.first][i].y());
            }
        }
    }

}

void DataLine::on_btBack_clicked()
{
    if (winIndex == 1)
        UIHandler::TestResultGoWin(1);
    else
        UIHandler::GoPage(UIHandler::PageId::Page_Data_View);
}

void DataLine::on_Item_clicked()
{
    qDebug()<<"on_Item_clicked"<<focusWidget()->objectName();
    TestModel::setCurrItemName(focusWidget()->objectName());
    foreach (QPushButton *pBtn, btnlist)
    {
        if(pBtn->objectName() == TestModel::getCurrItemName())
        {
            pBtn->setStyleSheet("border-radius:10px;background-color:#3584E4;color:#FFFFFF");
        }
        else
        {
            pBtn->setStyleSheet("border-radius:10px;background-color:#cccccc;color:#000000");
        }
    }

    foreach (QString label, axisY->categoriesLabels())
        axisY->remove(label);

    foreach (QLabel *label, list)
        delete label;
    list.clear();

    updateChart();
    update();
}

void DataLine::updateUI()
{

    foreach (QPushButton *btn, btnlist)
        delete btn;
    btnlist.clear();

    updateChart();

    QStringList itemName = TestModel::getTestName(TestModel::getCurrTestId());
    itemName.prepend(UIHandler::getItemName(2));

    int dispCount = 7;

    int tempWidth =260;
    int tempHeight =60;
    int xSpacing =10;
    int ySpacing =10;

    if (winIndex == 1)
    {
        tempWidth = tempWidth * 5/6;
        tempHeight = tempHeight*7/8;
    }


    for (int i = 0; i < itemName.size(); i++){
        QPushButton *btn = new QPushButton(itemName[i], this);
        btn->setGeometry(20+(tempWidth+xSpacing)*int(i%7),10 + (tempHeight+ySpacing)*int(i/7),tempWidth,tempHeight);
        btn->setObjectName(itemName[i]);
        btn->setText(itemName[i]);
        if(itemName[i] == TestModel::getCurrItemName())
        {
            btn->setStyleSheet("border-radius:10px;background-color:#3584E4;color:#FFFFFF;font:bold 15px");
        }
        else
        {
            btn->setStyleSheet("border-radius:10px;background-color:#cccccc;color:#000000");
        }
        connect(btn,&QPushButton::clicked,this,&DataLine::on_Item_clicked);
        btn->show();
        btnlist.append(btn);
    }
}
