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

BOOL AddClockDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	if (::IsWindow(m_ButtonMonday.m_hWnd))
		m_ButtonMonday.SetButtonStyle(m_ButtonMonday.GetButtonStyle() | BS_DEFPUSHBUTTON);

	return TRUE;
}



void AddClockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
	DDX_Control(pDX, IDC_EDIT1, m_EditClockName);
	DDX_Control(pDX, IDC_COMBO1, m_EditTag);
	DDX_Control(pDX, IDC_COMBO2, m_EditName);
	DDX_Control(pDX, IDC_COMBO3, m_EditThreads);
	DDX_Control(pDX, IDC_COMBO5, m_EditHour);
	DDX_Control(pDX, IDC_COMBO6, m_EditMinute);
	DDX_Control(pDX, IDC_CHECK2, m_CheckRepeat);
	DDX_Control(pDX, IDC_CHECK3, m_ButtonMonday);
	DDX_Control(pDX, IDC_CHECK1, m_ButtonTuesday);
	DDX_Control(pDX, IDC_CHECK4, m_ButtonWednesday);
	DDX_Control(pDX, IDC_CHECK5, m_ButtonThursday);
	DDX_Control(pDX, IDC_CHECK6, m_ButtonFriday);
	DDX_Control(pDX, IDC_CHECK7, m_ButtonSaturday);
	DDX_Control(pDX, IDC_CHECK8, m_ButtonSunday);
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



BOOL AddClockDlg::SetList(std::vector<SuiteRoot> coll)
{
	//for each (auto val in coll)
	//{
	//	m_ListCtrl.InsertItem(val.get_path(),)
	//}
	return TRUE;
}
