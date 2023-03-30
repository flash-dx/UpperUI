#ifndef TESTMODEL_H
#define TESTMODEL_H
#include<QAbstractListModel>
#include "testinfo.h"

class TestModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum LineInfo_Roles{
        RolesTestid = Qt::UserRole + 1,
        RolesDisplayid,
        RolesMachineNo,
        RolesPanelCode,
        RolesPanelName,
        RolesSerialNo,
        RolesBoxCode,
        RoleTestTime,
        RoleValidTime,
        RoleSampleInfo,
        RoleSampleId,
        RoleSampleRemark,
        RoleSampleType,
        RoleUser,
        RoleChecker,
        RoleResultType
    };
public:
    explicit TestModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    int columnCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    int AddLastTest(int machineNo,int testId);
    static int getLastTestType(int machineNo);
    bool ExistTest(int Testid);
    void InitTest();
    static bool TestValidCheck(int testid);
    static int getItemResultByName(int testid, QString name);
    static QString getItemImgByName(int testid, QString name);

    static QString getTestPanelCode(int testid);
    static QString getTestPanelName(int testid);
    static QString getTestBoxSerial(int testid);
    static QString getTestSamapleCode(int testid);
    static QString getTestSamapleInfo(int testid);
    static const Test getTest(int testid);

    static int getTestResultType(int testid);
    static QStringList getTestName(int testid);    

    static void setCurrTestByIndex(int TestIndex);
    static void setCurrTestById(int testId);
    static int getCurrTestId();
    static void setCurrItemName(QString name);
    static QString getCurrItemName();
    static int getItemCT(int testid, QString name);
    static TestData *getTestData(int testid);

    bool mayCheck();
    bool haveCheck();
    void checkTest();
    void uncheckTest();
    bool delCurrTest();
    //Test getTestItem(int index){return m_display_list[index];}

    static int getTestErrCode(int testid);
protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QHash<int, QByteArray> roles;
    void resetDisplayId();
};

#endif // TESTMODEL_H
