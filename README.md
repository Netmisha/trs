# TRS Manager
It is an automatic test running application. It lets you to run a set of your test's applications.
You can easy configure it with .xml project file. OS Windows.
# Reporting
All information about your test(s) after running is saved in .txt and .html formatt and you can check if some tests failed and why.
If you run your test(s) immediately, you can see that information on screen in console mode.
# How to use
1. Create directory “TestSuite”.
2. Copy trs.exe and TRSLibrary.dll into “TestSuite”.
3. Create Suite.xml file there as in the example.xml
			
Add test execution file in  “TestSuite” directory and set execution tag with name of your execution file into Suite.xml file
Set return value of your test into Suite.xml file in result tag.
Open command line in  “TestSuite” directory  
Execute “trs.exe run -p .”
# Console commands
1. Run - run tests.
2. List - write list of tests in current folder.
3. Validate - write information about current folder (if everithing is Ok with .xml and .exe files).
4. Pause - pause tests running.
5. Stop - stop tests running.

# Console additional parameters
1. -p D:\TestStructure - set path to your test's folder
2. -n Test1 - set name of test(s) which you want to run
3. -t Release - set tag of test(s) which you want to run
4. -j 17 - set amount of threads for test(s) running
5. -log D:\TestStructure - set path for .txt reporter
6. -hlog D:\TestStructure - set path for .html reporter

# Additional information
There is more comfortable way to use it if you don't like to work with console! Just run TRSui.exe file and you will be able to manipulate
functionality in the other way. You will see application window where you will be able to add you folder(s), to set all parameters, to
watch information about each test just by clicking on right mouse button on it in tree view. If you will run test(s) by clicking Run button,
you will see the result of each test's running in the same window. If you don't want to run test(s) immediately, you can even set time for application
to do this automatically (once or more).