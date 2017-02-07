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
    void testFinish(QString);
    void testBegin(QString);
    void sendMessage(QString);
public slots:
    void setPath(QString);
    void setName(QString);
    Q_INVOKABLE QString getPath();
    Q_INVOKABLE QString getName();
    Q_INVOKABLE QString getCurrentDir();
    Q_INVOKABLE void setData(QString, QString);
    Q_INVOKABLE QString getData(QString);
    Q_INVOKABLE bool isData(QString);
    Q_INVOKABLE void FINISH();
    Q_INVOKABLE void BEGIN();
    Q_INVOKABLE void ExitOnFinish(bool);
protected:
    QString currentPath;
    QString testName;
    bool defaultExit=true;
};

#endif // TEST_H
