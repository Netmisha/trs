function RunTest() {
	trs.SetAppName('C:/Windows/SYSTEM32/mspaint.exe');
	trs.SetWindowName('Untitled - Paint');
	trs.StartApp();
	trs.SetActive();
	trs.WindowMaximize();
	trs.SetMousePos(300,300);
	trs.MouseDown(0);
	trs.MouseMove(600,600,5);
	trs.MouseUp(0);
	trs.CloseApp();
	trs.Log("Done!");
	
	return;
}