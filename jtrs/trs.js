var fileSystem = require("fs"); // loads module
var xml2js = require('xml2js');
var suiteList = [];
var testsList = [];
var rootSuite={"suiteId":"0","path":"", "suite":{}, "children":[]};
var rootNode={"id":"0","path":"", "name":{}, "tests":[], "children":[]};
function ParseSuite(suite, node) {
    node.id=suite.suiteId;
    node.path=suite.path;
    node.name=suite.suite.$.name;
    for(var i=0; i<Object.keys(suite.suite.test).length; i++) {
        node.tests[i]={'id':suite.suiteId+"-"+String(i), 'name':suite.suite.test[i].$.name, 'path':node.path};
    }
    for(var i=0; i<Object.keys(suite.children).length; i++) {
        node.children[i]={"id":"0","path":"", "name":{}, "tests":[], "children":[]};
        ParseSuite(suite.children[i], node.children[i]);
    }
}
function GetStructure(dir) {
    FindTests(dir, 'node-0');
    if(rootSuite.suiteId=="0") {
        return;
    }
    ParseSuite(rootSuite, rootNode);
    console.log(rootNode);
    return JSON.stringify(rootNode);
}
function GetAllInfo(dir) {
    FindTests(dir, 'node-0');
    console.log(rootSuite);
    return JSON.stringify(rootSuite);
}
function GetSuiteInfo(file) {
    var parser = new xml2js.Parser();
    var suite;
    parser.parseString(fileSystem.readFileSync(file).toString(),function (err, result) {
        suite=result.suite;
        suite.path=file;
    });
    return JSON.stringify(suite);
}
function GetTestInfo(file, name) {
    var parser = new xml2js.Parser();
    var test;
    parser.parseString(fileSystem.readFileSync(file).toString(),function (err, result) {
        for(var j=0; j<Object.keys(result.suite.test).length; j++) {
            if(result.suite.test[j].$.name==name) {
                test=result.suite.test[j];
                test.path=file;
                break;
            }
       } 
    });
    return JSON.stringify(test);
}
function GetProperty(file, property) {
    var path=property.split('/');
    var parser = new xml2js.Parser();
    var res="";
    parser.parseString(fileSystem.readFileSync(file).toString(),function (err, result) {
        var obj=result.suite;
        return obj.property;
        /*for(var i=0; i<path.length;i++) {
            if(path[i]=='name') {
                res=obj.$.name;
                break;
            }
            if(path[i]=='description') {
                res=obj.$.description;
                break;
            }
            if(path[i]=='repeat') {
                res=obj.repeat[0]._;
                break;
            }
            if(path[i]=='pause') {
                res=obj.repeat[0].$.pause;
                break;
            }
            if(path[i]=='metadata') {
                res=obj.metadata[0];
                break;
            }
            if(path[i]=='test') {
                i++;
                res=obj.test;
                for(var j=0; j<obj.test.length; j++) {
                    if(obj.test[j].$.name==path[i]) {
                        obj=obj.test[j];
                        break;
                    }
                }
            }

        }*/
    });
    return JSON.stringify(suite);
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
function FindTests(dir, suiteId) {
    if(dir!=__dirname) {
        parseFolder(dir, rootSuite, suiteId);
    }
    else {
        fileSystem.readdirSync(dir).forEach(function(file) {
            file = dir+'/'+file;
            var stat = fileSystem.statSync(file);
            if(file.split('.').pop()=='xml') {
                var parser = new xml2js.Parser();
                var testsDir;
                parser.parseString(fileSystem.readFileSync(file).toString(),function (err, result) {
                    testsDir = dir + '/' + result.config.dir;
                });
                parseFolder(testsDir, rootSuite, suiteId);
            }
        });
    }
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
global.GetStructure = GetStructure;
global.GetSuiteInfo = GetSuiteInfo;
global.GetTestInfo = GetTestInfo;
global.GetAllInfo = GetAllInfo;