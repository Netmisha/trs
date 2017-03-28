#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QFile>
#include <QDomDocument>
namespace tags_name {
    const QString kXml = ".xml";
    const QString kName = "name";
    const QString kDescription = "description";
    const QString kTag = "tag";
    const QString kDisable = "disable";
    const QString kExecution = "execution";
    const QString kRepeat = "repeat";
    const QString kTest = "test";
    const QString kData = "data";
    const QString kSuite = "suite";
    const QString kImportant = "important";
    const QString kMetadata = "metadata";
    const QString kAuthor = "author";
    const QString kDate = "date";
    const QString kVersion = "version";
    const QString kMail = "mail";
    const QString kCopyright = "copyright";
    const QString kLicense = "license";
    const QString kInfo = "info";
    const QString kHeaders = "headers";
    const QString kAlwaysRun = "alwaysrun";
    const QString kScr = "src";
}
class DataManager : public QObject
{
    Q_OBJECT
public:
    explicit DataManager(QObject *parent = 0);

signals:
public slots:
    void Set(QString, QString);
    QString AddTest(QString, QString, QString, QString, QString, QString, QString, QString, QString);
    QString AddSuite(QString, QString, QString, QString, QString);
    QString AddRoot(QString, QString, QString, QString, QString);
    QString RemoveTest(QString, QString);
    QString RemoveSuite(QString);
    QString Get(QString);
    QStringList getHeaders(QString, QString);
private:
};

#endif // DATAMANAGER_H
