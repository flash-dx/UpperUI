#include "testloop.h"
#include "ui_testloop.h"
#include "../uihandler.h"
#include <QListView>
#include "components/onebtnmessagebox.h"

static TestLoop *winptr = nullptr;

TestLoop *TestLoop::getPtr()
{
    if (winptr == nullptr)
        winptr = new TestLoop;
    return winptr;
}

TestLoop::TestLoop(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestLoop)
{
    ui->setupUi(this);

    int btnW = 299;
    int btnH = 106;
    int btnRight = 100;
    int btnBottom = 30;
    int btnLeft = UIHandler::contentWidth - btnW - btnRight;
    int btnTop = UIHandler::contentHeight - btnBottom - btnH;
    int btnAdd = 20;

    ui->pButton_machine_back->setGeometry(btnLeft, btnTop, btnW, btnH);

    ui->comboBox_panel->setStyleSheet(UIHandler::getStyleSheet("QComboBox"));
    ui->comboBox_machine->setView(new QListView());
    ui->comboBox_machine->setGeometry(UIHandler::contentWidth - 200,10,200,75);
    ui->comboBox_machine->setStyleSheet(UIHandler::getStyleSheet("QComboBox"));

    caliMachineNo = -1;
    setStyleSheet("background-color:#f5f5f5;");
}

TestLoop::~TestLoop()
{
    delete ui;
}

void TestLoop::showEvent(QShowEvent *event){
    Q_UNUSED(event);
    ui->retranslateUi(this);

    QMap<int, QString> list;
    for(auto it : UIHandler::getPtr()->get_subMac_Name()) {
       list[it.first] = str2q(it.second);
    }
    ui->comboBox_machine->blockSignals(true);
    ui->comboBox_machine->clear();
    if( list.count() > 0){
        ui->comboBox_machine->addItems(list.values());
        //        if(caliMachineNo == -1)
        //            caliMachineNo = list.firstKey();
        caliMachineNo = UIHandler::getCurrMachineId();
        ui->comboBox_machine->setCurrentText(list.value(caliMachineNo));
    }
    ui->comboBox_machine->blockSignals(false);
    load_data();


    UIHandler::setBtTextCenter(ui->pButton_machine_back, 48,"background-image: url(:/images/back.png);text-align:left;padding-bottom:10px;");

    UIHandler::NotifyTitle("setup_testloop",5);
}

void TestLoop::hideEvent(QHideEvent *event){
    Q_UNUSED(event);
}
/*X
void TestLoop::slot_sequenceFinish(SequenceResult result, int machineNo)
{
    if(result == SequenceResult::Result_LoopTest_finish){
        OneBtnMessageBox::display(tr("耐久性测试完成！"),tr("返回"));
        goto Finish;
    }
    else if(result == SequenceResult::Result_CannelTest_ok)
    {
        OneBtnMessageBox::display(tr("耐久性测试停止！"),tr("返回"));
        goto Finish;
    }

    return;

Finish:
    UIHandler::getPtr()->NotifyTitle("loop_test", 5);
    enableButton(true);
    disconnect(UIHandler::getPtr(),&UIHandler::SequenceFinish,this,&TestLoop::slot_sequenceFinish);
}
*/
void TestLoop::on_pButton_machine_back_clicked()
{
     UIHandler::GoPage(UIHandler::PageId::Page_Setup_Menu);
}

void TestLoop::on_pButton_enter_test_clicked()
{
    QString value = QString("%1^%2").arg(ui->comboBox_panel->currentText()).arg(ui->spinBox_test_count->value());
    UIHandler::getPtr()->Looptest(value, caliMachineNo);
}

void TestLoop::on_pButton_exit_test_clicked()
{
    UIHandler::CancelLoopTest(caliMachineNo);
}

void TestLoop::enableButton(bool en)
{
    ui->comboBox_panel->setEnabled(en);
    ui->spinBox_test_count->setEnabled(en);
    ui->pButton_enter_test->setEnabled(en);
}

void TestLoop::on_comboBox_machine_currentIndexChanged(int index)
{
    if(index >= 0)
    {
        map<int, string> mac = UIHandler::get_subMac_Name();
        for(auto it:mac) {
           if(str2q(it.second) == ui->comboBox_machine->currentText())
           {
               caliMachineNo = it.first;
           }
        }
        qDebug()<<"TestLoop caliMachineNo"<<caliMachineNo;
        load_data();
    }
}

void TestLoop::on_spinBox_test_count_valueChanged(int arg1)
{
    qDebug()<<"spinBox_test_count"<<arg1<<999;
}

void TestLoop::load_data()
{
    int language = UIHandler::get_int_Param("LanguageCode");
    ui->comboBox_panel->clear();
    ui->comboBox_panel->addItems(UIHandler::getLoopTestList(language));
}
