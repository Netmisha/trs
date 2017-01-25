#include "database.h"

DataBase::DataBase()
{

}

void DataBase::InitDB(){

   db = QSqlDatabase::addDatabase("QSQLITE");
           db.setDatabaseName("D:\\TRS\\TBox\\TestInfo.db");
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
