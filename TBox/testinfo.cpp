#include "testinfo.h"
#include "datamanager.h"

TestInfo::TestInfo(QObject *parent) : QObject(parent)
{

}
void TestInfo::setPath(QString path) {
    currentPath=path;
}
void TestInfo::setName(QString name) {
    testName=name;
}
QString TestInfo::getPath() {
    return currentPath;
}
QString TestInfo::getName() {
    return testName;
}
QString TestInfo::getCurrentDir() {
    return QString(currentPath).replace("/suite.xml","");
}
void TestInfo::setData(QString tag, QString data) {
    QDomDocument doc;
    QFile file(currentPath);
    file.open(QIODevice::ReadOnly);
    if (doc.setContent(&file, false)) {
        QDomElement root = doc.documentElement();
        root = root.firstChildElement(tags_name::kTest);
        while (root.attribute(tags_name::kName)!=testName) {
            root = root.nextSiblingElement(tags_name::kTest);
        }
        if(root.firstChildElement(tags_name::kData).isNull()) {
            QDomElement node = doc.createElement(tags_name::kData);
            root.appendChild(node);
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
QString TestInfo::getData(QString tag) {
    QDomDocument doc;
    QFile file(currentPath);
    file.open(QIODevice::ReadOnly);
    if (doc.setContent(&file, false)) {
        QDomElement root = doc.documentElement();
        root = root.firstChildElement(tags_name::kTest);
        while (root.attribute(tags_name::kName)!=testName) {
            root = root.nextSiblingElement(tags_name::kTest);
        }
        root = root.firstChildElement(tags_name::kData);
        return root.firstChildElement(tag).firstChild().nodeValue();
    }
    file.close();
    return "";
}
bool TestInfo::isData(QString tag) {
    QDomDocument doc;
    QFile file(currentPath);
    file.open(QIODevice::ReadOnly);
    if (doc.setContent(&file, false)) {
        QDomElement root = doc.documentElement();
        root = root.firstChildElement(tags_name::kTest);
        while (root.attribute(tags_name::kName)!=testName) {
            root = root.nextSiblingElement(tags_name::kTest);
        }
        root = root.firstChildElement(tags_name::kData);
        return !root.firstChildElement(tag).isNull();
    }
    file.close();
    return false;
}
