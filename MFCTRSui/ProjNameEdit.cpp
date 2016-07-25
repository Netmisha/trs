// ProjNameEdit.cpp : implementation file
//

#include "stdafx.h"
#include "ProjNameEdit.h"
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
}


BEGIN_MESSAGE_MAP(ProjNameEdit, CDialogEx)
	ON_BN_CLICKED(IDOK, &ProjNameEdit::OnBnClickedOk)
END_MESSAGE_MAP()


// ProjNameEdit message handlers


void ProjNameEdit::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CString mess;
	name_edit.GetWindowTextW(mess);
	if (mess.GetLength() > 0)
	{
		char* name = fromCStringToChar(mess);
		pro_.setName(name);
		ToolBar->GetToolBarCtrl().HideButton(TOOLBAR_ADDGREY);
		ToolBar->GetToolBarCtrl().HideButton(TOOLBAR_ADD, false);
		CDialogEx::OnOK();
	}
	else
	{
		MessageBox(_T("Name of project is invalid"), _T("Error"), MB_ICONERROR | MB_OK);
	}
}
