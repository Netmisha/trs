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
class DataBaseManager
{
private:
    void InitDB();
    void calcTime(int msecs);
    void createTest();
    QTime start_;
    QTime start_time;
    QTime end_time;

    QString test_name;
    QString session_num;
    QString test_passed;
    QString test_suite;

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
    void getSuiteName();
    void getTestName();
public:
    DataBaseManager();
    void sessionStart();
    void sessionEnd();
};

#endif // DATABASEMANAGER_H
