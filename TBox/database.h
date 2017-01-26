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
class DataBase: public QObject,public QStandardItem
{

Q_OBJECT
    Q_PROPERTY(QString getDateQML READ getDateQML WRITE setDateQML NOTIFY DateChanged)
    Q_PROPERTY(QString get_EndDate READ get_EndDate WRITE setEndDateQML NOTIFY EndDateChanged)
signals:
   void DateChanged();
   void EndDateChanged();
public slots:
    Q_INVOKABLE void get_seesion_db( QString start, QString end);
public:
   //DataBase(QQmlApplicationEngine *engine);
    explicit DataBase(QObject *parent = 0);
    QString date;

     Q_INVOKABLE QString DateQML;
     Q_INVOKABLE QString End_date;
    struct row_data{
       QString ID;
       QString Test_name;
       QString Test_Day;
       QString Test_Month;
       QString Test_Year;
       QString Test_Passed;
    };
    Q_INVOKABLE QQmlApplicationEngine *engine;
    QVector<QString> Years;
    Q_INVOKABLE QString getDateQML(){
       return DateQML;
   }
   Q_INVOKABLE void setDateQML(QString &arg){
       if (DateQML == arg) return;
       DateQML = arg;
       DateQML = ParseDateS(DateQML);
       emit DateChanged();

   }
   Q_INVOKABLE QString get_EndDate(){
        return End_date;
    }
    Q_INVOKABLE void setEndDateQML(QString &arg){
        if (End_date == arg) return;
        End_date = arg;
        End_date = ParseDateE(End_date);
        emit EndDateChanged();

    }
   Q_INVOKABLE QString ParseDateS(QString data);
     Q_INVOKABLE QString ParseDateE(QString data);
   QStringList Date_;

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

