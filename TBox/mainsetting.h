#ifndef MAINSETTING_H
#define MAINSETTING_H

#include <QObject>
#include <QFile>
#include <QDomDocument>
namespace tags {
    const QString kDir="dir";
}
class MainSetting : public QObject
{
    Q_OBJECT
public:
    explicit MainSetting(QObject *parent = 0);

signals:
public slots:
    Q_INVOKABLE void setFileName(QString);
    Q_INVOKABLE QString getRootDir();
    Q_INVOKABLE void setRootDir(QString);
    Q_INVOKABLE QString getEditor();
    Q_INVOKABLE void setEditor(QString);
    Q_INVOKABLE QStringList getReceiversEmails();
    Q_INVOKABLE QString getSenderEmail();
    Q_INVOKABLE QString getSenderPassword();
    Q_INVOKABLE void setSenderEmail(QString);
    Q_INVOKABLE void setSenderPassword(QString);
    Q_INVOKABLE void setReceiversEmail(QString);
private:
    void CreateSetting();
    QString file_name="setting.xml";
    QFile file;
};

#endif // MAINSETTING_H
