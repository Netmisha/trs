var curent_folder = new Array();
var folder_d = new Array();
var el = new Array();
var final_data = new Array();
var final_folders = new Array();
var temp_final_data;
var ar = new Array();
//----structs_data_from_c++_side---//
function struct_list(path){
el = Box.getFullList(path);
for(i=0;i<el.length;i++){
if(Box.isFile(el[i])){
continue;}
if(Box.isDir(el[i])){
curent_folder.push(el[i]);
}
}
for(var i=0;i<curent_folder.length;i++){
final_folders[i] = curent_folder[i].split("/").pop();
temp_final_data = Box.getList(curent_folder[i]);
for(j=0;j<temp_final_data.length;j++){
ar[j] = temp_final_data[j].split("/").pop();
}
final_data.push(ar.join());
ar=[];
}
final_folders.push(path.split("\\").pop());
temp_final_data = Box.getList(path);
for(var i=0;i<Box.getList(path).length;i++){
ar[i] = temp_final_data[i].split("/").pop();
}
final_data.push(ar.join());
}

//final_data - contains data for folders in final_folders i=i;
//-----------function_end----------//

var dirFail = false;
function checkDir(XMLArray,LoArray){
for(var i=0;i<XMLArray.length;i++){
if(contains(XMLArray[i],LoArray) == true){
}else{
window.alert("Missing folder: " + XMLArray[i]);
dirFail = true;
return;
}
}
}
function checkFiles(XML_Folder,XML_Data,final_folders,final_data){
if(dirFail){return;}
var tempXMLFiles = new Array();
var tempFinFiles = new Array();
for(var i=0;i<XML_Folder.length;i++){
   for(var j=0;j<final_folders.length;j++){
    if(XML_Folder[i] == final_folders[j]){
       tempXMLFiles = XML_Data[i].split(",");
       tempFinFiles = final_data[j].split(",");
      for(var k=0;k<tempXMLFiles.length;k++){
      if(contains(tempXMLFiles[k],tempFinFiles)){
      }else{window.alert("Missing file:" + tempXMLFiles[k]+"\n"+"At folder:"+XML_Folder[i]);return; }
      }tempXMLFiles = []; tempFinFiles =[];

    }
   }
}
window.alert("All data parts are present")
}
function contains(data,array){
Box.log(data);
Box.log(array);
if(array.indexOf(data,0) >= 0){
return true;
}
else{
return false;
}
}
//------main_function------//
var FileData = Box.getFileData("Path to XML file");
struct_list("Path to folder");
var XML_Data = new Array();
var XML_Folder = new Array();
for(var i=0;i<FileData.length;i++){
var temp;
temp = FileData[i].split("|");
XML_Folder[i] = temp.pop();
XML_Data[i] = temp.join();
}
checkDir(XML_Folder,final_folders);
checkFiles(XML_Folder,XML_Data,final_folders,final_data);
//-------end_of_main_function------//