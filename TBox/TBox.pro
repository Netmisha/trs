#-------------------------------------------------
#
# Project created by QtCreator 2017-01-17T17:37:37
#
#-------------------------------------------------

QT       += core gui webkit webkitwidgets qml quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TBox
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

DISTFILES += \
    test.html

RESOURCES += \
    qml.qrc
