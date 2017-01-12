var lastCallback=undefined;
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
				trs.SaveLog(); 
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
  			if(event.data=="Done!") {
  				if(typeof lastCallback === 'function') {
  					lastCallback();
  				}
  			}
  			if(type=='GetScreenWidth') {
		        trs.screenWidth=Number(event.data);
		    }
		    else if(type=='GetScreenHeight') {
		        trs.screenHeight=Number(event.data);
		    }
  		}
  		else if(req[0]=='log') {
  			var type=req[1].split('&')[0].split('=')[1];
  			if(type=='list') {
		        alert(event.data.split('&'));
		    }
		    else if(type=='get') {
		        alert(event.data);
		    }
  		}
  		else if(req[0]=='success') {
  			if(testList.length>0) {	
				currentTest=testList.shift();
				Start();
			}
  		}
  		else if(req[0]=='fail') {
  			if(testList.length>0) {	
				currentTest=testList.shift();
				Start();
			}
  		}
	};
}
function TRS () {
	this.screenHeight=-1;
	this.screenWidth=-1;
}
TRS.prototype.Init = function() {
	this.GetScreenWidth();
	this.GetScreenHeight();
}
TRS.prototype.SetWindowName = function(name, callback) {
	lastCallback=callback;
	SendRequest('event?type=SetWindowName&name='+encodeURIComponent(name));	
}
TRS.prototype.SetAppName = function(name, callback) {
	lastCallback=callback;
	SendRequest('event?type=SetAppName&name='+encodeURIComponent(name));
}
TRS.prototype.StartApp = function(callback) {
	lastCallback=callback;
	SendRequest('event?type=StartApp');
}
TRS.prototype.CloseApp = function(callback) {
	lastCallback=callback;
	SendRequest('event?type=CloseApp');
}
TRS.prototype.WindowMinimize = function(callback) {
	lastCallback=callback;
	SendRequest('event?type=WindowMinimize');
}
TRS.prototype.WindowMaximize = function(callback) {
	lastCallback=callback;
	SendRequest('event?type=WindowMaximize');
}
TRS.prototype.SetActive = function(callback) {
	lastCallback=callback;
	SendRequest('event?type=SetActive');
}
TRS.prototype.WindowRestore = function(callback) {
	lastCallback=callback;
	SendRequest('event?type=WindowRestore');
}
TRS.prototype.GetScreenWidth = function(callback) {
	lastCallback=callback;
	SendRequest('event?type=GetScreenWidth');
}
TRS.prototype.GetScreenHeight = function(callback) {
	lastCallback=callback;
	SendRequest('event?type=GetScreenHeight');
}
TRS.prototype.KeyDown = function(key, callback) {
	lastCallback=callback;
	SendRequest('event?type=KeyDown&key='+String(key));
}
TRS.prototype.KeyUp = function(key, callback) {
	lastCallback=callback;
	SendRequest('event?type=KeyUp&key='+String(key));
}
TRS.prototype.KeyPress = function(key, callback) {
	lastCallback=callback;
	SendRequest('event?type=KeyPress&key='+String(key));
}
TRS.prototype.SetMousePos = function(x, y, callback) {
	lastCallback=callback;
	SendRequest('event?type=SetMousePos&x='+String(x)+'&y='+String(y));
}
TRS.prototype.MouseMove = function(x, y, pause, callback) {
	lastCallback=callback;
	SendRequest('event?type=MouseMove&x='+String(x)+'&y='+String(y)+'&pause='+String(pause));
}
TRS.prototype.MouseDown = function(button, callback) {
	lastCallback=callback;
	SendRequest('event?type=MouseDown&button='+String(button));
}
TRS.prototype.MouseUp = function(button, callback) {
	lastCallback=callback;
	SendRequest('event?type=MouseUp&button='+String(button));
}
TRS.prototype.MouseClick = function(button, callback) {
	lastCallback=callback;
	SendRequest('event?type=MouseClick&button='+String(button));
}
TRS.prototype.MouseWheelDown = function( callback) {
	lastCallback=callback;
	SendRequest('event?type=MouseWheelDown');
}
TRS.prototype.MouseWheelUp = function( callback) {
	lastCallback=callback;
	SendRequest('event?type=MouseWheelUp');
}
TRS.prototype.MouseWheelLeft = function( callback) {
	lastCallback=callback;
	SendRequest('event?type=MouseWheelLeft');
}
TRS.prototype.MouseWheelRight = function( callback) {
	lastCallback=callback;
	SendRequest('event?type=MouseWheelRight');
}
TRS.prototype.PrintScreen = function(file, callback) {
	lastCallback=callback;
	SendRequest('event?type=PrintScreen&file='+encodeURIComponent(file));
}
TRS.prototype.PrintScreenA = function(x, y, w, h, file, callback) {
	lastCallback=callback;
	SendRequest('event?type=PrintScreenA&x='+String(x)+'&y='+String(y)+'&w='+String(w)+'&h='+String(h)+'&file='+encodeURIComponent(file));
}
TRS.prototype.Sleep = function(time, callback){
	lastCallback=callback;
	SendRequest('event?type=Sleep&time='+time);
};
TRS.prototype.WriteLog = function(msg) {
	SendRequest('log?msg='+encodeURIComponent(msg));
}
TRS.prototype.CreateLog = function() {
	SendRequest('log?msg=create');
}
TRS.prototype.SaveLog = function() {
	SendRequest('log?msg=save');
}
TRS.prototype.LogList = function() {
	SendRequest('log?msg=list');
}
TRS.prototype.GetLog = function(name) {
	SendRequest('log?msg=get&name='+encodeURIComponent(name));
}
TRS.prototype.Success = function(msg) {
	if(msg==undefined) {
		SendRequest('success');
	}
	else {
		SendRequest('success?msg='+encodeURIComponent(msg));
	}
}
TRS.prototype.Fail = function(name) {
	if(msg==undefined) {
		SendRequest('fail');
	}
	else {
		SendRequest('fail?msg='+encodeURIComponent(msg));
	}
}
var trs = new TRS();
trs.Init();