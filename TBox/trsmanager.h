#ifndef TRSMANAGER_H
#define TRSMANAGER_H

#include <QObject>
#include <QDirIterator>
#include "maintree.h"
#include <QDebug>

class TRSManager : public QObject
{
    Q_OBJECT
public:
    explicit TRSManager(QObject *parent = 0);
signals:

public slots:
    Q_INVOKABLE QString ParseFolder(QString);
    QString Parse(MainTree *, QString , QString);
    static QStringList getTestsName(QString);
    static QString getSuiteName(QString);
    static QString getJS(QString, QString);
    static QString Run(QString);

private:
    MainTree tree_;
};

#endif // TRSMANAGER_H
