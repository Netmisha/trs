var os = require('os');
var messages = require(FindLibPath()+"modules/messages");
var msg;
var manage;
if (os.platform()=="win32") {
	var manageapp = require(FindLibPath()+"lib/Win/ApplicationManagementWin")
	manage = new manageapp.ApplicationManagement()
}	
function FindLibPath() {
	var path = __dirname;
	var index = path.indexOf("jtrs");
	path = path.substring(0, index+5);
	return path;
}
function CloseApp(repeat, pause){
	manage.CloseApp();
	if(--repeat>0) {
		setTimeout(StartApp,pause, repeat, pause);
	}
	else {
		msg.ResultOk(process);
	}
}
function SetActive(repeat, pause) {
	manage.isActive();
	setTimeout(CloseApp, pause, repeat, pause);	
}
function StartApp(repeat, pause){												
	manage.StartApp();
	setTimeout(SetActive,500, repeat, pause); 
}
function Test(){
	var fileSystem = require("fs");
    var xml2js = require(FindLibPath()+'xml2js/node_modules/xml2js'); 
    fileSystem.readdirSync(__dirname).forEach(function(file) {
        file = __dirname+'/'+file;
        var stat = fileSystem.statSync(file);
        if(file.split('.').pop()=='xml') {
            var parser = new xml2js.Parser();  
            fileSystem.readFile(file, function(err, data) {
                parser.parseString(data, function (err, result) {
                	manage.SetAppName(String(result.suite.application));
                	manage.SetWindowName(String(result.suite.windowName));
                	msg = new messages.Messages(result.suite.$.name, result.suite.test[0].$.name);
                    StartApp(Number(result.suite.test[0].repeat[0]._),Number(result.suite.test[0].repeat[0].$.pause));
                });
            });
        }
    });
}
Test();