#include "uihandler.h"
#include "upperhandler.h"

#include <QDebug>
#include <QFontMetrics>
#include <QCoreApplication>
#include <QThread>
#include "Module/testmodel.h"
#include "FDx/signalslot.h"

QString UIHandler::DataVersion = "V1.0";

QString UIHandler::t_version = "V1";
QString UIHandler::build_version = "V1.0.1(build20220407)";
QString UIHandler::temp_version = "V0.00";
QString UIHandler::ctrl_version = "V0.00";
QString UIHandler::XmlVersion = "0";

int UIHandler::contentWidth = 1920;
int UIHandler::contentHeight = 1;
int UIHandler::screenHeight = 1200;
int UIHandler::screenWidth = 1920;
int UIHandler::headerHeight = 50;
int UIHandler::footerHeight = 150;
bool UIHandler::debug = false;
bool UIHandler::HiddenFunction = false;
int UIHandler::DataEntry = 0;

QString UIHandler::abNormalInfo;
TestModel* UIHandler::pTestModel = nullptr;

int UIHandler::UserType = 3;
QMap<QString,QString> UIHandler::networkMap;
QString UIHandler::extNetMac;

static UIHandler *uihandler = nullptr;
static UpperHandler *upperHandler = nullptr;
void Respond(const char *buff, int len)
{
    qDebug()<<"UIHandler Respond"<<buff<<len;
}

void updateUiCallBk()
{

}

UIHandler::UIHandler(QObject *parent) : QObject(parent)
{

}

UIHandler *UIHandler::getPtr()
{
    if (uihandler == nullptr)
        uihandler = new UIHandler();
    return uihandler;
}

void UIHandler::Init(){

    if (uihandler == nullptr)
        uihandler = new UIHandler();

    qDebug()<<"upperHandler.Init start";
    if(upperHandler == nullptr)
        upperHandler = UpperHandler::getPtr();
    Fconnect(upperHandler,sig_test,getPtr(),&UIHandler::dealSignal);
    Fconnect(upperHandler,sig_updateUi,getPtr(),&UIHandler::slot_updateUi);
    Fconnect(upperHandler,sig_CamerView,getPtr(),&UIHandler::slot_CamerView);
    Fconnect(upperHandler,sig_testProgess,getPtr(),&UIHandler::slot_testProgress);
    Fconnect(upperHandler,sig_updateTestList,getPtr(),&UIHandler::slot_updateTestList);
    Fconnect(upperHandler,sig_autoFocusNotify,getPtr(),&UIHandler::slot_autoFocusNotify);
    Fconnect(upperHandler,sig_refreshLightValue,getPtr(),&UIHandler::slot_refreshLightValue);
    Fconnect(upperHandler,sig_clearProcess,getPtr(),&UIHandler::slot_clearProcess);
    Fconnect(upperHandler,sig_sendFileResult,getPtr(),&UIHandler::slot_sendFileResult);
    Fconnect(upperHandler,sig_errorSql,getPtr(),&UIHandler::slot_errSql);
    Fconnect(upperHandler,sig_DoorKeyDown,getPtr(),&UIHandler::slot_DoorKeyDown);
    Fconnect(upperHandler,sig_senorUpdate,getPtr(),&UIHandler::slot_senorUpdate);
    Fconnect(upperHandler,sig_tcpStatus,getPtr(),&UIHandler::slot_tcpStatus);
    //upperHandler->setCallBack(Respond);
    upperHandler->Init(q2str(QCoreApplication::applicationDirPath()));

    UpperHandler::Login("admin","123456");
    qDebug()<<"upperHandler.Init end";
    qDebug()<<"Test sendfile start";
//    QString filename = QCoreApplication::applicationDirPath() + "/11.txt";
//    upperHandler->sendFileTCP(filename.toUtf8().data());
//    qDebug()<<"Test sendfile end";

    pTestModel = new TestModel();
    pTestModel->InitTest();

    getNetworkMap();
    //getextNetMac();
    getUserList();
}

void UIHandler::GoPage(PageId id)
{
    emit UIHandler::getPtr()->Go(id);
}

void UIHandler::FooterSetEnabled(bool enable)
{
    emit UIHandler::getPtr()->sig_FooterSetEnabled(enable);
}

void UIHandler::NotifyTitle(QString title, int type)
{
    emit UIHandler::getPtr()->sig_NotifyTitle(title,type);
}

void UIHandler::GlobalMessage(int msg)
{    
    emit UIHandler::getPtr()->GlobalParamMessage(msg);
}

void UIHandler::QrCodeUpdate(QString code)
{
    emit UIHandler::getPtr()->sig_QrCodeChange(code);
}

void UIHandler::Close(){

}

QStringList UIHandler::getLogUser(){

    QStringList list;
    for(auto iter : UpperHandler::getLogUser())
    {
        list<< str2q(iter);
    }
    return  list;
}

int UIHandler::Login(QString name, QString password){
    qDebug()<<name<<password;

    return UpperHandler::Login(q2str(name),q2str(password));
}

int UIHandler::get_int_Param(QString paramname, int MachineNo)
{
    return UpperHandler::get_int_Param(paramname.toStdString(), MachineNo);
}

bool UIHandler::set_int_Param(QString paramname, int value, int MachineNo)
{
    return UpperHandler::set_int_Param(paramname.toStdString(),value, MachineNo);
}

void UIHandler::updata_int_Param(QString paramname, int value, int MachineNo)
{
    return UpperHandler::updata_int_Param(paramname.toStdString(),value, MachineNo);
}

const QString UIHandler::get_string_Param(QString paramname)
{
    return str2q(UpperHandler::get_string_Param(paramname.toStdString()));
}

bool UIHandler::set_string_Param(QString paramname, QString value)
{
    return UpperHandler::set_string_Param(q2str(paramname),q2str(value));
}

void UIHandler::updata_string_Param(QString paramname, QString value)
{
    return UpperHandler::updata_string_Param(q2str(paramname),q2str(value));
}

int UIHandler::getCurrMachineId()
{
    return  UpperHandler::getCurrMachineId();
}

void UIHandler::setCurrMachineId(const int id)
{
    UpperHandler::setCurrMachineId(id);
}

int UIHandler::getPrevMachineId()
{
    return UpperHandler::getPrevMachineId();
}

map<int, string> UIHandler::get_subMac_Name()
{
    return  UpperHandler::get_subMac_Name();
}

map<int, string> UIHandler::get_subMac_Mac()
{
    return  UpperHandler::get_subMac_Mac();
}

map<int, string> UIHandler::get_subMac_PowerMac()
{
    return  UpperHandler::get_subMac_PowerMac();
}

const QString UIHandler::getBoxCode(QString panelCode)
{
    return  str2q(UpperHandler::getBoxCode(q2str(panelCode)));
}

const QString UIHandler::getUser()
{
    return str2q(UpperHandler::getUser());
}

size_t UIHandler::getSubCount()
{
    return UpperHandler::getSubCount();
}

void UIHandler::setStage(const HomeStage stage)
{
    UpperHandler::setStage(stage);
}

HomeStage UIHandler::getStage(int machineNo)
{
    qDebug()<<"UIHandler::getStage"<<machineNo;
    return UpperHandler::getStage(machineNo);
}

void UIHandler::setSampleCode(const QString code)
{
    UpperHandler::setSampleCode(code.toStdString());
}

QString UIHandler::getSampleCode(int machineNo)
{
    return str2q(UpperHandler::getSampleCode(machineNo));
}

void UIHandler::setSampleInfo(const QString info)
{
    UpperHandler::setSampleInfo(info.toStdString());
}

QString UIHandler::getSampleInfo()
{
    return str2q(UpperHandler::getSampleInfo());
}

void UIHandler::setSampleRemark(const QString remark)
{
    UpperHandler::setSampleRemark(remark.toStdString());
}

QString UIHandler::getSampleRemark()
{
    return str2q(UpperHandler::getSampleRemark());
}

void UIHandler::setSampleType(const int type)
{
    UpperHandler::setSampleType(type);
}

int UIHandler::getSampleType()
{
    return UpperHandler::getSampleType();
}

void UIHandler::clearSample(const int machiNo)
{

}

void UIHandler::setMachineCode(const int code)
{
    UpperHandler::setMachineCode(code);
}

QString UIHandler::PanelName(int machineNo)
{
    return str2q(UpperHandler::PanelName(machineNo));
}

QString UIHandler::PanelCode()
{
    return str2q(UpperHandler::PanelCode());
}

QString UIHandler::BoxSerial()
{
    return str2q(UpperHandler::BoxSerial());
}

QString UIHandler::getSampleTypeName(int type)
{
    return str2q(UpperHandler::getSampleTypeName(type));
}

void UIHandler::setPanelName(const QString name)
{
    UpperHandler::setPanelName(name.toStdString());
}

void UIHandler::setPanelCode(const QString code)
{
    UpperHandler::setPanelCode(code.toStdString());
}

void UIHandler::setBoxSerial(const QString serial)
{
    UpperHandler::setBoxSerial(serial.toStdString());
}

void UIHandler::setBoxCode(const QString code)
{
    UpperHandler::setBoxCode(code.toStdString());
}

const StartupData *UIHandler::getStartupData(int machineNo)
{
    return UpperHandler::getStartupData(machineNo);
}

const IdleData *UIHandler::getIdleData(int machineNo)
{
    return UpperHandler::getIdleData(machineNo);
}

const TestProcessData *UIHandler::getTestProcessData(int machineNo)
{
    return UpperHandler::getTestProcessData(machineNo);
}

const ErrorInfo *UIHandler::getErrInfo(int machineNo)
{
    return UpperHandler::getErrInfo(machineNo);
}

void UIHandler::StartupOpenDoor()
{
    UpperHandler::StartupOpenDoor();
}

void UIHandler::IdleSwitchDoor()
{
    UpperHandler::IdleSwitchDoor();
}

QStringList UIHandler::getPanelList()
{

     QStringList list;
     for(auto iter : UpperHandler::getPanelList())
     {
         list<< str2q(iter);
     }
     return  list;
}

int UIHandler::decodeQr(QString code)
{
    return UpperHandler::decodeQr(q2str(code));
}

void UIHandler::ReadyStartTest()
{
    //emit UIHandler::getPtr()->UpdateUI(UpperHandler::getCurrMachineId());;
    UpperHandler::ReadyStartTest();
}

QStringList UIHandler::getSampleTypeArr()
{
    QStringList list;
    for(auto iter : UpperHandler::getSampleTypeArr())
    {
        list<< str2q(iter);
    }
    return  list;
}

void UIHandler::CancelTest(bool initiative)
{
    //emit UIHandler::getPtr()->UpdateUI(UpperHandler::getCurrMachineId());;
    UpperHandler::CancelTest(initiative);
}

void UIHandler::ContinueTest()
{
    UpperHandler::ContinueTest();
}

bool UIHandler::hasTesting()
{
    return  UpperHandler::hasTesting();
}

const list<Test> UIHandler::getTestList()
{
    return  UpperHandler::getTestList();
}

bool UIHandler::delCurrTest(int testId)
{
    return  UpperHandler::delCurrTest(testId);
}

bool UIHandler::checkTest(QString user,int testId)
{
    return  UpperHandler::checkTest(q2str(user),testId);
}

bool UIHandler::uncheckTest(int testId)
{
    return  UpperHandler::uncheckTest(testId);
}

const QString UIHandler::getItemName(int itemid)
{
    return  str2q( UpperHandler::getItemName(itemid));
}

const QString UIHandler::getItemCode(int itemid)
{
    return  str2q( UpperHandler::getItemCode(itemid));
}

int UIHandler::getItemCT(const map<int, TestData> testData, int testid, QString name)
{


//    std::map<int,TestData> _map;

//    Q_FOREACH(int id,testData.keys())
//    {
//        _map[id] = testData[id];
//    }

    return  UpperHandler::getItemCT(testData,testid,q2str(name));


}

const Test UIHandler::getLastTest(int machineNo)
{
    return UpperHandler::getLastTest(machineNo);
}

void UIHandler::setBtTextCenter(QPushButton *pBt, int padding, QString style)
{
    if(pBt == nullptr)
        return;

    QString text = pBt->text();
    text = text.trimmed();
    pBt->setText(text);
    QFontMetrics fontMetrics(pBt->font());
    int nStrWidth = fontMetrics.width(text);
    int nBtWidth = pBt->width();
    int nPadding = (nBtWidth - padding - nStrWidth)/2 + padding;
    QString strStyle = QString("QPushButton{%1padding-left:%2px;}").arg(style).arg(nPadding);
    pBt->setStyleSheet(strStyle);
    qDebug()<<text<<nBtWidth<<nStrWidth<<padding<<nPadding - padding<<nBtWidth-nStrWidth-nPadding;

}

void UIHandler::setLabelWordWrap(QLabel *lb, const QString text)
{
    if(text.isEmpty())
    {
        lb->setText(text);
        return;
    }

    QString res;
    QString target = text;
    QFontMetrics fm(lb->font());
    int nWidth = lb->width() - fm.horizontalAdvance('x');
    int nLength = fm.horizontalAdvance(text);
    int nCount = text.size();

    while(nWidth < nLength)
    {
        int n = (nWidth / (qreal)nLength) * nCount;
        QString temp = target.left(n);
        while(fm.horizontalAdvance(temp) <= nWidth)
        {
            n++;
            temp = target.left(n);
        }
        while(fm.horizontalAdvance(temp) > nWidth)
        {
            n--;
            temp = target.left(n);
        }
        temp.append("\n");
        res.append(temp);
        target.remove(0, n);
        nCount = nCount - n;
        nLength = fm.horizontalAdvance(target);
    }

    res.append(target);
    lb->setText(res);
}


subDoorInfo UIHandler::judgeDoorStatus()
{
    return UpperHandler::judgeDoorStatus();
}

bool UIHandler::getDoorState(int machineNo)
{
    return UpperHandler::getDoorState(machineNo);
}

bool UIHandler::getBoxState(int machineNo)
{
    return UpperHandler::getBoxState(machineNo);
}

int UIHandler::getTestProgress(int machineNo)
{
    return  UpperHandler::getTestProgress(machineNo);
}

QString UIHandler::getValidTime()
{
    return  str2q(UpperHandler::getValidTime());
}

int UIHandler::getSubCurTestId()
{
    return  UpperHandler::getSubCurTestId();
}

void UIHandler::TestResultGoWin(int WinID){
    //TestModel::setCurrTestById(arrMachine[currMachineId]->getCurrTestId());
    if (WinID == 0)
        UpperHandler::setStage(Stage_idle);
    else if (WinID == 1)
        UpperHandler::setStage(Stage_result);
    else if (WinID == 2)
        UpperHandler::setStage(Stage_line);

    emit getPtr()->UpdateUI(getCurrMachineId());
}

void UIHandler::dealTestData(const int testId,map<int, TestData>& testData)
{
//    std::map<int,TestData> _map;

//    Q_FOREACH(int id,testData.keys())
//    {
//        _map[id] = testData[id];
//    }

    UpperHandler::dealTestData(testId,testData);

}

int UIHandler::getItemResultByName(int testid, QString name,const map<int,TestData> testData)
{
    return  UpperHandler::getItemResultByName(testid,q2str(name),testData);
}

void UIHandler::dealSignal(const char *data)
{
    qDebug()<<data;
}

void UIHandler::slot_updateUi(int machineNo)
{
    qDebug()<<"UIHandler::slot_updateUI"<<machineNo;
    emit UpdateUI(machineNo);
    HomeStage stage = getPtr()->getStage(machineNo);
    if(stage == Stage_selfcheck || stage == Stage_error)
    {
        sig_updateMsgIcon(machineNo);
    }
}

void UIHandler::slot_testProgress(int complete, int total, int machineNo)
{
    emit TestProgress(complete,total,machineNo);
    if(machineNo == getCurrMachineId() && (getStage() == Stage_test || getStage() == Stage_looptest))
    {
        int remain = total - complete;
        QString title = QString(tr("正在测试，预计剩余")+QString("%1").arg(remain/60)+tr("分")+QString("%1").arg(remain%60)+tr("秒"));
        NotifyTitle(title,(complete*1000)/total+100);
    }
}

void UIHandler::slot_updateTestList(int machineNo, int testId)
{
    pTestModel->AddLastTest(machineNo,testId);
}

bool UIHandler::LoadFileData(string filename, map<int, std::vector<CPointF> > &posArr, map<int, int> &PosId, list<string> &Name, map<int, int> &CurrItemCT, map<int, int> &CT)
{
    return  UpperHandler::LoadFileData(filename,posArr,PosId,Name,CurrItemCT,CT);
}

void UIHandler::LoadResultData(int Testid, map<int, std::vector<CPointF> > &posArr, map<int, int> &PosId, list<string> &Name, map<int, int> &CurrItemCT, map<int, int> &CT)
{
    UpperHandler::LoadResultData(Testid,posArr,PosId,Name,CurrItemCT,CT);
}

QString UIHandler::getIP()
{
    return str2q(UpperHandler::getIP());
}

QString UIHandler::getWIFIIP()
{
    return str2q(UpperHandler::getWIFIIP());
}

QString UIHandler::getDataBaseIP()
{
    return str2q(UpperHandler::getDataBaseIP());
}

void UIHandler::setDataBaseIP(QString ip)
{
    return UpperHandler::setDataBaseIP(q2str(ip));
}

QMap<QString,QString> UIHandler::getNetworkMap()
{
    networkMap.clear();
    map<string,string> netmap = UpperHandler::getNetworkMap();
    for (auto  it = netmap.begin(); it != netmap.end(); ++it) {
        networkMap[str2q(it->first)] = str2q(it->second);
    }
    return networkMap;
}

void UIHandler::WriteXmlParam(const QString ParamName,const QString value)
{
    UpperHandler::WriteXmlParam(q2str(ParamName), q2str(value));
}

QString UIHandler::ReadXmlParam(QString ParamName, QString defaultValue)
{
    string str = UpperHandler::ReadXmlParam(q2str(ParamName), q2str(defaultValue));
    return str2q(str);
}

void UIHandler::setextNetMac(QString name)
{
    extNetMac = name;
    UpperHandler::setextNetMac(q2str(name));
}

QString UIHandler::getextNetMac()
{
    extNetMac = str2q(UpperHandler::getextNetMac());
    return extNetMac;
}

bool UIHandler::isSetNetName()
{
    if(networkMap.keys().contains(extNetMac) == false || extNetMac.isEmpty())
        return false;

    return true;
}

QList<USERINFO> UIHandler::getUserList()
{
    QList<USERINFO> userList;
    list<USERINFO> user = UpperHandler::getUserList();
    for (auto  it = user.begin(); it != user.end(); ++it) {
        userList<<*it;
    }
    return userList;
}

int UIHandler::getCurrUserListIndex()
{
    return UpperHandler::getCurrUserListIndex();
}

void UIHandler::setCurrUserListIndex(int index)
{
    UpperHandler::setCurrUserListIndex(index);
}

void UIHandler::deleteUser(int index)
{
    UpperHandler::deleteUser(index);
}

bool UIHandler::addUser(QString name, QString password, QString displayName, int type)
{
    bool res = UpperHandler::addUser(q2str(name), q2str(password), q2str(displayName), type);
    if(res)
    {
        getUserList();
    }

    return res;
}

bool UIHandler::updateUser(QString name, QString password, QString displayName, int type)
{
    bool res = UpperHandler::updateUser(q2str(name), q2str(password), q2str(displayName), type);
    if(res)
    {
       getUserList();
    }

    return res;
}

bool UIHandler::isUserNameExist(QString name)
{
    QList<USERINFO> userList = getUserList();
    for (auto it = userList.begin();  it != userList.end(); it++) {
        if(str2q(it->name) == name)
            return true;
    }

    return false;
}

void UIHandler::ActionDo(QString device, int value, int param1, int param2, int param3, int machineNo)
{
    UpperHandler::ActionDo(q2str(device), value, param1, param2, param3, machineNo);
}

void UIHandler::settingParam(QString type, int machineNo)
{
    UpperHandler::settingParam(q2str(type), machineNo);
}

bool UIHandler::isConnected(int machineNo)
{
    return UpperHandler::isConnected(machineNo);
}

void UIHandler::StartView(int id, int light, int machineNo)
{
    UpperHandler::StartView(id, light, machineNo);
}

void UIHandler::StopView(int machineNo)
{
    qDebug()<<"UIHandler::StopView"<<machineNo;
    UpperHandler::StopView(machineNo);
}

QString UIHandler::getStyleSheet(QString key)
{
    QString style = "";
    if(key == "QComboBox"){
        style = "QComboBox{background-color:#D2D2D2;color:black;selection-color:black;}\
            QComboBox QAbstractItemView{border: 0px;height:100px;selection-background-color:#E6E6E6;background-color:#ffffff;font-size:30px;}\
            QComboBox QAbstractItemView::item{min-height:60px;}";
    }

    return style;
}

QList<QString> UIHandler::updateSoft()
{
    QList<QString> qlist;
    list<string> slist = UpperHandler::updateSoft();
    for (auto it:slist) {
        qlist << str2q(it);
    }
    return qlist;
}

bool UIHandler::clearSubTable()
{
    return UpperHandler::clearSubTable();
}

QString UIHandler::getBuildversion()
{
    return build_version;
}

QString UIHandler::getMac()
{
    if(networkMap.keys().contains(extNetMac) == false || extNetMac.isEmpty())
        return networkMap[extNetMac];

    return networkMap[0];
}

bool UIHandler::AddSubMachine(string mac, int no, string name, string powermac)
{
    return UpperHandler::AddSubMachine(mac, no, name, powermac) == 0;
}

int UIHandler::modifySubMachine(QString oldmac, QString mac, int no, QString name, QString powermac)
{
    return UpperHandler::modifySubMachine(q2str(oldmac), q2str(mac), no, q2str(name), q2str(powermac));
}

QString UIHandler::getTwoBtnMsg()
{
    return  str2q(UpperHandler::getTwoBtnMsg());
}

bool UIHandler::clearMsg()
{
    return UpperHandler::clearMsg();
}

bool UIHandler::resetQrInfo()
{
    return UpperHandler::resetQrInfo();
}

bool UIHandler::delSubMachine(QString mac)
{
    return UpperHandler::delSubMachine(q2str(mac));
}

map<string, string> UIHandler::getBoardcastMac()
{
    return UpperHandler::getBoardcastMac();
}

map<string, string> UIHandler::getPowerMac()
{
    return UpperHandler::getPowerMac();
}

list<WifiItem> UIHandler::getWifiList()
{
    return UpperHandler::getWifiList();
}

void UIHandler::refreshWifi()
{
    UpperHandler::refreshWifi();
}

void UIHandler::disconnectWifi()
{
    UpperHandler::disconnectWifi();
}

void UIHandler::connectWifi(QString account, QString password)
{
    UpperHandler::connectWifi(account.toUtf8(), password.toUtf8());
}

QString UIHandler::getWifiPassword(QString name)
{
    return str2q(UpperHandler::getWifiPassword(q2str(name)));
}

void UIHandler::setNetIp(QString ip, QString mask, QString gate)
{
   UpperHandler::setNetIp(q2str(ip), q2str(mask), q2str(gate));
}

void UIHandler::slot_CamerView(string imgstr, int machineNo)
{
    //cout<<"UIHandler::slot_CamerView "<<imgstr.length()<<endl;
    emit sig_CamerView(imgstr, machineNo);
}

void UIHandler::slot_autoFocusNotify(int status, int value, int machineNo)
{
    emit sig_autoFocusNotify(status, value, machineNo);
}

QString UIHandler::getDisplayUser()
{
    return str2q(UpperHandler::getDisplayUser());
}

void UIHandler::setDebugMode(bool b)
{
    UpperHandler::setDebugMode(b);
}

void UIHandler::UpdataTempParam(int machineNo)
{
    UpperHandler::UpdataTempParam(machineNo);
}

list<string> UIHandler::onePointTestList(bool language)
{
    return UpperHandler::onePointTestList(language);
}

void UIHandler::slot_refreshLightValue(int lightvalue, int machineNo)
{
    emit sig_refreshLightValue(lightvalue, machineNo);
}

void UIHandler::slot_clearProcess(int machineNo)
{
    emit sig_clearProcess(machineNo);
}

list<logdata> UIHandler::getLogDataList(int index)
{
    return UpperHandler::getLogDataList(index);
}

void UIHandler::DebugMedianMachine(int param1, int param2, int param3)
{
    UpperHandler::DebugMedianMachine(param1,param2,param3);
}

void UIHandler::updatetimezone(int index)
{
    UpperHandler::updatetimezone(index);
}

bool UIHandler::setTime(QString time)
{
    return UpperHandler::setTime(q2str(time));
}

void UIHandler::setTimezoneopen(bool bopen)
{
    UpperHandler::setTimezoneopen(bopen);
}

void UIHandler::sendFile(QString pathname, QString filename, SendFileCallBack fun, int machineNo)
{
    UpperHandler::sendFile(q2str(pathname),q2str(filename), fun, machineNo);
}

void UIHandler::PowerOff()
{
    UpperHandler::PowerOff();
}

void UIHandler::setLogin(bool b)
{
    UpperHandler::setLogin(b);
}

bool UIHandler::getLogin()
{
    return UpperHandler::getLogin();
}

int UIHandler::getUserType(QString name)
{
    return UpperHandler::getUserType(q2str(name));
}

void UIHandler::setLedBlink(int machineNo, int time)
{
    qDebug()<<"UIHandler::setLedBlink"<<machineNo<<time;
    UpperHandler::setLedBlink(machineNo, time);
}

QList<int> UIHandler::getHasBoxNoList()
{
    QList<int> qlist;
    list<int> slist = UpperHandler::getHasBoxNoList();
    for (auto it:slist) {
        qlist << it;
    }
    return qlist;
}

vector<WholeMachine_T *> UIHandler::getWholeMacArr()
{
    return UpperHandler::getWholeMacArr();
}

void UIHandler::UpdateState(StateId id)
{
    emit uihandler->State(id);
}

void UIHandler::slot_sendFileResult(int param, int machineNo)
{
    emit sig_sendFileResult(param, machineNo);
}

void UIHandler::slot_errSql(int machineNo)
{
    emit sig_errorSql(machineNo);
}

QStringList UIHandler::getLoopTestList(bool language)
{
    QStringList list;
    for(auto iter : UpperHandler::getLoopTestList(language))
    {
        list<< str2q(iter);
    }
    return  list;
}

void UIHandler::Looptest(QString device, int MachineNo)
{
    UpperHandler::Looptest(q2str(device), MachineNo);
}

void UIHandler::CancelLoopTest(int MachineNo)
{
    UpperHandler::CancelLoopTest(MachineNo);
}

void UIHandler::slot_DoorKeyDown(int machineNo)
{
    emit sig_DoorKeyDown(machineNo);
}

void UIHandler::slot_senorUpdate(int type, int machineNo)
{
    emit UpdateUI(machineNo);
    emit sig_senorUpdate(type,machineNo);
}

void UIHandler::slot_tcpStatus(int status, int machineNo)
{
    emit UpdateUI(machineNo);
    emit sig_tcpStatus(status,machineNo);
}
