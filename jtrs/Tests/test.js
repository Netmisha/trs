var trs = require('trs');
var manager = new trs.Manager(__dirname);
manager.StartTest(function Test(manager) {
	manager.manage.StartApp();
	manager.manage.isActive();
	var kofX=manager.manage.GetScreenWidth()/1920;
	var kofY=manager.manage.GetScreenHeight()/1080;
	manager.manage.SetMousePos(720*kofX,140*kofY);
	setTimeout(function(){manager.manage.MouseClick(0);},100);
	setTimeout(function(){manager.manage.SetMousePos(800*kofX,900*kofY);},110);
	setTimeout(function(){manager.manage.MouseDown(0);},120);
	setTimeout(function(){manager.manage.MouseMove(1000*kofX,300*kofY,2);},1000);
	setTimeout(function(){manager.manage.SetMousePos(1000*kofX,300*kofY);},1100);
	setTimeout(function(){manager.manage.MouseMove(1200*kofX,900*kofY,2);},3000);
	setTimeout(function(){manager.manage.SetMousePos(1200*kofX,900*kofY);},3100);
	setTimeout(function(){manager.manage.MouseMove(600*kofX,500*kofY,2);},5000);
	setTimeout(function(){manager.manage.SetMousePos(600*kofX,500*kofY);},5100);
	setTimeout(function(){manager.manage.MouseMove(1400*kofX,500*kofY,2);},7000);
	setTimeout(function(){manager.manage.SetMousePos(1400*kofX,500*kofY);},7100);
	setTimeout(function(){manager.manage.MouseMove(800*kofX,900*kofY,2);},9000);
	setTimeout(function(){manager.manage.SetMousePos(800*kofX,900*kofY);},9100);
	setTimeout(function(){manager.manage.MouseUp(0);},9200);
	setTimeout(function(){manager.manage.SetMousePos(720*kofX,90*kofY);},9210);
	setTimeout(function(){manager.manage.MouseClick(0);},9220);
	setTimeout(function(){manager.manage.KeyDown(17);},9230);
	setTimeout(function(){manager.manage.KeyPress(65);},9240);
	setTimeout(function(){manager.manage.KeyUp(17);},9250);
	setTimeout(function(){manager.manage.SetMousePos(930*kofX,115*kofY);},9350);
	setTimeout(function(){manager.manage.MouseClick(0);},9360);
	setTimeout(function(){manager.manage.SetMousePos(930*kofX,350*kofY);},9450);
	setTimeout(function(){manager.manage.MouseClick(0);},9460);
	setTimeout(function(){manager.manage.SetMousePos(400*kofX,500*kofY);},9470);
	setTimeout(function(){manager.manage.MouseClick(0);},9480);
    setTimeout(function(){manager.manage.CloseApp();},13000);
    if(--manager.repeat>0) {
		setTimeout(Test, 13100, manager);
	}
	else {
		manager.msg.ResultOk(process);
	}
});
