#ifndef EXPORT_TXT_H
#define EXPORT_TXT_H
#include <QFile>
#include <QDir>

#include <QIODevice>
#include <QDebug>
class export_txt
{
public:
    export_txt();
    void init();
    void export_txt_file(QDir save_path);

};

#endif // EXPORT_TXT_H
