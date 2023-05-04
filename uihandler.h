#ifndef UIHANDLER_H
#define UIHANDLER_H

#include <QObject>
#include <QDebug>
#include <QPushButton>
#include <QLabel>
#include "dxtype.h"
#include <map>
#include "Module/testmodel.h"
#define str2q(str) QString::fromStdString(str)
#define q2str(str) QString(str).toStdString()

class UIHandler : public QObject
{
    Q_OBJECT
private:
    explicit UIHandler(QObject *parent = nullptr);

public:
    enum PageId{
        Page_One_Startup,
        Page_One_Idle,
        Page_One_BoxReady,
        Page_One_Test,
        Page_Home_AllMachine,
        Page_Home_SubMachine,
        Page_Home_Main,
        Page_Home_Login,
        Page_Home_E04,
        Page_Setup_Menu,
        Page_Setup_SystemName,
        Page_Setup_LockScreen,
        Page_Setup_Backlight,
        Page_Setup_Language,
        Page_Setup_Password,
        Page_Setup_Wifi,
        Page_Setup_Network,
        Page_Setup_Time,
        Page_Setup_User,
        Page_Setup_Machine,
        Page_Setup_Camera,
        Page_Setup_TestSetup,
        Page_Setup_TestLoop,
        Page_Setup_SystemParam,
        Page_Setup_ProjectParam,
        Page_Setup_UsbFile,
        Page_Setup_Light,
        Page_Setup_PumpParam,
        Page_Setup_Log,
        Page_Setup_PID,
        Page_Setup_Version,
        Page_Setup_Lis,
        Page_Setup_UpperMachine,
        Page_Data_Menu,
        Page_Data_View,
        Page_Data_InvalidView,
        Page_Data_Line,
        Page_Data_OneDataLine,
        Page_User_AddUser,
        Page_User_UpdateUser,
        Page_Setup_UpperMachineSetting,
        Page_Empty
    };

    enum StateId{
        State_MachineName_Update,
        State_SetupMenu_Update,
        State_Empty
    };

    static UIHandler *getPtr();
    static void Init();
    static void GoPage(PageId id);
    static void FooterSetEnabled(bool enable);
    static void NotifyTitle(QString title, int type = 0);
    static void GlobalMessage(int msg);
    static void ScanCode(QString code);
    static void Close();
    static QString getString(const int id);

    static size_t getSubCount();


    //login
    static QStringList getLogUser();
    static int Login(QString name, QString password);
    static void setLogin(bool b = true);
    static bool getLogin();
    static void setDebugMode(bool b );

    //globalalparam

    static int get_int_Param(QString paramname, int MachineNo = -1);
    static bool set_int_Param(QString paramname,int value, int MachineNo = -1);
    static void updata_int_Param(QString paramname,int value, int MachineNo = -1);

    static const QString get_string_Param(QString paramname);
    static bool set_string_Param(QString paramname,QString value);
    static void updata_string_Param(QString paramname,QString value);

    static int getCurrMachineId();
    static void setCurrMachineId(const int id);
    static int getPrevMachineId();

    static map<int,string>get_subMac_Name();
    static map<int,string>get_subMac_Mac();
    static map<int,string>get_subMac_PowerMac();

    static const QString getBoxCode(QString panelCode);

    //submachine
    static void setStage(const HomeStage state);
    static HomeStage getStage(int machineNo = getCurrMachineId());

    static void setSampleCode(const QString code );
    static QString getSampleCode(int machineNo = getCurrMachineId());
    static void setSampleInfo(const QString info);
    static QString getSampleInfo();
    static void setSampleRemark(const QString remark);
    static QString getSampleRemark();
    static void setSampleType(const int type);
    static int getSampleType();
    static void clearSample(const int machiNo = 0);
    static void setMachineCode(const int code);
    static QString PanelName(int machineNo = getCurrMachineId());
    static QString PanelCode();
    static QString BoxSerial();
    static QString getSampleTypeName(int type);
    static void setPanelName(const QString name);
    static void setPanelCode(const QString code);
    static void setBoxSerial(const QString serial);
    static void setBoxCode(const QString code);    
    static QString getIP();
    static QString getWIFIIP();
    static QString getDataBaseIP();
    static void setDataBaseIP(QString ip);
    static QMap<QString,QString> getNetworkMap();
    static void WriteXmlParam(const QString ParamName,const QString value);
    static QString ReadXmlParam(QString ParamName, QString defaultValue = "");
    static void setextNetMac(QString name);
    static QString getextNetMac();
    static bool isSetNetName();
    static void ActionDo(QString device, int value, int param1, int param2, int param3, int machineNo);
    static void settingParam(QString type, int machineNo);
    static bool isConnected(int MachineNo);
    static void StartView(int id, int light, int machineNo);
    static void StopView(int machineNo);
    static QString getStyleSheet(QString key);
    static QList<QString> updateSoft();
    static bool clearSubTable();
    static bool AddSubMachine(string mac, int no, string name, string powermac);
    static int modifySubMachine(QString oldmac, QString mac, int no, QString name, QString powermac);
    static bool delSubMachine(QString mac);
    static void UpdataTempParam(int machineNo);

    static void updatetimezone(int index);
    static bool setTime(QString time);
    static void setTimezoneopen(bool bopen);

    static void sendFile(QString pathname, QString filename, SendFileCallBack fun, int machineNo);

    static QString getTwoBtnMsg();
    static bool clearMsg();

    static const IdleData *getIdleData(int machineNo = getCurrMachineId());
    static const TestProcessData *getTestProcessData(int machineNo = getCurrMachineId());

    static const ErrorInfo *getErrInfo(int machineNo = getCurrMachineId());

    static void IdleSwitchDoor();

    /*    user    */
    static QList<USERINFO> getUserList();
    static int getCurrUserListIndex();
    static void setCurrUserListIndex(int index);
    static void deleteUser(int index);
    static bool addUser(QString name, QString password, QString displayName, int type);
    static bool updateUser(QString name, QString password, QString displayName, int type);
    static bool isUserNameExist(QString name);
    static const QString getUser();
    static QString getDisplayUser();
    static int getUserType(QString name);

    /*    idle    */
    static QStringList getPanelList();

    static int decodeQr(QString code);
    /*    ready    */
    static void ReadyStartTest();

    static QStringList getSampleTypeArr();
    /*    testprocess    */
    static void CancelTest(bool initiative = true);
    static void ContinueTest();

    static bool hasTesting();
    //testmodel
    static const list<Test> getTestList();
    static list<string> onePointTestList(bool language);

    static bool delCurrTest(int testId);

    static bool checkTest(QString user,int testId);
    static bool uncheckTest(int testId);

    static const QString getItemName(int itemid);
    
    static const QString getItemCode(int itemid);

    static int getItemCT(const map<int,TestData> testData,int testid, QString name);

    static const Test getLastTest(int machineNo);
    //dataloader
    static bool LoadFileData(string filename, map<int, std::vector<CPointF> > &posArr, map<int, int> &PosId, list<string> &Name, map<int, int> &CurrItemCT, map<int, int> &CT);
    static void LoadResultData(int Testid, map<int, std::vector<CPointF> > &posArr, map<int, int> &PosId, list<string> &Name, map<int, int> &CurrItemCT, map<int, int> &CT);


    static QString getBuildversion();
    static QString getTempversion(){return temp_version;}
    static QString getCtrlversion(){return ctrl_version;}
    static void settempversion(const QString &version){temp_version = version;}
    static void setctrlversion(const QString &version){ctrl_version = version;}
    static QString getSerial(){return "000000000";}
    static QString getMac();
    static QString Version(){return t_version;}
    static QString buildVersion(){return build_version;}
    static map<string, string> getBoardcastMac();
    static map<string, string> getPowerMac();
    static list<WifiItem> getWifiList();
    static void refreshWifi();
    static void disconnectWifi();
    static void connectWifi(QString account, QString password);
    static QString getWifiPassword(QString name);
    static void setNetIp(QString ip, QString mask, QString gate);
    static list<logdata> getLogDataList(int index);
    static void DebugMedianMachine(int param1 = 0, int param2 = 0, int param3 = 0);
    //testloop
    static QStringList getLoopTestList(bool language);
    static void Looptest(QString device, int MachineNo);
    static void CancelLoopTest(int MachineNo);
    //power
    static void setLedBlink(int machineNo, int time = 30000);

    static QList<int> getHasBoxNoList();

    static vector<WholeMachine_T *> getWholeMacArr();
public:
    static bool debug;
    static int screenHeight;
    static int screenWidth;
    static int headerHeight;
    static int footerHeight;
    static int contentHeight;
    static int contentWidth;

    static QString t_version;
    static QString build_version;
    static QString temp_version;
    static QString ctrl_version;
    static QString XmlVersion;

    static QString DataVersion;

    static int DataEntry;

    static QString abNormalInfo;

    static TestModel* pTestModel;

    static int UserType;
    static QMap<QString,QString> networkMap;
    static QString extNetMac;

    static void setHiddenFunction(){HiddenFunction = true;}
    static bool getHiddenFunction(){return HiddenFunction;}

    static int dataEntry(){return DataEntry;}
    static void setDataEntry(int entry){DataEntry = entry;}

    static void setBtTextCenter(QPushButton *pBt, int padding, QString style);
    static void setLabelWordWrap(QLabel * lb,const QString text);
    static subDoorInfo judgeDoorStatus();

    static bool getDoorState(int machineNo = getCurrMachineId());
    static bool getBoxState(int machineNo = getCurrMachineId());
    static bool isDoorOpening(int machineNo = getCurrMachineId());

    static int getTestProgress(int machineNo = getCurrMachineId());

    static QString getValidTime();
    //

    static int getSubCurTestId();

    static void TestResultGoWin(int WinID = 0);

    static void dealTestData(const int testId, map<int,TestData> &testData);

    static int getItemResultByName(int testid, QString name, const map<int, TestData> testData);

    static void PowerOff();
    static void UpdateState(StateId id);
private:
    static bool HiddenFunction;
    void dealSignal(const char * data);
    void slot_updateUi(int machineNo);
    void slot_CamerView(string imgstr, int machineNo);
    void slot_testProgress(int complete, int total, int machineNo);
    void slot_updateTestList(int machineNo,int testId);
    void slot_autoFocusNotify(int status, int value, int machineNo);
    void slot_refreshLightValue(int lightvalue, int machineNo);
    void slot_clearProcess(int machineNo);
    void slot_sendFileResult(int param, int machineNo);
    void slot_errSql(int machineNo);
    void slot_DoorKeyDown(int machineNo);
    void slot_senorUpdate(int type,int machineNo);
    void slot_tcpStatus(int status,int machineNo);
signals:
    void EnterLogin(bool bEnter);
    void Go(PageId id);
    void sig_FooterSetEnabled(bool enable);
    void sig_NotifyTitle(QString title, int type);
    void UpdateUI(int machineNo);
    void TestProgress(int complete, int total, int machineNo);
    void sig_clearProcess(int machineNo);
    void sig_CamerView(string imgstr, int machineNo);
    void sig_autoFocusNotify(int status, int value, int machineNo);
    void sig_QrCodeChange(QString code);
    void GlobalParamMessage(int code);
    void sig_refreshLightValue(int lightvalue, int machineNo);
    void State(StateId id);
    void sig_sendFileResult(int param, int machineNo);
    void sig_errorSql(int machineNo);
    void sig_DoorKeyDown(int machineNo);
    void sig_senorUpdate(int type, int machineNo);
    void sig_tcpStatus(int status, int machineNo);
    void sig_updateMsgIcon(int machineNo);
};

#endif // UIHANDLER_H
