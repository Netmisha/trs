var header= "<!DOCTYPE html><html><head><title>TRS Service</title><link rel=\"stylesheet\" href=\"http://cdnjs.cloudflare.com/ajax/libs/uikit/2.12.0/css/uikit.min.css\"><script type=\"text/javascript\" src=\"http://cdnjs.cloudflare.com/ajax/libs/uikit/2.12.0/js/uikit.min.js\"></script><script type=\"text/javascript\" src=\"http://cdnjs.cloudflare.com/ajax/libs/uikit/2.12.0/js/uikit.min.js\"></script></head><body class=\"tm-background\"><div class=\"uk-container uk-container-center uk-margin-top\"><div class=\"uk-panel uk-panel-box uk-text-center\"><h1>TRS Manager</h1><p>Some description</p></div><div class=\"uk-panel uk-panel-box uk-text-left\">\n<a href=\"/start\" class=\"uk-button uk-button-primary uk-button-large\">Start</a>\n<a href=\"/stop\" class=\"uk-button uk-button-primary uk-button-large\">Stop</a>\n<a href=\"/pause\" class=\"uk-button uk-button-primary uk-button-large\">Pause</a>\n<a href=\"/list\" class=\"uk-button uk-button-primary uk-button-large\">Info</a></div>";
var footer="</div></body></html>";

var http = require('http');
var url = require('url');
var trs=require('./trs.js');
var trsStarted=false;
var response;
var server = new http.Server();
server.listen(8888,'127.0.0.1');
server.on('request', function(req, res){
	var urlParsed = url.parse(req.url, true);
	res.writeHead(200,{Location:"/index"} );
		if(urlParsed.pathname == '/start') {
			if(!trsStarted || trsStarted && IsTRSPaused()) {
				trsStarted=true;
				response=res;
				Start();
			}
			else {
				res.write(SetStatus('TRS has been working'));
			}
		}
		else if(urlParsed.pathname == '/list') {
			res.write(SetStatus(GetTestsInfo()));
		}
		else if(urlParsed.pathname == '/pause') {
			if(trsStarted && !IsTRSPaused()) {
				response=res;
				PauseTRS();
				return;
			}
			else {
				res.write(SetStatus('TRS is not working'));
			}
		}
		else if(urlParsed.pathname == '/stop') {
			if(trsStarted) {
				response=res;
				if(IsTRSPaused()) {
					CancelTRS();
				}
				else {
					StopTRS();
				}
				return;
			}
			else {
				res.write(SetStatus('TRS is not working'));
			}
		}
		else {
			res.write(header+footer);
		}
		res.end();
});
server.on('event', function(req){
	if(req.event=='paused') {
		response.write(SetStatus('TRS paused'));
	}
	else if(req.event=='stopped') {
		response.write(SetStatus('TRS stopped'));
		trsStarted=false;
	}
	else if(req.event=='working') {
		response.write(SetStatus('TRS is working'));
	}
	response.end();
});
function GetIndexPage() {
	return require("fs").readFileSync('server/index.html').toString()
}
function SetStatus(msg) {
	var page= header;
	page += "<div class=\"uk-panel uk-panel-box uk-text-left\"><h3 id=\"status\">" +msg + "</h3></div> "; 
	page+=footer;
	return page;
}
function AddList(msg) {
	var page= header;
	page += "<div class=\"uk-panel uk-panel-box uk-text-left\"><h5 id=\"testinfo\">" +msg + "</h5></div> "; 
	page+=footer;
	return page;
}
process.on('message', (m) => {
    	console.log(m.msg);
    });

global.server=server;
