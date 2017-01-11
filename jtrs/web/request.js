function List () {
	SendRequest('list');
}
function ListPath (path) {
	SendRequest('list?path='+path);
}
function ListVerbose () {
	SendRequest('list?verbose=true');
}
function ListAll (path) {
	SendRequest('list?path='+path+'&verbose=true');
}
function Verify () {
	SendRequest('verify');
}
function VerifyPath (path) {
	SendRequest('verify?path='+path);
}
function Get (path) {
	SendRequest('get?path='+path);
}
function Set (path, value) {
	SendRequest('set?path='+path+'&value='+encodeURIComponent(value));
}
function SendRequest(req) {
	var socket = new WebSocket('ws://127.0.0.1:5000/' + req);
	socket.onmessage = function(event) {
		var pathName = event.currentTarget.url.substr(event.currentTarget.url.indexOf('/', 6)+1, event.currentTarget.url.length);
		var req = pathName.split('?'); 
  		if(req[0]=='list') {
  			if(req[1]!=undefined) {
  				if(req[1].indexOf('verbose')!=-1) {
		  			rootSuite = JSON.parse(event.data);
  				}
  				else {
	  				rootNode = JSON.parse(event.data);
			  		BuildTree();
	  			}
  			}
  			else {
  				rootNode = JSON.parse(event.data);
		  		BuildTree();
  			}
  		}
  		else if(req[0]=='verify') {
  			
  		}
  		else if(req[0]=='get') {
  			var path=req[1];
  			if(path.split('.')[1]=='xml') {
		        ShowSuiteInfo(JSON.parse(event.data));
		    }
		    else if(path.split('.')[1].split('/')[1]=='test' && path.split('.')[1].split('/').length == 3) {
		        ShowTestInfo(JSON.parse(event.data));
		    }
		    else if(path.split('.').length == 3){
		    	var script = document.createElement('script');
				script.id = "run";
				script.innerHTML = event.data;
				document.head.appendChild(script);
				RunTest();  
				document.head.removeChild(document.getElementById("run")); 
		    }
		    else {
		        alert(event.data);
		    }
  		}
  		else if(req[0]=='set') {
		    alert(event.data);
  		}
  		else if(req[0]=='event') {
  			var type=req[1].split('=')[1];
  			if(type=='GetScreenWidth') {
		        trs.screenWidth=Number(event.data);
		    }
		    else if(type=='GetScreenHeight') {
		        trs.screenHeight=Number(event.data);
		    }
		    //alert(event.data);
  		}
	};
}
function TRS () {
	this.screenHeight=-1;
	this.screenWidth=-1;
	this.Init();
}
TRS.prototype.Init = function() {
	this.GetScreenWidth();
	this.GetScreenHeight();
}
TRS.prototype.SetWindowName = function(name) {
	SendRequest('event?type=SetWindowName&name='+encodeURIComponent(name));	
}
TRS.prototype.SetAppName = function(name) {
	SendRequest('event?type=SetAppName&name='+encodeURIComponent(name));
}
TRS.prototype.StartApp = function(name) {
	SendRequest('event?type=StartApp');
}
TRS.prototype.CloseApp = function() {
	SendRequest('event?type=CloseApp');
}
TRS.prototype.WindowMinimize = function()  {
	SendRequest('event?type=WindowMinimize');
}
TRS.prototype.WindowMaximize = function() {
	SendRequest('event?type=WindowMaximize');
}
TRS.prototype.SetActive = function() {
	SendRequest('event?type=SetActive');
}
TRS.prototype.WindowRestore = function() {
	SendRequest('event?type=WindowRestore');
}
TRS.prototype.GetScreenWidth = function() {
	SendRequest('event?type=GetScreenWidth');
}
TRS.prototype.GetScreenHeight = function() {
	SendRequest('event?type=GetScreenHeight');
}
TRS.prototype.KeyDown = function(key) {
	SendRequest('event?type=KeyDown&key='+String(key));
}
TRS.prototype.KeyUp = function(key) {
	SendRequest('event?type=KeyUp&key='+String(key));
}
TRS.prototype.KeyPress = function(key) {
	SendRequest('event?type=KeyPress&key='+String(key));
}
TRS.prototype.SetMousePos = function(x, y) {
	SendRequest('event?type=SetMousePos&x='+String(x)+'&y='+String(y));
}
TRS.prototype.MouseMove = function(x, y, pause) {
	SendRequest('event?type=MouseMove&x='+String(x)+'&y='+String(y)+'&pause='+String(pause));
}
TRS.prototype.MouseDown = function(button) {
	SendRequest('event?type=MouseDown&button='+String(button));
}
TRS.prototype.MouseUp = function(button) {
	SendRequest('event?type=MouseUp&button='+String(button));
}
TRS.prototype.MouseClick = function(button) {
	SendRequest('event?type=MouseClick&button='+String(button));
}
TRS.prototype.MouseWheelDown = function() {
	SendRequest('event?type=MouseWheelDown');
}
TRS.prototype.MouseWheelUp = function() {
	SendRequest('event?type=MouseWheelUp');
}
TRS.prototype.MouseWheelLeft = function() {
	SendRequest('event?type=MouseWheelLeft');
}
TRS.prototype.MouseWheelRight = function() {
	SendRequest('event?type=MouseWheelRight');
}
TRS.prototype.Log = function(msg) {
	SendRequest('Log?msg='+encodeURIComponent(msg));
}

var trs = new TRS();