#include "suiteinfo.h"
#include <QDebug>
#include "datamanager.h"
SuiteInfo::SuiteInfo(QObject *parent) : QObject(parent)
{

}
void SuiteInfo::setPath(QString path) {
    currentPath=path;
}
void SuiteInfo::setName(QString name) {
    testName=name;
}
QString SuiteInfo::getPath() {
    return currentPath;
}
QString SuiteInfo::getName() {
    return testName;
}
QString SuiteInfo::getCurrentDir() {
    return QString(currentPath).replace("/suite.xml","");
}
void SuiteInfo::setData(QString tag, QString data) {
    QDomDocument doc;
    QFile file(currentPath);
    file.open(QIODevice::ReadOnly);
    if (doc.setContent(&file, false)) {
        QDomElement root = doc.documentElement();
        if(root.firstChildElement(tags_name::kData).isNull()) {
            QDomElement node = doc.createElement(tags_name::kData);
            root.insertAfter(node,root.firstChildElement(tags_name::kMetadata));
        }
        root = root.firstChildElement(tags_name::kData);
        if(!root.firstChildElement(tag).isNull()) {
            root.firstChildElement(tag).firstChild().setNodeValue(data);
        }
        else {
            QDomElement node = doc.createElement(tag);
            root.appendChild(node);
            node.appendChild( doc.createTextNode(data));
        }
    }
    file.close();
    file.open(QIODevice::WriteOnly);
    file.write(doc.toString().toLatin1());
    file.close();
}
QString SuiteInfo::getData(QString tag) {
    QDomDocument doc;
    QFile file(currentPath);
    file.open(QIODevice::ReadOnly);
    if (doc.setContent(&file, false)) {
        QDomElement root = doc.documentElement();
        root = root.firstChildElement(tags_name::kData);
        if(!root.firstChildElement(tag).firstChild().isNull()) {
            return root.firstChildElement(tag).firstChild().nodeValue();
        }
        else {
            return "";
        }
    }
    file.close();
    return "";
}

QString SuiteInfo::delData(QString tag) {
    QDomDocument doc;
    QFile file(currentPath);
    file.open(QIODevice::ReadOnly);
    if (doc.setContent(&file, false)) {
        QDomElement root = doc.documentElement();
        root = root.firstChildElement(tags_name::kData);
        file.close();
        if(!root.firstChildElement(tag).isNull()) {
            root.removeChild(root.firstChildElement(tag));
            file.open(QIODevice::WriteOnly);
            QTextStream stream( &file );
            stream << doc.toString();
            file.close();
            return "";
        }
        file.close();
        return "Test dont found!";
    }
}
bool SuiteInfo::isData(QString tag) {
    QDomDocument doc;
    QFile file(currentPath);
    file.open(QIODevice::ReadOnly);
    if (doc.setContent(&file, false)) {
        QDomElement root = doc.documentElement();
        root = root.firstChildElement(tags_name::kData);
        return !root.firstChildElement(tag).isNull();
    }
    file.close();
    return false;
}
