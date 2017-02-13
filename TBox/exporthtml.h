#ifndef EXPORTHTML_H
#define EXPORTHTML_H
#include <database.h>
#include <QVector>
#include <QStringList>
#include <QObject>
#include <qDebug>
#include <QDir>
#include <QMessageBox>
class ExportHTML: public QObject
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
        QString suite_full_time_execution;
        int quant_el;
    };
    struct TestData{
        QString test_name;
        QString test_description;
        QString test_repeat;
        QString total_test_time = "0:0:0:0";
        QString test_pass;
        QString test_suite_name;
        QString test_msg;
        int quant_el;
    };
    struct Time{
        int h=0,m=0,s=0,ms=0;
    };
    TestData *testD;
    suiteData *suiteD;
     QString total_time;
   Q_INVOKABLE QVector<QStringList*> htmldata;
    Q_INVOKABLE QDir *dir;
    Q_INVOKABLE void CreateDirIfNotExists();
    Q_INVOKABLE void CreateHTMLReportFile(QVector<QStringList*> table_data_e,int elements_e,QStringList summary_data_e,
                                          QStringList test_r_e,QVector<QStringList*> suite_info_e,QString current_session);
    Q_INVOKABLE ExportHTML();
    Q_INVOKABLE QString export_path_;
    QVector<suiteData*> SD;
    QVector<TestData*> TD;
    QVector<QStringList*> table_data_;int elements_;QStringList summary_data_;
                                     QStringList test_r_;QVector<QStringList*> suite_info_;QString current_session;
    QString IntTimetoString(Time time);
    Time StringTimetoInt(QString time);
    void parseSuiteData(QVector<QStringList *> suite_info_, QVector<QStringList *> table_data_);
 public slots:

   void ReceiveHTMLdata(QVector<QStringList*> table_data_e,int elements_e,QStringList summary_data_e,
                        QStringList test_r_e,QVector<QStringList*> suite_info_e,QString current_session);
   void ReceiveHTMLpath(QString exportPath);

};

#endif // EXPORTHTML_H
