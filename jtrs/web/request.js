function List () {
	SendRequestSync('list');
}
function ListPath (path) {
	SendRequestSync('list?path='+path);
}
function ListVerbose () {
	SendRequestSync('list?verbose=true');
}
function ListAll (path) {
	SendRequestSync('list?path='+path+'&verbose=true');
}
function Verify () {
	SendRequestSync('verify');
}
function VerifyPath (path) {
	SendRequestSync('verify?path='+path);
}
function Get (path) {
	SendRequestSync('get?path='+path);
}
function SendRequestSync(req) {
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
  			if(req[1].substr(req[1].lastIndexOf('/')+1, req[1].length).split('.')[1]=='xml') {
  				ShowSuiteInfo(JSON.parse(event.data));
  			}
  			else {
  				ShowTestInfo(JSON.parse(event.data));
  			}
  		}
	};
}