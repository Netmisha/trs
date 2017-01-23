#-------------------------------------------------
#
# Project created by QtCreator 2017-01-17T17:37:37
#
#-------------------------------------------------

QT       += core gui webkit webkitwidgets qml quick testlib sql
CONFIG   += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TBox
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    trsmanager.cpp \
    maintree.cpp \
    trscore.cpp \
    database.cpp \
    export_data.cpp \
    export_txt.cpp \
    reporter.cpp \
    treemodel.cpp \
    mainsetting.cpp

HEADERS  += mainwindow.h \
    trsmanager.h \
    maintree.h \
    trscore.h \
    database.h \
    export_data.h \
    export_txt.h \
    reporter.h \
    treemodel.h \
    mainsetting.h

FORMS    += mainwindow.ui

RESOURCES += \
    qml.qrc
