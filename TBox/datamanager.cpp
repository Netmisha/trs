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
QString DataManager::AddTest(QString path, QString name) {
    QDomDocument doc;
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    if (doc.setContent(&file, false)) {
        QDomElement root = doc.documentElement();
        QDomElement test  = root.firstChildElement(tags_name::kTest);
        while (!test.isNull()) {
            if(test.attribute(tags_name::kName)==name) {
                file.close();
                return "Test already exists!";
            }
            test = test.nextSiblingElement(tags_name::kTest);
        }
        test  = root.lastChildElement(tags_name::kTest);
        QDomElement node = doc.createElement(tags_name::kTest);
        node.setAttribute(tags_name::kName, name);
        node.setAttribute(tags_name::kDescription, test.attribute(tags_name::kDescription));
        root.appendChild(node);
        QDomElement snode = doc.createElement(tags_name::kTag);
        node.appendChild(snode);
        snode = doc.createElement(tags_name::kDisable);
        node.appendChild(snode);
        snode = doc.createElement(tags_name::kExecution);
        node.appendChild(snode);
        snode = doc.createElement(tags_name::kResult);
        node.appendChild(snode);
        snode = doc.createElement(tags_name::kRepeat);
        snode.setAttribute(tags_name::kPause, test.firstChildElement(tags_name::kRepeat).attribute(tags_name::kPause));
        node.appendChild(snode);
        snode = doc.createElement(tags_name::kMaxTime);
        node.appendChild(snode);
    }
    file.close();
    file.open(QIODevice::WriteOnly);
    file.write(doc.toString().toLatin1());
    file.close();
    return "";
}
QString DataManager::AddSuite(QString file, QString name) {

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
