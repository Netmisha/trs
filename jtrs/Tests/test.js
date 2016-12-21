var TRSManager = require(process.argv[2]+"/modules/TRSManager");
var manager = new TRSManager.Manager(__dirname);
manager.StartTest(function Test(manager) {
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
