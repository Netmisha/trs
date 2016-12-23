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
        }
    });
}
function Start() {
    FindTests();
    Sleep(2000);
    runSuite();
}
function ParseSuite(suite) {
    var string="";
    string+="Suite name: "+suite.$.name+'\n';
    string+="\tDescription: "+suite.$.description+'\n';
    string+="\tTag: "+suite.tag+'\n';
    string+="\tRepeat: "+suite.repeat[0]._+" (pause = "+suite.repeat[0].$.pause+")"+'\n';
    string+="\tMax time: "+suite.maxTime+'\n';
    string+="\tDisable: "+suite.disable+'\n';
    string+="\tApplication: "+suite.application+'\n';
    string+="\tWindow name: "+suite.windowName+'\n';
    string+="\tMetadata:"+'\n';
        string+="\t\tAuthor: "+suite.metadata[0].author+'\n';
        string+="\t\tDate: "+suite.metadata[0].date+'\n';
        string+="\t\tVersion: "+suite.metadata[0].version+'\n';
        string+="\t\tMail: "+suite.metadata[0].mail+'\n';
        string+="\t\tCopyright: "+suite.metadata[0].copyright+'\n';
        string+="\t\tLicense: "+suite.metadata[0].license+'\n';
        string+="\t\tInfo: "+suite.metadata[0].info+'\n';
    for(var i=0; i<1; i++) {//Object.keys(suite.$.test).length
        string+="\tTest name: "+suite.test[i].$.name+'\n';
        string+="\t\tTest description: "+suite.test[i].$.description+'\n';
        string+="\t\tTag: "+suite.test[i].tag+'\n';
        string+="\t\tDisable: "+suite.test[i].disable+'\n';
        string+="\t\tExecution: "+suite.test[i].execution+'\n';
        string+="\t\tResult: "+suite.test[i].result+'\n';
        string+="\t\tRepeat: "+suite.test[i].repeat[0]._+" (pause = "+suite.test[i].repeat[0].$.pause+")"+'\n';
        string+="\t\tMax time: "+suite.test[i].maxTime+'\n';
    }
    return string;
}
function GetTestsInfo() {
    FindTests();
    var parser = new xml2js.Parser();  
    var info = "";
    for(var i=0; i<suiteList.length;i++) {
        parser.parseString(fileSystem.readFileSync(suiteList[i]).toString(),function (err, result) {
            info=info + ParseSuite(result.suite);
        });
    }
    suiteList=[];
    return info;
}

global.Start = Start;
global.GetTestsInfo = GetTestsInfo;
