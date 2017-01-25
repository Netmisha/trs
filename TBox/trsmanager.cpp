#include "trsmanager.h"

TRSManager::TRSManager(QObject *parent) : QObject(parent) {

}
void TRSManager::Run(QString script, QString path, QString name) {
    view->page()->mainFrame()->evaluateJavaScript("Test.setPath('"+path+"'); Test.setName('"+name+"');"+script + "trs.RunNext();");
}
