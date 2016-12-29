require('trs');
var manager = new global.Manager()
manager.Test(function Test(manager) {
	manager.manage.StartApp();
	Sleep(1000);
    manager.manage.CloseApp();
    if(--manager.repeat>0) {
		Test(manager);
	}
	else {
		manager.msg.ResultOk(process);
	}
});