#include "datamanager.h"
#include <QDebug>
#include <QDomDocument>
#include <QDir>
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
            if(i+1==tags.length()) {
                if(!root.firstChildElement(tags[i]).isNull()) {
                    root.firstChildElement(tags[i]).firstChild().setNodeValue(data);
                }
                else {
                    QDomElement node = doc.createElement(tags[i]);
                    root.appendChild(node);
                    node.appendChild( doc.createTextNode(data));
                }
            }
        }
    }
    file.close();
    file.open(QIODevice::WriteOnly);
    QTextStream stream( &file );
    stream << doc.toString();
    file.close();
}
QString DataManager::AddTest(QString path, QString name, QString dis, QString tag, QString exe, QString rep, QString disable, QString important, QString alwaysRun) {
    if(name=="" || exe=="" || !(disable=="true" || disable=="false")) {
        return "Fill all fields correctly!";
    }
    QDomDocument doc;
    QString jspath=path;
    jspath.data()[path.lastIndexOf("/")+1]='\0';
    jspath=QString(jspath.data())+exe;
    QFile js(jspath);
    js.open(QIODevice::WriteOnly);
    js.close();
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
        QDomElement node = doc.createElement(tags_name::kTest);
        node.setAttribute(tags_name::kName, name);
        node.setAttribute(tags_name::kDescription, dis);
        root.appendChild(node);
        QDomElement snode = doc.createElement(tags_name::kTag);
        snode.appendChild( doc.createTextNode(tag));
        node.appendChild(snode);
        snode = doc.createElement(tags_name::kDisable);
        snode.appendChild( doc.createTextNode(disable));
        node.appendChild(snode);
        snode = doc.createElement(tags_name::kExecution);
        snode.appendChild( doc.createTextNode(exe));
        node.appendChild(snode);
        snode = doc.createElement(tags_name::kRepeat);
        snode.appendChild( doc.createTextNode(rep));
        node.appendChild(snode);
        snode = doc.createElement(tags_name::kImportant);
        snode.appendChild( doc.createTextNode(important));
        node.appendChild(snode);
        snode = doc.createElement(tags_name::kAlwaysRun);
        snode.appendChild( doc.createTextNode(alwaysRun));
        node.appendChild(snode);
        snode = doc.createElement(tags_name::kHeaders);
        node.appendChild(snode);
    }
    file.close();
    file.open(QIODevice::WriteOnly);
    file.write(doc.toString().toLatin1());
    file.close();
    return "";
}
QString DataManager::AddSuite(QString path, QString name, QString dis, QString rep, QString disable) {
    if(name=="" || !(disable=="true" || disable=="false")) {
        return "Fill all fields correctly!";
    }
    QDomDocument doc;
    QString newpath=path;
    newpath.data()[path.lastIndexOf("/")+1]='\0';
    newpath=QString(newpath.data())+name;
    if(QDir(newpath).exists()) {
        return "Suite already exists!";
    }
    QDir qd;
    qd.mkpath(newpath);
    QFile file(newpath+"/suite.xml");
    file.open(QIODevice::WriteOnly);
    QDomElement node = doc.createElement(tags_name::kSuite);
    node.setAttribute(tags_name::kName, name);
    node.setAttribute(tags_name::kDescription, dis);
    QDomElement snode = doc.createElement(tags_name::kRepeat);
    snode.appendChild( doc.createTextNode(rep));
    node.appendChild(snode);
    snode = doc.createElement(tags_name::kDisable);
    snode.appendChild( doc.createTextNode(disable));
    node.appendChild(snode);
    QDomElement mnode = doc.createElement(tags_name::kMetadata);
    snode = doc.createElement(tags_name::kAuthor);
    mnode.appendChild(snode);
    snode = doc.createElement(tags_name::kDate);
    mnode.appendChild(snode);
    snode = doc.createElement(tags_name::kVersion);
    mnode.appendChild(snode);
    snode = doc.createElement(tags_name::kMail);
    mnode.appendChild(snode);
    snode = doc.createElement(tags_name::kCopyright);
    mnode.appendChild(snode);
    snode = doc.createElement(tags_name::kLicense);
    mnode.appendChild(snode);
    snode = doc.createElement(tags_name::kInfo);
    mnode.appendChild(snode);
    node.appendChild(mnode);
    doc.appendChild(node);
    QTextStream stream( &file );
    stream << doc.toString();
    file.close();
    return "";
}
QString DataManager::AddRoot(QString path, QString name, QString dis, QString rep, QString disable) {
    if(name=="" || !(disable=="true" || disable=="false")) {
        return "Fill all fields correctly!";
    }
    QDomDocument doc;
    QFile file(path);
    file.open(QIODevice::WriteOnly);
    QDomElement node = doc.createElement(tags_name::kSuite);
    node.setAttribute(tags_name::kName, name);
    node.setAttribute(tags_name::kDescription, dis);
    QDomElement snode = doc.createElement(tags_name::kRepeat);
    snode.appendChild( doc.createTextNode(rep));
    node.appendChild(snode);
    snode = doc.createElement(tags_name::kDisable);
    snode.appendChild( doc.createTextNode(disable));
    node.appendChild(snode);
    QDomElement mnode = doc.createElement(tags_name::kMetadata);
    snode = doc.createElement(tags_name::kAuthor);
    mnode.appendChild(snode);
    snode = doc.createElement(tags_name::kDate);
    mnode.appendChild(snode);
    snode = doc.createElement(tags_name::kVersion);
    mnode.appendChild(snode);
    snode = doc.createElement(tags_name::kMail);
    mnode.appendChild(snode);
    snode = doc.createElement(tags_name::kCopyright);
    mnode.appendChild(snode);
    snode = doc.createElement(tags_name::kLicense);
    mnode.appendChild(snode);
    snode = doc.createElement(tags_name::kInfo);
    mnode.appendChild(snode);
    node.appendChild(mnode);
    doc.appendChild(node);
    QTextStream stream( &file );
    stream << doc.toString();
    file.close();
    return "";
}
QString DataManager::RemoveTest(QString path, QString name) {
    QDomDocument doc;
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    if (!doc.setContent(&file, false)) {
            return "";
    }
    QDomElement root = doc.documentElement();
    QDomElement test = root.firstChildElement(tags_name::kTest);
    while (test.attribute(tags_name::kName)!=name) {
        test = test.nextSiblingElement(tags_name::kTest);
    }
    file.close();
    if(!test.isNull()) {
        root.removeChild(test);
        file.open(QIODevice::WriteOnly);
        QTextStream stream( &file );
        stream << doc.toString();
        file.close();
        return "";
    }
    file.close();
    return "Test dont found!";
}
QString DataManager::RemoveSuite(QString path) {
    QString newpath=path;
    newpath.data()[path.lastIndexOf("/")]='\0';
    newpath=QString(newpath.data());
    if(!QDir(newpath).exists()) {
        return "Suite does not exists!";
    }
    QDir qd(newpath);
    qd.removeRecursively();
    return "";
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
QStringList DataManager::getHeaders(QString paht, QString test) {
    QDomDocument doc;
    QFile file(paht);
    QStringList headers;
    file.open(QIODevice::ReadOnly);
    if (doc.setContent(&file, false)) {
        QDomElement root = doc.documentElement();
        root = root.firstChildElement(tags_name::kTest);
        while (root.attribute(tags_name::kName)!=test) {
            root = root.nextSiblingElement(tags_name::kTest);
        }
        root = root.firstChildElement(tags_name::kHeaders);
        root = root.firstChildElement(tags_name::kScr);
        while (!root.isNull()) {
            headers.push_back(root.firstChild().nodeValue());
            root = root.nextSiblingElement(tags_name::kScr);
        }
    }
    file.close();
    return headers;
}
