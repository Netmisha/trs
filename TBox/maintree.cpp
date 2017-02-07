#include "maintree.h"
TreeInfo::TreeInfo(QString fil, QString nam, QString typ, int rep, QModelIndex ind)
    : file(fil), name(nam), type(typ), repeat(rep), item(ind) {}
QString TreeInfo::getPath(){
    return QString(file).replace("/suite.xml","");
}
