#include "maintree.h"
#include <QDebug>
TreeInfo::TreeInfo (TreeInfo *parent, QString fil, QString nam, QString typ, int rep, QModelIndex ind)
    : parent(parent), file(fil), name(nam), type(typ), repeat(rep), item(ind) {}

TreeInfo::~TreeInfo()
{
    for(auto&it:childTests) {
        delete it;
    }
    for(auto&it:childSuites) {
        delete it;
    }
    childTests.clear();
    childSuites.clear();
}
QString TreeInfo::getPath() {
    return QString(file).replace("/suite.xml","");
}
QString TreeInfo::getFile() {
    return file;
}
QString TreeInfo::getName() {
    return name;
}
QString TreeInfo::getType() {
    return type;
}
bool TreeInfo::isDisable() {
   return disable;
}
int TreeInfo::getRepeat() {
    return repeat;
}
int TreeInfo::getBaseRepeat() {
    return baseRepeat;
}
QModelIndex TreeInfo::getItem() {
    return item;
}
TreeInfo * TreeInfo::getParent() {
    return parent;
}
QList<TreeInfo *>& TreeInfo::getChildTests() {
    return childTests;
}
QList<TreeInfo *>& TreeInfo::getChildSuites() {
    return childSuites;
}
void TreeInfo::setFile(QString file) {
    this->file=file;
}
void TreeInfo::setName(QString name) {
    this->name=name;
}
void TreeInfo::setType(QString type) {
    this->type=type;
}
void TreeInfo::setDisable(bool status) {
    disable=status;
}
void TreeInfo::setRepeat(int repeat) {
    this->repeat=repeat;
}
void TreeInfo::setBaseRepeat(int brepeat) {
    this->baseRepeat=brepeat;
    ResetRepeat();
}
void TreeInfo::setItem(QModelIndex item) {
    this->item=item;
}
void TreeInfo::setParent(TreeInfo *parent) {
    this->parent=parent;
}
void TreeInfo::addChildTests(TreeInfo * test) {
    childTests.push_back(test);
}
void TreeInfo::addChildSuites(TreeInfo * suite) {
    childSuites.push_back(suite);
}
bool TreeInfo::DecreaseRepeat() {
    if(type=="suite") {
        if(repeat>1) {
            repeat--;
            qDebug()<<name+" : repeat is "+QString::number(repeat);
            return true;
        }
        else {
            qDebug()<<name+" : repeat is null";
            return false;
        }
    }
    else {
        if(repeat>0) {
            repeat--;
            qDebug()<<name+" : repeat is "+QString::number(repeat);
            return true;
        }
        else {
            qDebug()<<name+" : repeat is null";
            return false;
        }
    }
}
void TreeInfo::ResetRepeat() {
    repeat=baseRepeat;
}
void TreeInfo::ResetAllRepeat() {
    repeat=baseRepeat;
    for(auto&it:childTests) {
        it->ResetRepeat();
    }
    for(auto&it:childSuites) {
        it->ResetAllRepeat();
    }
}
void TreeInfo::ResetChildRepeat() {
    for(auto&it:childTests) {
        it->ResetRepeat();
    }
    for(auto&it:childSuites) {
        it->ResetAllRepeat();
    }
}
void TreeInfo::ResetFirsRun()
{
    firstRun=true;
    for(auto&it:childTests) {
        it->setFirsRun(true);
    }
    for(auto&it:childSuites) {
        it->ResetFirsRun();
    }
}
TreeInfo *TreeInfo::FindByItem(QModelIndex item)
{
    if(item==this->item) {
        return this;
    }
    for(auto&it:childTests) {
        if(item==it->getItem()) {
            return it;
        }
    }
    for(auto&it:childSuites) {
        auto res=it->FindByItem(item);
        if(res) {
            return res;
        }
    }
    return nullptr;
}

bool TreeInfo::isValid()
{
    if(name.isEmpty() || file.isEmpty() || repeat<1 || !item.isValid()) {
        return false;
    }
    for(auto&it:childTests) {
        if(it->getName().isEmpty() || it->getFile().isEmpty() || it->getRepeat()<1 || !it->getItem().isValid()) {
            return false;
        }
    }
    for(auto&it:childSuites) {
        auto res=it->isValid();
        if(!res) {
            return res;
        }
    }
    return true;
}

QStringList TreeInfo::getSuites()
{
    QStringList suites;
    if(type=="suite") {
        suites.append(name);
        for(auto&it:childSuites) {
            suites.append(it->getSuites());
        }
    }
    return suites;
}

TreeInfo *TreeInfo::getNextTest()
{
    if(disable) {
        return nullptr;
    }
    TreeInfo * nextTest=nullptr;
    for(auto&it:childTests) {
        if(!it->isDisable() && it->DecreaseRepeat()) {
            nextTest=it;
            qDebug()<<QString("Next test is")+it->getName();
            break;
        }
    }
    for(auto&it:childSuites) {
        nextTest=it->getNextTest();
        if(nextTest) {            
            qDebug()<<QString("Next test is")+nextTest->getName();
            break;
        }
    }
    if(!nextTest) {
        if(DecreaseRepeat()) {
            qDebug()<<QString("Next test din`t find. Decrese ")+name + "and reset children repeat";
            ResetChildRepeat();
            nextTest = getNextTest();
        }
    }
    return nextTest;
}

void TreeInfo::setAsFail()
{
    for(auto&it:parent->getChildTests()) {
        it->setRepeat(0);
    }
}
void TreeInfo::setFirsRun(bool val)
{
    firstRun=val;
}

bool TreeInfo::isFirstRun()
{
    return firstRun;
}
