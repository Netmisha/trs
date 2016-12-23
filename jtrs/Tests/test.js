require('trs');
var manager = new Manager()
manager.Test(function Test(manager) {
	manager.StartApp();
	manager.SetWindowSize(1920, 1080);
	manager.SetMousePos(800,900);
	manager.MouseDown(0);
	manager.MouseMove(1000,300,2);
	manager.MouseMove(1200,900,2);
	manager.MouseMove(600,500,2);
	manager.MouseMove(1400,500,2);
	manager.MouseMove(800,900,2);
	manager.MouseUp(0);
	Sleep(1000);
	manager.PrintScreen("D:\\ScreenShot\\","1.bmp");
    manager.CloseApp();
    if(--manager.repeat>0) {
		Test(manager);
	}
	else {
		manager.ResultOk(process);
	}
});
