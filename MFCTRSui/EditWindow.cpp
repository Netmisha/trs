// EditWindow.cpp : implementation file
//

#include "stdafx.h"
#include "EditWindow.h"
#include "afxdialogex.h"


// EditWindow dialog

IMPLEMENT_DYNAMIC(EditWindow, CDialogEx)

EditWindow::EditWindow(CWnd* pParent /*=NULL*/)
	: CDialogEx(EditWindow::IDD, pParent)
{

}

EditWindow::~EditWindow()
{
}

void EditWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_AUTHOR, Author_name);
	DDX_Control(pDX, ID_SAVEB, Save_button);
}


BEGIN_MESSAGE_MAP(EditWindow, CDialogEx)
	ON_BN_CLICKED(IDOK, &EditWindow::OnBnClickedOk)
//	ON_EN_CHANGE(IDC_EDIT20, &EditWindow::OnEnChangeEdit20)
//	ON_EN_CHANGE(IDC_EDIT26, &EditWindow::OnEnChangeEdit26)
ON_EN_CHANGE(IDC_AUTHOR, &EditWindow::OnEnChangeAuthor)
END_MESSAGE_MAP()


// EditWindow message handlers


void EditWindow::OnBnClickedOk() // saveButton
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString strd = L"HELLO";
	//Author_name.GetWindowText(strd);
	Author_name.SetWindowTextW(strd);
	UpdateData(FALSE);
	//CDialogEx::OnOK();
}




void EditWindow::OnEnChangeAuthor()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
