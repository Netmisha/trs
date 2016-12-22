require('trs');
var manager = new Manager()
manager.Test(function Test(manager) {
	manager.StartApp();
	var kofX=manager.GetScreenWidth()/1920;
	var kofY=manager.GetScreenHeight()/1080;
	manager.SetMousePos(800*kofX,900*kofY);
	manager.MouseDown(0);
	manager.MouseMove(1000*kofX,300*kofY,2);
	manager.MouseMove(1200*kofX,900*kofY,2);
	manager.MouseMove(600*kofX,500*kofY,2);
	manager.MouseMove(1400*kofX,500*kofY,2);
	manager.MouseMove(800*kofX,900*kofY,2);
	manager.MouseUp(0);
	Sleep(4);
    manager.CloseApp();
    if(--manager.repeat>0) {
		Test(manager);
	}
	else {
		manager.msg.ResultOk(process);
	}
});
