#include "testmodel.h"

#include<QDebug>
#include<QFont>
#include<QIcon>

#include <QCoreApplication>
#include "uihandler.h"
#define UDCT 43


static map<int,TestData> testData;

static QList<Test> m_display_list;
static int currTestid;
static int currTestIndex;
static QString currItemName;

static int getTestIndex(int testid){
    for (int i = 0; i < m_display_list.count(); i++){
        if (m_display_list[i].testId == testid)
            return i;
    }
    return -1;
}

static bool isExistTestData(int testid){
    if (testData.count(testid) == 1)
        return true;
    int listIndex = getTestIndex(testid);
    if (listIndex == -1 || m_display_list[listIndex].resultType < 2)
        return false;
    testData[testid].boxCode = m_display_list[listIndex].boxCode;


    if (m_display_list[listIndex].panelCode.at(0) == '2')
        UIHandler::LoadFileData(q2str(QCoreApplication::applicationDirPath()+"/RawData.csv"),testData[testid].posArr,testData[testid].PosId,testData[testid].Name,testData[testid].ItemThreshold,testData[testid].CT);
    else if(m_display_list[listIndex].resultType > 2)
        UIHandler::LoadResultData(testid,testData[testid].posArr,testData[testid].PosId,testData[testid].Name,testData[testid].ItemThreshold,testData[testid].CT);


    UIHandler::dealTestData(testid,testData);

    return true;
}

TestData *TestModel::getTestData(int testid){
    if (isExistTestData(testid))
        return &testData[testid];
    return nullptr;
}

TestModel::TestModel(QObject *parent):QAbstractListModel (parent)
{
    roles[RolesTestid] = "Testid";
    roles[RolesDisplayid] = "Displayid";
    roles[RoleUser] = "User";
    roles[RoleChecker] = "Checker";
    roles[RoleTestTime] = "TestTime";
    roles[RoleValidTime] = "ValidTime";
    roles[RolesSerialNo] = "SerialNo";
    roles[RolesBoxCode] = "BoxCode";
    roles[RoleResultType] = "ResultType";
    roles[RoleSampleInfo] = "SampleInfo";
    roles[RoleSampleType] = "SampleType";
    roles[RoleSampleRemark] = "SampleRemark";
    roles[RoleSampleId] = "SampleId";
    roles[RolesPanelCode] = "PanelCode";
    roles[RolesPanelName] = "PanelName";
    roles[RolesMachineNo] = "MachineNo";
    strOrder = "order by Testid DESC";
}

int TestModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_display_list.count();
}
int TestModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 8;
}
QVariant TestModel::data(const QModelIndex &index, int role) const
{    
    if (index.row()<0 || index.row()>=m_display_list.count())
        return QVariant();

    const Test &test = m_display_list[index.row()];

    if (role == Qt::DisplayRole){
        if (index.column() == 0)
            return test.testId;
        else if (index.column() == 2)
            return str2q(test.panelName);
        else if (index.column() == 3)
            return str2q(to_string(test.machineNo));
        else if (index.column() == 4)
            return str2q(test.sampleId);
        else if (index.column() == 5)
            return str2q(test.user);
        else if (index.column() == 6)
            return str2q(test.checker);
        else if (index.column() == 7)
            return str2q(test.testTime);
    }
    else if(role == Qt::DecorationRole){
        if (index.column() == 1 && test.resultType<2)
            return QIcon(":/images/thrAlarmSmall.png");
    }
    else if(role == Qt::TextAlignmentRole)
        return Qt::AlignCenter;    
    else if(role == Qt::FontRole)
        return QFont("Times",20);
    else if (role == RolesTestid)
        return test.testId;
    else if(role == RolesDisplayid)
        return test.displayId;
    else if(role == RoleUser)
        return str2q(test.user);
    else if(role == RoleChecker)
        return str2q(test.checker);
    else if(role == RoleTestTime)
        return str2q(test.testTime);
    else if(role == RoleValidTime)
        return str2q(test.validTime);
    else if(role == RolesSerialNo)
        return str2q(test.serialNo);
    else if(role == RolesBoxCode)
        return str2q(test.boxCode);
    else if(role == RoleResultType)
        return test.resultType;
    else if(role == RoleSampleInfo)
        return str2q(test.sampleInfo);
    else if(role == RoleSampleId)
        return str2q(test.sampleId);
    else if(role == RoleSampleRemark)
        return str2q(test.sampleRemark);
    else if(role == RoleSampleType)
        return test.sampleType;
    else if(role == RolesPanelCode)
        return str2q(test.panelCode);
    else if(role == RolesPanelName)        
        return str2q(test.panelName);
    else if(role == RolesMachineNo)
        return str2q(to_string(test.machineNo));

    return QVariant();
}

QHash<int, QByteArray> TestModel::roleNames() const
{    
    return roles;
}

void TestModel::InitTest(){
    qDebug()<<"TestModel,InitTest";

    m_display_list.clear();

    QString filter;
    if(strfilter.isEmpty())
        filter = strOrder;
    else
        filter = QString("where %1 %2").arg(strfilter).arg(strOrder);

    const list<Test>  list= UIHandler::getTestList(filter);

    foreach (Test test, list) {
       m_display_list<<test;
    }

    resetDisplayId();
}

int TestModel::AddLastTest(int machineNo, int testId){

    if(!ExistTest(testId))
    {
        beginInsertRows(QModelIndex(),0,0);
        m_display_list.prepend(UIHandler::getLastTest(machineNo));
        resetDisplayId();
        currTestIndex = 0;
        currTestid = m_display_list[currTestIndex].testId;
        endInsertRows();
    }
    return currTestid;
}

bool TestModel::ExistTest(int Testid){
    foreach(Test test, m_display_list){
        if (test.testId == Testid)
            return true;
    }
    return false;
}

bool TestModel::mayCheck(){
    //XXX qDebug()<<"mayCheck,"<<GlobalParam::UserType<<"Checker:"<<m_display_list[currTestIndex].Checker;
     if ((UIHandler::UserType & 0x2)/* && m_display_list[currTestIndex].Checker.length() == 0*/)
        return true;
    return false;
}

bool TestModel::haveCheck(){
    return (m_display_list[currTestIndex].checker.length() != 0);
}

void TestModel::checkTest(){    
    if(UIHandler::checkTest(UIHandler::getUser(),currTestid))
    {
       m_display_list[currTestIndex].checker = q2str(UIHandler::getUser());
       emit dataChanged(createIndex(currTestIndex,0),createIndex(currTestIndex,0));
    }
}

void TestModel::uncheckTest(){
    if(UIHandler::checkTest(UIHandler::getUser(),currTestid))
    {
       m_display_list[currTestIndex].checker = "";
       emit dataChanged(createIndex(currTestIndex,0),createIndex(currTestIndex,0));
    }
}

bool TestModel::delCurrTest(){
    if(UIHandler::delCurrTest(currTestid))
    {
        beginResetModel();
        m_display_list.removeAt(currTestIndex);
        resetDisplayId();
        endResetModel();
        return true;
    }
    return false;
}

int TestModel::getItemResultByName(int testid, QString name){
    if (isExistTestData(testid))
        return  UIHandler::getItemResultByName(testid,name,testData);
    return 0;
}

QString TestModel::getItemImgByName(int testid, QString name){
    int result = getItemResultByName(testid,name);
    if (result == 1)
        return ":/images/Positive.png";
    else if(result == 2)
        return ":/images/ud.png";
    return ":/images/Negative.png";
}

bool TestModel::TestValidCheck(int testid){
    if (isExistTestData(testid)){
        for(auto it : testData[testid].Name){
            if (getItemResultByName(testid,str2q(it)) == 1)
                return true;
        }
        if (getItemResultByName(testid,UIHandler::getItemName(2)) == 1)
            return true;
    }
    return false;
}

void TestModel::resetDisplayId(){
    int testCount = m_display_list.size();
    QList<Test>::iterator i;
    for(i = m_display_list.begin(); i!=m_display_list.end(); i++){
        i->displayId = testCount;
        testCount--;
    }
}

QString TestModel::getTestPanelCode(int testid){
    int index = getTestIndex(testid);
    if (index >=0)
        return str2q(m_display_list[index].panelCode);
    return "";
}

QString TestModel::getTestPanelName(int testid){
    int index = getTestIndex(testid);
    if (index >=0)
        return str2q(m_display_list[index].panelName);
    return "";
}

QString TestModel::getTestBoxSerial(int testid){
    int index = getTestIndex(testid);
    if (index >=0)
        return str2q(m_display_list[index].serialNo);
    return "";
}

QString TestModel::getTestSamapleCode(int testid){
    int index = getTestIndex(testid);
    if (index >=0)
        return str2q(m_display_list[index].sampleId);
    return "";
}

QString TestModel::getTestSamapleInfo(int testid)
{
    int index = getTestIndex(testid);
    if (index >=0)
        return str2q(m_display_list[index].sampleInfo);
    return "";
}

const Test TestModel::getTest(int testid)
{
    int index = getTestIndex(testid);
    if (index >=0)
        return m_display_list[index];
    return Test();
}

int TestModel::getTestResultType(int testid){
    int index = getTestIndex(testid);
    if (index >=0)
        return m_display_list[index].resultType;
    return -1;
}

QStringList TestModel::getTestName(int testid){
    QStringList name;
    if (isExistTestData(testid))
    {
        foreach (string strName, testData[testid].Name) {
            name << str2q(strName);
        }
    }
    return name;
}

int TestModel::getTestErrCode(int testid){
    int index = getTestIndex(testid);
    if (index >=0)
        return m_display_list[index].ErrCode;
    return 0;
}

void TestModel::setCurrTestById(int testId){
    int listIndex = getTestIndex(testId);
    if (listIndex != -1)
        setCurrTestByIndex(listIndex);
}

void TestModel::setCurrTestByIndex(int TestIndex){
    if (m_display_list.count() > TestIndex){
        currTestIndex = TestIndex;
        currTestid = m_display_list[TestIndex].testId;
    }
}

int TestModel::getCurrTestId(){
    return currTestid;
}

void TestModel::setCurrItemName(QString name){
    currItemName = name;
}

QString TestModel::getCurrItemName(){
    return currItemName;
}

int TestModel::getItemCT(int testid, QString name){
    int ItemCT = 0;
    if (isExistTestData(testid)){
        ItemCT = UIHandler::getItemCT(testData,testid,name);
    }
    return ItemCT;
}
