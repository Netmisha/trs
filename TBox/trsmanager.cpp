#include "trsmanager.h"

TRSManager::TRSManager(QObject *parent) : QObject(parent) {

}
QString TRSManager::Parse(MainTree *node, QString path, QString t) {
    QString res="";
    QDirIterator it(path, QDirIterator:: NoIteratorFlags);
    while (it.hasNext()) {
        it.next();
        if(it.filePath().contains("/.") || it.filePath().contains("/.")) {
            continue;
        }
        else {
            if(it.filePath().contains(".xml")) {
                node->setName(node->getSuiteName(it.filePath()));
                res=t+node->name()+'\n';
                QStringList list=node->getTestsName(it.filePath());
                for(auto& iter:list) {
                    node->addTest(iter);
                    res+=t+"\t"+iter+'\n';
                }
            }
            if(it.fileInfo().isDir()) {
                MainTree *child = new MainTree();
                node->addSuite(child);
                res+=Parse(child, it.filePath(), t+"\t");
            }
        }
    }
    return res;
}

QStringList TRSManager::getTestsName(QString file_name) {
    QFile file(file_name);
    file.open(QIODevice::ReadOnly);
    QXmlStreamReader Rxml;
    QStringList testList;
    Rxml.setDevice(&file);
    Rxml.readNext();
    while(!Rxml.atEnd()) {
        if(Rxml.isStartElement()) {
            if(Rxml.name() == tags::kTest) {
                testList.push_back(Rxml.attributes().value(tags::kName).toString());
            }
        }
        Rxml.readNext();
    }
    file.close();
    return testList;
}

QString TRSManager::getSuiteName(QString file_name)
{
    QFile file(file_name);
    file.open(QIODevice::ReadOnly);
    QXmlStreamReader Rxml;
    Rxml.setDevice(&file);
    Rxml.readNext();
    while(!Rxml.atEnd()) {
        if(Rxml.isStartElement()) {
            if(Rxml.name() == tags::kSuite) {
                return Rxml.attributes().value(tags::kName).toString();
            }
        }
        Rxml.readNext();
    }
    file.close();
    return "";
}

QString TRSManager::getJS(QString file_name, QString test_name)
{
    QFile file(file_name);
    file.open(QIODevice::ReadOnly);
    QXmlStreamReader Rxml;
    file_name.data()[file_name.lastIndexOf('/')+1]='\0';
    QString exe=QString(file_name.data());
    Rxml.setDevice(&file);
    Rxml.readNext();
    while(!Rxml.atEnd()) {
        if(Rxml.isStartElement()) {
            if(Rxml.name() == tags::kTest) {
                if(Rxml.attributes().value(tags::kName).toString()==test_name) {
                    while(Rxml.name()!=tags::kExecution) {
                        Rxml.readNext();
                    }
                    exe+= Rxml.readElementText();
                    break;
                }
            }
        }
        Rxml.readNext();
    }
    file.close();
    qDebug()<<exe;
    file.setFileName(exe);
    file.open(QIODevice::ReadOnly);
    QString data(file.readAll());
    return data;
}
QString TRSManager::Run(QString script) {
    QFile file("qrc:/html/test.html");
    file.open(QIODevice::ReadWrite);
    QString data(file.readAll());
    QString newData = data.split("<script type=\"text/javascript\">")[0]+"<script type=\"text/javascript\">"+script+"</script>"+data.split("<script type=\"text/javascript\">")[1].split("</script>")[1];
    qDebug()<<newData;
}
QString TRSManager::ParseFolder(QString path)
{
    MainTree *root = new MainTree();
    QString res=Parse(root, path, "");
    root->getTestsName(root->name());
    return res;
}
