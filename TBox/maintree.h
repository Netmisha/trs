#ifndef MAINTREE_H
#define MAINTREE_H
#include <QStandardItemModel>
#include "report.h"
class TreeInfo {
public:
    TreeInfo (){}
    TreeInfo (QString, QString, QString, int, QModelIndex);
    QString getPath();
    QString file;
    QString name;
    QString type;
    int repeat;
    QModelIndex item; // make class and add root dir
};
#endif // MAINTREE_H


