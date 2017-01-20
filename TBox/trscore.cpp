#include "trscore.h"

TRSCore::TRSCore(QObject *parent) : QObject(parent) {
    process=new QProcess(this);
}
void TRSCore::StartApp(QString appName) {
    process->start(appName);
}
void TRSCore::CloseApp() {
    process->close();
}
