#include "database.h"
#define FOLDER_DB_NAME "DataBase\\\\"
#define DATABASE_NAME "TBoxData.db"
#define LOCALHOST "127.0.0.1"
#include <algorithm>
DataBase::DataBase(QObject *parent) :
    QObject(parent)
{

}
void DataBase::defaultTableValue(QString start, QString end){

    QRegExp exp("/");
    start_dates = start.split(exp);
    std::reverse(start_dates.begin(),start_dates.end());
    end_dates = end.split(exp);
    std::reverse(end_dates.begin(),end_dates.end());
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
    QSqlQuery *query = new QSqlQuery(db);
   QStringList cd_;
   QStringList Time_S;
   QStringList Time_E;
   QString duration_s;
   QString Start_date_S;
   QString End_date_S;
   QStringList pass_session;
   cd_.append(QDate::currentDate().toString("dd"));
   cd_.append(QDate::currentDate().toString("MM"));
   cd_.append(QDate::currentDate().toString("yyyy"));
   int i=0;
   qDebug()<< query->exec("select Session_num, Test_Day,Test_Month,Test_Year,min(S_Start_time),Session_duration,Test_day_e,Test_month_e,Test_year_e,max(S_Session_end),Test_Passed from Info WHERE (Test_Day BETWEEN "+start_dates.at(0)+" and "+end_dates.at(0)+") and (Test_Month between "+start_dates.at(1)+" and "+end_dates.at(1)+") and (Test_Year between "+start_dates.at(2)+" and "+end_dates.at(2)+") group by Session_num" );
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
   emit sendExportPath(exportFilePath);
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
    if(!start.isEmpty()){
        start_dates = start.split("/");
    }
    if(!end.isEmpty()){
        end_dates = end.split("/");
    }
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
         qDebug()<<qu->exec("SELECT Test_Name,Test_Suite,Test_Passed,Test_repeat,Session_duration,Test_repeat,Test_Desc FROM Info WHERE Session_num = "+list_from_ui.at(row.toInt()));
         row_fields rf;
         while(qu->next()){
            e = new QStringList;
            e->append(qu->value(qu->record().indexOf(rf.Test_name)).toString());
            e->append(qu->value(qu->record().indexOf("Test_Desc")).toString());
            e->append(qu->value(qu->record().indexOf("Test_repeat")).toString());
            e->append(qu->value(qu->record().indexOf("Session_duration")).toString());
            e->append(qu->value(qu->record().indexOf(rf.Test_Passed)).toString());
            e->append(qu->value(qu->record().indexOf(rf.Test_Suite)).toString());
            session_data.push_back(e);
         }
    QVector<QStringList*> suite_full_time;
    QStringList *suite_time;

    delete qu; qu = new QSqlQuery(db);
    QVector<QStringList*> Suite_info;
    QStringList *Suite;


   qDebug()<<qu->exec("select Test_Suite,Suite_repeat, Suite_desc, count(distinct Test_Name) from Info where Session_num = "+list_from_ui.at(row.toInt())+" group by Test_Suite");
    while(qu->next()){
        Suite = new QStringList;
        Suite->append(qu->value(qu->record().indexOf("Test_Suite")).toString());
        Suite->append(qu->value(qu->record().indexOf("Suite_desc")).toString());
        Suite->append(qu->value(qu->record().indexOf("Suite_repeat")).toString());
        Suite->append("Total");
        Suite->append("Pass");
        Suite->append(qu->value(qu->record().indexOf("count(distinct Test_Name)")).toString());
        Suite_info.append(Suite);
    }
    current_session = list_from_ui.at(row.toInt());
    index = e->size();
    delete qu;
    qu = new QSqlQuery(db);
    QStringList t;
    qu->exec("select Test_Passed from Info where Session_num = "+list_from_ui.at(row.toInt()));
    while(qu->next()){
        t.append(qu->value(qu->record().indexOf(rf.Test_Passed)).toString());
    }
    int y=0,n=0;
    for(int i=0;i<t.size();i++){
        (t.at(i)=="yes")?y++:n++;
    }
    (y > n)? Sumary_data.append("All tests passed"):Sumary_data.append("Some tests didn't make it");
    delete qu;
    SessionWindowTable WindowTable;
    qu = new QSqlQuery(db);
    qDebug()<<qu->exec("select min(Test_Day), min(Test_Month),min(Test_Year),min(S_Start_time) from Info where Session_num ="+list_from_ui.at(row.toInt()));
    QString Start_time;
    while(qu->next()){
        Start_time.append(qu->value(qu->record().indexOf("min(Test_Day)")).toString());
        Start_time.append("/");
        Start_time.append(qu->value(qu->record().indexOf("min(Test_Month)")).toString());
        Start_time.append("/");
        Start_time.append(qu->value(qu->record().indexOf("min(Test_Year)")).toString());
        Start_time.append(" ");
        Start_time.append(qu->value(qu->record().indexOf("min(S_Start_time)")).toString());
    }
    Sumary_data.append(Start_time);
    delete qu;
    qu = new QSqlQuery(db);
    qu->exec("select max(Test_day_e), max(Test_month_e),max(Test_year_e),max(S_Session_end) from Info where Session_num ="+list_from_ui.at(row.toInt()));
    QString End_time;
    while(qu->next()){
        End_time.append(qu->value(qu->record().indexOf("max(Test_day_e)")).toString());
        End_time.append("/");
        End_time.append(qu->value(qu->record().indexOf("max(Test_month_e)")).toString());
        End_time.append("/");
        End_time.append(qu->value(qu->record().indexOf("max(Test_year_e)")).toString());
        End_time.append(" ");
        End_time.append(qu->value(qu->record().indexOf("max(S_Session_end)")).toString());
    }
    Sumary_data.append(End_time);
    delete qu;
    qu = new QSqlQuery(db);
    qDebug()<<qu->exec("select Session_duration from Info where Session_num ="+list_from_ui.at(row.toInt()));
    QStringList Duration;
    while(qu->next()){
        Duration.append(qu->value(qu->record().indexOf("Session_duration")).toString());
    }
    qDebug()<<Duration;
    Sumary_data.append(Duration);
    emit sendSummaryData(Sumary_data);
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
    QStringList test_r; test_r.append(QString::number(y)); test_r.append(QString::number(n));
    WindowTable.CreateTable(table_path,session_data,e->size(),Sumary_data,test_r,Suite_info);
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
