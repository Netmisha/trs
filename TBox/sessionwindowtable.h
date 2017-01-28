#ifndef SESSIONWINDOWTABLE_H
#define SESSIONWINDOWTABLE_H
#include <QString>
#include <QVector>
#include <QObject>
#include <QFile>
#include <QFileInfo>
#include <qdebug.h>
#include <QVector>

class SessionWindowTable: public QObject
{
Q_OBJECT
public:
    QString html_path;
    bool file_open=0;
    int index;
    QStringList table_n;
    SessionWindowTable();
    void setTableNames(QStringList table_name);
    QStringList getTableNames();
    void CreateTable(QString html_url,QVector<QVector<QStringList*>> table_data);
    int getIndex();
    void setIndex(int i);
    void setHTMLPath(QString html_url);
    QString getHTMLPath();
    void CreateHTMLTable( QVector<QVector<QStringList*>> table_data);
    void setTableData( QVector<QVector<QStringList*>> table_data);


};

#endif // SESSIONWINDOWTABLE_H
