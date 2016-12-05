// ShowDescription.cpp : implementation file
//

#include "stdafx.h"
#include "ShowDescription.h"
#include "afxdialogex.h"


// ShowDescription dialog

IMPLEMENT_DYNAMIC(ShowDescription, CDialogEx)

ShowDescription::ShowDescription(CWnd* pParent /*=NULL*/)
	: CDialogEx(ShowDescription::IDD, pParent)
{

}

ShowDescription::~ShowDescription()
{
}

void ShowDescription::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, DesDataBox);
}
BOOL ShowDescription::OnInitDialog(){
	CDialogEx::OnInitDialog();
	DesDataBox.SetWindowTextW(Description);
	return TRUE;
}

BEGIN_MESSAGE_MAP(ShowDescription, CDialogEx)
END_MESSAGE_MAP()


// ShowDescription message handlers
