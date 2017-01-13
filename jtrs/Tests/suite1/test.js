function RunTest() {
	trs.SetAppName('C:/Windows/SYSTEM32/mspaint.exe', function () {
		trs.SetWindowName('Untitled - Paint',function () {
			trs.StartApp(function () {
				var iter=100;
				trs.SetActive(function tro() {
					var x= Math.round((Math.random() * 1000) + 10);
					var y= Math.round((Math.random() * 700) + 10);
					trs.SetMousePos(x,y, function () {
						trs.MouseClick(0, function () {
							console.log(100-iter);
							if(--iter>0){
								tro();
							}
							else {
								trs.Sleep(10000, function () {
									trs.CloseApp(function () {
										trs.WriteLog("Done!");
										trs.Success();
									});
								});
							}
						});
					});
				});
			});
		});
	});	
}