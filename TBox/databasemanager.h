#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include <QString>
#include <QTime>
#include <QDebug>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QStringList>
#include <mainwindow.h>
#include <QSqlRecord>
class DataBaseManager: public QObject
{
Q_OBJECT
private:
    void InitDB();
    void calcTime(int msecs);
    void createTest();
    void ClearData();
    QTime start_;
    QTime start_time;
    QTime end_time;

    QString test_name_;
    int session_num_;
    QString test_passed_;
    QString test_suite_;

    QString session_execution;
    QString start_time_;
    QString end_time_;
    QStringList current_date_;
    QStringList end_date_;
    int msecs=0;
    int hours = 0;
    int minutes =0;
    int seconds = 0;
    int milliseconds =0;
    QSqlDatabase db;
    QSqlQuery *query_;
public slots:
void getSuiteName(QString);
void getTestName(QString);
void sessionNum();
public:
    DataBaseManager();
    void sessionStart();
    void sessionEnd();
};

#endif // DATABASEMANAGER_H
