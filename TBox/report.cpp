#include "report.h"
#include <thread>
#include <windows.h>
Report::Report(QObject *parent) : QObject(parent) {
    object=parent;
}
void Report::FAIL(QString msg) {

}
void Report::SUCCESS(QString msg) {

}
void Report::MESSAGE(QString msg) {

}
