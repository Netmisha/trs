#-------------------------------------------------
#
# Project created by QtCreator 2017-01-17T17:37:37
#
#-------------------------------------------------

QT       += core gui webkit webkitwidgets qml quick
CONFIG   += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TBox
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    trsmanager.cpp \
    maintree.cpp

HEADERS  += mainwindow.h \
    trsmanager.h \
    maintree.h

FORMS    += mainwindow.ui

DISTFILES +=

RESOURCES += \
    qml.qrc
