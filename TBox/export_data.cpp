#include "export_data.h"

Export_data::Export_data()
{

}
void Export_data::exportTXT(QDir file_path){
    obj.export_txt_file(file_path);

}
