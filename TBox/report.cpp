#include "report.h"
#include <thread>
#include <windows.h>
Report::Report(QObject *parent) : QObject(parent) {
    object=parent;
}
void Report::FAIL(QString msg) {
    emit sendMessage("Test fail. "+msg);
}
void Report::SUCCESS(QString msg) {
    emit sendMessage("Test success. "+msg);
}
void Report::MESSAGE(QString msg) {
    emit sendMessage(msg);
}
