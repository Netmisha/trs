// AddClockDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AddClockDlg.h"
#include "afxdialogex.h"


// AddClockDlg dialog

IMPLEMENT_DYNAMIC(AddClockDlg, CDialogEx)

AddClockDlg::AddClockDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(AddClockDlg::IDD, pParent)
{

}

AddClockDlg::~AddClockDlg()
{
}

void AddClockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AddClockDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &AddClockDlg::OnBnClickedOk)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &AddClockDlg::OnLvnItemchangedList1)
END_MESSAGE_MAP()


// AddClockDlg message handlers


void AddClockDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void AddClockDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}
