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
    int w = (UIHandler::contentWidth-100)/8;
    int h = 80;
    ui->Data_Menu_lbHeader1->setGeometry(0,0,w-40,h);
    ui->Data_Menu_lbHeader1->setAlignment(Qt::AlignCenter);
    ui->Data_Menu_lbHeader2->setGeometry(w*1-40,0,w,h);
    ui->Data_Menu_lbHeader2->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
    ui->Data_Menu_lbHeader3->setGeometry(w*2-40,0,w+40,h);
    ui->Data_Menu_lbHeader3->setAlignment(Qt::AlignCenter);
    ui->Data_Menu_lbHeader4->setGeometry(w*3,0,w,h);
    ui->Data_Menu_lbHeader4->setAlignment(Qt::AlignCenter);
    ui->Data_Menu_lbHeader5->setGeometry(w*4,0,w,h);
    ui->Data_Menu_lbHeader5->setAlignment(Qt::AlignCenter);
    ui->Data_Menu_lbHeader6->setGeometry(w*5,0,w,h);
    ui->Data_Menu_lbHeader6->setAlignment(Qt::AlignCenter);
    ui->Data_Menu_lbHeader7->setGeometry(w*6,0,w,h);
    ui->Data_Menu_lbHeader7->setAlignment(Qt::AlignCenter);
    ui->Data_Menu_lbHeader8->setGeometry(w*7,0,w,h);
    ui->Data_Menu_lbHeader8->setAlignment(Qt::AlignCenter);
    ui->Data_Menu_lbHeader1->installEventFilter(this);
    ui->Data_Menu_lbHeader2->installEventFilter(this);
    ui->Data_Menu_lbHeader3->installEventFilter(this);
    ui->Data_Menu_lbHeader4->installEventFilter(this);
    ui->Data_Menu_lbHeader5->installEventFilter(this);
    ui->Data_Menu_lbHeader6->installEventFilter(this);
    ui->Data_Menu_lbHeader7->installEventFilter(this);
    ui->Data_Menu_lbHeader8->installEventFilter(this);

    //ui->tableView->setFocusPolicy(Qt::WheelFocus);
    ui->tableView->setGeometry(0,h,UIHandler::contentWidth,UIHandler::contentHeight-h*2);
    ui->tableView->setVerticalScrollMode(QTableView::ScrollMode::ScrollPerPixel);
    QScroller::grabGesture(ui->tableView->viewport(),QScroller::LeftMouseButtonGesture);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->horizontalHeader()->hide();
    ui->tableView->verticalHeader()->setDefaultSectionSize(h);
    ui->tableView->horizontalHeader()->setVisible(false);
    ui->tableView->setModel(&testModel);
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setShowGrid(false);
    ui->tableView->setColumnWidth(0,w);
    ui->tableView->setColumnWidth(1,w);
    ui->tableView->setColumnWidth(2,w);
    ui->tableView->setColumnWidth(3,w);
    ui->tableView->setColumnWidth(4,w);
    ui->tableView->setColumnWidth(5,w);
    ui->tableView->setColumnWidth(6,w);
    ui->tableView->setColumnWidth(7,w);
    ui->tableView->setIconSize(QSize(50,50));

    ui->tableView->verticalScrollBar()->setStyleSheet("QScrollBar:vertical {background:rgb(255,255,255);min-width:50px;}"
        "QScrollBar::handle:vertical {background:rgb(193,193,193);border: 3px solid gray;border-radius:25px;min-height: 100px;min-width:20px;}"
        "QScrollBar::handle:vertical:hover {background:rgb(111,111,111);border: 3px solid gray;border-radius:25px;min-height: 100px;min-width:20px;}");

    ui->tableView->setStyleSheet("alternate-background-color: #f8f8f8;background-color:#ffffff;");

    ui->tableView->horizontalScrollBar()->setVisible(false);

    w = 95;
    ui->Data_Menu_lbPage->setGeometry(UIHandler::contentWidth - 300,ui->tableView->geometry().bottom(),200,h);
    ui->Data_Menu_btnNext->setGeometry(UIHandler::contentWidth - 400,ui->tableView->geometry().bottom()+h/4,w,h/2);
    ui->Data_Menu_btnJump->setGeometry(UIHandler::contentWidth - 500,ui->tableView->geometry().bottom()+h/4,w,h/2);
    ui->Data_Menu_EditPage->setGeometry(UIHandler::contentWidth - 600,ui->tableView->geometry().bottom()+h/4,w,h/2);
    ui->Data_Menu_btnPre->setGeometry(UIHandler::contentWidth - 700,ui->tableView->geometry().bottom()+h/4,w,h/2);
    ui->Data_Menu_btnFilter->setGeometry(UIHandler::contentWidth - 800,ui->tableView->geometry().bottom()+h/4,w,h/2);
    ui->Data_Menu_btnAll->setGeometry(UIHandler::contentWidth - 900,ui->tableView->geometry().bottom()+h/4,w,h/2);
    bAsc = true;
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
     ui->Data_Menu_lbHeader1->setText(tr("序号") + "↓");
     ui->Data_Menu_lbHeader2->setText(tr("是否异常"));
     ui->Data_Menu_lbHeader3->setText(tr("测试项目"));
     ui->Data_Menu_lbHeader4->setText(tr("通道名"));
     ui->Data_Menu_lbHeader5->setText(tr("样本号"));
     ui->Data_Menu_lbHeader6->setText(tr("操作员"));
     ui->Data_Menu_lbHeader7->setText(tr("审核员"));
     ui->Data_Menu_lbHeader8->setText(tr("测试时间"));

     testModel.InitTest();
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

bool DataMenu::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonRelease){
        QString name;
        if(obj->objectName() == "Data_Menu_lbHeader1")
            name = "Testid";
        else if(obj->objectName() == "Data_Menu_lbHeader2")
            name = "ResultType";
        else if(obj->objectName() == "Data_Menu_lbHeader3")
            name = "PanelCode";
        else if(obj->objectName() == "Data_Menu_lbHeader4")
            name = "MachineNo";
        else if(obj->objectName() == "Data_Menu_lbHeader5")
            name = "SampleId";
        else if(obj->objectName() == "Data_Menu_lbHeader6")
            name = "UserName";
        else if(obj->objectName() == "Data_Menu_lbHeader7")
            name = "Checker";
        else if(obj->objectName() == "Data_Menu_lbHeader8")
            name = "TestTime";
        if(!name.isEmpty())
        {
            bAsc = !bAsc;
            testModel.setOrder(name, bAsc);
            testModel.InitTest();
            ui->tableView->update();

            ui->Data_Menu_lbHeader1->setText(tr("序号"));
            ui->Data_Menu_lbHeader2->setText(tr("是否异常"));
            ui->Data_Menu_lbHeader3->setText(tr("测试项目"));
            ui->Data_Menu_lbHeader4->setText(tr("通道名"));
            ui->Data_Menu_lbHeader5->setText(tr("样本号"));
            ui->Data_Menu_lbHeader6->setText(tr("操作员"));
            ui->Data_Menu_lbHeader7->setText(tr("审核员"));
            ui->Data_Menu_lbHeader8->setText(tr("测试时间"));

            QLabel *label = qobject_cast<QLabel *>(obj);
            QString text = label->text();
            if(bAsc)
                label->setText(text + "↓");
            else
                label->setText(text + "↑");
            qDebug()<<"DataMenu::eventFilter"<<obj->objectName()<<bAsc;
            return true;
        }
    }
    return false;
}
