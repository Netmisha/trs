
var suiteList = [];
var _runScript = function(file) {
    var fork = require('child_process').fork;
    var child = fork(file);
    child.on('message', (m) => {
        console.log(m.msg);
        if(suiteList.length != 0) {
            _isEnable(suiteList.shift());
        }
    });
}
var _isEnable = function(file) {
    var fs = require('fs'); 
    var xml2js = require('./xml2js/node_modules/xml2js'); 
    var parser = new xml2js.Parser();  
    fs.readFile(file, function(err, data) {
    parser.parseString(data, function (err, result) {
        if(result.suite.disable=="true") {
            console.log(file + " is disabled");
            if(suiteList.length != 0) {
                _isEnable(suiteList.shift());
            }
        }
        else {
             console.log(file + " is started");
            var index = file.indexOf("/");
            var jsFile;
            while (index!=-1) {
                var tmpIndex = file.indexOf("/", index+1);
                if(tmpIndex==-1) {
                    break;
                }
                else {
                    index=tmpIndex;
                }
            }
            index++;
            var jsFile = file.substring(0, index) + result.suite.test[0].execution;
            _runScript(jsFile);
        }
    });
});
};
var _parseFolder = function(dir) {
    var fileSystem = require("fs");
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
        _parseFolder(file);
    });
};
var _runTest = function(dir) {
    var fileSystem = require("fs");
    var xml2js = require('./xml2js/node_modules/xml2js'); 
    fileSystem.readdirSync(dir).forEach(function(file) {
        file = dir+'/'+file;
        var stat = fileSystem.statSync(file);
        if(file.split('.').pop()=='xml') {
            var parser = new xml2js.Parser();  
            fileSystem.readFile(file, function(err, data) {
                parser.parseString(data, function (err, result) {
                    _parseFolder(dir + '/' + result.config.dir);
                    if(suiteList.length != 0) {
                        _isEnable(suiteList.shift());
                    }
                });
            });
        }
    });
};
_runTest(__dirname);