require('trs');
var manager = new Manager()
manager.Test(function Test(manager) {
	manager.manage.StartApp();
	var kofX=manager.manage.GetScreenWidth()/1920;
	var kofY=manager.manage.GetScreenHeight()/1080;
	manager.MouseClickAt(0,720*kofX,140*kofY);
	manager.manage.SetMousePos(800*kofX,900*kofY);
	manager.manage.MouseDown(0);
	manager.manage.MouseMove(1000*kofX,300*kofY,2);
	manager.manage.MouseMove(1200*kofX,900*kofY,2);
	manager.manage.MouseMove(600*kofX,500*kofY,2);
	manager.manage.MouseMove(1400*kofX,500*kofY,2);
	manager.manage.MouseMove(800*kofX,900*kofY,2);
	manager.manage.MouseUp(0);
	manager.MouseClickAt(0,720*kofX,90*kofY);
	manager.Shortcut(17,65);
	//green
	manager.MouseClickAt(0,930*kofX,115*kofY);
	manager.MouseClickAt(0,1040*kofX,390*kofY);
	manager.MouseClickAt(0,930*kofX,115*kofY);
	Sleep(2);
	//blue
	manager.MouseClickAt(0,930*kofX,115*kofY);
	manager.MouseClickAt(0,1110*kofX,310*kofY);
	manager.MouseClickAt(0,930*kofX,115*kofY);
	Sleep(2);
	//red
	manager.MouseClickAt(0,930*kofX,115*kofY);
	manager.MouseClickAt(0,930*kofX,350*kofY);
	manager.MouseClickAt(0,930*kofX,115*kofY);
	Sleep(2);
	//manager.MouseClickAt(0,400*kofX,500*kofY);
	manager.MouseClickAt(0,400*kofX,200*kofY);
	manager.PrintText("HURRAY");
	manager.MouseClickAt(0,300*kofX,200*kofY);
	Sleep(4);
    manager.manage.CloseApp();
    if(--manager.repeat>0) {
		Test(manager);
	}
	else {
		manager.msg.ResultOk(process);
	}
});
