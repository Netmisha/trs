function RunTest() {
	trs.SetAppName('C:/Windows/SYSTEM32/mspaint.exe', function () {
		trs.SetWindowName('Untitled - Paint',function () {
			trs.StartApp(function () {
				trs.WindowMaximize(function () {
					trs.SetMousePos(300,300, function () {
						trs.MouseDown(0, function () {
							trs.MouseMove(600,600,5, function () {
								trs.MouseUp(0, function () {
									trs.CloseApp(function () {
										trs.WriteLog("Done!");
									});
								});
							});
						});
					});
				});
			});
		});
	});	
	return;
}