var http = require('http');
var url = require('url');
var trs=require('./trs.js');
var fork = require('child_process').fork;
var trsStarted=false;
var server = new http.Server();
server.listen(8888,'127.0.0.1');
server.on('request', function(req, res){
	var urlParsed = url.parse(req.url, true);
		if(urlParsed.pathname == '/start') {
			if(!trsStarted) {
				trsStarted=true;
				res.end('TRS started');
				Start();
			}
			else {
				res.end('TRS has been working');
			}
		}
		else if(urlParsed.pathname == '/list') {
			var list=GetTestsInfo();
			res.end(list);
		}
		else if(urlParsed.pathname == '/pause') {
			fPauseTRS();
			res.end('TRS paused');
			trsStarted=false;
		}
		else if(urlParsed.pathname == '/stop') {
			fStopTRS();
			res.end('TRS stopped');
			trsStarted=false;
		}
		else {
			res.end('Page not found');
		}
});
process.on('message', (m) => {
    	server.post();
    });

