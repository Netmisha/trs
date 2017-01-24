#include "datamanager.h"
#include <QDebug>
#include <QDomDocument>
DataManager::DataManager(QObject *parent) : QObject(parent) {

}
void DataManager::Set(QString path, QString data) {
    QDomDocument doc;
    QStringList tags=path.split(tags_name::kXml+"/")[1].split("/");
    QFile file(path.split(tags_name::kXml)[0]+tags_name::kXml);
    file.open(QIODevice::ReadOnly);
    if (!doc.setContent(&file, false)) {
            return;
    }
    QDomElement root = doc.documentElement();
    for (int i=1; i<tags.length(); i++) {
        if(root.attributes().contains(tags[i])) {
            root.setAttribute(tags[i], data);
        }
        else if(tags[i]==tags_name::kTest) {
            root = root.firstChildElement(tags[i]);
            while (root.attribute(tags_name::kName)!=tags[i+1]) {
                root = root.nextSiblingElement(tags[i]);
            }
            i++;
        }
        else {
            root = root.firstChildElement(tags[i]);
            if(i+1==tags.length()) {
                root.firstChild().setNodeValue(data);
            }
        }
    }
    file.close();
    file.open(QIODevice::WriteOnly);
    file.write(doc.toString().toLatin1());
    file.close();
}
QString DataManager::Get(QString path) {
    QDomDocument doc;
    QStringList tags=path.split(tags_name::kXml+"/")[1].split("/");
    QFile file(path.split(tags_name::kXml)[0]+tags_name::kXml);
    file.open(QIODevice::ReadOnly);
    if (doc.setContent(&file, false)) {
        QDomElement root = doc.documentElement();
        for (int i=1; i<tags.length(); i++) {
            if(root.attributes().contains(tags[i])) {
                return root.attribute(tags[i]);
            }
            else if(tags[i]==tags_name::kTest) {
                root = root.firstChildElement(tags[i]);
                while (root.attribute(tags_name::kName)!=tags[i+1]) {
                    root = root.nextSiblingElement(tags[i]);
                }
                i++;
            }
            else {
                root = root.firstChildElement(tags[i]);
                if(i+1==tags.length()) {
                    return root.firstChild().nodeValue();
                }
            }
        }
    }
    file.close();
    return "";
}
void DataManager::SetData(QString, QString) {

}
QString DataManager::GetData(QString path) {
    return Get(path);
}
