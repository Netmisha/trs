var manageapp = require("./ApplicationManagementWin")
var manage = new manageapp.ApplicationManagement()
function close() {
	manage.CloseApp();
}
function clean() {
	manage.SetActive()
	manage.WindowMaximize()
	manage.SetMousePos(200, 300);
	manage.MouseDown(1);
	manage.MouseMove(1300, 1000,2);
	manage.MouseUp(1);
	setTimeout(close,2000);
}
function paint() {
	manage.SetWindowName("Untitled - Paint")
	manage.SetActive()
	manage.WindowMaximize()
	manage.SetMousePos(200, 300);
	manage.MouseDown(0);
	manage.MouseMove(1300, 1000,2);
	manage.MouseUp(0);
	setTimeout(clean,2000); 	
}
function setactive() {
	manage.SetWindowName("Untitled - Paint")
	manage.SetActive()
	manage.WindowMaximize()
	setTimeout(paint,1000); 	
}
function start() {
	manage.StartApp("C:\\Windows\\SYSTEM32\\mspaint.exe")
	setTimeout(setactive,1000); 
}
start();
/*
Run any js-file
var exec = require('child_process').exec;
child= exec("node 1.js",(error, stdout, stderr) => {
  if (error) {
    throw error;
  }
  console.log(stdout);
});
*/