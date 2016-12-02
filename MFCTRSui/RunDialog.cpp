// RunDialog.cpp : implementation file
//

#include "stdafx.h"
#include "RunDialog.h"
#include "afxdialogex.h"


char* tag = nullptr;
char* name = nullptr;
char* threads = nullptr;
char* testName = nullptr;
bool checkRunParameters;
// RunDialog dialog

IMPLEMENT_DYNAMIC(RunDialog, CDialogEx)

RunDialog::RunDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(RunDialog::IDD, pParent)
{
	
}

RunDialog::~RunDialog()
{
}

void RunDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, Tag_edit);
	DDX_Control(pDX, IDC_EDIT2, Name_edit);
	DDX_Control(pDX, IDC_EDIT3, Threads_edit);
}


BEGIN_MESSAGE_MAP(RunDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &RunDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &RunDialog::OnBnClickedCancel)
END_MESSAGE_MAP()


// RunDialog message handlers


void RunDialog::OnBnClickedOk()
{
	ifCancelPressed = true;
	CString messName,messTag,messThreads;
	Name_edit.GetWindowTextW(messName);
	Tag_edit.GetWindowTextW(messTag);
	Threads_edit.GetWindowTextW(messThreads);
	if (messName.GetLength() == 0 && messTag.GetLength() == 0 && messThreads.GetLength()!=0)
	{
		char* Thr = fromCStringToChar(messThreads);
		if (atoi(Thr))
		{
			char buf[] = "Name and Tag are empty, so TRS will run all tests in current path with ";
			char addbuf[] = " threads.";
			int sizeBuf = strlen(buf);
			int sizeAdd = strlen(addbuf);
			char* message = new char[sizeBuf + sizeAdd + messThreads.GetLength() + 1];
			strncpy_s(message, sizeBuf + 1, buf, sizeBuf);
			strncpy_s(message + sizeBuf, messThreads.GetLength() + 1, Thr, messThreads.GetLength());
			strncpy_s(message + sizeBuf + messThreads.GetLength(), sizeAdd + 1, addbuf, sizeAdd);
			TCHAR* buffer = new TCHAR[strlen(message) + 1];
			convertToTCHAR(buffer, message);
			int res = MessageBox(buffer, _T("Note:"), MB_ICONINFORMATION | MB_YESNO);
			if (res == IDYES)
			{
				delete[] buffer;
				threads = Thr;
				CDialogEx::OnOK();
			}
			
		}
		else
		{
			delete[] Thr;
			int res = MessageBox(_T("Please, put decimal variable into threads!"), _T("Note:"), MB_ICONERROR|MB_OK);
		}
	}
	if ( messThreads.GetLength() == 0)
	{
		int res = MessageBox(_T("Threads is empty, so TRS won't run tests! Please, set at least 1 thread."), _T("Error"), MB_YESNO);
		if (res == IDYES)
		{
			CDialogEx::OnOK();
		}
	}
	if (messName.GetLength() != 0 && messTag.GetLength() == 0 && messThreads.GetLength()!=0 )
	{
		char* Thr = fromCStringToChar(messThreads);
		if (atoi(Thr))
		{
			char buf[] = "Tag is empty, so TRS will run all tests in current path whith name ";
			char addBuf[] = " with ";
			char endbuff[] = " threads.";
			int sizeAdd = strlen(addBuf + 1);
			int sizeEnd = strlen(endbuff + 1);
			int size = strlen(buf);
			char* message = new char[size + sizeAdd + sizeEnd + messName.GetLength() + 1];
			strncpy_s(message, size + 1, buf, size);
			char* pString = fromCStringToChar(messName);
			strncpy_s(message + size, messName.GetLength() + 1, pString, messName.GetLength());
			strncpy_s(message + size + messName.GetLength(), sizeAdd + 1, addBuf, sizeAdd);
			strncpy_s(message + size + messName.GetLength() + sizeAdd,strlen(Thr) + 1, Thr, strlen(Thr));
			strncpy_s(message + size + messName.GetLength() + sizeAdd + strlen(Thr)+1, sizeEnd + 1, endbuff, sizeEnd);
			TCHAR* buffer = new TCHAR[strlen(message) + 1];
			convertToTCHAR(buffer, message);
			int res = MessageBox(buffer, _T("Note:"), MB_ICONINFORMATION | MB_YESNO);
			if (res == IDYES)
			{
				delete[] buffer;
				delete[] pString;
				threads = Thr;
				name = fromCStringToChar(messName);
				CDialogEx::OnOK();
			}
			else
			{
				delete[] pString;
				delete[] buffer;
				delete[] message;
			}
		}
		else
		{
			delete[] Thr;
			int res = MessageBox(_T("Please, put decimal variable into threads!"), _T("Note:"), MB_ICONERROR | MB_OK);
		}
	}
	if (messName.GetLength() == 0 && messTag.GetLength() != 0 && messThreads.GetLength() != 0)
	{
		char* Thr = fromCStringToChar(messThreads);
		if (atoi(Thr))
		{
			char buf[] = "Name is empty, so TRS will run all tests in current path whith tag ";
			int size = strlen(buf);
			char addBuf[] = " with ";
			char endbuff[] = " threads.";
			int sizeAdd = strlen(addBuf + 1);
			int sizeEnd = strlen(endbuff + 1);
			char* message = new char[sizeAdd + sizeEnd + size + messTag.GetLength() + 1];
			strncpy_s(message, size + 1, buf, size);
			char* pString = fromCStringToChar(messTag);
			strncpy_s(message + size, messTag.GetLength() + 1, pString, messTag.GetLength());
			strncpy_s(message + size + messTag.GetLength(), sizeAdd + 1, addBuf, sizeAdd);
			strncpy_s(message + size + messTag.GetLength() + sizeAdd, strlen(Thr) + 1, Thr, strlen(Thr));
			strncpy_s(message + size + messTag.GetLength() + sizeAdd + strlen(Thr), sizeEnd + 1, endbuff, sizeEnd);
			TCHAR* buffer = new TCHAR[strlen(message) + 1];
			convertToTCHAR(buffer, message);
			int res = MessageBox(buffer, _T("Note:"), MB_ICONINFORMATION|MB_YESNO);
			if (res == IDYES)
			{
				delete[] buffer;
				delete[] pString;
				threads = Thr;
				tag = fromCStringToChar(messTag);
				CDialogEx::OnOK();
				
			}
			else
			{
				delete[] pString;
				delete[] buffer;
				delete[] message;
			}
		}
		else
		{
			delete[] Thr;
			int res = MessageBox(_T("Please, put decimal variable into threads!"), _T("Note:"), MB_ICONERROR | MB_OK);
		}
	}
	if (messName.GetLength() != 0 && messTag.GetLength() != 0 && messThreads.GetLength() != 0)
	{
		char* Thr = fromCStringToChar(messThreads);
		if (atoi(Thr))
		{
			char buf[] = "TRS will run all tests in current path whith name ";
			char addbufTag[] = " and tag ";
			char addBuf[] = " with ";
			char endbuff[] = " threads.";
			int sizeAdd = strlen(addBuf + 1);
			int sizeEnd = strlen(endbuff + 1);
			int sizeBuf = strlen(buf);
			int sizeAddTag = strlen(addbufTag);
			char* message = new char[sizeAdd + sizeEnd + sizeBuf + sizeAddTag + messTag.GetLength() + messName.GetLength() + 1];
			strncpy_s(message, sizeBuf + 1, buf, sizeBuf);
			char* pString = fromCStringToChar(messName);
			strncpy_s(message + sizeBuf, messName.GetLength() + 1, pString, messName.GetLength());
			strncpy_s(message + sizeBuf + messName.GetLength(), sizeAddTag + 1, addbufTag, sizeAddTag);
			pString = fromCStringToChar(messTag);
			strncpy_s(message + sizeBuf + sizeAddTag + messName.GetLength(), messTag.GetLength() + 1, pString, messTag.GetLength());
			strncpy_s(message + sizeBuf + messTag.GetLength(), sizeAdd + 1, addBuf, sizeAdd);
			strncpy_s(message + sizeBuf + messTag.GetLength() + sizeAdd, strlen(Thr) + 1, Thr, strlen(Thr));
			strncpy_s(message + sizeBuf + messTag.GetLength() + sizeAdd + strlen(Thr), sizeEnd + 1, endbuff, sizeEnd);
			TCHAR* buffer = new TCHAR[strlen(message) + 1];
			convertToTCHAR(buffer, message);
			int res = MessageBox(buffer, _T("Note:"), MB_ICONINFORMATION | MB_YESNO);
			if (res == IDYES)
			{
				delete[] buffer;
				delete[] pString;
				threads = Thr;
				name = fromCStringToChar(messName);
				tag = fromCStringToChar(messTag);
				CDialogEx::OnOK();
			}
			else
			{
				delete[] pString;
				delete[] buffer;
				delete[] message;
			}
		}
		else
		{
			delete[] Thr;
			int res = MessageBox(_T("Please, put decimal variable into threads!"), _T("Note:"), MB_ICONERROR | MB_OK);
		}
	}
}


BOOL RunDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	Threads_edit.SetWindowTextW(_T("1"));
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void RunDialog::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	ifCancelPressed = false;
	CDialogEx::OnCancel();
}
