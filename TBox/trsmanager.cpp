#include "trsmanager.h"
#include <thread>
#include <windows.h>
TRSManager::TRSManager(QObject *parent) : QObject(parent) {
    object=parent;
}
void TRSManager::WriteLog(QString msg) {
    QMetaObject::invokeMethod(object, "writeLog", Q_ARG(QVariant, msg));
}
