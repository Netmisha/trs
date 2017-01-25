#ifndef EXPORT_DATA_H
#define EXPORT_DATA_H
#pragma once
#include <reporter.h>
#include <export_txt.h>
#include <export_html.h>
class export_txt;
class Export_HTML;
class Export_data: public Reporter{
public:
    Export_data();
    virtual void export_data(export_txt *data);
    virtual void export_data(Export_HTML *data);
};

#endif // EXPORT_DATA_H
