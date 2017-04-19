#include "mainsetting.h"
#include <QDir>
#include <QDebug>
MainSetting::MainSetting(QObject *parent) : QObject(parent) {
    file.setFileName(QDir::currentPath()+"/"+file_name);
    CreateSetting();
}
void MainSetting::setFileName(QString name) {
    file_name=name;
    file.setFileName(QDir::currentPath()+"/"+name);
}
QString MainSetting::getRootDir() {
    QDomDocument doc;
    file.open(QIODevice::ReadOnly);
    QString res="";
    doc.setContent(&file, false);
    QDomElement root = doc.documentElement();
    res=root.firstChildElement("dir").firstChild().nodeValue();
    file.close();
    return res;
}
void MainSetting::setRootDir(QString data) {
    QDomDocument doc;
    file.open(QIODevice::ReadOnly);
    doc.setContent(&file, false);
    QDomElement root = doc.documentElement();
    root = root.firstChildElement("dir");
    if(root.firstChild().isNull()) {
        root.appendChild(doc.createTextNode(data));
    }
    else {
        root.firstChild().setNodeValue(data);
    }
    file.close();
    file.open(QIODevice::WriteOnly);
    QTextStream stream( &file );
    stream << doc.toString();
    file.close();
}
QString MainSetting::getEditor() {
    QDomDocument doc;
    file.open(QIODevice::ReadOnly);
    QString res="";
    doc.setContent(&file, false);
    QDomElement root = doc.documentElement();
    res=root.firstChildElement("editor").firstChild().nodeValue();
    file.close();
    return res;
}
void MainSetting::setEditor(QString data) {
    QDomDocument doc;
    file.open(QIODevice::ReadOnly);
    doc.setContent(&file, false);
    QDomElement root = doc.documentElement();
    if(root.firstChildElement("editor").isNull()) {
        QDomElement node = doc.createElement("editor");
        root.appendChild(node);
    }
    root = root.firstChildElement("editor");
    if(root.firstChild().isNull()) {
        root.appendChild(doc.createTextNode(data));
    }
    else {
        root.firstChild().setNodeValue(data);
    }
    file.close();
    file.open(QIODevice::WriteOnly);
    QTextStream stream( &file );
    stream << doc.toString();
    file.close();
}

void MainSetting::setSenderEmail(QString data) {
    QDomDocument doc;
    file.open(QIODevice::ReadOnly);
    doc.setContent(&file, false);
    QDomElement root = doc.documentElement();
    if(root.firstChildElement("SenderEmail").isNull()) {
        QDomElement node = doc.createElement("SenderEmail");
        root.appendChild(node);
    }
    root = root.firstChildElement("SenderEmail");
    if(root.firstChild().isNull()) {
        root.appendChild(doc.createTextNode(data));
    }
    else {
        root.firstChild().setNodeValue(data);
    }
    file.close();
    file.open(QIODevice::WriteOnly);
    QTextStream stream( &file );
    stream << doc.toString();
    file.close();
}

void MainSetting::setSenderPassword(QString data) {
    QDomDocument doc;
    file.open(QIODevice::ReadOnly);
    doc.setContent(&file, false);
    QDomElement root = doc.documentElement();
    if(root.firstChildElement("SenderPassword").isNull()) {
        QDomElement node = doc.createElement("SenderPassword");
        root.appendChild(node);
    }
    root = root.firstChildElement("SenderPassword");
    if(root.firstChild().isNull()) {
        root.appendChild(doc.createTextNode(data));
    }
    else {
        root.firstChild().setNodeValue(data);
    }
    file.close();
    file.open(QIODevice::WriteOnly);
    QTextStream stream( &file );
    stream << doc.toString();
    file.close();
}

void MainSetting::setReceiversEmail(QString data) {
    QRegExp rx("[, ]");
    QStringList list = data.split(rx,QString::SkipEmptyParts);
    QDomDocument doc;
    file.open(QIODevice::ReadOnly);
    doc.setContent(&file, false);
    QDomElement root = doc.documentElement();
    if(root.firstChildElement("receivers").isNull()) {
        QDomElement node = doc.createElement("receivers");
        root.appendChild(node);
    }
    root = root.firstChildElement("receivers");
    if(root.firstChildElement("receiverEmail").isNull()) {
        for(int i=0; i < list.length(); ++i) {
            QDomElement node = doc.createElement("receiverEmail");
            node.appendChild(doc.createTextNode(list[i]));
            root.appendChild(node);
        }
    }
    else {
        root.firstChildElement("receiverEmail").firstChild().setNodeValue(list[0]);
        QDomElement el= root;
        root = root.firstChildElement("receiverEmail");
        for(int i=1; i < list.length(); ++i) {
            if(!root.nextSiblingElement().isNull()) {
                root = root.nextSiblingElement();
                root.firstChild().setNodeValue(list[i]);
            }
            else {
                QDomElement node = doc.createElement("receiverEmail");
                root.parentNode().appendChild(node);
                node.appendChild(doc.createTextNode(list[i]));
                root = root.nextSiblingElement();
            }
        }
        while(!root.nextSiblingElement().isNull()) {
            el.removeChild(root.nextSiblingElement());
        }
    }
    file.close();
    file.open(QIODevice::WriteOnly);
    QTextStream stream( &file );
    stream << doc.toString();
    file.close();
}

QStringList MainSetting::getReceiversEmails() {
    QDomDocument doc;
    QStringList emailList;
    file.open(QIODevice::ReadOnly);
    doc.setContent(&file, false);
    QDomElement root = doc.documentElement().firstChildElement("receivers");
    if(!root.isNull()) {
        root = root.firstChildElement("receiverEmail");
        emailList.push_back(root.firstChild().nodeValue());
        while(!root.nextSiblingElement().isNull()) {
            root = root.nextSiblingElement();
            emailList.push_back(root.firstChild().nodeValue());
        }
    }
    file.close();
    return emailList;
}

QString MainSetting::getSenderEmail() {
    QDomDocument doc;
    file.open(QIODevice::ReadOnly);
    doc.setContent(&file, false);
    QString email = doc.documentElement().firstChildElement("SenderEmail").firstChild().nodeValue();
    file.close();
    return email;
}
QString MainSetting::getSenderPassword() {
    QDomDocument doc;
    file.open(QIODevice::ReadOnly);
    doc.setContent(&file, false);
    QString password = doc.documentElement().firstChildElement("SenderPassword").firstChild().nodeValue();
    file.close();
    return password;
}

void MainSetting::CreateSetting() {
    QDomDocument doc;
    file.open(QIODevice::ReadOnly);
    if(!file.isOpen()) {
        QDomDocument doc;
        file.close();
        file.open(QIODevice::WriteOnly);
        QDomElement node = doc.createElement("config");
        QDomElement snode = doc.createElement("name");
        snode.appendChild( doc.createTextNode("Test run sollution"));
        node.appendChild(snode);
        snode = doc.createElement("info");
        snode.appendChild( doc.createTextNode("Info"));
        node.appendChild(snode);
        snode = doc.createElement("editor");
        node.appendChild(snode);
        snode = doc.createElement("dir");
        node.appendChild(snode);
        doc.appendChild(node);
        QTextStream stream( &file );
        stream << doc.toString();
    }
    file.close();
}
