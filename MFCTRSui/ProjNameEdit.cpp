// ProjNameEdit.cpp : implementation file
//

#include "stdafx.h"
#include "ProjNameEdit.h"
//#include "MFCTRSuiDlg.h"
#include "afxdialogex.h"

ProjectProperties pro_;
// ProjNameEdit dialog

IMPLEMENT_DYNAMIC(ProjNameEdit, CDialogEx)

ProjNameEdit::ProjNameEdit(CWnd* pParent /*=NULL*/)
	: CDialogEx(ProjNameEdit::IDD, pParent)
{

}

ProjNameEdit::~ProjNameEdit()
{
}

void ProjNameEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, name_edit);
	DDX_Control(pDX, BUTTON_BROWSE, m_ButtonBrowse);
	DDX_Control(pDX, IDC_EDIT2, m_EditLocation);
}


BEGIN_MESSAGE_MAP(ProjNameEdit, CDialogEx)
	ON_BN_CLICKED(IDOK, &ProjNameEdit::OnBnClickedOk)
	ON_BN_CLICKED(BUTTON_BROWSE, &ProjNameEdit::OnBnClickedBrowse)
END_MESSAGE_MAP()


// ProjNameEdit message handlers


void ProjNameEdit::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CString mess;
	name_edit.GetWindowTextW(mess);

	if (m_Location.IsEmpty())
		m_EditLocation.GetWindowText(m_Location);

	DWORD dwAttrib = GetFileAttributesW(m_Location.GetString());
	if (dwAttrib == INVALID_FILE_ATTRIBUTES || !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY))
	{
		MessageBox(_T("The location of a project is invalid"), _T("Error"), MB_ICONERROR | MB_OK);
		return;
	}

	char path[MAX_PATH];
	int size = WideCharToMultiByte(CP_ACP, 0, m_Location.GetString(), -1, path, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, m_Location.GetString(), -1, path, size, NULL, NULL);


	pro_.setPath(path);


	if (mess.GetLength() > 0)
	{
		char* name = fromCStringToChar(mess);
		pro_.setName(name);
		//ToolBar->GetToolBarCtrl().HideButton(TOOLBAR_ADDGREY);
		//ToolBar->GetToolBarCtrl().HideButton(TOOLBAR_ADD, false);
		CDialogEx::OnOK();
	}
	else
	{
		MessageBox(_T("Name of project is invalid"), _T("Error"), MB_ICONERROR | MB_OK);
	}
}


void ProjNameEdit::OnBnClickedBrowse()
{
	BROWSEINFO bi = { 0 };
	bi.lpszTitle = _T("Select Location");
	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
	if (pidl != 0)
	{
		// get the name of the folder
		TCHAR path[MAX_PATH];
		SHGetPathFromIDList(pidl, path);

		m_Location.SetString(path);

		int start = 0;
		int end = m_EditLocation.GetWindowTextLength();
		m_EditLocation.SetSel(start, end);
		m_EditLocation.ReplaceSel(m_Location.GetString());

		// free memory used
		IMalloc * imalloc = 0;
		if (SUCCEEDED(SHGetMalloc(&imalloc)))
		{
			imalloc->Free(pidl);
			imalloc->Release();
		}
	}
}
