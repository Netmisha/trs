#pragma once
#include <Windows.h>
#include <atlstr.h>
#include <iostream>
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
	bool saveBitmap(LPCSTR filename, HBITMAP bmp, HPALETTE pal)
	{
		bool result = false;
		PICTDESC pd;

		pd.cbSizeofstruct = sizeof(PICTDESC);
		pd.picType = PICTYPE_BITMAP;
		pd.bmp.hbitmap = bmp;
		pd.bmp.hpal = pal;

		LPPICTURE picture;
		HRESULT res = OleCreatePictureIndirect(&pd, IID_IPicture, false,
			reinterpret_cast<void**>(&picture));

		if (!SUCCEEDED(res))
			return false;

		LPSTREAM stream;
		res = CreateStreamOnHGlobal(0, true, &stream);

		if (!SUCCEEDED(res))
		{
			picture->Release();
			return false;
		}

		LONG bytes_streamed;
		res = picture->SaveAsFile(stream, true, &bytes_streamed);

		HANDLE file = CreateFile(filename, GENERIC_WRITE, FILE_SHARE_READ, 0,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

		if (!SUCCEEDED(res) || !file)
		{
			stream->Release();
			picture->Release();
			return false;
		}

		HGLOBAL mem = 0;
		GetHGlobalFromStream(stream, &mem);
		LPVOID data = GlobalLock(mem);

		DWORD bytes_written;

		result = !!WriteFile(file, data, bytes_streamed, &bytes_written, 0);
		result &= (bytes_written == static_cast<DWORD>(bytes_streamed));

		GlobalUnlock(mem);
		CloseHandle(file);

		stream->Release();
		picture->Release();

		return result;
	}
	BOOL PrintScreen(char * file) {
		int ScreenWidth = GetScreenWidth();
		int ScreenHeight = GetScreenHeight();
		HWND DesktopWnd = GetDesktopWindow();
		HDC DesktopDC = GetDC(DesktopWnd);
		HDC CaptureDC = CreateCompatibleDC(DesktopDC);
		HBITMAP CaptureBitmap = CreateCompatibleBitmap(DesktopDC,
			ScreenWidth, ScreenHeight);
		SelectObject(CaptureDC, CaptureBitmap);
		BitBlt(CaptureDC, 0, 0, ScreenWidth, ScreenHeight,
			DesktopDC, 0, 0, SRCCOPY | CAPTUREBLT);
		ReleaseDC(DesktopWnd, DesktopDC);
		DeleteDC(CaptureDC);
		HPALETTE hpal = NULL;
		if (saveBitmap(CString(file), CaptureBitmap, hpal)){
			DeleteObject(CaptureBitmap);
			return TRUE;
		}
		else {
			DeleteObject(CaptureBitmap);
			return TRUE;
		} 
	}
	BOOL PrintScreen(int x, int y, int w, int h, char * file){
		int ScreenWidth = GetScreenWidth();
		int ScreenHeight = GetScreenHeight();
		HWND DesktopWnd = GetDesktopWindow();
		HDC DesktopDC = GetDC(DesktopWnd);
		HDC CaptureDC = CreateCompatibleDC(DesktopDC);
		HBITMAP CaptureBitmap = CreateCompatibleBitmap(DesktopDC,
			w, h);
		SelectObject(CaptureDC, CaptureBitmap);
		BitBlt(CaptureDC, 0, 0, w, h,
			DesktopDC, x, y, SRCCOPY | CAPTUREBLT);
		ReleaseDC(DesktopWnd, DesktopDC);
		DeleteDC(CaptureDC);
		HPALETTE hpal = NULL;
		if (saveBitmap(CString(file), CaptureBitmap, hpal)){
			DeleteObject(CaptureBitmap);
			return TRUE;
		}
		else {
			DeleteObject(CaptureBitmap);
			return TRUE;
		}
	}
private:
	PROCESS_INFORMATION app_;
	BOOL started_ = FALSE;
	HWND WindowHandle = NULL;
	CString WindowName;
	CString sAppName;
	POINT current_pos;
};

