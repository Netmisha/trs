var testsList = GetTestsInfo();
var stopTests=false;
var pauseTests=false;
var init=0;
function Start () {
	stopTests=false;
	pauseTests=false;
	for(var index=init; index<testsList.length; index++) {
		RunTests(testsList[index].file);
		if(stopTests || pauseTests) {
			break;
		}
	}
}
function RunTests (file) {
	var script = document.createElement('script');
	script.id = "run";
	script.innerHTML = SendRequestSync('file?file='+file);
	document.head.appendChild(script);
	RunTest();  
	document.head.removeChild(document.getElementById("run")); 
}
function TestsInfo () {
	if(document.getElementById("info") !=undefined) {
		document.body.removeChild(document.getElementById("info")); 
	}
	var info = document.createElement('div');
	info.id = "info";
	info.innerHTML = SendRequestSync('info');
	document.body.appendChild(info);
}
function Stop () {
	stopTests=true;
	init=0;
}
function Pause () {
	pauseTests=true;
}
function GetSuitesInfo (argument) {
	return JSON.parse(SendRequestSync('suites'));
}
function GetTestsInfo () {
	return JSON.parse(SendRequestSync('tests'));
}
function SendRequestSync(req) {
    var xhr = new XMLHttpRequest();
    xhr.open('GET', req, false);
    xhr.send();
    return xhr.responseText;
}
function SendRequestAsync(req) {
	var xhr = new XMLHttpRequest();
    xhr.open('GET', req, true);
    xhr.send();
    return xhr.responseText;
} 