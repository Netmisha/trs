#ifndef TEST_H
#define TEST_H

#include <QObject>
#include <QFile>
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
    Q_INVOKABLE void SetData(QString, QString);
    Q_INVOKABLE QString GetData(QString);
private:
    QString currentPath;
    QString testName;
};

#endif // TEST_H
