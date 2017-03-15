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
//for(int i=0;i<datalist.size();i++){
//delete datalist.at(i);
//}
    datalist.clear();
    QRegExp exp("/");
    start_dates = start.split(exp);
    std::reverse(start_dates.begin(),start_dates.end());
    end_dates = end.split(exp);
    std::reverse(end_dates.begin(),end_dates.end());
    QDir DIR;
    QStringList path = DIR.absolutePath().split("/");
   // path.removeLast();
   // path.append("TBox");
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
   QStringList pass_session_;
   QStringList pass_session;
   QStringList session_nums;
   cd_.append(QDate::currentDate().toString("dd"));
   cd_.append(QDate::currentDate().toString("MM"));
   cd_.append(QDate::currentDate().toString("yyyy"));
   int i=0;
   QStringList TestStatus;
   qDebug()<<query->exec("select Session_num, Test_Day,Test_Month,Test_Year,min(S_Start_time),Session_duration,Test_day_e,Test_month_e,Test_year_e,max(S_Session_end),Test_Passed from Info WHERE (Test_Day BETWEEN "+start_dates.at(0)+" and "+end_dates.at(0)+") and (Test_Month between "+start_dates.at(1)+" and "+end_dates.at(1)+") and (Test_Year between "+start_dates.at(2)+" and "+end_dates.at(2)+") group by Session_num order by Session_num desc" );
   QSqlQuery *query_ = new QSqlQuery(db);
   query_->exec("select Test_Passed,Session_num from info  where Test_Passed like '%fail%' order by Session_num desc");
   while(query_->next()){
     pass_session_.append(query_->value(query_->record().indexOf("Test_Passed")).toString());
     session_nums.append(query_->value(query_->record().indexOf("Session_num")).toString());
   }
   while(query->next()){
        QString res_ses;
         QStringList session_duration;
       it.append(query->value(query->record().indexOf("Session_num")).toString());
       //pass_session.append(query->value(query->record().indexOf("Test_Passed")).toString());
       Time_S.append( query->value(  query->record().indexOf("Test_Day")).toString());
       Time_S.append( query->value(  query->record().indexOf("Test_Month")).toString());
       Time_S.append( query->value(  query->record().indexOf("Test_Year")).toString());
       Time_S.append( query->value(  query->record().indexOf("min(S_Start_time)")).toString());
       Time_E.append( query->value(  query->record().indexOf("Test_day_e")).toString());
       Time_E.append( query->value(  query->record().indexOf("Test_month_e")).toString());
       Time_E.append( query->value(  query->record().indexOf("Test_year_e")).toString());
       Time_E.append( query->value(  query->record().indexOf("max(S_Session_end)")).toString());

       QString date_;
       date_ = QString::number(Time_E.at(0).toInt()-Time_S.at(0).toInt());
       if(date_.toInt()<0){
           date_ = QString::number(std::abs(date_.toInt()));
       }
      session_duration.append(date_);
      date_ = QString::number(Time_E.at(1).toInt()-Time_S.at(1).toInt());
      if(date_.toInt()<0){
          date_ = QString::number(std::abs(date_.toInt()));
      }
      session_duration.append(date_);
      date_ = QString::number(Time_E.at(2).toInt()-Time_S.at(2).toInt());
      if(date_.toInt()<0){
          date_ = QString::number(std::abs(date_.toInt()));
      }
      session_duration.append(date_);
      QRegExp exp(":");
      QString t = Time_E.at(3);
      QString t1 = Time_S.at(3);
      QStringList temp = t.split(exp);
      QStringList temp1 = t1.split(exp);
      QString time_res;
      QString time_time;
      QString TT = QString::number((temp.at(0).toInt()*60*60)+(temp.at(1).toInt()*60)+temp.at(2).toInt()); //end time
      QString TT1 = QString::number((temp1.at(0).toInt()*60*60)+(temp1.at(1).toInt()*60)+temp1.at(2).toInt()); //start time
      QString T_dif = QString::number(TT.toInt() - TT1.toInt());
      QString TT2 =  QString::number(T_dif.toInt() / 60);
      time_time.append(QString::number(TT2.toInt()/60));
      time_time.append(":");
      time_time.append(QString::number(TT2.toInt()%60));
      time_time.append(":");
      time_time.append(QString::number(T_dif.toInt()%60));
      /*
      time_time = QString::number(temp.at(0).toInt() - temp1.at(0).toInt());
      if(time_time.toInt()<0){
         time_time = QString::number(std::abs(time_time.toInt()));
      }
      time_res.append(time_time);
      time_res.append(":");
       time_time = QString::number(temp.at(1).toInt() - temp1.at(1).toInt());
       if(time_time.toInt()<0){
          time_time = QString::number(std::abs(time_time.toInt()+60));
       }
       time_res.append(time_time);
       time_res.append(":");
       time_time = QString::number(temp.at(2).toInt() - temp1.at(2).toInt());
       if(time_time.toInt()<0){
          time_time = QString::number(std::abs(time_time.toInt()+60));
       }
       */
        time_res.append(time_time);
        for(int i=0;i<session_duration.size();i++){
        res_ses.append(session_duration.at(i)+"/");
        }
        session_duration.clear();
        session_duration.append(time_res);
        res_ses.append(" "+session_duration.first());
       //duration_s.append(  query->value(  query->record().indexOf("Session_duration")).toString());
       for(int j=0,k=0;j<Time_S.size();j++,k++){
           Start_date_S.append(Time_S.at(j)+"/");
           End_date_S.append(Time_E.at(k)+"/");
       }

      if(session_nums.contains(it.at(i))){
      pass_session.append("fail");
      }else{pass_session.append("success");}
       datalist.append( new LisModel(it.at(i),Start_date_S,res_ses,End_date_S,pass_session.at(i)));

       Start_date_S.clear(); End_date_S.clear(); duration_s.clear();
       Time_S.clear(); Time_E.clear();
       i++;
    }
   /*
   QList<QObject*> temp;
   temp.reserve( datalist.size() );
   std::reverse_copy(datalist.begin(), datalist.end(), std::back_inserter( temp ) );
   datalist.clear(); datalist = temp;
*/

    engine->rootContext()->setContextProperty("MLM", QVariant::fromValue(datalist)); // list model
    list_from_ui = it;

    it.clear();
}
 QList<QObject*> DataBase::setDataList(QList<QObject*> list){
     tempData = list;
 }
QList<QObject*> DataBase::getReportList(){
    return tempData;

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
    exportFilePath.clear();
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
   // path.removeLast();
   // path.append("TBox");
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
           // for(int i=0;i<datalist.size();i++){
           // delete datalist.at(i);
            //}
            datalist.clear();
             qDebug()<<query->exec("select Session_num, Test_Day,Test_Month,Test_Year,min(S_Start_time),Session_duration,Test_day_e,Test_month_e,Test_year_e,max(S_Session_end),Test_Passed from Info WHERE (Test_Day BETWEEN "+start_dates.at(0)+" and "+end_dates.at(0)+") and (Test_Month between "+start_dates.at(1)+" and "+end_dates.at(1)+") and (Test_Year between "+start_dates.at(2)+" and "+end_dates.at(2)+") group by Session_num order by Session_num desc" );
            query->executedQuery();
           QStringList Time_S;
           QString res_ses;
            QStringList session_duration;
           QStringList Time_E;
           QString duration_s;
           QString Start_date_S;
           QString End_date_S;
           QStringList pass_session;
           QStringList session_nums;
           QStringList pass_session_;
           int i=0;
           QSqlQuery *query_ = new QSqlQuery(db);
           query_->exec("select Test_Passed,Session_num from info  where Test_Passed like '%fail%' order by Session_num desc");
           while(query_->next()){
             pass_session_.append(query_->value(query_->record().indexOf("Test_Passed")).toString());
             session_nums.append(query_->value(query_->record().indexOf("Session_num")).toString());
           }
           while(query->next()){    
              it.append(query->value(query->record().indexOf("Session_num")).toString());
              //pass_session.append(query->value(query->record().indexOf("Test_Passed")).toString());
              Time_S.append( query->value(  query->record().indexOf("Test_Day")).toString());
              Time_S.append( query->value(  query->record().indexOf("Test_Month")).toString());
              Time_S.append( query->value(  query->record().indexOf("Test_Year")).toString());
              Time_S.append( query->value(  query->record().indexOf("min(S_Start_time)")).toString());
              Time_E.append( query->value(  query->record().indexOf("Test_day_e")).toString());
              Time_E.append( query->value(  query->record().indexOf("Test_month_e")).toString());
              Time_E.append( query->value(  query->record().indexOf("Test_year_e")).toString());
              Time_E.append( query->value(  query->record().indexOf("max(S_Session_end)")).toString());
              //duration_s.append(  query->value(  query->record().indexOf("Session_duration")).toString());
              QString date_;
              date_ = QString::number(Time_E.at(0).toInt()-Time_S.at(0).toInt());
              if(date_.toInt()<0){
                  date_ = QString::number(std::abs(date_.toInt()));
              }
             session_duration.append(date_);
             date_ = QString::number(Time_E.at(1).toInt()-Time_S.at(1).toInt());
             if(date_.toInt()<0){
                 date_ = QString::number(std::abs(date_.toInt()));
             }
             session_duration.append(date_);
             date_ = QString::number(Time_E.at(2).toInt()-Time_S.at(2).toInt());
             if(date_.toInt()<0){
                 date_ = QString::number(std::abs(date_.toInt()));
             }
             session_duration.append(date_);
             QRegExp exp(":");
             QString t = Time_E.at(3);
             QString t1 = Time_S.at(3);
             QStringList temp = t.split(exp);
             QStringList temp1 = t1.split(exp);
             QString time_res;
             QString time_time;
             QString TT = QString::number((temp.at(0).toInt()*60*60)+(temp.at(1).toInt()*60)+temp.at(2).toInt());// end time
             QString TT1 = QString::number((temp1.at(0).toInt()*60*60)+(temp1.at(1).toInt()*60)+temp1.at(2).toInt()); //start time
             QString T_dif = QString::number(TT.toInt() - TT1.toInt());
             QString TT2 =  QString::number(T_dif.toInt() / 60);
             time_time.append(QString::number(TT2.toInt()/60));
             time_time.append(":");
             time_time.append(QString::number(TT2.toInt()%60));
             time_time.append(":");
             time_time.append(QString::number(T_dif.toInt()%60));
               time_res.append(time_time);
               for(int i=0;i<session_duration.size();i++){
               res_ses.append(session_duration.at(i)+"/");
               }
               session_duration.clear();
               session_duration.append(time_res);
               res_ses.append(" "+session_duration.first());
              for(int j=0,k=0;j<Time_S.size();j++,k++){
                  Start_date_S.append(Time_S.at(j)+"/");
                  End_date_S.append(Time_E.at(k)+"/");
              }
              if(session_nums.contains(it.at(i))){
              pass_session.append("fail");
              }else{pass_session.append("success");}
              datalist.append( new LisModel(it.at(i),Start_date_S,res_ses,End_date_S,pass_session.at(i)));
              Start_date_S.clear(); End_date_S.clear(); duration_s.clear();res_ses.clear();
              Time_S.clear(); Time_E.clear();
              session_duration.clear();
              i++;
           }
           /*
           QList<QObject*> temp;
           temp.reserve( datalist.size() );
           std::reverse_copy(datalist.begin(), datalist.end(), std::back_inserter( temp ) );
           datalist.clear(); datalist = temp;*/
           tempData = datalist;
           engine->rootContext()->setContextProperty("MLM", QVariant::fromValue(datalist)); // list model
           list_from_ui = it;
           it.clear();
           return it;
}
void DataBase::callBrowser(){
    QDir dir;
    QString path = dir.absolutePath();
    QStringList pathToHtml = path.split("/");
    path.clear();
    for(int i=0;i<pathToHtml.size();i++){
        path.append(pathToHtml.at(i)+"//");
    }
    path.append("WebViewSessionTable.html");
    QString link = "file:///" +path;
    QDesktopServices::openUrl(QUrl(link));

}
void DataBase::setListFromUI(QString l){

        list_from_ui.append(QString::number(l.toInt()));

}
QString DataBase::row_selected(QString row){
    Sumary_data.clear();
    //for(int i=0;i<session_data.size();i++){
   //     delete session_data[i];
   // }
    session_data.clear();
   // for(int i=0;i<Suite_info.size();i++){
   //     delete Suite_info[i];
   // }
    Suite_info.clear();
    tn.clear();
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
          qu->exec("SELECT Test_Name,Test_Suite,Test_Passed,Test_repeat,Session_duration,Test_repeat,Test_Desc,Test_msg FROM Info WHERE Session_num = "+list_from_ui.at(row.toInt()));
         row_fields rf;
         while(qu->next()){
            e = new QStringList;
            e->append(qu->value(qu->record().indexOf(rf.Test_name)).toString());
            e->append(qu->value(qu->record().indexOf("Test_Desc")).toString());
            e->append(qu->value(qu->record().indexOf("Test_repeat")).toString());
            e->append(qu->value(qu->record().indexOf("Session_duration")).toString());
            e->append(qu->value(qu->record().indexOf(rf.Test_Passed)).toString());
            e->append(qu->value(qu->record().indexOf(rf.Test_Suite)).toString());
            e->append(qu->value(qu->record().indexOf("Test_msg")).toString());
            session_data.push_back(e);
         }
    delete qu; qu = new QSqlQuery(db);

    QStringList *Suite;
    qu = new QSqlQuery(db);
    QStringList t;
    qu->exec("select Test_Passed from Info where Session_num = "+list_from_ui.at(row.toInt()));

     int y=0,n=0;
    while(qu->next()){
        t.append(qu->value(qu->record().indexOf(rf.Test_Passed)).toString());
    }

    for(int i=0;i<t.size();i++){
        (t.at(i)=="success")?y++:n++;
    }
    (y > n)? Sumary_data.append("All tests passed"):Sumary_data.append("Tests have failed");
    delete qu;

 qu = new QSqlQuery(db);

    qu->exec("select Test_Suite,Suite_repeat, Suite_desc, count(distinct Test_Name) from Info where Session_num = "+list_from_ui.at(row.toInt())+" group by Test_Suite");
    while(qu->next()){
        Suite = new QStringList;
        Suite->append(qu->value(qu->record().indexOf("Test_Suite")).toString());
        Suite->append(qu->value(qu->record().indexOf("Suite_desc")).toString());
        Suite->append(qu->value(qu->record().indexOf("Suite_repeat")).toString());
        Suite->append("Total");
        (y > n)? Suite->append("success"):Suite->append("fail");
        Suite->append(qu->value(qu->record().indexOf("count(distinct Test_Name)")).toString());
        Suite_info.append(Suite);
    }

    current_session = list_from_ui.at(row.toInt());
    index = e->size();
    delete qu;
    SessionWindowTable WindowTable;
    qu = new QSqlQuery(db);
     qu->exec("select min(Test_Day), min(Test_Month),min(Test_Year),min(S_Start_time) from Info where Session_num ="+list_from_ui.at(row.toInt()));
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
     qu->exec("select Session_duration from Info where Session_num ="+list_from_ui.at(row.toInt()));
    QStringList Duration;
    while(qu->next()){
        Duration.append(qu->value(qu->record().indexOf("Session_duration")).toString());
    }

    Sumary_data.append(Duration);
   // emit sendSummaryData(Sumary_data);
    WindowTable.setIndex(row.toInt());
    WindowTable.setTableNames(tn);
    QDir DIR;
    QStringList path = DIR.absolutePath().split("/");
    QString table_path;
    //path.removeLast();
    //path.append("TBox");
    for(int i=0;i<path.size();i++){
        table_path.append(path.at(i)+"\\\\");
    }
    table_path.append("WebViewSessionTable.html");
    TableSessionPath =table_path;
    QStringList test_r; test_r.append(QString::number(y)); test_r.append(QString::number(n));
    table_data_e = session_data;
    elements_e = e->size();
    summary_data_e = Sumary_data;
    test_r_e =  test_r;
    suite_info_e = Suite_info;
    WindowTable.CreateTable(table_path,session_data,e->size(),Sumary_data,test_r,Suite_info);

    /*
    for(int i=0;i<session_data.size();i++){
        session_data.at(i)->clear();
    }
    Sumary_data.clear();
    session_data.clear();
    */
    tn.clear();
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
