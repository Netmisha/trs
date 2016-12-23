var http = require('http');
var url = require('url');
var trsStarted=false;
var server = new http.Server();
server.listen(8888,'127.0.0.1');
server.on('request', function(req, res){
	var urlParsed = url.parse(req.url, true);
		if(urlParsed.pathname == '/start') {
			if(!trsStarted) {
				trsStarted=true;
				res.end('TRS started');
				runTRS(res);
			}
			else {
				res.end('TRS has been working');
			}
		}
		else {
			res.end('Page not found');
		}
});
process.on('message', (m) => {
    	server.post();
    });
function runTRS(res) {
    var fork = require('child_process').fork;
    var child = fork(__dirname +'\\trs.js');
    child.on('message', (m) => {
    	trsStarted=false;
    });
}

