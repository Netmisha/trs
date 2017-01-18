#include "maintree.h"

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
QVector<QString> MainTree::tests() {
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
    tests_.push_back(test);
}
void MainTree::addSuite(MainTree * suite) {
    suites_.push_back(suite);
}
