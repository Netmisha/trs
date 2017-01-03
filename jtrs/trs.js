var fileSystem = require("fs");
var xml2js = require('xml2js');
var suiteList = [];
var testsList = [];
function ParseSuite(suite, index) {
    var string = "";
    if(suite.disable=='false') {
        string="<li><input type=\"checkbox\" id=\"node-0-"+index+"\"  /><label><input type=\"checkbox\" checked=\"checked\"/><span></span></label><label onClick=\"GetInfo('"+suite.$.name+"', '')\" for=\"node-0-"+index+"\">";
    }
    else {
        string="<li><input type=\"checkbox\" id=\"node-0-"+index+"\"  /><label><input type=\"checkbox\" /><span></span></label><label onClick=\"GetInfo('"+suite.$.name+"', '')\" for=\"node-0-"+index+"\">";    
    }
    string+=suite.$.name+"</label><ul>";
    for(var i=0; i<Object.keys(suite.test).length; i++) {
        if(suite.disable=='false' && suite.test[i].disable == 'false') {
            string+="<li><input type=\"checkbox\" id=\"node-0-"+index+"-"+i+"\" checked=\"checked\" /><label><input type=\"checkbox\" checked=\"checked\"/><span></span></label><label onClick=\"GetInfo('"+suite.$.name+"', '"+suite.test[i].$.name+"')\" style=\"padding-left:10px;\">";
        }
        else {
            string+="<li><input type=\"checkbox\" id=\"node-0-"+index+"-"+i+"\" checked=\"checked\" /><label><input type=\"checkbox\" /><span></span></label><label onClick=\"GetInfo('"+suite.$.name+"', '"+suite.test[i].$.name+"')\" style=\"padding-left:10px;\">";  
        }
        string+=suite.test[i].$.name+"</label></li>";
    }
    string+="</ul></li>";
    /*string+="<li>Suite name: "+suite.$.name+'</li>';
    string+="<ul><li>Description: "+suite.$.description+'</li>';
    string+="<li>Tag: "+suite.tag+'</li>';
    string+="<li>Repeat: "+suite.repeat[0]._+" (pause = "+suite.repeat[0].$.pause+")"+'</li>';
    string+="<li>Max time: "+suite.maxTime+'</li>';
    string+="<li>Disable: "+suite.disable+'</li>';
    string+="<li>Application: "+suite.application+'</li>';
    string+="<li>Window name: "+suite.windowName+'</li>';
    string+="<li>Metadata:"+'</li>';
        string+="<ul><li>Author: "+suite.metadata[0].author+'</li>';
        string+="<li>Date: "+suite.metadata[0].date+'</li>';
        string+="<li>Version: "+suite.metadata[0].version+'</li>';
        string+="<li>Mail: "+suite.metadata[0].mail+'</li>';
        string+="<li>Copyright: "+suite.metadata[0].copyright+'</li>';
        string+="<li>License: "+suite.metadata[0].license+'</li>';
        string+="<li>Info: "+suite.metadata[0].info+'</li></ul>';
    for(var i=0; i<Object.keys(suite.test).length; i++) {
        string+="<li>Test name: "+suite.test[i].$.name+'</li>';
        string+="<ul><li>Description: "+suite.test[i].$.description+'</li>';
        string+="<li>Tag: "+suite.test[i].tag+'</li>';
        string+="<li>Disable: "+suite.test[i].disable+'</li>';
        string+="<li>Execution: "+suite.test[i].execution+'</li>';
        string+="<li>Result: "+suite.test[i].result+'</li>';
        string+="<li>Repeat: "+suite.test[i].repeat[0]._+" (pause = "+suite.test[i].repeat[0].$.pause+")"+'</li>';
        string+="<li>Max time: "+suite.test[i].maxTime+'</li></ul>';
    }
    string+="</ul>";*/
    return string;
}
function GetTestsInfo() {
    FindTests();
    if(suiteList.length == 0) {
        return "";
    }
    var parser = new xml2js.Parser();  
    var info = "<ul><li><input type=\"checkbox\" id=\"node-0\" checked=\"checked\" /><label><input type=\"checkbox\" checked=\"checked\" /><span></span></label><label onClick=\"GetInfo('', '')\" for=\"node-0\">Tests</label><ul>";
    for(var i=0; i<suiteList.length;i++) {
        parser.parseString(fileSystem.readFileSync(suiteList[i]).toString(),function (err, result) {
            info=info + ParseSuite(result.suite, i);
        });
    }
    info+="</ul></li></ul>";
    return info;
}
function GetSuitesInfo() {
    FindTests();
    var parser = new xml2js.Parser();  
    var suites= [];
    for(var i=0; i<suiteList.length;i++) {
        parser.parseString(fileSystem.readFileSync(suiteList[i]).toString(),function (err, result) {
            suites.push(result.suite);
        });
    }
    return JSON.stringify(suites);
}
function parseFolder(dir) {
    var childDir=[];
    fileSystem.readdirSync(dir).forEach(function(file) {
        file = dir+'/'+file;
        var stat = fileSystem.statSync(file);
        if (stat && stat.isDirectory()) {
            childDir.push(file);
        }
        else {
            if(file.split('.').pop()=='xml') {
                suiteList.push(file);
            }
        }
    });
    childDir.forEach(function(file){
        parseFolder(file);
    });
};
function FindTests() {
    suiteList=[];
    fileSystem.readdirSync(__dirname).forEach(function(file) {
        file = __dirname+'/'+file;
        var stat = fileSystem.statSync(file);
        if(file.split('.').pop()=='xml') {
            var parser = new xml2js.Parser();
            var dir;
            parser.parseString(fileSystem.readFileSync(file).toString(),function (err, result) {
                dir = __dirname + '/' + result.config.dir;
            });
            parseFolder(dir);
        }
    });
}
function GetTestsList () {
    testsList=[];
    FindTests();
    var parser = new xml2js.Parser();
    for(var i=0; i<suiteList.length; i++) { 
        parser.parseString(fileSystem.readFileSync(suiteList[i]).toString(),function (err, result) {
            if(result.suite.disable=="false") {
               for(var j=0; j<Object.keys(result.suite.test).length; j++) {
                    if(result.suite.test[j].disable=="false") {
                        var info = {
                            "name" : result.suite.test[j].$.name,
                            "file" : suiteList[i].substring(0, suiteList[i].lastIndexOf("/")+1) + result.suite.test[j].execution,
                            "suite": result.suite.$.name,
                            "description":result.suite.test[j].$.description,
                            "tag":result.suite.test[j].tag,
                            "disable":result.suite.test[j].disable,
                            "execution":result.suite.test[j].execution,
                            "result":result.suite.test[j].result,
                            "repeat":result.suite.test[j].repeat[0]._,
                            "repeatPause":result.suite.test[j].repeat[0].$.pause,
                            "maxTime":result.suite.test[j].maxTime,
                            "repeat":result.suite.test[j].repeat[0]._,
                            "pause":result.suite.test[j].repeat[0].$.pause
                        }
                        testsList.push(info);
                    }
               } 
            }
        });
    }
    return JSON.stringify(testsList);
}
global.GetTestsList = GetTestsList;
global.GetTestsInfo = GetTestsInfo;
global.GetSuitesInfo = GetSuitesInfo;