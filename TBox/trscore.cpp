#include "trscore.h"
#include <QDesktopWidget>
#include <QObject>
TRSCore::TRSCore(QObject *parent) : QObject(parent) {
    process=new QProcess(this);
}
void TRSCore::StartApp(QString appName) {
    process->start(appName);
}
void TRSCore::CloseApp() {
    process->close();
}
void TRSCore::Sleep(int msec) {
    QTest::qSleep(msec);
}

int TRSCore::GetScreenWidth()
{
    QDesktopWidget desktop;
    return desktop.geometry().width();
}

int TRSCore::GetScreenHeight()
{
    QDesktopWidget desktop;
    return desktop.geometry().height();
}

void TRSCore::WindowMinimize()
{

}

void TRSCore::WindowMaximize()
{

}

void TRSCore::WindowRestore()
{

}
