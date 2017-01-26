#-------------------------------------------------
#
# Project created by QtCreator 2017-01-17T17:37:37
#
#-------------------------------------------------

QT+= core gui webkit webkitwidgets qml quick testlib sql xml

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
    export_html.cpp \
    testinfo.cpp \
    mainsetting.cpp \
    datamanager.cpp \
    reportform.cpp \
    lismodel.cpp

HEADERS+= mainwindow.h \
    trsmanager.h \
    maintree.h \
    trscore.h \
    database.h \
    export_data.h \
    export_txt.h \
    reporter.h \
    treemodel.h \
    export_html.h \
    testinfo.h \
    mainsetting.h \
    datamanager.h \
    reportform.h \
    lismodel.h
FORMS+=mainwindow.ui \
    reportform.ui
RESOURCES+= \
    qml.qrc
