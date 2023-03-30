#-------------------------------------------------
#
# Project created by QtCreator 2023-03-30T14:06:37
#
#-------------------------------------------------

QT       += core gui charts

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
    mainwin.cpp

HEADERS += \
        mainwindow.h \
    logindlg.h \
    uihandler.h \
    Module/testmodel.h \
    mainwin.h

FORMS += \
        mainwindow.ui \
    logindlg.ui \
    mainwin.ui

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
