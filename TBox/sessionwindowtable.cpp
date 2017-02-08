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
void SessionWindowTable::CreateHTMLTable(QVector<QStringList*> table_data,int elements,QStringList summary_data){
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
         output<<"<style>\n"
                 "details {\n"
                     "border-radius: 3px;\n"
                     "background: #EEE;}\n"
                 "details summary {\n"
                     "font-size: 17px;\n"
                    " vertical-align: top;\n"
                    " background: #333;\n"
                    " color: #FFF;\n"
                    " border-radius: 3px;\n"
                     "padding: 5px 10px;\n"
                    " outline: none;\n"
                 "}\n"
                 "details[open] summary {\n"
                     "background: #69c773;\n"
                     "color: #333;\n"
                 "}\n"

                 "details summary::-webkit-details-marker {\n"
                     "display: none;\n"
                 "}\n"
                 "details summary:before {\n"
                     "display: inline-block;\n"
                     "width: 20px;\n"
                     "height: 20px;\n"
                     "margin-right: 8px;\n"
                     "content:''; \n"
                     "background-image: url(plus_sign.png);\n"
                     "background-repeat: no-repeat;\n"
                     "background-position: 0 0;\n"
                 "}\n"
                 "details[open] summary:before {\n"
                      "background-image: url(inspector.png);\n"
                 "}\n </style>\n";

         output<<"</head>\n<body style = 'background-color:#F8F8F8   '>\n";
         output<<"<h1> Summary Report </h1>";
         output<<"<table>";
         output<<"<tr>"; output<<"<td>"; output<<"Status: ";output<<summary_data.at(0); output<<"</td>"; output<<"</tr>";
         output<<"<tr>"; output<<"<td>"; output<<"Start time: ";output<<summary_data.at(1); output<<"</td>";output<<"</tr>";output<<"<tr>"; output<<"<td>"; output<<"End time: ";output<<summary_data.at(2); output<<"</td>";
         output<<"</tr>"; output<<"<tr>";output<<"<td>"; output<<"Execution time: ";output<<summary_data.at(3); output<<"</td>";  output<<"</tr>";
         output<<"<tr>";
         output<<"<td>";output<<"File generated: ";output<<today_;output<<"</td>";
         output<<"</tr>";
         output<<"</table>";
         output<<"<h1> Statics: </h1>";
         output<<"<table style='width:100%';'border-collapse: collapse'>\n";
         output<<"<tr style='border: 1px solid black'>\n";
         output<<"<th style='border: 1px solid black;background-color:#B0B0B0'>";
         output<<"Name";
         output<<"</th >\n";
         output<<"<th style='border: 1px solid black;background-color:#B0B0B0'>";
         output<<"Suite";
         output<<"</th>\n";
         output<<"<th style='border: 1px solid black;background-color:#B0B0B0'>";
         output<<"Passed";
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
                 output<<"<summary style='background-color:#D0D0D0';>";
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
                 if(table_data.at(i)->at(2) == "yes"){
                     output<<"<td style='border: 1px solid black'; bgcolor=#7FFF00>";
                     output<<table_data.at(i)->at(2);
                 }else if(table_data.at(i)->at(2)=="no"){
                     output<<"<td style='border: 1px solid black'; bgcolor=	#DC143C>";
                     output<<table_data.at(i)->at(2);
                 }else{
                     output<<"<td style='border: 1px solid black'>";
                     output<<table_data.at(i)->at(2);
                 }
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
                     if(table_data.at(i)->at(2) == "yes"){
                         output<<"<td style='border: 1px solid black'; bgcolor=#7FFF00>";
                         output<<table_data.at(i)->at(2);
                     }else if(table_data.at(i)->at(2)=="no"){
                         output<<"<td style='border: 1px solid black'; bgcolor=	#DC143C>";
                         output<<table_data.at(i)->at(2);
                     }else{
                         output<<"<td style='border: 1px solid black'>";
                         output<<table_data.at(i)->at(2);
                     }
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
                     output<<"<summary style='background-color:#D0D0D0'>";
                     output<<cur;
                     output<<"</summary>\n";
                     output<<"<table style='width:100%'; 'border-collapse: collapse'>\n";

                 }
           }
         output<<"</body>\n";
         output<<"</html>";
}

void SessionWindowTable::CreateTable(QString html_url,QVector<QStringList*> table_data,int elements,QStringList summary_data){
    setHTMLPath(html_url);
    CreateHTMLTable(table_data,elements,summary_data);
}

