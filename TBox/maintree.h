#ifndef MAINTREE_H
#define MAINTREE_H
#include <QStandardItemModel>
#include <QList>
class TreeInfo {
public:
    TreeInfo ():parent(nullptr){}
    TreeInfo (TreeInfo *parent, QString, QString, QString, int, QModelIndex);
    ~TreeInfo();
    QString getPath();
    QString getFile();
    QString getName();
    QString getType();
    bool isDisable();
    int getRepeat();
    int getBaseRepeat();
    QModelIndex getItem();
    TreeInfo * getParent();
    QList<TreeInfo *>& getChildTests();
    QList<TreeInfo *>& getChildSuites();
    void setFile(QString);
    void setName(QString);
    void setType(QString);
    void setDisable(bool);
    void setRepeat(int);
    void setBaseRepeat(int);
    void setItem(QModelIndex);
    void setParent(TreeInfo *);
    void addChildTests(TreeInfo *);
    void addChildSuites(TreeInfo *);
    bool DecreaseRepeat();
    void ResetRepeat();
    void ResetAllRepeat();
    void ResetChildRepeat();
    TreeInfo * FindByItem(QModelIndex);
    bool isValid();
    QStringList getSuites();
    TreeInfo * getNextTest();
    void setAsFail();
private:
    QString file;
    QString name;
    QString type;
    int repeat;
    int baseRepeat;
    bool disable;
    QModelIndex item; // make class and add root dir
    QList<TreeInfo *> childTests;
    QList<TreeInfo *> childSuites;
    TreeInfo * parent;
};
#endif // MAINTREE_H


