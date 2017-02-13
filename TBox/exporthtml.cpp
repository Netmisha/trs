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
 void ExportHTML::ReceiveHTMLpath(QString exportPath){
     export_path_ = exportPath;
     CreateHTMLReportFile(table_data_,elements_, summary_data_,test_r_,suite_info_,current_session);
 }
 QString ExportHTML::IntTimetoString(Time time){
     QString res;
     res.append(QString::number(time.h));res.append(":");res.append(QString::number(time.m));res.append(":");
     res.append(QString::number(time.s));res.append(":");res.append(QString::number(time.ms));
     return res;
 }
 void ExportHTML::parseSuiteData(QVector<QStringList *> suite_info_, QVector<QStringList *> table_data_){
     //QVector<suiteData*> SD;
     //QVector<TestData*> TD;
     Time total_execution;
     Time test_exe;
     for(int i=0;i<suite_info_.size();i++){
         suiteD = new suiteData;
         suiteD->suite_name = suite_info_.at(i)->at(0);
         suiteD->suite_description=suite_info_.at(i)->at(1);
         suiteD->repeat = suite_info_.at(i)->at(2);
         suiteD->total_time = suite_info_.at(i)->at(3);
         suiteD->pass = suite_info_.at(i)->at(4);
         suiteD->test_num = suite_info_.at(i)->at(5);
         suiteD->quant_el =  suite_info_.size();
         SD.push_back(suiteD);
     }
    int a=0;
    for(int i =0;i<table_data_.size();){
      testD = new TestData;
      testD->test_name = table_data_.at(i)->at(0);
      testD->test_description = table_data_.at(i)->at(1);
      testD->test_repeat = table_data_.at(i)->at(2);
      testD->test_pass = table_data_.at(i)->at(4);
      testD->test_suite_name = table_data_.at(i)->at(5);
      QString inc_i = table_data_.at(i)->at(2);
      Time res;
      QString jmp=0;
          jmp = table_data_.at(i)->at(2);
          a+=jmp.toInt();
          Time prev,cur;
          for(int j=i;j<a;j++){
              QString temp_time =  table_data_.at(j)->at(3);
              cur =StringTimetoInt(testD->total_test_time);
              prev = StringTimetoInt(temp_time);
              cur.ms = prev.ms+cur.ms;
              if(cur.ms >=100){cur.ms = cur.ms-100;cur.s++;}
              cur.s = prev.s + cur.s;
              if(cur.s >=60){cur.s = cur.s-60; cur.m++;}
              cur.m = prev.m + cur.m;
              if(res.m >=60){cur.m = res.m-60;res.h++;}
              cur.h = prev.h+cur.h;
              testD->total_test_time = IntTimetoString(cur);
          }
          testD->quant_el = elements_;
          TD.push_back(testD);
          i+=jmp.toInt();
     }

    total_execution.h=0;total_execution.m=0;total_execution.s=0;total_execution.ms=0;
    int h=0;
    bool pass = false;
    for(int i=0,j=0;i<SD.size();i++){
          Time my_time;
          h+=SD.at(i)->test_num.toInt();
         for(;j<h;j++){
            if(TD.at(j)->test_pass == "yes"){
                pass = true;
            }
            my_time =StringTimetoInt( TD.at(j)->total_test_time);
            total_execution.ms = total_execution.ms+my_time.ms;
            if(total_execution.ms >=100){total_execution.ms = total_execution.ms-100;total_execution.s++;}
            total_execution.s = total_execution.s +my_time.s;
            if(total_execution.s >=60){total_execution.s = total_execution.s-60; total_execution.m++;}
            total_execution.m = total_execution.m + my_time.m;
            if(total_execution.m >=60){total_execution.m = total_execution.m-60;total_execution.h++;}
            total_execution.h = total_execution.h+my_time.h;
         }
         (pass)?SD.at(i)->pass = "yes":0;
         pass = false;
         SD.at(i)->total_time = IntTimetoString(total_execution);
         total_execution.h=0;total_execution.m=0;total_execution.s=0;total_execution.ms=0;
     }
 }
 ExportHTML::Time ExportHTML::StringTimetoInt(QString time){
     QStringList tempListTime = time.split(":");
     Time time_;
     for(int q = 0;q<tempListTime.size();q++){
         time.append(tempListTime.at(q));
     }
     time_.h = tempListTime.at(0).toInt(); time_.m = tempListTime.at(1).toInt();
     time_.s = tempListTime.at(2).toInt();
     time_.ms = tempListTime.at(3).toInt();
     return time_;
 }
void ExportHTML::CreateHTMLReportFile(QVector<QStringList*> table_data,int elements,QStringList summary_data,
                                      QStringList test_r,QVector<QStringList*> suite_info,QString current_session){
    bool file_open = 0;
    QFile file(export_path_+"Session"+current_session+"_"+QDate::currentDate().toString("dd_MM_yyyy_")+QTime::currentTime().toString("(HH_mm_ss)")+".html");
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
     parseSuiteData(suite_info,table_data);
         QTextStream output(&file);
         output<<"<!DOCTYPE html>\n<html>\n<head>\n";
         output<<"</head>\n<body style = 'background-color:#F8F8F8   '>\n";
         output<<"<h1> Summary Report </h1>";
         output<<"<table>";
         output<<"<tr>"; output<<"<td>"; output<<"Status: ";output<<summary_data.at(0); output<<"</td>"; output<<"</tr>";
         output<<"<tr>"; output<<"<td>"; output<<"Start time: ";output<<summary_data.at(1); output<<"</td>";output<<"</tr>";output<<"<tr>"; output<<"<td>"; output<<"End time: ";output<<summary_data.at(2); output<<"</td>";
         output<<"</tr>"; output<<"<tr>";output<<"<td>"; output<<"Execution time: ";output<<total_time; output<<"</td>";  output<<"</tr>";
         output<<"<tr>"; output<<"<td>"; output<<"Tests quantity: ";output<<table_data.size()-2; output<<"</td>"; output<<"</tr>";
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
         /*
         output<<"<th style='border: 1px solid black;background-color:#B0B0B0'>";
         output<<"Result";
         output<<"</th >\n"; */
         output<<"</tr>\n";
         int beg=0;
         int end=0;
         for(int i=0;i<SD.size();i++){
              output<<"<tr style='border: 2px solid black;'>";
             output<<"<td style='border: 2px solid black;font-weight:bold'>";
             output<<SD.at(i)->suite_name;
             output<<"</td>";
             output<<"<td style='border: 2px solid black;font-weight:bold'>";
             output<<SD.at(i)->suite_description;
             output<<"</td>";
             output<<"<td style='border: 2px solid black;font-weight:bold'>";
             output<<SD.at(i)->repeat;
             output<<"</td>";
             output<<"<td style='border: 2px solid black;font-weight:bold'>";
             output<<SD.at(i)->total_time;
             output<<"</td>";
             if(SD.at(i)->pass =="yes"){
             output<<"<td style='border: 2px solid black;font-weight:bold;background-color:#50D050'>";
             output<<"</td>";
             output<<"<td style='border: 2px solid black;font-weight:bold;'>";
             output<<"</td>";
             }else if(SD.at(i)->pass =="no"){
                 output<<"<td style='border: 2px solid black;font-weight:bold;'>";
                 output<<"</td>";
                 output<<"<td style='border: 2px solid black;font-weight:bold;background-color:red'>";
                 output<<"</td>";
             }
            output<<"</tr>";
            end+=SD.at(i)->test_num.toInt();
        for(int t =beg;t<end;t++){
             output<<"<tr style='border: 1px solid black;'>";
             output<<"<td style='border: 1px solid black;'>";
             output<<TD.at(t)->test_name;
             output<<"</td>";
             output<<"<td style='border: 1px solid black;'>";
             output<<TD.at(t)->test_description;
             output<<"</td>";
             output<<"<td style='border: 1px solid black;'>";
             output<<TD.at(t)->test_repeat;
             output<<"</td>";
             output<<"<td style='border: 1px solid black;'>";
             output<<TD.at(t)->total_test_time;
             output<<"</td>";
             if(TD.at(t)->test_pass=="yes"){
                 output<<"<td style='border: 1px solid black;background-color:#50D050'>";
                 output<<"</td>";
                 output<<"<td style='border: 1px solid black;'>";
                 output<<"</td>";
                 /*
                 output<<"<td style='border: 1px solid black;'>";
                 output<<"</td>"; */
             }else if(TD.at(t)->test_pass=="no"){
                 output<<"<td style='border: 1px solid black;'>";
                 output<<"</td>";
                 output<<"<td style='border: 1px solid black;background-color:red'>";
                 output<<"</td>";
             }
    }
    beg+=SD.at(i)->test_num.toInt();
         }
         output<<"</table>";
         output<<"</html>";
         output<<"</body>";
               QMessageBox msgBox;
               msgBox.setText("File has been saved at:"+export_path_);
               msgBox.exec();

}
void ExportHTML::ReceiveHTMLdata(QVector<QStringList*> table_data_e,int elements_e,QStringList summary_data_e,
                                 QStringList test_r_e,QVector<QStringList*> suite_info_e,QString current_session_e){
table_data_ = table_data_e;
elements_ = elements_e;
summary_data_ = summary_data_e;
        test_r_ = test_r_e;
        suite_info_ = suite_info_e;
        current_session = current_session_e;
 }


