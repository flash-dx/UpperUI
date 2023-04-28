#-------------------------------------------------
#
# Project created by QtCreator 2023-03-30T14:06:37
#
#-------------------------------------------------

QT       += core gui charts printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DxHS
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    logindlg.cpp \
    uihandler.cpp \
    Module/testmodel.cpp \
    mainwin.cpp \
    components/e04.cpp \
    components/loading.cpp \
    components/lock.cpp \
    components/onebtnmessagebox.cpp \
    components/progressbutton.cpp \
    components/threequery.cpp \
    components/TimeScrollBar.cpp \
    components/twobtnmessagebox.cpp \
    components/twobutton.cpp \
    DataUI/datainvaildview.cpp \
    DataUI/dataline.cpp \
    DataUI/datamenu.cpp \
    DataUI/dataview.cpp \
    HomeUI/homeallmachine.cpp \
    HomeUI/homeidle.cpp \
    HomeUI/homeready.cpp \
    HomeUI/homestartup.cpp \
    HomeUI/hometest.cpp \
    SetupUI/adduser.cpp \
    SetupUI/adminpassword.cpp \
    SetupUI/camerasetup.cpp \
    SetupUI/languageset.cpp \
    SetupUI/light.cpp \
    SetupUI/lockscreenset.cpp \
    SetupUI/logview.cpp \
    SetupUI/machinecalibration.cpp \
    SetupUI/network.cpp \
    SetupUI/pidparam.cpp \
    SetupUI/projectparam.cpp \
    SetupUI/pumpparam.cpp \
    SetupUI/setupmenu.cpp \
    SetupUI/systemname.cpp \
    SetupUI/systemparam.cpp \
    SetupUI/testloop.cpp \
    SetupUI/timeset.cpp \
    SetupUI/updateuser.cpp \
    SetupUI/uppermachine.cpp \
    SetupUI/uppermachineSetting.cpp \
    SetupUI/usbfile.cpp \
    SetupUI/user.cpp \
    SetupUI/version.cpp \
    SetupUI/version2.cpp \
    SetupUI/wifimenu.cpp \
    HomeUI/homesubmachine.cpp \
    HomeUI/unitmain.cpp \
    globalapplication.cpp

HEADERS += \
        mainwindow.h \
    logindlg.h \
    uihandler.h \
    Module/testmodel.h \
    mainwin.h \
    components/e04.h \
    components/loading.h \
    components/lock.h \
    components/onebtnmessagebox.h \
    components/progressbutton.h \
    components/threequery.h \
    components/TimeScrollBar.h \
    components/twobtnmessagebox.h \
    components/twobutton.h \
    DataUI/datainvaildview.h \
    DataUI/dataline.h \
    DataUI/datamenu.h \
    DataUI/dataview.h \
    HomeUI/homeallmachine.h \
    HomeUI/homeidle.h \
    HomeUI/homeready.h \
    HomeUI/homestartup.h \
    HomeUI/hometest.h \
    SetupUI/adduser.h \
    SetupUI/adminpassword.h \
    SetupUI/camerasetup.h \
    SetupUI/languageset.h \
    SetupUI/light.h \
    SetupUI/lockscreenset.h \
    SetupUI/logview.h \
    SetupUI/machinecalibration.h \
    SetupUI/network.h \
    SetupUI/pidparam.h \
    SetupUI/projectparam.h \
    SetupUI/pumpparam.h \
    SetupUI/setupmenu.h \
    SetupUI/systemname.h \
    SetupUI/systemparam.h \
    SetupUI/testloop.h \
    SetupUI/timeset.h \
    SetupUI/updateuser.h \
    SetupUI/uppermachine.h \
    SetupUI/uppermachineSetting.h \
    SetupUI/usbfile.h \
    SetupUI/user.h \
    SetupUI/version.h \
    SetupUI/version2.h \
    SetupUI/wifimenu.h \
    HomeUI/homesubmachine.h \
    HomeUI/unitmain.h \
    globalapplication.h

FORMS += \
        mainwindow.ui \
    logindlg.ui \
    mainwin.ui \
    components/cqrcodeinfo.ui \
    components/e04.ui \
    components/Homeloading.ui \
    components/loading.ui \
    components/lock.ui \
    components/onebtnmessagebox.ui \
    components/threequery.ui \
    components/twobtnmessagebox.ui \
    components/twobutton.ui \
    DataUI/datainvaildview.ui \
    DataUI/dataline.ui \
    DataUI/datamenu.ui \
    DataUI/dataview.ui \
    HomeUI/homeallmachine.ui \
    HomeUI/homeidle.ui \
    HomeUI/homemain.ui \
    HomeUI/homeready.ui \
    HomeUI/homestartup.ui \
    HomeUI/hometest.ui \
    SetupUI/adduser.ui \
    SetupUI/adminpassword.ui \
    SetupUI/camerasetup.ui \
    SetupUI/languageset.ui \
    SetupUI/light.ui \
    SetupUI/lockscreenset.ui \
    SetupUI/logview.ui \
    SetupUI/machinecalibration.ui \
    SetupUI/network.ui \
    SetupUI/pidparam.ui \
    SetupUI/projectparam.ui \
    SetupUI/pumpparam.ui \
    SetupUI/setupmenu.ui \
    SetupUI/systemname.ui \
    SetupUI/systemparam.ui \
    SetupUI/testloop.ui \
    SetupUI/timeset.ui \
    SetupUI/updateuser.ui \
    SetupUI/uppermachine.ui \
    SetupUI/uppermachineSetting.ui \
    SetupUI/usbfile.ui \
    SetupUI/user.ui \
    SetupUI/version.ui \
    SetupUI/version2.ui \
    SetupUI/wifimenu.ui \
    HomeUI/homesubmachine.ui \
    HomeUI/unitmain.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

linux-g++ {
QMAKE_CXXFLAGS+=-Wno-deprecated-copy
INCLUDEPATH += $$PWD/../UpperLib/
LIBS += -L$$PWD/../HandlerLib/Linux/ -lUpperHandler
DEPENDPATH += $$PWD/../HandlerLib/Linux
}

win32 {
QMAKE_CFLAGS += /utf-8
QMAKE_CXXFLAGS += /utf-8
INCLUDEPATH += $$PWD/../UpperLib/
DEPENDPATH += $$PWD/../UpperLib/
LIBS += -L$$PWD/../HandlerLib/Windows/ -lUpperHandler
}

QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO
