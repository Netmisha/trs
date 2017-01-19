#include "maintree.h"
#include <QDebug>
#include <QFile>
MainTree::MainTree(QObject *parent) : QObject(parent) {

}
MainTree::~MainTree() {
    tests_.clear();
    for(auto &it:suites_) {
        delete it;
    }
    suites_.clear();
}
QString MainTree::path() {
    return path_;
}
QString MainTree::name() {
    return name_;
}
QVector<TestItem> MainTree::tests() {
    return tests_;
}
QVector<MainTree *> MainTree::suites() {
    return suites_;
}
void MainTree::setPath(QString path) {
    path_=path;
}
void MainTree::setName(QString name) {
    name_=name;
}
void MainTree::addTest(QString test) {
    TestItem newTest;
    newTest.name=test;
    tests_.push_back(newTest);
}
void MainTree::addSuite(MainTree * suite) {
    suites_.push_back(suite);
}
QStringList MainTree::getTestsName(QString file_name) {
    QFile file(file_name);
    file.open(QIODevice::ReadOnly);
    QXmlStreamReader Rxml;
    QStringList testList;
    Rxml.setDevice(&file);
    Rxml.readNext();
    while(!Rxml.atEnd()) {
        if(Rxml.isStartElement()) {
            if(Rxml.name() == tags::kTest) {
                testList.push_back(Rxml.attributes().value(tags::kName).toString());
            }
        }
        Rxml.readNext();
    }
    file.close();
    return testList;
}

QString MainTree::getSuiteName(QString file_name)
{
    QFile file(file_name);
    file.open(QIODevice::ReadOnly);
    QXmlStreamReader Rxml;
    Rxml.setDevice(&file);
    Rxml.readNext();
    while(!Rxml.atEnd()) {
        if(Rxml.isStartElement()) {
            if(Rxml.name() == tags::kSuite) {
                return Rxml.attributes().value(tags::kName).toString();
            }
        }
        Rxml.readNext();
    }
    file.close();
    return "";
}
