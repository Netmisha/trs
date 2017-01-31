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
SOURCES+= main.cpp\
    mainwindow.cpp \
    trsmanager.cpp \
    maintree.cpp \
    trscore.cpp \
    database.cpp \
    export_data.cpp \
    export_txt.cpp \
    reporter.cpp \
    treemodel.cpp \
    mainsetting.cpp \
    testinfo.cpp \
    filesave.cpp\
    datamanager.cpp \
    reportform.cpp \
    lismodel.cpp \
    sessionwindowtable.cpp \
    exporthtml.cpp \
    databasemanager.cpp

HEADERS+= mainwindow.h \
    trsmanager.h \
    maintree.h \
    trscore.h \
    database.h \
    export_data.h \
    export_txt.h \
    reporter.h \
    treemodel.h \
    mainsetting.h \
    testinfo.h \
    filesave.h\
    datamanager.h \
    reportform.h \
    lismodel.h \
    sessionwindowtable.h \
    exporthtml.h \
    databasemanager.h

FORMS+= mainwindow.ui \
    reportform.ui

RESOURCES+= \
    qml.qrc
