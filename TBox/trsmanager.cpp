#include "trsmanager.h"
#include <thread>
#include <windows.h>
TRSManager::TRSManager(QObject *parent) : QObject(parent) {

}
void TRSManager::Run(QString script, QString path, QString name) {
    std::thread thr(RunInThread, script, path, name);
    thr.detach();
}

void TRSManager::RunInThread(QString script, QString path, QString name) {

}
