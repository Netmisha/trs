#include "export_data.h"

Export_data::Export_data()
{

}
void Export_data::export_data(export_txt *data){
data->export_txt_data();
}
 void Export_data::export_data(Export_HTML *data){
 data->export_html_data();
 }
