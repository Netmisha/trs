#include "sessionwindowtable.h"

SessionWindowTable::SessionWindowTable()
{

}
void SessionWindowTable::setHTMLPath(QString html_url){
    html_path = html_url;

}
QString SessionWindowTable::getHTMLPath(){
    return html_path;
}
int SessionWindowTable::getIndex(){
    return index;
}
void SessionWindowTable::setIndex(int i){

    index = i;
}
void SessionWindowTable::setTableNames(QStringList table_name){
    table_n = table_name;

}
QStringList SessionWindowTable::getTableNames(){
    return table_n;

}
void SessionWindowTable::CreateHTMLTable(QVector<QStringList*> table_data,int elements,QStringList summary_data,QStringList test_r,QVector<QStringList*> suite_info){
    elements_ = elements;
    QFile file(getHTMLPath());
    QFileInfo *file_info = new QFileInfo(file);
    if(!file.exists()){
        qDebug()<<"file does not exist";
        file_open = file.open(QIODevice::ReadWrite);
        qDebug()<<"file created at:"+file_info->absoluteFilePath();
    }
     qDebug()<<"file exists";
     if(!file_open){
        file.open(QIODevice::ReadWrite);
     }
    QString today_;
    today_.append(QDate::currentDate().toString("dd/"));
    today_.append(QDate::currentDate().toString("MM/"));
    today_.append(QDate::currentDate().toString("yyyy_"));
    today_.append(QTime::currentTime().toString("hh:mm:ss"));
     file.resize(0);
         QTextStream output(&file);
         output<<"<!DOCTYPE html>\n<html>\n<head>\n";

         output<<"</head>\n<body style = 'background-color:#F8F8F8   '>\n";
         output<<"<h1> Summary Report </h1>";
         output<<"<table>";
         output<<"<tr>"; output<<"<td>"; output<<"Status: ";output<<summary_data.at(0); output<<"</td>"; output<<"</tr>";
         output<<"<tr>"; output<<"<td>"; output<<"Start time: ";output<<summary_data.at(1); output<<"</td>";output<<"</tr>";output<<"<tr>"; output<<"<td>"; output<<"End time: ";output<<summary_data.at(2); output<<"</td>";
         output<<"</tr>"; output<<"<tr>";output<<"<td>"; output<<"Execution time: ";output<<summary_data.at(3); output<<"</td>";  output<<"</tr>";
         output<<"<tr>"; output<<"<td>"; output<<"Tests quantity: ";output<<test_r.size()-1; output<<"</td>"; output<<"</tr>";
         output<<"<tr>"; output<<"<td>"; output<<"Test Passed: ";output<<test_r.at(0); output<<"</td>"; output<<"</tr>";
         output<<"<tr>"; output<<"<td>"; output<<"Test Failed: ";output<<test_r.at(1); output<<"</td>"; output<<"</tr>";
         output<<"<tr>";
         output<<"<td>";output<<"File generated: ";output<<today_;output<<"</td>";
         output<<"</tr>";
         output<<"</table>";
         output<<"<table style='width:100%;border-collapse: collapse;border: 1px solid black;'>\n";
         output<<"<col width=100>";
        output<<"<col width=100>";
        output<<"<col width=100>";
        output<<"<col width=100>";
        output<<"<col width=100>";
       output<<"<col width=100>";
       output<<"<col width=100>";
       output<<"<col width=100>";
         output<<"<tr style='border: 1px solid black'>\n";
         output<<"<th style='border: 1px solid black;background-color:#B0B0B0'>";
         output<<"Name";
         output<<"</th >\n";
         output<<"<th style='border: 1px solid black;background-color:#B0B0B0'>";
         output<<"Descirption";
         output<<"</th >\n";
         output<<"<th style='border: 1px solid black;background-color:#B0B0B0'>";
         output<<"Count";
         output<<"</th >\n";
         output<<"<th style='border: 1px solid black;background-color:#B0B0B0'>";
         output<<"Total Duration";
         output<<"</th >\n";
         output<<"<th style='border: 1px solid black;background-color:#B0B0B0'>";
         output<<"Pass";
         output<<"</th>\n";
         output<<"<th style='border: 1px solid black;background-color:#B0B0B0'>";
         output<<"Fail";
         output<<"</th>\n";
         output<<"<th style='border: 1px solid black;background-color:#B0B0B0'>";
         output<<"Result";
         output<<"</th >\n";
         output<<"</tr>\n";
         int t=0;
         bool init_ = true;
         bool cu = true;
         QString cur;
         QString next;
         bool next_suite = false;
         for(int i=0;i<suite_info.size();i++ ){
              output<<"<tr style='border: 1px solid black;'>";
             for(int t =0;t<suite_info.at(i)->size();t++){
             output<<"<td style='border: 1px solid black;'>";
             output<<suite_info.at(i)->at(t);
             output<<"</td>";
             }
              output<<"</tr>";

         for(int j=0;j<table_data.size();j++){
             output<<"<tr style='border: 1px solid black;'>";
             output<<"<td style='border: 1px solid black;'>";
             output<<table_data.at(j)->at(0);
             output<<"</td>";
             output<<"<td style='border: 1px solid black;'>";
             output<<table_data.at(j)->at(1);
             output<<"</td>";
             output<<"<td style='border: 1px solid black;'>";
             output<<table_data.at(j)->at(2);
             output<<"</td>";
             output<<"<td style='border: 1px solid black;'>";
             output<<table_data.at(j)->at(3);
             output<<"</td>";
             if(table_data.at(j)->at(4)=="yes"){
                 output<<"<td style='border: 1px solid black;background-color:green'>";
                 output<<"</td>";
                 output<<"<td style='border: 1px solid black;'>";
                 output<<"</td>";
                 output<<"<td style='border: 1px solid black;'>";
                 output<<"</td>";
             }else if(table_data.at(j)->at(4)=="no"){
                 output<<"<td style='border: 1px solid black;'>";
                 output<<"</td>";
                 output<<"<td style='border: 1px solid black;background-color:red'>";
                 output<<"</td>";
                 output<<"<td style='border: 1px solid black;'>";
                 output<<"</td>";
             }


         }
         }
         output<<"</table>";
         output<<"</html>";
         output<<"</body>";
}

void SessionWindowTable::CreateTable(QString html_url,QVector<QStringList*> table_data,int elements,QStringList summary_data,QStringList test_r,QVector<QStringList*> suite_info){
    setHTMLPath(html_url);
    CreateHTMLTable(table_data,elements,summary_data,test_r,suite_info);
}

