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
	DDX_Control(pDX, IDSAVEEdit, SaveButton);
}
BOOL ShowDescription::OnInitDialog(){
	CDialogEx::OnInitDialog();
	DesDataBox.SetWindowTextW(Description);
	return TRUE;
}

BEGIN_MESSAGE_MAP(ShowDescription, CDialogEx)
	ON_BN_CLICKED(IDSAVEEdit, &ShowDescription::OnBnClickedSaveedit)
END_MESSAGE_MAP()


// ShowDescription message handlers


void ShowDescription::OnBnClickedSaveedit()
{
	CString tempdata;
		DesDataBox.GetWindowTextW(tempdata);
		if (tempdata.Compare(Description)){
			Description.Empty();
			r = true;
			Description.Append(tempdata);
			MessageBox(L"Description has beed saved", L"INFO", MB_OK);
		}
		else{
			MessageBox(L"Same info.Nothing to save", L"INFO", MB_OK);
		}
	// TODO: Add your control notification handler code here
}
CString ShowDescription::getDescriptionData(){
	return Description;
}
