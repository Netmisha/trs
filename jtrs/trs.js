var fileSystem = require("fs");
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
    return JSON.stringify(rootNode);
}
function GetAllInfo(dir) {
    FindTests(dir, 'node-0');
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
        if(path[0]=='name') {
            res=obj.$.name;
        }
        else if(path[0]=='description') {
            res=obj.$.description;
        }
        else if(path[0]=='repeat') {
            res=obj.repeat[0]._;
        }
        else if(path[0]=='pause') {
            res=obj.repeat[0].$.pause;
        }
        else if(path[0]=='metadata') {
            obj=obj.metadata[0];
            res=obj[path[1]]
        }
        else if(path[0]=='test') {
            res=obj.test;
            for(var j=0; j<obj.test.length; j++) {
                if(obj.test[j].$.name==path[1]) {
                    obj=obj.test[j];
                    if(path[2]=='name') {
                        res=obj.$.name;
                    }
                    else if(path[2]=='description') {
                        res=obj.$.description;
                    }
                    else if(path[2]=='repeat') {
                        res=obj.repeat[0]._;
                    }
                    else if(path[2]=='pause') {
                        res=obj.repeat[0].$.pause;
                    }
                    else if(path[2]=='execution.js') {
                        res=fileSystem.readFileSync(file.substr(0, file.lastIndexOf('/')+1)+obj.execution).toString();
                    }
                    else {
                        res=obj[path[2]]
                    }
                    break;
                }
            }
        }
        else  {
            res=obj[path[0]]
        }
    });
    return String(res);
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
global.GetStructure = GetStructure;
global.GetSuiteInfo = GetSuiteInfo;
global.GetTestInfo = GetTestInfo;
global.GetAllInfo = GetAllInfo;
global.GetProperty = GetProperty;