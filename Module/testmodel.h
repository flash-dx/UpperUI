#ifndef TESTMODEL_H
#define TESTMODEL_H
#include<QAbstractListModel>
#include<QSortFilterProxyModel>
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
    bool ExistTest(int Testid);
    void InitTest();
    bool TestValidCheck(int testid);
    int getItemResultByName(int testid, QString name);
    QString getItemImgByName(int testid, QString name);

    QString getTestPanelCode(int testid);
    QString getTestPanelName(int testid);
    QString getTestBoxSerial(int testid);
    QString getTestSamapleCode(int testid);
    QString getTestSamapleInfo(int testid);
    const Test getTest(int testid);
    QString getTestPanelCode(QString panelName);

    int getTestResultType(int testid);
    QStringList getTestName(int testid);

    void setCurrTestByIndex(int TestIndex);
    void setCurrTestById(int testId);
    int getCurrTestId();
    void setCurrItemName(QString name);
    QString getCurrItemName();
    int getItemCT(int testid, QString name);
    TestData *getTestData(int testid);
    int getTestIndex(int testid);
    bool isExistTestData(int testid);

    bool mayCheck();
    bool haveCheck();
    void checkTest();
    void uncheckTest();
    bool delCurrTest();
    //Test getTestItem(int index){return m_display_list[index];}

    int getTestErrCode(int testid);
    void setFilter(QString filter){ strFilter = filter;}
    void setOrder(QString column, bool asc){ strOrder = QString("order by %1 %2").arg(column).arg(asc?"DESC":"asc");}
    void setLimit(int start, int count);
    int  getFilterRowCount();
    QList<QString> getTestPanelNameList();
    QList<QString> getTestSampleIdList();
    QList<QString> getTestSampleTypeNameList();
    QList<QString> getTestMachineNoList();
    QList<QString> getTestUserList();
    QList<QString> getTestCheckerList();
    int getTestSampleType(QString sampleTypeName);

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QHash<int, QByteArray> roles;
    void resetDisplayId();

    QString strFilter;
    QString strOrder;
    QString strLimit;

    map<int,TestData> testData;
    QList<Test> m_display_list;
    int currTestid;
    int currTestIndex;
    QString currItemName;
};

#endif // TESTMODEL_H
