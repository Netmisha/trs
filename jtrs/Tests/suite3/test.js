var manager = require('trs');
var manager = new manager.Manager();
manager.Test(function Test(manager) {
	manager.manage.StartApp();
	manager.manage.isActive();
    setTimeout(function(){manager.manage.CloseApp();},manager.pause);
    if(--manager.repeat>0) {
		setTimeout(Test, manager.pause, manager);
	}
	else {
		manager.msg.ResultOk(process);
	}
});
