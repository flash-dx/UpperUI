#include "datamenu.h"
#include "ui_datamenu.h"
#include "uihandler.h"

#include <QScroller>
#include <QScrollBar>

#include <Module/testmodel.h>

static DataMenu *winptr = nullptr;

DataMenu::DataMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataMenu)
{
    ui->setupUi(this);
    ui->Data_Menu_lbHeader1->setGeometry(0,0,120,80);
    ui->Data_Menu_lbHeader1->setAlignment(Qt::AlignCenter|Qt::AlignRight);
    ui->Data_Menu_lbHeader2->setGeometry(150,0,150,80);
    ui->Data_Menu_lbHeader2->setAlignment(Qt::AlignCenter);
    ui->Data_Menu_lbHeader3->setGeometry(300,0,500,80);
    ui->Data_Menu_lbHeader3->setAlignment(Qt::AlignCenter);
    ui->Data_Menu_lbHeader4->setGeometry(800,0,300,80);
    ui->Data_Menu_lbHeader4->setAlignment(Qt::AlignCenter);
    ui->Data_Menu_lbHeader5->setGeometry(1100,0,200,80);
    ui->Data_Menu_lbHeader5->setAlignment(Qt::AlignCenter);
    ui->Data_Menu_lbHeader6->setGeometry(1300,0,250,80);
    ui->Data_Menu_lbHeader6->setAlignment(Qt::AlignCenter);
    ui->Data_Menu_lbHeader7->setGeometry(1550,0,250,80);
    ui->Data_Menu_lbHeader7->setAlignment(Qt::AlignCenter);

    //ui->tableView->setFocusPolicy(Qt::WheelFocus);
    ui->tableView->setGeometry(0,100,UIHandler::contentWidth,UIHandler::contentHeight-100);
    ui->tableView->setVerticalScrollMode(QTableView::ScrollMode::ScrollPerPixel);
    QScroller::grabGesture(ui->tableView->viewport(),QScroller::LeftMouseButtonGesture);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->horizontalHeader()->hide();
    ui->tableView->verticalHeader()->setDefaultSectionSize(100);
    ui->tableView->horizontalHeader()->setVisible(false);
    ui->tableView->setModel(UIHandler::pTestModel);
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setShowGrid(false);
    ui->tableView->setColumnWidth(0,200);
    ui->tableView->setColumnWidth(1,100);
    ui->tableView->setColumnWidth(2,500);
    ui->tableView->setColumnWidth(3,300);
    ui->tableView->setColumnWidth(4,200);
    ui->tableView->setColumnWidth(5,200);
    ui->tableView->setColumnWidth(6,370);
    ui->tableView->setIconSize(QSize(50,50));

    ui->tableView->verticalScrollBar()->setStyleSheet("QScrollBar:vertical {background:rgb(255,255,255);min-width:50px;}"
        "QScrollBar::handle:vertical {background:rgb(193,193,193);border: 3px solid gray;border-radius:25px;min-height: 100px;min-width:20px;}"
        "QScrollBar::handle:vertical:hover {background:rgb(111,111,111);border: 3px solid gray;border-radius:25px;min-height: 100px;min-width:20px;}");

    ui->tableView->setStyleSheet("alternate-background-color: #f8f8f8;background-color:#ffffff;");

    ui->tableView->horizontalScrollBar()->setVisible(false);
}

DataMenu::~DataMenu()
{
    delete ui;
}

DataMenu *DataMenu::getPtr()
{
    if (winptr == nullptr)
        winptr = new DataMenu;
    return winptr;
}

void DataMenu::showEvent(QShowEvent *event){
    Q_UNUSED(event);

     ui->retranslateUi(this);
     ui->Data_Menu_lbHeader1->setText(tr("序号"));
     ui->Data_Menu_lbHeader2->setText(tr("是否异常"));
     ui->Data_Menu_lbHeader3->setText(tr("测试项目"));
     ui->Data_Menu_lbHeader4->setText(tr("样本号"));
     ui->Data_Menu_lbHeader5->setText(tr("操作员"));
     ui->Data_Menu_lbHeader6->setText(tr("审核员"));
     ui->Data_Menu_lbHeader7->setText(tr("测试时间"));

     UIHandler::NotifyTitle("datamenu",5);
}

void DataMenu::on_tableView_clicked(const QModelIndex &index)
{
    TestModel::setCurrTestByIndex(index.row());
    UIHandler::setDataEntry(0);
    if (TestModel::getTestResultType(TestModel::getCurrTestId()) >= 2)
      UIHandler::GoPage(UIHandler::PageId::Page_Data_View);
    else
      UIHandler::GoPage(UIHandler::PageId::Page_Data_InvalidView);
}
