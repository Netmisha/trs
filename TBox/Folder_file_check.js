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


//---------checkDir_Start-----------//
var dirFail = false;
function checkDir(XMLArray,LoArray){
for(var i=0;i<XMLArray.length;i++){
if(contains(XMLArray[i],LoArray) == true){
}else{
dirFail = true;
window.alert("Missing folder: " + XMLArray[i]);
return;
}
}
}
//-----------checkDir_End-----------//

//-----------checkFile_Start--------//
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
      }else{window.alert("Missing data:" + tempXMLFiles[k]+"\n"+"At folder:"+XML_Folder[i]);return; }
      }tempXMLFiles = []; tempFinFiles =[];

    }
   }
}
window.alert("All data parts are present")
}
//-------------checkFile_END--------//

//------------contains_START--------//
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
//----------contains_END-----------//

//------main_function------//
var FileData = Box.getFileData("PATH_TO_XML"); // Double slash! (//)
var parser = new DOMParser();
var xmlData = parser.parseFromString(FileData,"text/xml");

//------Parse_XML_FILE---------------------//
var folder_name = new Array();
var folder_data = new Array();
var tmp_folder_data = new Array();
var nodes = xmlData.getElementsByTagName("dir");
for(var i=0;i<nodes.length;i++){
	folder_name.push(nodes[i].getAttribute("name"));
	for(var j=0;j<nodes[i].childNodes.length;j++){
		try{
		tmp_folder_data.push(nodes[i].childNodes[j].getAttribute("name"));
		}catch(e){}
	}
	tmp_folder_data.push(folder_name[i]);
	folder_data.push(tmp_folder_data.join("|"));
	tmp_folder_data  = [];
}
//--------END_of_Parse_XML_FILE----------//

struct_list("PATH_TO_TEST_FOLDER"); // Double slash (//)
var XML_Data = new Array();
var XML_Folder = new Array();
for(var i=0;i<folder_data.length;i++){
var temp;
temp = folder_data[i].split("|");
XML_Folder[i] = temp.pop();
XML_Data[i] = temp.join();
}
checkDir(XML_Folder,final_folders);
checkFiles(XML_Folder,XML_Data,final_folders,final_data);
//-------end_of_main_function------//