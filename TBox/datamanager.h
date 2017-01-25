#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QFile>
#include <QDomDocument>
namespace tags_name {
    const QString kXml = ".xml";
    const QString kName = "name";
    const QString kTest = "test";
    const QString kData = "data";
}
class DataManager : public QObject
{
    Q_OBJECT
public:
    explicit DataManager(QObject *parent = 0);

signals:
public slots:
    void Set(QString, QString);
    QString Get(QString);
private:
};

#endif // DATAMANAGER_H
