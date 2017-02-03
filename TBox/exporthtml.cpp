#include "exporthtml.h"
#define FOLDERNAME "/Reports"
ExportHTML::ExportHTML()
{

}

 void ExportHTML::CreateDirIfNotExists(){
        dir = new QDir("Reports");
         QString file_path= QDir::currentPath();
        qDebug()<<file_path;
        file_path.append(FOLDERNAME);
        if(!dir->exists(file_path)){
            qDebug()<<"No such dir";
        }
        if(!dir->mkdir(file_path)){
            qDebug()<<"Dir is present. No need to create a new one";
        }
        qDebug()<<"dir was created";
       qDebug()<<dir->absolutePath();

 }
void ExportHTML::CreateHTMLReportFile(QVector<QStringList*> table_data,QStringList table_n,int elements_,QString current_session){
qDebug()<<dir->absolutePath();
bool file_open = 0;
QFile file(dir->absolutePath()+"/Session"+current_session+"_"+QDate::currentDate().toString("dd_MM_yyyy_")+QTime::currentTime().toString("(HH_mm_ss)")+".html");
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
 void ExportHTML::ReceiveHTMLdata(QVector<QStringList*> r_data,QStringList tn,int index,QString current_session){
CreateDirIfNotExists();
CreateHTMLReportFile(r_data,tn,index,current_session);
 }


