require('trs');
var manager = new Manager()
manager.Test(function Test(manager) {
	manager.manage.StartApp();
	Sleep(3);
    manager.manage.CloseApp();
    if(--manager.repeat>0) {
		Test(manager);
	}
	else {
		manager.msg.ResultOk(process);
	}
});