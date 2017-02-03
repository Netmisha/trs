#ifndef TEST_H
#define TEST_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QDomDocument>

class TestInfo : public QObject
{
    Q_OBJECT
public:
    explicit TestInfo(QObject *parent = 0);
signals:

public slots:
    void setPath(QString);
    void setName(QString);
    Q_INVOKABLE QString getPath();
    Q_INVOKABLE QString getName();
    Q_INVOKABLE QString getCurrentDir();
    Q_INVOKABLE void setData(QString, QString);
    Q_INVOKABLE QString getData(QString);
    Q_INVOKABLE bool isData(QString);
private:
    QString currentPath;
    QString testName;
};

#endif // TEST_H
