#include "mainsetting.h"
#include <QDir>
#include <QDebug>
MainSetting::MainSetting(QObject *parent) : QObject(parent) {
    file.setFileName(QDir::currentPath()+"/"+file_name);
}
void MainSetting::setFileName(QString name) {
    file_name=name;
    file.setFileName(QDir::currentPath()+"/"+name);
}
QString MainSetting::getRootDir() {
    file.open(QIODevice::ReadOnly);
    QString res="";
    if(file.isOpen()) {
        QXmlStreamReader Rxml;
        Rxml.setDevice(&file);
        Rxml.readNext();
        while(!Rxml.atEnd()) {
            if(Rxml.isStartElement()) {
                if(Rxml.name() == tags::kDir) {
                    res=Rxml.readElementText();
                }
            }
            Rxml.readNext();
        }
    }
    file.close();
    return res;
}
void MainSetting::setRootDir(QString data) {
    file.open(QIODevice::ReadOnly);
    if(file.isOpen()) {
        QString old_data(file.readAll());
        file.close();
        QString new_data ="";
        new_data+=old_data.split(getRootDir())[0]+data+old_data.split(getRootDir())[1];
        file.close();
        file.open(QIODevice::WriteOnly);
        file.write(new_data.toLatin1());
        file.close();
    }
}
