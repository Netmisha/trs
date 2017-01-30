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
void SessionWindowTable::CreateHTMLTable(QVector<QVector<QStringList*>> table_data){
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
     file.resize(0);
     QTextStream output(&file);
     output<<"<!DOCTYPE html>\n<html>\n<head>\n</head>\n<body>\n<table style='width:100%;border: 1px solid black'; 'border-collapse: collapse'>\n";
     output<<"<tr style='border: 1px solid black'>\n";
     output<<"<th style='border: 1px solid black'>";
     output<<table_n.at(1);
     output<<"</th >\n";
     output<<"<th style='border: 1px solid black'>";
     output<<table_n.at(7);
     output<<"</th>\n";
     output<<"<th style='border: 1px solid black'>";
     output<<table_n.at(5);
     output<<"</th>\n";
     output<<"</tr>\n";
     for(int i=0;i<table_data.at(index).size();i++){
         output<<"<tr style='border: 1px solid black'>\n";
         output<<"<td style='border: 1px solid black'>";
         output<<table_data.at(index).at(index)->at(0);
         output<<"</td>\n";
         output<<"<td style='border: 1px solid black'>";
         output<<table_data.at(index).at(index)->at(1);
         output<<"</td>\n";
         output<<"<td style='border: 1px solid black'>";
         output<<table_data.at(index).at(index)->at(2);
         output<<"</td>\n";
         output<<"</tr>\n";
     }
    output<<"</table>\n";
    output<<"</body>\n";
    output<<"</html>\n";


}

void SessionWindowTable::CreateTable(QString html_url,QVector<QVector<QStringList*>> table_data){
    setHTMLPath(html_url);
    CreateHTMLTable(table_data);
}

