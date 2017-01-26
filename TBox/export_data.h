#ifndef EXPORT_DATA_H
#define EXPORT_DATA_H
#include <export_txt.h>

class Export_data: public export_txt
{
public:
    Export_data();
    export_txt obj;
    void exportTXT(QDir file_path);

};

#endif // EXPORT_DATA_H
