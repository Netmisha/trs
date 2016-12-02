// AddSuite.cpp : implementation file
//

#include "stdafx.h"
#include "AddSuite.h"
#include "afxdialogex.h"
#include <Windows.h>


// AddSuite dialog

IMPLEMENT_DYNAMIC(AddSuite, CDialogEx)

AddSuite::AddSuite(CWnd* pParent /*=NULL*/)
	: CDialogEx(AddSuite::IDD, pParent)
	, sSuiteName(_T(""))
{

}

AddSuite::~AddSuite()
{
}

void AddSuite::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SUITENAME, sSuiteName);
}


BEGIN_MESSAGE_MAP(AddSuite, CDialogEx)
	ON_BN_CLICKED(IDOK, &AddSuite::OnBnClickedOk)
END_MESSAGE_MAP()


// AddSuite message handlers

void AddSuite::setPath(CString & sPath) {
	sPath_ = sPath;
}
CString AddSuite::getPathToFile() {
	return sPath_ + sSuiteName + "\\" + sSuiteName + ".xml";
}
void AddSuite::OnBnClickedOk()
{
	UpdateData();
	CreateDirectory(sPath_ + sSuiteName, NULL);
	HANDLE hFile;
	hFile = CreateFile(sPath_ + sSuiteName+"\\"+sSuiteName+".xml", FILE_APPEND_DATA, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	CloseHandle(hFile);
	CDialogEx::OnOK();
}
