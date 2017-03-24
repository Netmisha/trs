#include "testinfo.h"
#include <QDebug>
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
QString TestInfo::delData(QString tag) {
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

QString TestInfo::clearAllData()
{
    QDomDocument doc;
    QFile file(currentPath);
    file.open(QIODevice::ReadOnly);
    if (doc.setContent(&file, false)) {
        QDomElement root = doc.documentElement();
        root = root.firstChildElement(tags_name::kTest);
        while (root.attribute(tags_name::kName)!=testName) {
            root = root.nextSiblingElement(tags_name::kTest);
        }
        if(!root.firstChildElement(tags_name::kData).isNull()) {
            root.removeChild(root.firstChildElement(tags_name::kData));
            QDomElement node = doc.createElement(tags_name::kData);
            root.appendChild(node);
            file.close();
            file.open(QIODevice::WriteOnly);
            QTextStream stream( &file );
            stream << doc.toString();
            file.close();
            return "";
        }
        return "Data is not exist";
    }
    return "Test dont found!";
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
void TestInfo::BEGIN() {
    emit testBegin("Test \""+testName+"\" started.");
}
void TestInfo::ExitOnFinish(bool val) {
    defaultExit=val;
}
void TestInfo::FAIL(QString msg) {
    if(!finished) {
        finished=true;
        emit testFinish(" fail_ "+msg);
    }
}
void TestInfo::SUCCESS(QString msg) {
    if(defaultExit) {
        if(!finished) {
            finished=true;
            emit testFinish("success_ "+msg);
        }
    }
    else {
        defaultExit=true;
        emit sendMessage("SUCCESS Waiting...");
    }
}
void TestInfo::VERIFY(bool value)
{
    if(!value) {
        emit testFinish(" fail_");
    }
}

bool TestInfo::isFirstRun()
{
    return firstRun;
}

void TestInfo::setFirstRun(bool value)
{
    firstRun=value;
}
