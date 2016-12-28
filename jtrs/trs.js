var fileSystem = require("fs");
var xml2js = require('xml2js');
require('trs');
var suiteList = [];
var stopTRS = false;
var pauseTRS = false;
var testFile;
var testSuite;
var testIndex = -1;
function runScript(file, suite, index) {
    var fork = require('child_process').fork;
    var child = fork(file.substring(0, file.lastIndexOf("/")+1) + suite.test[index].execution,[__dirname,index]);
    child.on('message', (m) => {
        onTestFinished(m);
        if(pauseTRS) {
            testFile=file;
            testSuite=suite;
            testIndex=index+1;
            server.emit('event', {event:"paused"});
        } 
        else if(stopTRS) {
            suiteList = [];
            testIndex=-1;
            server.emit('event', {event:"stopped"});
        }
        else {
            runTests(file, suite, index+1);
        }
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
    stopTRS = false;
    pauseTRS = false;
    server.emit('event', {event:"working"});
    if(testIndex==-1) {  
        FindTests();
        Sleep(2000);
        runSuite(); 
    }
    else {
        runTests(testFile, testSuite, testIndex);
    }
}
function ParseSuite(suite) {
    var string="";
    string+="<li>Suite name: "+suite.$.name+'</li>';
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
    string+="</ul>";
    return string;
}
function GetTestsInfo() {
    FindTests();
    var parser = new xml2js.Parser();  
    var info = "<ul>";
    for(var i=0; i<suiteList.length;i++) {
        parser.parseString(fileSystem.readFileSync(suiteList[i]).toString(),function (err, result) {
            info=info + ParseSuite(result.suite);
        });
    }
    suiteList=[];
    info+="</ul>";
    return info;
}
function PauseTRS() {
    pauseTRS=true;
}
function IsTRSPaused() {
    return pauseTRS;
}
function StopTRS() {
    stopTRS=true;    
}
function CancelTRS() {
    suiteList = [];
    testIndex=-1;
    server.emit('event', {event:"stopped"});
}
global.Start = Start;
global.GetTestsInfo = GetTestsInfo;
global.PauseTRS = PauseTRS;
global.StopTRS = StopTRS;
global.IsTRSPaused = IsTRSPaused;
global.CancelTRS = CancelTRS;