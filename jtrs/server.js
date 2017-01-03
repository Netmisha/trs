var http = require('http');
var url = require('url');
var trs=require('./trs.js');
var fileSystem = require("fs");
var trsStarted=false;
var response;
var server = new http.Server(function(req, res){
	var urlParsed = url.parse(req.url, true);
		var htmlPage = fileSystem.readFileSync('src/index.html').toString();
		if(req.url=='/tests') {
			res.writeHead(200, {
      			'Content-Type': 'text/plain',
      			'Cache-Control': 'no-cache'
    		});
			res.write(GetTestsList());
			res.end();
		}
		else if(urlParsed.path.split("?")[0]=='/info') {
			res.write(GetTestsInfo());
			res.end();
		}
		else if(urlParsed.path.split("?")[0]=='/file') {
			res.write(fileSystem.readFileSync(urlParsed.path.split("?")[1].split("=")[1]).toString());
			res.end();
		}
		else if(urlParsed.path=='/suites') {
			res.write(GetSuitesInfo());
			res.end();
		}
		else if(urlParsed.path=='/trs') {
			res.write(fileSystem.readFileSync('src/trs.js').toString());
			res.end();
		}
		else {
			res.write(htmlPage);
			res.end();
		}
	});
server.listen(8888,'127.0.0.1');
/*server.on('request', function(req, res){
	var urlParsed = url.parse(req.url, true);
		var htmlPage = fileSystem.readFileSync('src/index.html').toString();
		console.log(req.url)
		if(req.url=='/Start') {
			console.log("Accept");
			var urlParsed = url.parse(req.url, true);
			res.write(urlParsed.pathname);
			res.end();
			return;
		}
		res.write(htmlPage);
		res.end();
		/*res.writeHead(200,{Location:"/index"} );
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
});*/
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
	else if(req.event=='done') {
		trsStarted=false;
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
