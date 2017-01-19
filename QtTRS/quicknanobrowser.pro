requires(contains(QT_CONFIG, accessibility))

TEMPLATE = app
TARGET = quicknanobrowser

HEADERS = \
    database.h \
    treemodel.h
SOURCES = main.cpp \
    database.cpp \
    treemodel.cpp

OTHER_FILES += ApplicationRoot.qml \
               BrowserDialog.qml \
               BrowserWindow.qml \
               FullScreenNotification.qml \
               main_Window.qml

RESOURCES += resources.qrc

QT += qml quick webengine sql

qtHaveModule(widgets) {
    QT += widgets # QApplication is required to get native styling with QtQuickControls
}

target.path = $$[QT_INSTALL_EXAMPLES]/webengine/quicknanobrowser
INSTALLS += target

DISTFILES += \
    main_Window.qml
