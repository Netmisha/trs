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