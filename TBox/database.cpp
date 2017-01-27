#include "database.h"

DataBase::DataBase(QObject *parent) :
    QObject(parent)
{
}
void DataBase::InitDB(){
   db = QSqlDatabase::addDatabase("QSQLITE");
           db.setDatabaseName("D:/TRS/QtTRS/TestInfo.db");
           db.setHostName("127.0.0.1");
            if(db.open()){
                qDebug()<<"Database: connection ok";
            }
            else{
                qDebug()<<db.lastError().text();
            }
}
void DataBase::FilterData(){
    for(int i=0;i<rc_data.size();i++){
        if(!Years.contains(rc_data.at(i)->Test_Year)){
        Years.push_back(rc_data.at(i)->Test_Year);
        }
    }
}
void DataBase::getDataFromDB(){
    rdO = new DataBase::row_data;
    rfO = new DataBase::row_fields;
    query = new QSqlQuery(db);
    query->exec("SELECT * FROM Info");
    while (query->next()) {
       rdO->ID = query->value(query->record().indexOf(rfO->ID)).toString();
       rdO->Test_name = query->value(query->record().indexOf(rfO->Test_name)).toString();
       rdO->Test_Day = query->value(query->record().indexOf(rfO->Test_Day)).toString();
       rdO->Test_Month = query->value(query->record().indexOf(rfO->Test_Month)).toString();
       rdO->Test_Year = query->value(query->record().indexOf(rfO->Test_Year)).toString();
       rdO->Test_Passed = query->value(query->record().indexOf(rfO->Test_Passed)).toString();
       rc_data.push_back(rdO);
       rdO = new DataBase::row_data;
    }
FilterData();
}

QString DataBase::ParseDateS(QString data){
    QRegExp ex("(-|T|:)");
    Date_  = data.split(ex);
    QString T;
    T.append(Date_.at(2));
    T.append("/");
    T.append(Date_.at(1));
    T.append("/");
    T.append(Date_.at(0));
    return T;

}
QString DataBase::ParseDateE(QString data){
    QRegExp ex("(-|T|:)");
    Date_  = data.split(ex);
    QString T;
    T.append(Date_.at(2));
    T.append("/");
    T.append(Date_.at(1));
    T.append("/");
    T.append(Date_.at(0));
    return T;

}
QStringList DataBase::get_seesion_db( QString start,  QString end){
if(start.isEmpty() || end.isEmpty()){
   qDebug()<<"start or end date is empty";
   return it;
}
else{

            db = QSqlDatabase::addDatabase("QSQLITE");
            db.setDatabaseName("D:\\TRS\\TBox\\TestInfo.db");
            db.setHostName("127.0.0.1");
             if(db.open()){
                 qDebug()<<"Database: connection ok";
             }
             else{
                 qDebug()<<db.lastError().text();
                 return it ;
             }
              query = new QSqlQuery(db);

            QStringList start_dates = start.split("/");
           // QStringList month;
            //month<<"January"<<"February"<<"March"<<"April"<<"May"<<"June"<<"July"<<"August"<<"September"<<"October"<<"November"<<"December";
           // start_dates[1]  = month.at(start_dates.at(1).toInt());
            QStringList end_dates = end.split("/");
           // end_dates[1] = month.at(end_dates.at(1).toInt());
          // query->exec("select Session_num from Info where (Test_Day BETWEEN 01 and 03) or (Test_Month between 01 and 02) or (Test_Year between 2017 and 2017");
            //query->exec("select Session_num from Info where (Test_Day BETWEEN "+start_dates.at(0)+" and "+end_dates.at(0)+") OR "
             //           +"( Test_Month BETWEEN "+start_dates.at(1)+" AND "+end_dates.at(1)+") OR "
              //          +"(Test_Year BETWEEEN "+start_dates.at(2)+" AND "+end_dates.at(2)+")");
           query->exec("SELECT Session_num FROM Info WHERE (Test_Day BETWEEN "+start_dates.at(0)+" and "+end_dates.at(0)+") and (Test_Month between "
                       +start_dates.at(1)+" and "+end_dates.at(1)+") and (Test_Year between "+start_dates.at(2)+" and "+end_dates.at(2)+")");
           qDebug()<<query->executedQuery();
           while(query->next()){
              qDebug()<<query->value(query->record().indexOf("Session_num")).toString();
              it.append(query->value(query->record().indexOf("Session_num")).toString());
           }
          //this->engine->rootContext()->setContextProperty("MLM", QVariant::fromValue(it));
           return it;

}
return it;
}

QVector<DataBase::row_data*> DataBase::getDBdata(){
    return rc_data;
}
QString DataBase::getID(int index){
    return rc_data.at(index)->ID;
}
QString DataBase::getTestName(int index){
    return rc_data.at(index)->Test_name;
}
QString DataBase::getTestDay(int index){
    return rc_data.at(index)->Test_Day;
}
QString DataBase::getTestMonth(int index){
    return rc_data.at(index)->Test_Month;
}
QString DataBase::getTestYear(int index){
    return rc_data.at(index)->Test_Year;
}
QString DataBase::getTestPassed(int index){
    return rc_data.at(index)->Test_Passed;
}
