NB.ready(function(){
   Box.log("READY");
/*
//convert Objects to Base64
var array_objects = NB.page.getObjectsAsArray();
var ObjectsString = JSON.stringify(array_objects);
var result_ = btoa(ObjectsString);
console.log(result_);
*/
var strPageHash = "Panda";
Test.setData(strPageHash, "2799dff34b91ea88da62fc224143b116");
var PandaBase64 = Box.getFileData(Test.getCurrentDir()+"\\" + "PandaBase64.txt");
var decodedPanda = atob(PandaBase64);
var PSettings = new Array()
PSettings = JSON.parse(decodedPanda);
for(var i=0;i<PSettings.length;i++){
console.log(PSettings[i]);
var prototype = NB.objectPrototype.shape("triangle",PSettings[i]);
NB.addObject(prototype);
}
   objs = NB.page.getObjects();
   var curHash=getHash(objs);
   Box.log("Cur hash"+curHash);
   if(Test.isData(strPageHash)){
       if(Test.getData(strPageHash)==curHash){
           SUCCESS("Same Data");
       }else{
           FAIL("strPageHash: " + curHash);
       }
   }
});
Test.ExitOnFinish(false);
Box.log("END");