#ifndef SUITEINFO_H
#define SUITEINFO_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QDomDocument>

class SuiteInfo : public QObject
{
    Q_OBJECT
public:
    explicit SuiteInfo(QObject *parent = 0);
public slots:
    void setPath(QString);
    void setName(QString);
    Q_INVOKABLE QString getPath();
    Q_INVOKABLE QString getName();
    Q_INVOKABLE QString getCurrentDir();
    Q_INVOKABLE void setData(QString, QString);
    Q_INVOKABLE QString getData(QString);
    Q_INVOKABLE QString delData(QString);
    Q_INVOKABLE bool isData(QString);
protected:
    QString currentPath;
    QString testName;
    bool defaultExit=true;
};

#endif // SUITEINFO_H
