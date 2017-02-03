#pragma once

#include <QFileDialog>
#include <QUrl>
#include <QQmlContext>
#include <QQmlEngine>
#include <QDebug>
class SelectFolderDialog: public QFileDialog {
    Q_OBJECT
public:
    explicit SelectFolderDialog() {
        this->setModal(true);
        this->setFileMode(QFileDialog::Directory);
        this->setOption(QFileDialog::ShowDirsOnly);
        this->setWindowTitle("Please choose a folder");
        connect(this, SIGNAL(fileSelected(QString)), this, SLOT(OnFolderSelected(QString)));

    }
    virtual ~SelectFolderDialog(){}
public slots:
    Q_INVOKABLE QString getFolder() {
        return this->getOpenFileName();
    }

    void OnFolderSelected(QString folder) {
        QMetaObject::invokeMethod(obj, "setSelectedFolder", Q_ARG(QVariant, folder));
    }
    void setObject(QObject * o) {
        obj=o;
    }
    Q_INVOKABLE void setFromSetting(bool status) {
        fromSetting=status;
    }
    Q_INVOKABLE bool isFromSetting() {
        return fromSetting;
    }
private:
    QObject *obj;
    bool fromSetting=false;
};
