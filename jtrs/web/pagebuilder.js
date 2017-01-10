var rootSuite;
var rootNode;
var suiteList = "tree";
var infoId = "info";
function ParseSuite(node) {
    var string = "<li>";
    if(true) {
        string+="<input type=\"checkbox\" id=\""+node.id+"\"  /><label><input type=\"checkbox\" checked=\"checked\"/><span></span></label><label onClick=\"GetInfo('"+node.id+"', '')\" for=\""+node.id+"\">";
    }
    else {
        string+="<input type=\"checkbox\" id=\""+node.id+"\"  /><label><input type=\"checkbox\" /><span></span></label><label onClick=\"GetInfo('"+node.id+"', '')\" for=\""+node.id+"\">";    
    }
    string+=node.name+"</label><ul>";
    string+=ParseChildren(node.children);
    for(var i=0; i<Object.keys(node.tests).length; i++) {
        if(true) {
            string+="<li><input type=\"checkbox\" id=\""+node.id+"-"+String(i)+"\" checked=\"checked\" /><label><input type=\"checkbox\" checked=\"checked\"/><span></span></label><label onClick=\"GetInfo('"+node.id+"', '"+node.tests[i].name+"')\" style=\"padding-left:10px;\">";
        }
        else {
            string+="<li><input type=\"checkbox\" id=\""+node.id+"-"+String(i)+"\" checked=\"checked\" /><label><input type=\"checkbox\" /><span></span></label><label onClick=\"GetInfo('"+node.id+"', '"+node.tests[i].name+"')\" style=\"padding-left:10px;\">";  
        }
        string+=node.tests[i].name+"</label></li>";
    }
    string+="</ul></li>";
    return string;
}
function ParseChildren (suites, id) {
    var info="";
    if(suites.length == 0) {
        return info;
    }
    info+="<ul>";
    for(var i=0; i<suites.length; i++) {
        info+=ParseSuite(suites[i]);
    }
    return info+"</ul>";
}
function BuildTree() {
    var info="";
    if(rootNode.suiteId=="0") {
        return;
    }
    info=info + ParseSuite(rootNode);
    info+="</ul></li></ul>";
    var tree = document.getElementById(suiteList);
	tree.innerHTML = info;
}
function GetInfo (suiteId, test) {
	var string = "";
	string += ShowInfo (rootNode, suiteId, test);
	info.innerHTML = string;
}
function ShowSuiteInfo (suite) {
	var string = "";
	string+="<li>Suite name: "+suite.$.name+"</li>";
    string+="<li>Description: "+suite.$.description+"</li>";
    string+="<li>Path: "+suite.path+"</li>";
    string+="<li>Tag: "+suite.tag+"</li>";
    string+="<li>Repeat: "+suite.repeat[0]._+" (pause = "+suite.repeat[0].$.pause+")"+"</li>";
    string+="<li>Max time: "+suite.maxTime+"</li>";
    string+="<li>Disable: "+suite.disable+"</li>";
    string+="<li>Application: "+suite.application+"</li>";
    string+="<li>Window name: "+suite.windowName+"</li>";
    string+="<li>Metadata:"+"</li>";
        string+="<ul><li>Author: "+suite.metadata[0].author+"</li>";
        string+="<li>Date: "+suite.metadata[0].date+"</li>";
        string+="<li>Version: "+suite.metadata[0].version+"</li>";
        string+="<li>Mail: "+suite.metadata[0].mail+"</li>";
        string+="<li>Copyright: "+suite.metadata[0].copyright+"</li>";
        string+="<li>License: "+suite.metadata[0].license+"</li>";
        string+="<li>Info: "+suite.metadata[0].info+"</li></ul>";
    var info = document.getElementById(infoId);
	info.innerHTML = string;
}
function ShowTestInfo (test){
	var string = "";
	string+="<li>Test name: "+test.$.name+'</li>';
	string+="<li>Description: "+test.$.description+'</li>';
	string+="<li>Path: "+test.path+"</li>";
	string+="<li>Tag: "+test.tag+'</li>';
	string+="<li>Disable: "+test.disable+'</li>';
	string+="<li>Execution: "+test.execution+'</li>';
	string+="<li>Result: "+test.result+'</li>';
	string+="<li>Repeat: "+test.repeat[0]._+" (pause = "+test.repeat[0].$.pause+")"+'</li>';
	string+="<li>Max time: "+test.maxTime+'</li>';
	info.innerHTML = string;
}
function ShowInfo (node, suiteId, test) {
	var string = "";
	if(node.id != suiteId) {
		for(var j=0; j<node.children.length; j++) {
	    		string += ShowInfo (node.children[j], suiteId, test);
	    		if(string!="") {
	    			break;
	    		}
	    	}
	}
	else {
		if(test=="") {
			document.getElementById("req").value =node.path+'/';
			Get(node.path);
	    }
		else {
			for(var j=0; j<Object.keys(node.tests).length; j++) {
		        if(node.tests[j].name == test) {
		        	document.getElementById("req").value =node.path+'/test/'+node.tests[j].name+'/';
		        	Get(node.path+'/test/'+node.tests[j].name);	        	
		        }
		    }
		}
	}
	return string;
}
function SendReq() {
	var req=document.getElementById("req").value;
	Get(req);
}




/*var currentTestInfo={"test":{}, "path":"", "execution":""};
var stopTests=false;
var pauseTests=false;
var init=0;
function Start () {
	stopTests=false;
	pauseTests=false;
	if(currentTestInfo.path!="") {
		RunTests(currentTestInfo.execution);
	}
	for(var index=init; index<testsList.length; index++) {
		RunTests(testsList[index].file);
		if(stopTests || pauseTests) {
			break;
		}
	}
}
function Stop () {
	stopTests=true;
	init=0;
}
function Pause () {
	pauseTests=true;
}
function GetSuitesInfo () {
	SendRequestSync('suites');
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
function GetTestsInfo () {
	return JSON.parse(SendRequestSync('tests'));
}
function RunTests (file) {
	var script = document.createElement('script');
	script.id = "run";
	script.innerHTML = SendRequestSync('file?file='+file);
	document.head.appendChild(script);
	RunTest();  
	document.head.removeChild(document.getElementById("run")); 
}*/