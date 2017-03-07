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
SessionWindowTable::Time SessionWindowTable::StringTimetoInt(QString time){

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
QString SessionWindowTable::IntTimetoString(Time time){
    QString res;
    res.append(QString::number(time.h));res.append(":");res.append(QString::number(time.m));res.append(":");
    res.append(QString::number(time.s));res.append(":");res.append(QString::number(time.ms));
    return res;
}
void SessionWindowTable::parseSuiteData(QVector<QStringList *> suite_info_, QVector<QStringList *> table_data_){
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
     testD->test_msg = table_data_.at(i)->at(6);
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
             if(cur.ms >=1000){cur.ms = cur.ms-1000;cur.s++;}
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
           if(TD.at(j)->test_pass == "success"){
               pass = true;
           }
           my_time =StringTimetoInt( TD.at(j)->total_test_time);
           total_execution.ms = total_execution.ms+my_time.ms;
           if(total_execution.ms >=1000){total_execution.ms = total_execution.ms-1000;total_execution.s++;}
           total_execution.s = total_execution.s +my_time.s;
           if(total_execution.s >=60){total_execution.s = total_execution.s-60; total_execution.m++;}
           total_execution.m = total_execution.m + my_time.m;
           if(total_execution.m >=60){total_execution.m = total_execution.m-60;total_execution.h++;}
           total_execution.h = total_execution.h+my_time.h;
        }
        (pass)?SD.at(i)->pass = "success":0;
        pass = false;
        SD.at(i)->total_time = IntTimetoString(total_execution);
        total_execution.h=0;total_execution.m=0;total_execution.s=0;total_execution.ms=0;
    }
}
void SessionWindowTable::CreateHTMLTable(QVector<QStringList*> table_data,int elements,QStringList summary_data,QStringList test_r,QVector<QStringList*> suite_info){
    elements_ = elements;
     SD.clear(); TD.clear();
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
    today_.append(QDate::currentDate().toString("yyyy( "));
    today_.append(QTime::currentTime().toString("hh:mm:ss )"));


QString res__;
QString st = summary_data.at(1);
QString en = summary_data.at(2);
QStringList split_ = st.split(" ");
QString date_start = split_.at(0);
QString time_start = split_.at(1);

QStringList td = date_start.split("/");
QStringList tt = time_start.split(":");

QStringList split__ = en.split(" ");
QString date_start_ = split__.at(0);
QString time_start_ = split__.at(1);

QStringList td_ = date_start_.split("/");
QStringList tt_ = time_start_.split(":");
QString temp;
for(int i=0;i<td.size();i++){
    temp = QString::number(td_.at(i).toInt() - td.at(i).toInt());
    (temp.toInt()<0)?std::abs(temp.toInt()):0;
res__.append(temp);
res__.append("/");
temp.clear();
}
res__.append(" ");
QString TT1 = QString::number((tt.at(0).toInt()*60*60)+(tt.at(1).toInt()*60)+tt.at(2).toInt()); //start time
QString TT = QString::number((tt_.at(0).toInt()*60*60)+(tt_.at(1).toInt()*60)+tt_.at(2).toInt()); // end time
QString T_dif = QString::number(TT.toInt() - TT1.toInt());
QString TT2 =  QString::number(T_dif.toInt() / 60);
res__.append(QString::number(TT2.toInt()/60));
res__.append(":");
res__.append(QString::number(TT2.toInt()%60));
res__.append(":");
res__.append(QString::number(T_dif.toInt()%60));
     file.resize(0);
     parseSuiteData(suite_info,table_data);
         QTextStream output(&file);
         output<<"<!DOCTYPE html>\n<html>\n<head>\n";
         output<<"</head>\n<body style = 'background-color:#F8F8F8   '>\n";
         output<<"<h1>Report </h1>";
         output<<"<table>";
         output<<"<tr>"; output<<"<td>"; output<<"Start time: ";output<<summary_data.at(1); output<<"</td>";output<<"</tr>";output<<"<tr>"; output<<"<td>"; output<<"End time: ";output<<summary_data.at(2); output<<"</td>";
         output<<"</tr>"; output<<"<tr>";output<<"<td>"; output<<"Execution time: ";output<<res__; output<<"</td>";  output<<"</tr>";
         output<<"<tr>"; output<<"<td>"; output<<"Tests quantity: ";output<<table_data.size(); output<<"</td>"; output<<"</tr>";
         output<<"<tr>"; output<<"<td>"; output<<"Test Passed: ";output<<test_r.at(0); output<<"</td>"; output<<"</tr>";
         output<<"<tr>"; output<<"<td>"; output<<"Test Failed: ";output<<test_r.at(1); output<<"</td>"; output<<"</tr>";
         output<<"<tr>";
         output<<"<td>";output<<"File generated: ";output<<today_;output<<"</td>";
         output<<"</tr>";
         output<<"<tr>"; output<<"<td >"; output<<"Status: ";output<<summary_data.at(0); output<<"</td>"; output<<"</tr>";
         output<<"</table>";
         output<<"<table style='width:100%;border-collapse: collapse;border: 1px solid black;'>\n";
         output<<"<col width=100>";
        output<<"<col width=100>";
        output<<"<col width=20>";
        output<<"<col width=20>";
        output<<"<col width=20>";
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
         output<<"Status";
         output<<"</th>\n";
         output<<"<th style='border: 1px solid black;background-color:#B0B0B0'>";
         output<<"Info";
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
             output<<"<td style='border: 2px solid black;font-weight:bold;background-color:	#E0E0E0 '>";
             output<<SD.at(i)->suite_name;
             output<<"</td>";
             output<<"<td style='border: 2px solid black;font-weight:bold;background-color:	#E0E0E0 '>";
             output<<SD.at(i)->suite_description;
             output<<"</td>";
             output<<"<td style='border: 2px solid black;font-weight:bold;background-color:	#E0E0E0 '>";
             output<<SD.at(i)->repeat;
             output<<"</td>";
             output<<"<td style='border: 2px solid black;font-weight:bold;background-color:	#E0E0E0 '>";
             output<<SD.at(i)->total_time;
             output<<"</td>";
             if(SD.at(i)->pass =="success"){
             output<<"<td style='border: 2px solid black;font-weight:bold;background-color:#50D050'>";
             output<<"Success";
             output<<"</td>";

             }else{
                 output<<"<td style='border: 2px solid black;font-weight:bold;background-color:red'>";
                 output<<"Fail";
                 output<<"</td>";
             }
             output<<"<td style='border: 2px solid black;font-weight:bold;background-color:#E0E0E0 '>";
             output<<"</td>";
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
             if(TD.at(t)->test_pass=="success"){
                 output<<"<td style='border: 1px solid black;background-color:#50D050'>";
                 output<<"Success";
                 output<<"</td>";

             }else{

                 output<<"<td style='border: 1px solid black;background-color:red'>";
                 output<<"Fail";
                 output<<"</td>";
             }
             output<<"<td style='border: 1px solid black; '>";
             output<<TD.at(t)->test_msg;
             output<<"</td>";
    }
    beg+=SD.at(i)->test_num.toInt();
         }
         output<<"</table>";
         output<<"</html>";
         output<<"</body>";
}

void SessionWindowTable::CreateTable(QString html_url,QVector<QStringList*> table_data,int elements,QStringList summary_data,QStringList test_r,QVector<QStringList*> suite_info){
    setHTMLPath(html_url);
    CreateHTMLTable(table_data,elements,summary_data,test_r,suite_info);
}

