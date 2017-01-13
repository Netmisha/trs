function RunTest() {
	trs.SetAppName('C:/Windows/SYSTEM32/mspaint.exe', function () {
		trs.SetWindowName('Untitled - Paint',function () {
			trs.StartApp(function () {
				trs.SetActive(function () {
					trs.CloseApp(function () {
						trs.WriteLog("Done!");
						trs.Success();
					});
				});
			});
		});
	});	
}