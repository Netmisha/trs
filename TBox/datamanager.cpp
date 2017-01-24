#include "datamanager.h"
#include <QDebug>
DataManager::DataManager(QObject *parent) : QObject(parent) {

}
void DataManager::Set(QString path, QString data) {
    QStringList tags=path.split(tags_name::kXml+"/")[1].split("/");
    QFile file(path.split(tags_name::kXml)[0]+tags_name::kXml);
    file.open(QIODevice::ReadOnly);
    QXmlStreamReader Rxml;
    Rxml.setDevice(&file);
    Rxml.readNext();
    int index=0;
    while(!Rxml.atEnd()) {
        if(Rxml.isStartElement()) {
            if(Rxml.name() == tags[index]) {
                if(index==tags.length()-1) {
                    //return Rxml.readElementText();
                }
                else if(index==tags.length()-2 && Rxml.attributes().hasAttribute(tags[index+1])) {
                    //return Rxml.attributes().value(tags[index+1]).toString();
                }
                else if(index<=tags.length()-3 && Rxml.attributes().value(tags_name::kName).toString()==tags[index+1]) {
                    if(Rxml.attributes().hasAttribute(tags[index+2])){
                        //return Rxml.attributes().value(tags[index+2]).toString();
                    }
                    index+=2;
                    while(!Rxml.atEnd()) {
                        if(Rxml.isStartElement()) {
                            if(Rxml.name() == tags[index]) {
                                if(index==tags.length()-1) {
                                    //return Rxml.readElementText();
                                }
                                else if(index==tags.length()-2 && Rxml.attributes().hasAttribute(tags[index+1])) {
                                    //return Rxml.attributes().value(tags[index+1]).toString();
                                }
                                index++;
                            }
                        }
                        Rxml.readNext();
                    }
                }
                if(tags[index]!=tags_name::kTest) {
                    index++;
                }
            }
        }
        Rxml.readNext();
    }
    //return "";
}
QString DataManager::Get(QString path) {
    QStringList tags=path.split(tags_name::kXml+"/")[1].split("/");
    QFile file(path.split(tags_name::kXml)[0]+tags_name::kXml);
    file.open(QIODevice::ReadOnly);
    QXmlStreamReader Rxml;
    Rxml.setDevice(&file);
    Rxml.readNext();
    int index=0;
    while(!Rxml.atEnd()) {
        if(Rxml.isStartElement()) {
            if(Rxml.name() == tags[index]) {
                if(index==tags.length()-1) {
                    return Rxml.readElementText();
                }
                else if(index==tags.length()-2 && Rxml.attributes().hasAttribute(tags[index+1])) {
                    return Rxml.attributes().value(tags[index+1]).toString();
                }
                else if(index<=tags.length()-3 && Rxml.attributes().value(tags_name::kName).toString()==tags[index+1]) {
                    if(Rxml.attributes().hasAttribute(tags[index+2])){
                        return Rxml.attributes().value(tags[index+2]).toString();
                    }
                    index+=2;
                    while(!Rxml.atEnd()) {
                        if(Rxml.isStartElement()) {
                            if(Rxml.name() == tags[index]) {
                                if(index==tags.length()-1) {
                                    return Rxml.readElementText();
                                }
                                else if(index==tags.length()-2 && Rxml.attributes().hasAttribute(tags[index+1])) {
                                    return Rxml.attributes().value(tags[index+1]).toString();
                                }
                                index++;
                            }
                        }
                        Rxml.readNext();
                    }
                }
                if(tags[index]!=tags_name::kTest) {
                    index++;
                }
            }
        }
        Rxml.readNext();
    }
    return "";
}
void DataManager::SetData(QString, QString) {

}
QString DataManager::GetData(QString path) {
    return Get(path);
}
