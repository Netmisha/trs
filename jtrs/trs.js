var fileSystem = require("fs");
var xml2js = require('xml2js');
require('trs');
var suiteList = [];
function runScript(file, suite, index) {
    var fork = require('child_process').fork;
    var child = fork(file.substring(0, file.lastIndexOf("/")+1) + suite.test[index].execution,[__dirname,index]);
    child.on('message', (m) => {
        onTestFinished(m);
        runTests(file, suite, index+1);
    });
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
function onSuiteStarted (suite) {
    console.log('Suite: "'+suite.$.name+'" started ');
}
function onTestStarted (test) {
    console.log('\tTest: "'+test.$.name+'" started ');
}
function onTestFinished (data) {
    console.log('\tTest: "'+data.test+'" finished '+data.msg);
}
function onSuiteFinished (suite) {
    console.log('Suite: "'+suite.$.name+'" finished ');
}
function runTests(file, suite, index) {
    if(index<Object.keys(suite.test).length){
        if(suite.test[index].disable=="true") {
            runTests(file, suite, index+1);
        }
        else {
            onTestStarted(suite.test[index]);
            runScript(file, suite, index);
        }
    }
    else {
        onSuiteFinished(suite);
        runSuite();
    }                                
};
function runSuite() {
    if(suiteList.length!=0) {
        var file = suiteList.shift();
        var parser = new xml2js.Parser();  
        fileSystem.readFile(file, function(err, data) {
            parser.parseString(data, function (err, result) {
                if(result.suite.disable=="true") {
                    runSuite();
                }
                else {
                    onSuiteStarted(result.suite);
                    runTests(file, result.suite, 0);
                }
            });
        });
    }
    else {
        //process.send({msg:"done" });
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
            runSuite();
        }
    });
}
Sleep(2000);
FindTests();
