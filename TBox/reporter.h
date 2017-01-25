#ifndef REPORTER_H
#define REPORTER_H
#pragma once
#include <QDir>
#include <QFile>
#include <QIODevice>
#include <QDebug>
#include <export_txt.h>
#include <export_html.h>

class Reporter
{
public:
    Reporter();
    void init();
    virtual void export_data(export_txt *data);
    virtual void export_data(Export_HTML *data);

};

#endif // REPORTER_H
