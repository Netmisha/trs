#include "trsmanager.h"

TRSManager::TRSManager(QObject *parent) : QObject(parent) {

}
void TRSManager::Run(QString script) {
    view->page()->mainFrame()->evaluateJavaScript(script + "trs.RunNext();");
}
