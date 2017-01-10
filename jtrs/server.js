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
    var path=req.url.split('?')[1];
    if(path==undefined) {
        ws.send(GetStructure(__dirname));
    }
    else {
        if(path.indexOf('verbose')!=-1) {
            if(path.indexOf('path')!=-1) {
                ws.send(GetAllInfo(path.split('&')[0].split('=')[1]));
            }
            else {
                ws.send(GetAllInfo(__dirname));
            }
        }
        else {
            if(path.indexOf('path')!=-1) {
                ws.send(GetStructure(path.split('&')[0].split('=')[1]));
            }
            else {
                ws.send(GetStructure(__dirname));
            }
        }
    }
  });
});
app.use('/get', function (req, res, next) {
  res.websocket(function (ws) {
    var path=req.url.split('=')[1];
    if(path.split('.')[1]=='xml') {
        ws.send(GetSuiteInfo(path.substr(0, path.indexOf('xml')+3)));
    }
    else if(path.split('.')[1].split('/')[1]=='test' && path.split('.')[1].split('/').length == 3) {
        ws.send(GetTestInfo(path.substr(0, path.indexOf('xml')+3),path.split('.')[1].split('/')[2]));
    }
    else {
        ws.send(GetProperty(path.substr(0, path.indexOf('xml')+3), path.substr(path.indexOf('xml')+4, path.length)));
    }
  });
});
server.on('upgrade', handleUpgrade(app, wss));
 
server.listen(5000);