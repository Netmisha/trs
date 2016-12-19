Enumeration of function
BOOL StartApp(char * name) name - string which consist of path and name of application
									example:"C:\\Windows\\SYSTEM32\\mspaint.exe"
BOOL CloseApp()
BOOL WindowMinimize() 
BOOL WindowMaximize()
BOOL SetActive()
BOOL WindowRestore()
int GetScreenWidth()
int GetScreenHeight()
BOOL KeyDown(int dkey) dkey - key code on keyboard
BOOL KeyUp(int dkey)
BOOL KeyPress(int dkey)
BOOL SetMousePos(int x, int y)  x, y - coordinates of cursor
BOOL MouseMove(int x, int y, int pause) pause - number of milliseconds 
void MouseDown(int button)	button - mouse button, left button - 0, right button - 1
void MouseUp(int button)
void MouseClick(int button)
void MouseWheelDown()
void MouseWheelUp()
void MouseWheelLeft()
void MouseWheelRight()
int GetPID()
void SetWindowName(char * name)	name - name of window, example:"Untitled - Paint"
