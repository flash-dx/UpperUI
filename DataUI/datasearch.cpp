#include "datasearch.h"
#include "ui_datasearch.h"
#include <QPainter>
#include <QDebug>
#include "uihandler.h"

DataSearch::DataSearch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataSearch)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground,true);

    ui->combox_panelCode->addItem(tr("全部"));
    ui->combox_panelCode->addItems(UIHandler::pTestModel->getTestPanelNameList());
    ui->combox_sampleid->addItem(tr("全部"));
    ui->combox_sampleid->addItems(UIHandler::pTestModel->getTestSampleIdList());
    ui->combox_SampleType->addItem(tr("全部"));
    ui->combox_SampleType->addItems(UIHandler::pTestModel->getTestSampleTypeNameList());
    ui->combox_MachineNo->addItem(tr("全部"));
    ui->combox_MachineNo->addItems(UIHandler::pTestModel->getTestMachineNoList());
    ui->combox_checker->addItem(tr("全部"));
    ui->combox_checker->addItems(UIHandler::pTestModel->getTestCheckerList());
    ui->combox_user->addItem(tr("全部"));
    ui->combox_user->addItems(UIHandler::pTestModel->getTestUserList());

    QString type = "QWidget{font: 18px '宋体';background-color: transparent;}"\
                   "QPushButton {border-image: url(:/images/btnbk.png);}"\
                   "QLineEdit {font-size:20px;background-color:#E6E6E6;}"\
                   "QComboBox {font-size:20px;background-color:#E6E6E6;}";
    setStyleSheet(type);
    type = "font: 22px '宋体';";
    ui->btn_ok->setStyleSheet(type);
    ui->btn_Cancel->setStyleSheet(type);
    type = "color:white;font: 38px '华文中宋';";
    ui->lb_logo->setStyleSheet(type);
}

DataSearch::~DataSearch()
{
    delete ui;
}

void DataSearch::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/images/datasearchbg.png"));
}

void DataSearch::showEvent(QShowEvent *event)
{
    Init();
}

void DataSearch::on_btn_Cancel_clicked()
{
    close();
}

void DataSearch::Init()
{
    ui->combox_panelCode->setCurrentIndex(0);
    ui->combox_sampleid->setCurrentIndex(0);
    ui->combox_SampleType->setCurrentIndex(0);
    ui->combox_MachineNo->setCurrentIndex(0);
    ui->combox_user->setCurrentIndex(0);
    ui->combox_checker->setCurrentIndex(0);

    ui->radioButton_resultAll->setChecked(true);
    ui->radioButton_resultValid->setChecked(false);
    ui->radioButton_resultInvalid->setChecked(false);
    ui->dateTimeEdit->setDate(QDate(2020,1,1));
    ui->dateTimeEdit_2->setDateTime(QDateTime::currentDateTime());
    searchFilter = "";
}

void DataSearch::on_radioButton_resultAll_clicked()
{
    ui->radioButton_resultValid->setChecked(false);
    ui->radioButton_resultInvalid->setChecked(false);
}

void DataSearch::on_radioButton_resultValid_clicked()
{
    ui->radioButton_resultAll->setChecked(false);
    ui->radioButton_resultInvalid->setChecked(false);
}

void DataSearch::on_radioButton_resultInvalid_clicked()
{
    ui->radioButton_resultAll->setChecked(false);
    ui->radioButton_resultValid->setChecked(false);
}

void DataSearch::on_btn_ok_clicked()
{
    QString temp;
    searchFilter = QString("TestTime>='%1' AND TestTime<'%2'").arg(ui->dateTimeEdit->date().toString("yyyy-MM-dd")).arg(ui->dateTimeEdit_2->date().addDays(1).toString("yyyy-MM-dd"));
    //1
    temp = ui->combox_panelCode->currentText();
    if(temp == tr("空")){
        searchFilter += " AND panelCode=''";
    }
    else if(temp != tr("全部")){
        searchFilter += QString(" AND panelCode LIKE '%%1%'").arg(UIHandler::pTestModel->getTestPanelCode(temp));
    }
    //2
    temp = ui->combox_sampleid->currentText();
    if(temp == tr("空")){
        searchFilter += " AND sampleid=''";
    }
    else if(temp != tr("全部")){
        searchFilter += QString(" AND sampleid LIKE '%%1%'").arg(temp);
    }
    //3
    temp = ui->combox_SampleType->currentText();
    if(temp != tr("全部")){
        searchFilter += QString(" AND SampleType=%1").arg(UIHandler::pTestModel->getTestSampleType(temp));
    }
    //4
    temp = ui->combox_MachineNo->currentText();
    if(temp != tr("全部")){
        searchFilter += QString(" AND MachineNo=%1").arg(temp);
    }
    //5
    temp = ui->combox_user->currentText();
    if(temp != tr("全部")){
        searchFilter += QString(" AND UserName='%1'").arg(temp);
    }
    //6
    temp = ui->combox_checker->currentText();
    if(temp != tr("全部")){
        searchFilter += QString(" AND Checker='%1'").arg(temp);
    }
    //7
    if(ui->radioButton_resultValid->isChecked())
        searchFilter += QString(" AND ResultType>=3");
    else if(ui->radioButton_resultInvalid->isChecked())
        searchFilter += QString(" AND (ResultType<3 OR ResultType IS NULL)");

    accept();
}

void DataSearch::on_btn_all_clicked()
{
    Init();
}
