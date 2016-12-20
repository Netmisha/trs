#pragma once
#include <Windows.h>
#include <atlstr.h>

#define MOUSEEVENTF_HWHEEL 4096

class ApplicationManagement
{
public:
	ApplicationManagement() {}
	BOOL StartApp(){
		STARTUPINFO cif;
		ZeroMemory(&cif, sizeof(STARTUPINFO));
		if (started_) {
			return FALSE;
		}
		started_ = CreateProcess(sAppName, NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &cif, &app_);
		return started_;
	}
	BOOL CloseApp(){
		if (started_) {
			started_=!TerminateProcess(app_.hProcess, NO_ERROR);
			ZeroMemory(&app_, sizeof(PROCESS_INFORMATION));
		}
		return !started_;
	}
	BOOL WindowMinimize() {
		if (WindowHandle) {
			return ShowWindow(WindowHandle, SW_MINIMIZE);
		}
		return FALSE;
	}
	BOOL WindowMaximize() {
		if (WindowHandle) {
			return ShowWindow(WindowHandle, SW_MAXIMIZE);
		}
		return FALSE;
	}
	BOOL SetActive() {
		return SetForegroundWindow(WindowHandle);
	}
	int isActive() {
		CString title;
		TCHAR * buff = new TCHAR[1024];
		while (title != WindowName)
		{
			GetWindowText(GetForegroundWindow(), buff, GetWindowTextLength(GetForegroundWindow()) + 1);
			title = CString(buff);
			ZeroMemory(buff, sizeof(TCHAR)*1024);
			if (title.Find("activationwizard.exe") >= 0) {
				KeyPress(13);
			}
			Sleep(500);
			SetActive();
		}
		return 1;
	}
	BOOL WindowRestore() {
		if (WindowHandle) {
			return ShowWindow(WindowHandle, SW_RESTORE);
		}
		return FALSE;
	}
	int GetScreenWidth() {
		RECT desktop;
		const HWND hDesktop = GetDesktopWindow();
		GetWindowRect(hDesktop, &desktop);
		return desktop.right;
	}
	int GetScreenHeight() {
		RECT desktop;
		const HWND hDesktop = GetDesktopWindow();
		GetWindowRect(hDesktop, &desktop);
		return desktop.bottom;
	}
	BOOL KeyDown(int dkey){
		keybd_event(dkey, 0, 0, 0);
		return TRUE;
	}
	BOOL KeyUp(int dkey){
		keybd_event(dkey, 0, KEYEVENTF_KEYUP, 0);
		return TRUE;
	}
	BOOL KeyPress(int dkey){
		KeyDown(dkey);
		KeyUp(dkey);
		return TRUE;
	}
	~ApplicationManagement() {
		TerminateProcess(app_.hProcess, NO_ERROR);
	}
	BOOL SetMousePos(int x, int y) {
		current_pos.x = x;
		current_pos.y = y;
		return SetCursorPos(x, y);
	}
	BOOL MouseMove(int x, int y, int pause) {
		auto fun = [&](int _x){ return (_x - current_pos.x)*(y - current_pos.y) / (x - current_pos.x) + current_pos.y; };
		for (int i = current_pos.x; i < x; i++) {
			Sleep(pause);
			SetCursorPos(i, fun(i));
		}
		GetCursorPos(&current_pos);
		return TRUE;
	}
	void MouseDown(int button) {
		if (button) {
			mouse_event(MOUSEEVENTF_RIGHTDOWN, current_pos.x, current_pos.y, 0, 0);
		}
		else {
			mouse_event(MOUSEEVENTF_LEFTDOWN, current_pos.x, current_pos.y, 0, 0);
		}
	}
	void MouseUp(int button) {
		if (button) {
			mouse_event(MOUSEEVENTF_RIGHTUP, current_pos.x, current_pos.y, 0, 0);
		}
		else {
			mouse_event(MOUSEEVENTF_LEFTUP, current_pos.x, current_pos.y, 0, 0);
		}
	}
	void MouseClick(int button) {
		if (button) {
			mouse_event(MOUSEEVENTF_RIGHTDOWN, current_pos.x, current_pos.y, 0, 0);
			mouse_event(MOUSEEVENTF_RIGHTUP, current_pos.x, current_pos.y, 0, 0);
		}
		else {
			mouse_event(MOUSEEVENTF_LEFTDOWN, current_pos.x, current_pos.y, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, current_pos.x, current_pos.y, 0, 0);
		}
	}
	void MouseWheelDown() {
		mouse_event(MOUSEEVENTF_WHEEL, 0, 0, -WHEEL_DELTA, 0);
	}
	void MouseWheelUp() {
		mouse_event(MOUSEEVENTF_WHEEL, 0, 0, WHEEL_DELTA, 0);
	}
	void MouseWheelLeft() {
		mouse_event(MOUSEEVENTF_HWHEEL, 0, 0, -WHEEL_DELTA, 0);
	}
	void MouseWheelRight() {
		mouse_event(MOUSEEVENTF_HWHEEL, 0, 0, WHEEL_DELTA, 0);
	}
	int GetPID() {
		return app_.dwProcessId;
	}
	void SetWindowName(char * name) {
		WindowName = CString(name);
		WindowHandle = FindWindow(NULL, WindowName);
	}
	void SetAppName(char * name) {
		sAppName = CString(name);
	}
private:
	PROCESS_INFORMATION app_;
	BOOL started_ = FALSE;
	HWND WindowHandle = NULL;
	CString WindowName;
	CString sAppName;
	POINT current_pos;
};

