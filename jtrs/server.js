/*var express = require("express");
var fs = require('fs');
var url = require('url');
var app = express();
app.use(express.static(__dirname + '/web'));
app.get('/info', function(req, res) {
    console.log('tree');
    res.write(GetTestsInfo());
	res.end();
});
app.get('/tests', function(req, res) {
    res.write(GetTestsList());
	res.end();
});
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
});*/

var trs=require('./trs.js');
var fs = require('fs');
var url = require('url');
var express = require('express');
var http = require('http');
var ws = require('ws');
 
var handleUpgrade = require('express-websocket');
 
var app = express();
var server = http.createServer(app);
var wss = new ws.Server({ noServer: true });
 
app.use('/list', function (req, res, next) {
  res.websocket(function (ws) {
    ws.send(GetStructure());
  });
});
app.use('/get', function (req, res, next) {
  res.websocket(function (ws) {
    var path=req.url.split('=')[1];
    if(path.substr(path.lastIndexOf('/')+1, path.length).split('.')[1]=='xml') {
        ws.send(GetSuiteInfo(path.substr(0, path.indexOf('xml')+3)));
    }
    else {
        ws.send(GetTestInfo(path.substr(0, path.indexOf('xml')+3),path.substr(path.indexOf('xml')+4, path.length)));
    }
  });
});
server.on('upgrade', handleUpgrade(app, wss));
 
server.listen(5000);