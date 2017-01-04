var express = require("express");
var fs = require('fs');
var trs=require('./trs.js');
var url = require('url');
var index = fs.readFileSync('web/index.html');
var app = express();
app.use(express.static(__dirname + '/web'));
app.get('/', function(req, res) {
    res.end(index);
});
app.get('/info', function(req, res) {
    res.write(GetTestsInfo());
	res.end();
});
/*app.get('/tests', function(req, res) {
    res.write(GetTestsList());
	res.end();
});*/
app.get('/suites', function(req, res) {
    res.write(GetSuitesInfo());
	res.end();
});
app.get('/file', function(req, res) {
	var urlParsed = url.parse(req.url, true);
   	res.write(fs.readFileSync(urlParsed.path.split("?")[1].split("=")[1]).toString());
	res.end();
});
var port = Number(process.env.PORT || 5000);
app.listen(port, function() {
    console.log("Listening on " + port);
});





/*var http = require('http');
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



global.server=server;
*/