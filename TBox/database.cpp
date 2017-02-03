#include "database.h"
#define FOLDER_DB_NAME "DataBase\\\\"
#define DATABASE_NAME "TBoxData.db"
#define LOCALHOST "127.0.0.1"
DataBase::DataBase(QObject *parent) :
    QObject(parent)
{

}
void DataBase::InitDB(){
    QDir DIR;
    QStringList path = DIR.absolutePath().split("/");
    path.removeLast();
    path.append("TBox");
    QString path_for_db;
    for(int i=0;i<path.size();i++){
        path_for_db.append(path.at(i)+"\\\\");
    }
    path_for_db.append(FOLDER_DB_NAME);
    if(!QDir().exists(path_for_db)){
        QDir().mkdir(path_for_db);
    }
    path_for_db.append(DATABASE_NAME);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path_for_db);
    db.setHostName(LOCALHOST);
              if(db.open()){
                  qDebug()<<"Database: connection ok";
              }
              else{
                  qDebug()<<db.lastError().text();
                  return;
              }
}
void DataBase::getExportPath(QString path){
   QRegExp exp("file| ///|/");
   QStringList l = path.split(exp);
   l.removeFirst();
   l.removeFirst();
   l.removeFirst();
   l.removeFirst();
   for(int i=0;i<l.size();i++){
       exportFilePath.append(l.at(i)+"/");
   }
}
QString DataBase::getTableSessionPath(){
   return TableSessionPath;
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
    QDir DIR;
    QStringList path = DIR.absolutePath().split("/");
    path.removeLast();
    path.append("TBox");
    QString path_for_db;
    for(int i=0;i<path.size();i++){
        path_for_db.append(path.at(i)+"\\\\");
    }
    path_for_db.append(FOLDER_DB_NAME);
    if(!QDir().exists(path_for_db)){
        QDir().mkdir(path_for_db);
    }
    path_for_db.append(DATABASE_NAME);
            db = QSqlDatabase::addDatabase("QSQLITE");
            db.setDatabaseName(path_for_db);
            db.setHostName(LOCALHOST);

             if(db.open()){
                 qDebug()<<"Database: connection ok";
             }
             else{
                 qDebug()<<db.lastError().text();
                 return it ;
             }
            query = new QSqlQuery(db);
            datalist.clear();
            start_dates = start.split("/");
            end_dates = end.split("/");
           qDebug()<< query->exec("select Session_num, Test_Day,Test_Month,Test_Year,min(S_Start_time),Session_duration,Test_day_e,Test_month_e,Test_year_e,max(S_Session_end),Test_Passed from Info WHERE (Test_Day BETWEEN "+start_dates.at(0)+" and "+end_dates.at(0)+") and (Test_Month between "+start_dates.at(1)+" and "+end_dates.at(1)+") and (Test_Year between "+start_dates.at(2)+" and "+end_dates.at(2)+") group by Session_num" );
           qDebug()<<query->executedQuery();
           QStringList Time_S;
           QStringList Time_E;
           QString duration_s;
           QString Start_date_S;
           QString End_date_S;
           QStringList pass_session;
           int i=0;
           while(query->next()){    
              it.append(query->value(query->record().indexOf("Session_num")).toString());
              pass_session.append(query->value(query->record().indexOf("Test_Passed")).toString());
              Time_S.append( query->value(  query->record().indexOf("Test_Day")).toString());
              Time_S.append( query->value(  query->record().indexOf("Test_Month")).toString());
              Time_S.append( query->value(  query->record().indexOf("Test_Year")).toString());
              Time_S.append( query->value(  query->record().indexOf("min(S_Start_time)")).toString());
              Time_E.append( query->value(  query->record().indexOf("Test_day_e")).toString());
              Time_E.append( query->value(  query->record().indexOf("Test_month_e")).toString());
              Time_E.append( query->value(  query->record().indexOf("Test_year_e")).toString());
              Time_E.append( query->value(  query->record().indexOf("max(S_Session_end)")).toString());
              duration_s.append(  query->value(  query->record().indexOf("Session_duration")).toString());
              for(int j=0,k=0;j<Time_S.size();j++,k++){
                  Start_date_S.append(Time_S.at(j)+"/");
                  End_date_S.append(Time_E.at(k)+"/");
              }
              datalist.append( new LisModel(it.at(i),Start_date_S,duration_s,End_date_S,pass_session.at(i)));
              Start_date_S.clear(); End_date_S.clear(); duration_s.clear();
              Time_S.clear(); Time_E.clear();
              i++;
           }
           engine->rootContext()->setContextProperty("MLM", QVariant::fromValue(datalist)); // list model
           list_from_ui = it;
           it.clear();
           return it;
}
return it;
}
QString DataBase::row_selected(QString row){
    // qDebug()<<list_from_ui.at(row.toInt());
     QSqlQuery *qu;
     if(!db.isOpen()){
         qDebug()<<"Database is not open";
         return row;
     }
         qu = new QSqlQuery(db);
         qu->exec("select * from Info LIMIT 0,0 ");
         QSqlRecord rec = qu->record();
         for(int i=0;i<rec.count();i++){
             tn.append(rec.fieldName(i)); // save db columns
         }
         qDebug()<<list_from_ui;
         qDebug()<<qu->exec("SELECT Test_Name,Test_Suite,Test_Passed FROM Info WHERE Session_num = "+list_from_ui.at(row.toInt()));
         row_fields rf;
         while(qu->next()){
            e = new QStringList;
            e->append(qu->value(qu->record().indexOf(rf.Test_name)).toString());
            e->append(qu->value(qu->record().indexOf(rf.Test_Suite)).toString());
            e->append(qu->value(qu->record().indexOf(rf.Test_Passed)).toString());
            session_data.push_back(e);
         }
    current_session = list_from_ui.at(row.toInt());
    index = e->size();
    SessionWindowTable WindowTable;
    WindowTable.setIndex(row.toInt());
    WindowTable.setTableNames(tn);
    QDir DIR;
    QStringList path = DIR.absolutePath().split("/");
    QString table_path;
    path.removeLast();
    path.append("TBox");
    for(int i=0;i<path.size();i++){
        table_path.append(path.at(i)+"\\\\");
    }
    table_path.append("WebViewSessionTable.html");
    TableSessionPath =table_path;
    WindowTable.CreateTable(table_path,session_data,e->size());
    return row;
 }
void DataBase::Export_Clicked(){
    qDebug()<<"Export clicked";

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
