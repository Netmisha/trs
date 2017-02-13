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
    hours = msecs/(100*60*60);
    minutes = (msecs-(hours*100*60*60))/(100*60);
    seconds = (msecs-(minutes*100*60)-(hours*1000*60*60))/100;
    milliseconds = msecs-(seconds*100)-(minutes*100*60)-(hours*100*60*60);
    session_execution.append(QString::number(hours)+":"+QString::number(minutes)+":"+QString::number(seconds)+":"+QString::number(milliseconds));
}
void DataBaseManager::getTestMsg(QString msg){
  QRegExp exp("_");
  QStringList t = msg.split(exp);
  test_msg.append(t.at(1));
  test_status = t.at(0);
  /*
  if(test_status == "success"){
      test_status = "yes";
  }else if(test_status == "fail"){
      test_status = "no";
  }*/
}
void DataBaseManager::InitDB(){
    //msecs =  test duration;
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
                "Test_Passed INTEGER NOT NULL, Session_num INTEGER, Test_Suite TEXT, S_Start_time TEXT,Test_day_e INTEGER, Test_month_e INTEGER, Test_year_e INTEGER, S_Session_end TEXT, Session_duration TEXT,Test_repeat TEXT,Test_Desc TEXT,Suite_repeat TEXT, Suite_desc TEXT,Test_msg TEXT)");
   }
}

void DataBaseManager::createTest(){
    if(!db.open()){
        qDebug()<<"db is not open";
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
                     "Test_Passed INTEGER NOT NULL, Session_num INTEGER, Test_Suite TEXT, S_Start_time TEXT,Test_day_e INTEGER, Test_month_e INTEGER, Test_year_e INTEGER, S_Session_end TEXT, Session_duration TEXT,Test_repeat TEXT,Test_Desc TEXT,Suite_repeat TEXT, Suite_desc TEXT,Test_msg TEXT)");
        }
        //return;
    }

    query_ = new QSqlQuery(db);
    qDebug()<<query_->exec("insert into Info (Test_Name,Test_Day,Test_Month,Test_Year,Test_Passed,Session_num,Test_Suite,S_Start_time,Test_day_e,Test_month_e,Test_year_e,S_session_end,Session_duration,Test_repeat,Test_Desc,Suite_repeat,Suite_desc,Test_msg) values ( '"+test_name_+"',"+current_date_.at(0)+" , "+current_date_.at(1)+", "+current_date_.at(2)+" , '"+test_status+"', '"+QString::number(session_num_)+"' , '"+test_suite_+"' ,'"+start_time_+"',"+end_date_.at(0)+","+end_date_.at(1)+","+end_date_.at(2)+",'"+end_time_+"','"+session_execution+"', '"+repeatNumTest+"','"+test_desc+"', '"+SuiteRepeat+"','"+SuiteDesc+"','"+test_msg+"');");
    test_msg.clear();
}
void DataBaseManager::getDescTest(QString description){
    test_desc = description;
}
void DataBaseManager::getSuiteName(QString suite_name){
    test_suite_ = suite_name;

}
void DataBaseManager::getSuiteInfo(QString desc, QString repeat){
    SuiteDesc = desc; SuiteRepeat = repeat;
}
void DataBaseManager::getTestName(QString test_name){
    test_name_ = test_name;
}
void DataBaseManager::getRepeatNum(QString repeat_num){
    repeatNumTest = repeat_num;

}
void DataBaseManager::sessionNum(){
    qDebug()<<"session_started";
    if(!db.open()){
        qDebug()<<"cannot open db";
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
test_suite_.clear();
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
