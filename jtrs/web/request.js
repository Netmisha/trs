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
	};
}
function SetWindowName(name) {
	SendRequest('event?type=SetWindowName&name='+encodeURIComponent(name));	
}
function SetAppName(name) {
	SendRequest('event?type=SetAppName&name='+encodeURIComponent(name));
}
function StartApp(name) {
	SendRequest('event?type=StartApp');
}
function CloseApp() {
	SendRequest('event?type=CloseApp');
}
function WindowMinimize()  {
	
}
function WindowMaximize() {
	
}
function SetActive() {
	
}
function WindowRestore() {
	
}
function GetScreenWidth() {
	
}
function GetScreenHeight() {
	
}
function KeyDown(dkey) {
	
}
function KeyUp(dkey) {
	
}
function KeyPress(dkey) {
	
}
function SetMousePos(x, y) {
	
}
function MouseMove(x, y, pause) {
	
}
function MouseDown(button) {
	
}
function MouseUp(button) {
	
}
function MouseClick(button) {
	
}
function MouseWheelDown() {
	
}
function MouseWheelUp() {
	
}
function MouseWheelLeft() {
	
}
function MouseWheelRight() {
	
}
function GetPID() {
	
}