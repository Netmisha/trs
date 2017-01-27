#include "mainsetting.h"
#include <QDir>
#include <QDebug>
MainSetting::MainSetting(QObject *parent) : QObject(parent) {
    file.setFileName(QDir::currentPath()+"/"+file_name);
    CreateSetting();
}
void MainSetting::setFileName(QString name) {
    file_name=name;
    file.setFileName(QDir::currentPath()+"/"+name);
}
QString MainSetting::getRootDir() {
    QDomDocument doc;
    file.open(QIODevice::ReadOnly);
    QString res="";
    doc.setContent(&file, false);
    QDomElement root = doc.documentElement();
    res=root.firstChildElement("dir").firstChild().nodeValue();
    file.close();
    return res;
}
void MainSetting::setRootDir(QString data) {
    QDomDocument doc;
    file.open(QIODevice::ReadOnly);
    doc.setContent(&file, false);
    QDomElement root = doc.documentElement();
    root = root.firstChildElement("dir");
    if(root.firstChild().isNull()) {
        root.appendChild(doc.createTextNode(data));
    }
    else {
        root.firstChild().setNodeValue(data);
    }
    file.close();
    file.open(QIODevice::WriteOnly);
    QTextStream stream( &file );
    stream << doc.toString();
    file.close();
}
void MainSetting::CreateSetting() {
    QDomDocument doc;
    file.open(QIODevice::ReadOnly);
    if(!file.isOpen()) {
        QDomDocument doc;
        file.close();
        file.open(QIODevice::WriteOnly);
        QDomElement node = doc.createElement("config");
        QDomElement snode = doc.createElement("name");
        snode.appendChild( doc.createTextNode("Test run sollution"));
        node.appendChild(snode);
        snode = doc.createElement("info");
        snode.appendChild( doc.createTextNode("Info"));
        node.appendChild(snode);
        snode = doc.createElement("dir");
        node.appendChild(snode);
        doc.appendChild(node);
        QTextStream stream( &file );
        stream << doc.toString();
    }
    file.close();
}
