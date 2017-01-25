#ifndef MAINTREE_H
#define MAINTREE_H
#include <QStandardItemModel>
#include "trsmanager.h"
struct TreeInfo {
    QString file;
    QString name;
    QString type;
    int repeat;
    QModelIndex item;
};
#endif // MAINTREE_H


