#ifndef TRSCORE_H
#define TRSCORE_H

#include <QObject>
#include <QProcess>
#include <QTest>
#include <QTestEventList>

class TRSCore : public QObject
{
    Q_OBJECT
public:
    explicit TRSCore(QObject *parent = 0);
    void StartApp(QString);
    void CloseApp();
signals:

public slots:
private:
    QProcess *process;
};

#endif // TRSCORE_H
