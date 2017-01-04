var rootSuite;
var currentTestInfo={"test":{}, "path":"", "execution":""};
var stopTests=false;
var pauseTests=false;
var init=0;
function Start () {
	stopTests=false;
	pauseTests=false;
	if(currentTestInfo.path!="") {
		RunTests(currentTestInfo.execution);
	}
	/*for(var index=init; index<testsList.length; index++) {
		RunTests(testsList[index].file);
		if(stopTests || pauseTests) {
			break;
		}
	}*/
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
}
function ShowInfo (node, suiteId, test) {
	var string = "";
	if(node.suiteId != suiteId) {
		for(var j=0; j<node.children.length; j++) {
	    		string += ShowInfo (node.children[j], suiteId, test);
	    		if(string!="") {
	    			break;
	    		}
	    	}
	}
	else {
		if(test=="") {
			currentTestInfo={"test":{}, "path":"", "execution":""};
	    	string+="<li>Suite name: "+node.suite.$.name+"</li>";
		    string+="<li>Description: "+node.suite.$.description+"</li>";
		    string+="<li>Path: "+node.path+"</li>";
		    string+="<li>Tag: "+node.suite.tag+"</li>";
		    string+="<li>Repeat: "+node.suite.repeat[0]._+" (pause = "+node.suite.repeat[0].$.pause+")"+"</li>";
		    string+="<li>Max time: "+node.suite.maxTime+"</li>";
		    string+="<li>Disable: "+node.suite.disable+"</li>";
		    string+="<li>Application: "+node.suite.application+"</li>";
		    string+="<li>Window name: "+node.suite.windowName+"</li>";
		    string+="<li>Metadata:"+"</li>";
		        string+="<ul><li>Author: "+node.suite.metadata[0].author+"</li>";
		        string+="<li>Date: "+node.suite.metadata[0].date+"</li>";
		        string+="<li>Version: "+node.suite.metadata[0].version+"</li>";
		        string+="<li>Mail: "+node.suite.metadata[0].mail+"</li>";
		        string+="<li>Copyright: "+node.suite.metadata[0].copyright+"</li>";
		        string+="<li>License: "+node.suite.metadata[0].license+"</li>";
		        string+="<li>Info: "+node.suite.metadata[0].info+"</li></ul>";
	    }
		else {
			for(var j=0; j<Object.keys(node.suite.test).length; j++) {
		        if(node.suite.test[j].$.name == test) {
		        	currentTestInfo={"test":node.suite.test[j], "path":node.path, "execution":node.path.substring(0, node.path.lastIndexOf("/")+1) + node.suite.test[j].execution};
		        	string+="<li>Test name: "+node.suite.test[j].$.name+'</li>';
			        string+="<li>Description: "+node.suite.test[j].$.description+'</li>';
		    		string+="<li>Path: "+node.path+"</li>";
			        string+="<li>Tag: "+node.suite.test[j].tag+'</li>';
			        string+="<li>Disable: "+node.suite.test[j].disable+'</li>';
			        string+="<li>Execution: "+node.suite.test[j].execution+'</li>';
			        string+="<li>Result: "+node.suite.test[j].result+'</li>';
			        string+="<li>Repeat: "+node.suite.test[j].repeat[0]._+" (pause = "+node.suite.test[j].repeat[0].$.pause+")"+'</li>';
			        string+="<li>Max time: "+node.suite.test[j].maxTime+'</li>';		        	
		        }
		    }
		}
	}
	return string;
}
function GetInfo (suiteId, test) {
	var string = "";
	string += ShowInfo (rootSuite, suiteId, test);
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