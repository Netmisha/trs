#ifndef SESSIONWINDOWTABLE_H
#define SESSIONWINDOWTABLE_H
#include <QString>
#include <QVector>
#include <QObject>
#include <QFile>
#include <QFileInfo>
#include <qdebug.h>
#include <QVector>
#include <QTime>
class SessionWindowTable: public QObject
{
Q_OBJECT
public:
    struct suiteData{
        QString suite_name;
        QString suite_description;
        QString repeat;
        QString total_time;
        QString pass;
        QString test_num;
        int quant_el;
    };
    struct TestData{
        QString test_name;
        QString test_description;
        QString test_repeat;
        QString total_test_time;
        QString test_pass;
        QString test_suite_name;
        int quant_el;
    };
    struct Time{
        int h=0,m=0,s=0,ms=0;
    };
    Time *count_time;
    TestData *testD;
    suiteData *suiteD;
    QString html_path;
    bool file_open=0;
    int index;
    QStringList table_n;
    SessionWindowTable();
    int elements_;
    QVector<suiteData*> SD;
    QVector<TestData*> TD;
    Time StringTimetoInt(QString time_data);
    QString IntTimetoString(Time time);
    QVector<QStringList> suite_data;
    void parseSuiteData(QVector<QStringList*> suite_info_,QVector<QStringList*> table_data_);
    void setTableNames(QStringList table_name);
    QStringList getTableNames();
    void CreateTable(QString html_url,QVector<QStringList*> table_data,int elements,QStringList summary_data,QStringList test_r,QVector<QStringList*> suite_info);
    int getIndex();
    void setIndex(int i);
    void setHTMLPath(QString html_url);
    QString getHTMLPath();
    void CreateHTMLTable( QVector<QStringList*> table_data,int elements,QStringList summary_data,QStringList test_r,QVector<QStringList*> suite_info);
    void setTableData( QVector<QStringList*> table_data);


};

#endif // SESSIONWINDOWTABLE_H

