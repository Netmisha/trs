#ifndef TRSMANAGER_H
#define TRSMANAGER_H

#include <QObject>
#include <QDirIterator>
#include <QtWebKitWidgets/QWebPage>
#include <QtWebKitWidgets/QWebView>
#include <QtWebKitWidgets/QWebFrame>
#include "maintree.h"
#include <QDebug>
extern QWebView * view;
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
    static void Run(QString);

private:
    MainTree tree_;
};

#endif // TRSMANAGER_H
