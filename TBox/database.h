#ifndef DATABASE_H
#define DATABASE_H
#include <QStringList>
#include <QQuickView>
#include <QObject>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QtSql>
#include <QVariantList>
#include <QGuiApplication>
#include <QtQml>
#include <QDebug>
#include <QtGui>
#include <QStringList>
class DataBase: public QObject
{

Q_OBJECT
public:
    DataBase();
    struct row_data{
       QString ID;
       QString Test_name;
       QString Test_Day;
       QString Test_Month;
       QString Test_Year;
       QString Test_Passed;
    };
    QVector<QString> Years;


    struct row_fields{
        QString ID = "ID";
        QString Test_name="Test_Name";
        QString Test_Day="Test_Day";
        QString Test_Month="Test_Month";
        QString Test_Year="Test_Year";
        QString Test_Passed="Test_Passed";
    };
    void FilterData();
    void InitDB();
    void getDataFromDB();
    Q_INVOKABLE  QString getID(int ind);
    Q_INVOKABLE QString getTestName(int ind);
    Q_INVOKABLE  QString getTestDay(int ind);
    Q_INVOKABLE QString getTestMonth(int ind);
    Q_INVOKABLE QString getTestYear(int ind);
    Q_INVOKABLE  QString getTestPassed(int ind);
    QVector<row_data*> getDBdata();
    //void setDataForDB();
public:
    QString db_name;
    row_fields *rfO;
    row_data *rdO; // rdO = row_data Object
    QVariantList rc_dataV;
    QVector <row_data*> rc_data;
    QSqlDatabase db;
    QSqlQuery *query;
    QStringList data;

};

#endif // DATABASE_H

