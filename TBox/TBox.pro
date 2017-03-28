#-------------------------------------------------
#
# Project created by QtCreator 2017-01-17T17:37:37
#
#-------------------------------------------------

QT+= core gui webkit webkitwidgets qml quick testlib sql xml core-private gui-private
CONFIG+= c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = TBox
TEMPLATE = app
win32:LIBS += -lpsapi
SOURCES+= main.cpp\
    mainwindow.cpp \
    trscore.cpp \
    database.cpp \
    reporter.cpp \
    treemodel.cpp \
    mainsetting.cpp \
    testinfo.cpp \
    filesave.cpp\
    datamanager.cpp \
    reportform.cpp \
    sessionwindowtable.cpp \
    exporthtml.cpp \
    databasemanager.cpp \
    highlighter.cpp \
    selectfolderdialog.cpp \
    suiteinfo.cpp \
    smtp.cpp \
    smtpreport.cpp \
    TreeInfo.cpp \
    listmodel.cpp

HEADERS+= mainwindow.h \
    trscore.h \
    database.h \
    reporter.h \
    treemodel.h \
    mainsetting.h \
    testinfo.h \
    filesave.h\
    datamanager.h \
    reportform.h \
    sessionwindowtable.h \
    exporthtml.h \
    databasemanager.h \
    highlighter.h \
    selectfolderdialog.h \
    suiteinfo.h \
    smtp.h \
    smtpreport.h \
    TreeInfo.h \
    listmodel.h

FORMS+= mainwindow.ui \
    reportform.ui

RESOURCES+= \
    qml.qrc
