#include "databasemanager.h"
DataBaseManager::DataBaseManager()
{
InitDB(); // test passed not yet implemented
//test name,session num,test suite
}
void DataBaseManager::sessionStart(){
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
}

void  DataBaseManager::calcTime(int msecs){
    hours = msecs/(1000*60*60);
    minutes = (msecs-(hours*1000*60*60))/(1000*60);
    seconds = (msecs-(minutes*1000*60)-(hours*1000*60*60))/1000;
    milliseconds = msecs-(seconds*1000)-(minutes*1000*60)-(hours*1000*60*60);
    session_execution.append(QString::number(hours)+":"+QString::number(minutes)+":"+QString::number(seconds)+":"+QString::number(milliseconds));
}
void DataBaseManager::InitDB(){ // creates db if one does not exist
   db = QSqlDatabase::addDatabase("QSQLITE");
   db.setDatabaseName("D:\\TRS\\TBox\\TestInfo.db");
   db.setHostName("127.0.0.1");
             if(db.open()){
                 qDebug()<<"Database: connection ok";
             }
             else{
                 qDebug()<<db.lastError().text();
                 return;
             }

}
void DataBaseManager::createTest(){
     // QString Test_Day,QString Test_Month,QString Test_Year,QString Session_start_time
     //QString Test_EDay,QString Test_EMonth,QString Test_EYear,QString Session_end_time
    if(!db.open()){
        qDebug()<<"db is not open";
        return;
    }
 query_ = new QSqlQuery(db);
 query_->exec("insert into Info (Test_Name,Test_Day,Test_Month,Test_Year,Test_Passed,Session_num,Test_Suite,S_Start_time,Test_day_e,Test_month_e,Test_year_e,S_session_end,Session_duration) values ('Test_name','"+current_date_.at(0)+"' , '"+current_date_.at(1)+"' , '"+current_date_.at(2)+"' , 'yes' "+","+"'5'"+" , "+"'4'"+",'"+start_time_+"','"+end_date_.at(0)+"','"+end_date_.at(1)+"','"+end_date_.at(2)+"','"+end_time_+"','"+session_execution+"');");
}
void DataBaseManager::getSuiteName(){
  qDebug()<<"suite name";
}
void DataBaseManager::getTestName(){
    qDebug()<<"test name";
}

