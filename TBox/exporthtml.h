#ifndef EXPORTHTML_H
#define EXPORTHTML_H
#include <database.h>
#include <QVector>
#include <QStringList>
#include <QObject>
#include <qDebug>
#include <QDir>

class ExportHTML: public QObject
{
    Q_OBJECT
public:
   Q_INVOKABLE QVector<QStringList*> htmldata;
    Q_INVOKABLE QDir *dir;
    Q_INVOKABLE void CreateDirIfNotExists();
    Q_INVOKABLE void CreateHTMLReportFile(QVector<QStringList*> table_n,QStringList tn,int index,QString current_session);
    Q_INVOKABLE ExportHTML();
    Q_INVOKABLE QString export_path_;
    QVector<QStringList*> table_data;QStringList table_n;int elements_;QString current_session;
    Q_INVOKABLE QStringList summary_data;
 public slots:
   void ReceiveHTMLdata(QVector<QStringList*> r_data,QStringList tn,int index,QString current_session);
   void ReceiveHTMLpath(QString exportPath);
   void ReceiveSummaryData(QStringList summary_data_);
};

#endif // EXPORTHTML_H
