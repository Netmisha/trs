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
void SessionWindowTable::CreateHTMLTable(QVector<QStringList*> table_data,int elements){
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
     file.resize(0);
     QTextStream output(&file);
     output<<"<!DOCTYPE html>\n<html>\n<head>\n</head>\n<body>\n<table style='width:100%;border: 1px solid black'; 'border-collapse: collapse'>\n";
     /*
     output<<"<details> ";
     output<<"<summary>Copyright 1999-2014.</summary> ";
     output<<" <p> - by Refsnes Data. All Rights Reserved.</p> ";
     output<<" </details>";
     */
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
     int t = 0;
     for(int i=0;i<table_data.size();i++){
         output<<"<tr style='border: 1px solid black'>\n";
         for(;t<elements_;t++){
         output<<"<td style='border: 1px solid black'>";
         output<<table_data.at(i)->at(t);
         output<<"</td>\n";
         }
         output<<"</tr>\n";
         (t == elements_)?t=0:0;
     }
    output<<"</table>\n";
    output<<"</body>\n";
    output<<"</html>\n";
}

void SessionWindowTable::CreateTable(QString html_url,QVector<QStringList*> table_data,int elements){
    setHTMLPath(html_url);
    CreateHTMLTable(table_data,elements);
}

