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
 public slots:
   Q_INVOKABLE void ReceiveHTMLdata(QVector<QStringList*> r_data,QStringList tn,int index,QString current_session);
};

#endif // EXPORTHTML_H
