#ifndef SESSIONWINDOWTABLE_H
#define SESSIONWINDOWTABLE_H
#include <QString>
#include <QVector>
#include <QObject>
#include <QFile>
#include <QFileInfo>
#include <qdebug.h>
#include <QVector>
#include <QTime>
class SessionWindowTable: public QObject
{
Q_OBJECT
public:
    QString html_path;
    bool file_open=0;
    int index;
    QStringList table_n;
    SessionWindowTable();
    int elements_;
    void setTableNames(QStringList table_name);
    QStringList getTableNames();
    void CreateTable(QString html_url,QVector<QStringList*> table_data,int elements,QStringList summary_data);
    int getIndex();
    void setIndex(int i);
    void setHTMLPath(QString html_url);
    QString getHTMLPath();
    void CreateHTMLTable( QVector<QStringList*> table_data,int elements,QStringList summary_data);
    void setTableData( QVector<QStringList*> table_data);


};

#endif // SESSIONWINDOWTABLE_H

