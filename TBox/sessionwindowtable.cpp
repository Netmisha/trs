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
         output<<"<!DOCTYPE html>\n<html>\n<head>\n</head>\n<body>\n<table style='width:100%';'border-collapse: collapse'>\n";

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
         output<<"</table>\n";
         int t=0;
         bool init_ = true;
         bool cu = true;
         QString cur;
         QString next;
         for(int i=0;i<table_data.size();i++){
             if(init_){
                 init_=false;
                 cur = table_data.at(i)->at(1);
                 output<<" <table style='width:100%';'border-collapse: collapse'>\n";
                 output<<"<tr style='border: 1px solid black'>\n";
                 output<<"<td style='border: 1px solid black';'border-collapse: collapse'>\n";
                 output<<"<details>\n";
                 output<<"<summary>";
                 output<<cur;
                 output<<"</summary>\n";
                 output<<"<table style='width:100%'; 'border-collapse: collapse'>\n";
                 output<<"<tr style='border: 1px solid black'>\n";
                 output<<"<td style='border: 1px solid black'>";
                 output<<table_data.at(i)->at(0);
                 output<<"</td >\n";
                 output<<"<td style='border: 1px solid black'>";
                 output<<table_data.at(i)->at(1);
                 output<<"</td>\n";
                 output<<"<td style='border: 1px solid black'>";
                 output<<table_data.at(i)->at(2);
                 output<<"</td>\n";
                 output<<"</tr>\n";
                 output<<"</td>\n";
                 output<<"</tr>\n";
                 (i+1 >=table_data.size())?next=" ": next = table_data.at(i+1)->at(1);
                 continue;

             }
                 if(cur == next){
                     cu = true;
                     output<<"<tr style='border: 1px solid black'>\n";
                     output<<"<td style='border: 1px solid black'>";
                     output<<table_data.at(i)->at(0);
                     output<<"</td >\n";
                     output<<"<td style='border: 1px solid black'>";
                     output<<table_data.at(i)->at(1);
                     output<<"</td>\n";
                     output<<"<td style='border: 1px solid black'>";
                     output<<table_data.at(i)->at(2);
                     output<<"</td>\n";
                     output<<"</tr>\n";
                     output<<"</td>\n";
                     output<<"</tr>\n";
                     cur = table_data.at(i)->at(1);
                     (i+1 >=table_data.size())?next=" ": next = table_data.at(i+1)->at(1);
                 }else{
                     if(cu){
                         output<<"</table>";
                          output<<"</table>\n";
                         output<<"</details>\n";
                     }
                     cu = false;
                     cur = table_data.at(i)->at(1);
                     (i+1 >=table_data.size())?next=" ": next = table_data.at(i+1)->at(1);
                     output<<" <table style='width:100%';'border-collapse: collapse'>\n";
                     output<<"<tr style='border: 1px solid black'>\n";
                     output<<"<td style='border: 1px solid black';'border-collapse: collapse'>\n";
                     output<<"<details>\n";
                     output<<"<summary>";
                     output<<cur;
                     output<<"</summary>\n";
                     output<<"<table style='width:100%'; 'border-collapse: collapse'>\n";

                 }


           }


         output<<"</body>\n";
         output<<"</html>";
}

void SessionWindowTable::CreateTable(QString html_url,QVector<QStringList*> table_data,int elements){
    setHTMLPath(html_url);
    CreateHTMLTable(table_data,elements);
}

