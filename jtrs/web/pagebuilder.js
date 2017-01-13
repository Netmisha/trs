var rootSuite;
var rootNode;
var testList = [];
var currentTest = "";
var suiteList = "tree";
var infoId = "info";
var pauseRun=false;
function ParseSuite(node) {
    var string = "<li>";
    if(node.disable[0]!='true') {
        string+="<input type=\"checkbox\" id=\""+node.id+"\"  /><label><input type=\"checkbox\" checked=\"checked\"/><span></span></label><label onClick=\"GetInfo('"+node.id+"', '')\" for=\""+node.id+"\">";
    }
    else {
        string+="<input type=\"checkbox\" id=\""+node.id+"\"  /><label><input type=\"checkbox\" disabled /><span></span></label><label onClick=\"GetInfo('"+node.id+"', '')\" for=\""+node.id+"\">";    
    }
    string+=node.name+"</label><ul>";
    string+=ParseChildren(node.children);
    for(var i=0; i<Object.keys(node.tests).length; i++) {
        if(node.disable[0]!='true' && node.tests[i].disable[0]!='true') {
            string+="<li><input type=\"checkbox\" id=\""+node.tests[i].id+"\" checked=\"checked\" /><label><input type=\"checkbox\" checked=\"checked\"/><span></span></label><label onClick=\"GetInfo('"+node.id+"', '"+node.tests[i].name+"')\" style=\"padding-left:10px;\">";
        }
        else {
            string+="<li><input type=\"checkbox\" id=\""+node.tests[i].id+"\" checked=\"checked\"/><label><input type=\"checkbox\" disabled /><span></span></label><label onClick=\"GetInfo('"+node.id+"', '"+node.tests[i].name+"')\" style=\"padding-left:10px;\">";  
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
			currentTest="";
			Get(node.path);
	    }
		else {
			for(var j=0; j<Object.keys(node.tests).length; j++) {
		        if(node.tests[j].name == test) {
		        	currentTest=node.path+'/test/'+node.tests[j].name+'/execution.js';
		        	Get(node.path+'/test/'+node.tests[j].name);	        	
		        }
		    }
		}
	}
	return string;
}
function Start () {
	trs.CreateLog();
	if(currentTest!="") {
		Get(currentTest);
	}
}
function ParseSuiteStructure(node) {
	if(node.children.length>0) {
		for(var j=0; j<node.children.length; j++) {
			if(document.getElementById(node.children[j].id).nextElementSibling.firstChild.checked==true) {
				ParseSuiteStructure(node.children[j]);
			}
		}
	}
	for(var j=0; j<Object.keys(node.tests).length; j++) {
	        if(document.getElementById(node.tests[j].id).nextElementSibling.firstChild.checked==true) {
	        	testList.push(node.path+'/test/'+node.tests[j].name+'/execution.js');	
	        }
	}
}
function StartTree () {
	pauseRun=false;
	if(testList.length==0) {
		ParseSuiteStructure(rootNode);
	}
	if(testList.length>0) {	
		currentTest=testList.shift();
		Start();
	}
}
function StopTree () {
	testList=[];
}
function PauseTree () {
	pauseRun=true;
}