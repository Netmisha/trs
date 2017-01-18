#include "trsmanager.h"

TRSManager::TRSManager(QObject *parent) : QObject(parent) {

}
QString TRSManager::ParseFolder(QString path) {
    qDebug() << "ParseFolder";
    QDirIterator it(path, QDirIterator::Subdirectories);
    QString files;
    while (it.hasNext()) {
        files+=it.next()+"\n";
    }
    return files;
}
