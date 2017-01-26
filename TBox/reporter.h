#ifndef REPORTER_H
#define REPORTER_H
#include <QDir>
#include <QFile>
#include <QIODevice>
#include <QDebug>
class Reporter
{
public:
    Reporter();
    void init(QDir save_path);
    QFile *file;
};

#endif // REPORTER_H
