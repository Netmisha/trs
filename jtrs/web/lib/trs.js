var testsList = GetTestsInfo();
var suitesList = GetSuitesInfo();
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
	var tree = document.getElementById("tree")
	tree.innerHTML = SendRequestSync('info');
	/*if(document.getElementById("info") !=undefined) {
		document.body.removeChild(document.getElementById("info")); 
	}
	var info = document.createElement('div');
	info.id = "info";
	info.innerHTML = SendRequestSync('info');
	document.body.appendChild(info);*/
}
function GetInfo (suite, test) {
	var string = "";
	if(suite=="") {
		string+="<li>All tests:</li><ul>";
		for(var i=0; i<suitesList.length; i++) {
	        for(var j=0; j<Object.keys(suitesList[i].test).length; j++) {
		       string+="<li>"+suitesList[i].$.name+" : "+suitesList[i].test[j].$.name+"</li>";
		    }
    	}
    	string+="</ul>";
	}
	else if(test=="") {
		for(var i=0; i<suitesList.length; i++) {
	        if(suitesList[i].$.name == suite) {
	        	string+="<li>Suite name: "+suitesList[i].$.name+"</li>";
			    string+="<li>Description: "+suitesList[i].$.description+"</li>";
			    string+="<li>Tag: "+suitesList[i].tag+"</li>";
			    string+="<li>Repeat: "+suitesList[i].repeat[0]._+" (pause = "+suitesList[i].repeat[0].$.pause+")"+"</li>";
			    string+="<li>Max time: "+suitesList[i].maxTime+"</li>";
			    string+="<li>Disable: "+suitesList[i].disable+"</li>";
			    string+="<li>Application: "+suitesList[i].application+"</li>";
			    string+="<li>Window name: "+suitesList[i].windowName+"</li>";
			    string+="<li>Metadata:"+"</li>";
			        string+="<ul><li>Author: "+suitesList[i].metadata[0].author+"</li>";
			        string+="<li>Date: "+suitesList[i].metadata[0].date+"</li>";
			        string+="<li>Version: "+suitesList[i].metadata[0].version+"</li>";
			        string+="<li>Mail: "+suitesList[i].metadata[0].mail+"</li>";
			        string+="<li>Copyright: "+suitesList[i].metadata[0].copyright+"</li>";
			        string+="<li>License: "+suitesList[i].metadata[0].license+"</li>";
			        string+="<li>Info: "+suitesList[i].metadata[0].info+"</li></ul>";
	        }
	    }	
	}
	else {
		for(var i=0; i<suitesList.length; i++) {
	        if(suitesList[i].$.name == suite) {
	        	for(var j=0; j<Object.keys(suitesList[i].test).length; j++) {
			        if(suitesList[i].test[j].$.name == test) {
			        	string+="<li>Test name: "+suitesList[i].test[j].$.name+'</li>';
				        string+="<li>Description: "+suitesList[i].test[j].$.description+'</li>';
				        string+="<li>Tag: "+suitesList[i].test[j].tag+'</li>';
				        string+="<li>Disable: "+suitesList[i].test[j].disable+'</li>';
				        string+="<li>Execution: "+suitesList[i].test[j].execution+'</li>';
				        string+="<li>Result: "+suitesList[i].test[j].result+'</li>';
				        string+="<li>Repeat: "+suitesList[i].test[j].repeat[0]._+" (pause = "+suitesList[i].test[j].repeat[0].$.pause+")"+'</li>';
				        string+="<li>Max time: "+suitesList[i].test[j].maxTime+'</li>';		        	
			        }
			    }
	        }
    	}
	}
	info.innerHTML = string;
}
function Stop () {
	stopTests=true;
	init=0;
}
function Pause () {
	pauseTests=true;
}
function GetSuitesInfo () {
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