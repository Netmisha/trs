#ifndef TREEINFO_H
#define TREEINFO_H
#include <QStandardItemModel>
#include <QList>
#include "datamanager.h"
class TreeInfo {
public:
    TreeInfo ():parent(nullptr){dm=new  DataManager();}
    TreeInfo (TreeInfo *parent, QString, QString, QString, int, QModelIndex);
    ~TreeInfo();
    QString getPath();
    QString getFile();
    int getPosition();
    QString getName();
    QString getType();
    bool isDisable();
    int getRepeat();
    int getBaseRepeat();
    QModelIndex getItem();
    TreeInfo * getParent();
    QList<TreeInfo *>& getChildren();
    void setFile(QString);
    void setName(QString);
    void setType(QString);
    void setPosition(int);
    void setDisable(bool);
    void setRepeat(int);
    void setBaseRepeat(int);
    void setItem(QModelIndex);
    void setParent(TreeInfo *);
    int addChild(TreeInfo *);
    bool DecreaseRepeat();
    void ResetRepeat();
    void ResetAllRepeat();
    void ResetChildRepeat();
    void ResetFirsRun();
    TreeInfo * FindByItem(QModelIndex);
    bool isValid();
    QStringList getSuites();
    TreeInfo * getNextTest();
    int setAsFail();
    int getTotalRuns();
    void setFirsRun(bool);
    bool isFirstRun();
private:
    QString file;
    QString name;
    QString type;
    int repeat;
    int baseRepeat;
    bool disable;
    bool firstRun=false;
    int position;
    QModelIndex item; // make class and add root dir
    QList<TreeInfo *> children;
    DataManager *dm;
    TreeInfo * parent=nullptr;
};
#endif // MAINTREE_H


