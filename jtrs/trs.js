
var fileSystem = require("fs");
var xml2js = require('xml2js');
var suiteList = [];
function runScript(file) {
    var fork = require('child_process').fork;
    var child = fork(file,[__dirname]);
    child.on('message', (m) => {
        console.log(m.msg);
        runTests();
    });
}
function isEnable(file) {
    var enabled;
    var parser = new xml2js.Parser();  
    fileSystem.readFile(file, function(err, data) {
    parser.parseString(data, function (err, result) {
        if(result.suite.disable=="true") {
            enabled = false;
        }
        else {
            enabled = true;
        }
    });
    console.log(enabled);
    return enabled;
});
};
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
function runTests() {
    if(suiteList.length!=0) {
        var file = suiteList.shift();
        var parser = new xml2js.Parser();  
        fileSystem.readFile(file, function(err, data) {
            parser.parseString(data, function (err, result) {
                if(result.suite.disable=="true") {
                    console.log(file + " is disabled");
                    runTests();
                }
                else {
                    console.log(file + " is started");
                    runScript(file.substring(0, file.lastIndexOf("/")+1) + result.suite.test[0].execution);
                }
            });
        });
    }                                 
};
function FindTests() {
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
            runTests();
        }
    });
}
FindTests();
