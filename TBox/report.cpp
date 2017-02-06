#include "report.h"
#include <thread>
#include <windows.h>
Report::Report(QObject *parent) : QObject(parent) {
    object=parent;
}
