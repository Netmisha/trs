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
#include <QQmlApplicationEngine>
#include <sessionwindowtable.h>
#include <exporthtml.h>
#include <lismodel.h>
#include <QQuickView>
class DataBase: public QObject // class for reading data from DB
{

Q_OBJECT
    Q_PROPERTY(QString getDateQML READ getDateQML WRITE setDateQML NOTIFY DateChanged)
    Q_PROPERTY(QString get_EndDate READ get_EndDate WRITE setEndDateQML NOTIFY EndDateChanged)
signals:
   void DateChanged();
   void EndDateChanged();
   void PassHTMLdata(QVector<QStringList*> data,QStringList tn,int index,QString current_session);
public slots:
    Q_INVOKABLE QStringList get_seesion_db( QString start, QString end);
   Q_INVOKABLE void Export_Clicked();
signals:
   void sendExportPath(QString exp);
   void sendSummaryData(QStringList sum_data);
public:
   Q_INVOKABLE QStringList Sumary_data;
   Q_INVOKABLE void defaultTableValue(QString start, QString end);
   Q_INVOKABLE QString getTableSessionPath();
   Q_INVOKABLE void getExportPath(QString path);
   Q_INVOKABLE QString exportFilePath;
   Q_INVOKABLE QString TableSessionPath;
   Q_INVOKABLE QList<QObject*> datalist;
   Q_INVOKABLE QString current_session;
   Q_INVOKABLE int index;
   Q_INVOKABLE QString path_for_db;
   Q_INVOKABLE void test(){
       qDebug()<<"Inside";
      emit PassHTMLdata(session_data,tn,index,current_session);
   }
   Q_INVOKABLE QString datad(int i){
       if(i==0){
   return "Hello from func";
       }else{return "new";}
   }

    explicit DataBase(QObject *parent = 0);
     QString date;
     Q_INVOKABLE QString DateQML;
     Q_INVOKABLE QString End_date;
     Q_INVOKABLE QString row_selected(QString row);
     Q_INVOKABLE QString row_;

     struct row_data{
        QString ID;
        QString Test_name;
        QString Test_Day;
        QString Test_Month;
        QString Test_Year;
        QString Test_Passed;
     };
     Q_INVOKABLE QStringList tn;
    Q_INVOKABLE QStringList *e;
     Q_INVOKABLE QVector <QStringList*> session_data;
     Q_INVOKABLE QVector<QVector<QStringList*>> pass;

     QQuickView *engine;
     Q_INVOKABLE void setEngi(QQuickView *e){
             engine = e;
     }
     //
     Q_INVOKABLE QStringList start_dates;
     Q_INVOKABLE  QStringList end_dates;
     //
     Q_INVOKABLE QStringList it;
     Q_INVOKABLE QStringList list_from_ui;
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
         QString Test_Suite = "Test_Suite";
         QString Test_Passed="Test_Passed";
     };
     QVector<QStringList*> htmlData;
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

     row_fields *rfO;
     row_data *rdO; // rdO = row_data Object
     QVariantList rc_dataV;
     QVector <row_data*> rc_data;
     QSqlDatabase db;
     QSqlQuery *query;
     QStringList data;

 };

 #endif // DATABASE_H

