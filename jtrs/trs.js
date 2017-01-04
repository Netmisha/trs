var fileSystem = require("fs");
var xml2js = require('xml2js');
var suiteList = [];
var testsList = [];
var rootSuite={"suiteId":"0","path":"", "suite":{}, "children":[]};
function ParseSuite(node, suiteId) {
    var string = "<li>";
    if(node.suite.disable=='false') {
        string+="<input type=\"checkbox\" id=\""+suiteId+"\"  /><label><input type=\"checkbox\" checked=\"checked\"/><span></span></label><label onClick=\"GetInfo('"+suiteId+"', '')\" for=\""+suiteId+"\">";
    }
    else {
        string+="<input type=\"checkbox\" id=\""+suiteId+"\"  /><label><input type=\"checkbox\" /><span></span></label><label onClick=\"GetInfo('"+suiteId+"', '')\" for=\""+suiteId+"\">";    
    }
    string+=node.suite.$.name+"</label><ul>";
    string+=ParseChildren(node.children, node.suiteId);
    for(var i=0; i<Object.keys(node.suite.test).length; i++) {
        if(node.suite.disable=='false' && node.suite.test[i].disable == 'false') {
            string+="<li><input type=\"checkbox\" id=\""+suiteId+"-"+String(i)+"\" checked=\"checked\" /><label><input type=\"checkbox\" checked=\"checked\"/><span></span></label><label onClick=\"GetInfo('"+suiteId+"', '"+node.suite.test[i].$.name+"')\" style=\"padding-left:10px;\">";
        }
        else {
            string+="<li><input type=\"checkbox\" id=\""+suiteId+"-"+String(i)+"\" checked=\"checked\" /><label><input type=\"checkbox\" /><span></span></label><label onClick=\"GetInfo('"+suiteId+"', '"+node.suite.test[i].$.name+"')\" style=\"padding-left:10px;\">";  
        }
        string+=node.suite.test[i].$.name+"</label></li>";
    }
    string+="</ul></li>";
    return string;
}
function ParseChildren (suites, id) {
    var info="";
    if(suites.length == 0) {
        return info;
    }
    info+="<ul>";
    for(var i=0; i<suites.length; i++) {
        info+=ParseSuite(suites[i], suites[i].suiteId);
    }
    return info+"</ul>";
}
function GetTestsInfo() {
    FindTests('node-0');
    var info="";
    if(rootSuite.suiteId=="0") {
        return;
    }
    info=info + ParseSuite(rootSuite, rootSuite.suiteId);
    info+="</ul></li></ul>";
    return info;
}
function GetSuitesInfo() {
    FindTests('node-0');
    return JSON.stringify(rootSuite);
}
function parseFolder(dir, rootSuite, suiteId) {
    var childDir=[];
    var index = 0;
    var parser = new xml2js.Parser();
    fileSystem.readdirSync(dir).forEach(function(file) {
        file = dir+'/'+file;
        var stat = fileSystem.statSync(file);
        if (stat && stat.isDirectory()) {
            childDir.push(file);
        }
        else {
            if(file.split('.').pop()=='xml') {
                parser.parseString(fileSystem.readFileSync(file).toString(),function (err, result) {
                    rootSuite.suite=result.suite;
                    rootSuite.suiteId=suiteId;
                    rootSuite.path=file;
                });
            }
        }
    });
    childDir.forEach(function(file){
        rootSuite.children[index]={"suiteId":suiteId+"-"+String(index), "path":"", "suite":{}, "children":[]};
        parseFolder(file,rootSuite.children[index], rootSuite.children[index++].suiteId);
    });
};
function FindTests(suiteId) {
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
            parseFolder(dir, rootSuite, suiteId);
        }
    });
}
/*function GetTestsList () {
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
global.GetTestsList = GetTestsList;*/
global.GetTestsInfo = GetTestsInfo;
global.GetSuitesInfo = GetSuitesInfo;