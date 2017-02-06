#include "databasemanager.h"
#define FOLDER_DB_NAME "DataBase\\\\"
#define DATABASE_NAME "TBoxData.db"
#define LOCALHOST "127.0.0.1"
DataBaseManager::DataBaseManager()
{
InitDB();
}
void DataBaseManager::sessionStart(){
    InitDB();
    start_time_ = QTime::currentTime().toString();
    current_date_.append(QDate::currentDate().toString("dd"));
    current_date_.append(QDate::currentDate().toString("MM"));
    current_date_.append(QDate::currentDate().toString("yyyy"));
    start_.start();
}
void DataBaseManager::sessionEnd(){
    msecs = start_.elapsed();
    end_time_ = QTime::currentTime().toString();
    end_date_.append(QDate::currentDate().toString("dd"));
    end_date_.append(QDate::currentDate().toString("MM"));
    end_date_.append(QDate::currentDate().toString("yyyy"));
    calcTime(msecs);
    createTest();
    ClearData();
}

void  DataBaseManager::calcTime(int msecs){
    hours = msecs/(1000*60*60);
    minutes = (msecs-(hours*1000*60*60))/(1000*60);
    seconds = (msecs-(minutes*1000*60)-(hours*1000*60*60))/1000;
    milliseconds = msecs-(seconds*1000)-(minutes*1000*60)-(hours*1000*60*60);
    session_execution.append(QString::number(hours)+":"+QString::number(minutes)+":"+QString::number(seconds)+":"+QString::number(milliseconds));
}
void DataBaseManager::InitDB(){
   db = QSqlDatabase::addDatabase("QSQLITE");
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
   db.setDatabaseName(path_for_db);
   db.setHostName(LOCALHOST);
             if(db.open()){
                 qDebug()<<"Database: connection ok";
             }
             else{
                 qDebug()<<db.lastError().text();
                 return;
             }
   QSqlQuery *qu = new QSqlQuery(db);
   qu->exec("select * from Info LIMIT 0,0 ");
   if( qu->record().count() <=0){
       delete qu; qu = new QSqlQuery(db);      
       qDebug()<<qu->exec("create table Info ( ID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, Test_Name TEXT NOT NULL, Test_Day INTEGER NOT NULL, Test_Month INTEGER NOT NULL, Test_Year INTEGER NOT NULL,"
                "Test_Passed INTEGER NOT NULL, Session_num INTEGER, Test_Suite TEXT, S_Start_time TEXT,Test_day_e INTEGER, Test_month_e INTEGER, Test_year_e INTEGER, S_Session_end TEXT, Session_duration TEXT)");
   }
}
void DataBaseManager::createTest(){
    if(!db.open()){
        qDebug()<<"db is not open";
        return;
    }
    query_ = new QSqlQuery(db);
    qDebug()<<query_->exec("insert into Info (Test_Name,Test_Day,Test_Month,Test_Year,Test_Passed,Session_num,Test_Suite,S_Start_time,Test_day_e,Test_month_e,Test_year_e,S_session_end,Session_duration) values ( '"+test_name_+"',"+current_date_.at(0)+" , "+current_date_.at(1)+", "+current_date_.at(2)+" , 'yes' "+", '"+QString::number(session_num_)+"' , '"+test_suite_+"' ,'"+start_time_+"',"+end_date_.at(0)+","+end_date_.at(1)+","+end_date_.at(2)+",'"+end_time_+"','"+session_execution+"');");
}
void DataBaseManager::getSuiteName(QString suite_name){
    test_suite_ = suite_name;

}
void DataBaseManager::getTestName(QString test_name){
    test_name_ = test_name;
}

void DataBaseManager::sessionNum(){
    qDebug()<<"session_started";
    if(!db.open()){
        qDebug()<<"cannot open db";
        return;
    }
    QSqlQuery *qu = new QSqlQuery(db);
    qu->exec("select max(Session_num) from Info");
    while(qu->next()){
        session_num_ = qu->value(0).toInt();
    }
    session_num_++;
    delete qu;
}
void DataBaseManager::ClearData(){
test_passed_.clear();
session_execution.clear();
start_time_.clear();
end_time_.clear();
current_date_.clear();
end_date_.clear();
msecs=0;
hours = 0;
minutes =0;
seconds = 0;
milliseconds =0;
delete query_;
}
