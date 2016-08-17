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
	if (!initialized)
		return FALSE;

	for each (auto val in coll)
	{
		m_ListCtrl.InsertItem(m_ListCtrl.GetItemCount(), val.get_path());
	}

	for each (auto val in coll_name)
	{
		m_EditName.AddString(val.GetString());
	}
	m_EditName.SetCurSel(name_sel);

	for each (auto val in coll_tag)
	{
		m_EditTag.AddString(val.GetString());
	}
	m_EditTag.SetCurSel(tag_sel);

	CString mes;
	CString helpMes;
	for (int i = 0; i < 9; ++i)
	{
		mes.Format(L"%S", "0");
		helpMes.Format(L"%d", i + 1);
		mes += helpMes;
		m_EditThreads.AddString(mes);
	}

	for (int i = 9; i < 100; ++i)
	{
		mes.Format(L"%d", int(i + 1));
		m_EditThreads.AddString(mes);
	}
	m_EditThreads.SetCurSel(thread_sel);

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

	CDialogEx::OnOK();
}


void AddClockDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}



BOOL AddClockDlg::Init(std::vector<SuiteRoot> coll_, vector<CString> name_, int name_sel_, vector<CString> tag_, int tag_sel_, int thread_sel_)
{
	initialized = false;
	coll = coll_;
	if (!coll.size())
		return FALSE;

	coll_name = name_;
	coll_tag = tag_;
	if ((name_sel = name_sel_) >= coll_name.size() ||
		(tag_sel = tag_sel_) >= coll_tag.size() ||
		(thread_sel = thread_sel_) > 100)
	return FALSE;

	initialized = true;
	return TRUE;
}
