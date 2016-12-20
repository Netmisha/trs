function Messages(suite, test){
	this.suite=suite;
	this.test=test;
}
Messages.prototype.ShowTest = function() {
	return "Suite #"+this.suite+":"+"Test #"+this.test+" : ";
};
Messages.prototype.ResultOk = function(process) {
	process.send({ msg: this.ShowTest()+"Result OK" });
};
Messages.prototype.Fail = function(process, msg) {
	process.send({ msg: this.ShowTest()+"Fail: "+msg });
};
Messages.prototype.Error = function(process, msg) {
	process.send({ msg: this.ShowTest()+"Error: "+msg });
};

exports.Messages = Messages;