var trs=require('testinfo');
var fs = require('fs');
var url = require('url');
var url = require('trs');
var express = require('express');
var http = require('http');
var ws = require('ws');
var handleUpgrade = require('express-websocket');
 
var manager = new Manager();
var log = new Logs(__dirname+'/logs');
var app = express();
var server = http.createServer(app);
var wss = new ws.Server({ noServer: true });
var rep = new Report(__dirname+'/report');

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


app.use('/set', function (req, res, next) {
  res.websocket(function (ws) {
    var path=req.url.split('&');
    ws.send(SetInfo(path[0].split('=')[1].substr(0, path[0].split('=')[1].indexOf('xml')+3), path[0].split('=')[1].substr(path[0].split('=')[1].indexOf('xml')+4, path[0].split('=')[1].length), path[1].split('=')[1]));
  });
});


app.use('/report', function (req, res, next) {
  res.websocket(function (ws) {
  
    if(decodeURIComponent(req.url.split('?')[1].split('=')[1])=='create') {
       var report_path = rep.Create_rep();
       
       fs.openSync(report_path.toString(),'a');
    }
    
  });
});



app.use('/success', function (req, res, next) {
  res.websocket(function (ws) {
    ws.send();
  });
});
app.use('/fail', function (req, res, next) {
  res.websocket(function (ws) {
    ws.send();
  });
});

app.use('/log', function (req, res, next) {
  res.websocket(function (ws) {

    if(decodeURIComponent(req.url.split('?')[1].split('=')[1])=='create') {
        log.Create();
    }
    else if(decodeURIComponent(req.url.split('?')[1].split('=')[1])=='save') {
        log.SaveToFile();
    }
    else if(decodeURIComponent(req.url.split('?')[1].split('=')[1])=='list') {
        ws.send(log.GetList());
    }
    else if(decodeURIComponent(req.url.split('?')[1].split('&')[0].split('=')[1])=='get') {
        ws.send(log.GetLog(decodeURIComponent(req.url.split('&')[1].split('=')[1])));
    }
    else {
        log.AddLog(decodeURIComponent(req.url.split('?')[1].split('=')[1]));        
    }
  });
});
app.use('/event', function (req, res, next) {
  res.websocket(function (ws) {
    var path=req.url.split('?')[1].split('&');
    var msg="Request: "+decodeURIComponent(path[0].split('=')[1]);
    if(path.length>1) {
        msg+=", parametrs: ";
        for(var i=1; i<path.length; i++) {
            msg+=decodeURIComponent(path[i])+"; ";
        }
    }
    log.AddLog(msg);
    var resp="Done!";
    if(path[0].split('=')[1]=='StartApp') {
        manager.StartApp();
    }
    else if(path[0].split('=')[1]=='CloseApp') {
        manager.CloseApp();
    }
    else if(path[0].split('=')[1]=='SetAppName') {
        manager.SetAppName(decodeURIComponent(path[1].split('=')[1]));
    }
    else if(path[0].split('=')[1]=='SetWindowName') {
        manager.SetWindowName(decodeURIComponent(path[1].split('=')[1]));
    }
    else if(path[0].split('=')[1]=='WindowMinimize') {
        manager.WindowMinimize();
    }
    else if(path[0].split('=')[1]=='WindowMaximize') {
        manager.WindowMaximize()
    }
    else if(path[0].split('=')[1]=='SetActive') {
        manager.SetActive();
    }
    else if(path[0].split('=')[1]=='WindowRestore') {
        manager.WindowRestore();
    }
    else if(path[0].split('=')[1]=='KeyDown') {
        manager.KeyDown(Number(path[1].split('=')[1]));
    }
    else if(path[0].split('=')[1]=='KeyUp') {
        manager.KeyUp(Number(path[1].split('=')[1]));
    }
    else if(path[0].split('=')[1]=='KeyPress') {
        manager.KeyPress(Number(path[1].split('=')[1]));
    }
    else if(path[0].split('=')[1]=='SetMousePos') {
        manager.SetMousePos(Number(path[1].split('=')[1]),Number(path[2].split('=')[1]));
    }
    else if(path[0].split('=')[1]=='MouseMove') {
        manager.MouseMove(Number(path[1].split('=')[1]),Number(path[2].split('=')[1]),Number(path[3].split('=')[1]));
    }
    else if(path[0].split('=')[1]=='MouseDown') {
        manager.MouseDown(Number(path[1].split('=')[1]));
    }
    else if(path[0].split('=')[1]=='PrintScreenA') {
        manager.PrintScreenA(Number(path[1].split('=')[1]),Number(path[2].split('=')[1]),Number(path[3].split('=')[1]),Number(path[4].split('=')[1]),decodeURIComponent(path[5].split('=')[1]));
    }
    else if(path[0].split('=')[1]=='PrintScreen') {
        manager.PrintScreen(decodeURIComponent(path[1].split('=')[1]));
    }
    else if(path[0].split('=')[1]=='MouseUp') {
        manager.MouseUp(Number(path[1].split('=')[1]));
    }
    else if(path[0].split('=')[1]=='MouseClick') {
        manager.MouseClick(Number(path[1].split('=')[1]));
    }
    else if(path[0].split('=')[1]=='MouseWheelDow') {
        manager.MouseWheelDow();
    }
    else if(path[0].split('=')[1]=='MouseWheelUp') {
        manager.MouseWheelUp();
    }
    else if(path[0].split('=')[1]=='MouseWheelLeft') {
        manager.MouseWheelLeft();
    }
    else if(path[0].split('=')[1]=='MouseWheelRight') {
        manager.MouseWheelRight();
    }
    else if(path[0].split('=')[1]=='GetScreenWidth') {
        resp=String(manager.GetScreenWidth());
    }
    else if(path[0].split('=')[1]=='GetScreenHeight') {
        resp=String(manager.GetScreenHeight());
    }
    else if(path[0].split('=')[1]=='Sleep') {
        manager.Sleep(Number(path[1].split('=')[1]));
    }
    ws.send(resp);
  });
});
server.on('upgrade', handleUpgrade(app, wss));
 
server.listen(5000);