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

	m_ListCtrl.SetExtendedStyle(m_ListCtrl.GetExtendedStyle() | LVS_EX_CHECKBOXES | LVS_EX_TRANSPARENTSHADOWTEXT);

	for (int i = 0; i < coll.size(); ++i)
	{
		m_ListCtrl.InsertItem(m_ListCtrl.GetItemCount(), coll[i].get_path());
		m_ListCtrl.SetCheck(i, is_check[i]);
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

	m_PathImageList.Create(32, 32, ILC_COLORDDB, 2, 2);

	CBitmap m_Bitmap5;
	m_Bitmap5.LoadBitmap(IDB_BITMAP5);
	m_PathImageList.Add(&m_Bitmap5, RGB(0, 0, 0));

	m_ListCtrl.SetImageList(&m_PathImageList, LVSIL_SMALL);

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
	LPNMLISTVIEW  pNMLV = reinterpret_cast<LPNMLISTVIEW >(pNMHDR);

	UINT state = pNMLV->uOldState ^ pNMLV->uNewState;
	if (pNMLV->uChanged & LVIF_STATE) // item state has been changed
	{
		switch (pNMLV->uNewState & LVIS_STATEIMAGEMASK)
		{
		case INDEXTOSTATEIMAGEMASK(BST_CHECKED + 1): // new state: checked
		{
	//		selected_suites.push_back(SuiteRoot(m_ListCtrl.GetItemText(pNMLV->iItem, 0)));
			selected_suites.push_back(pNMLV->iItem);
			break;
		}
		case INDEXTOSTATEIMAGEMASK(BST_UNCHECKED + 1): // new state: unchecked
		{
			/*auto iter = std::find(selected_suites.begin(), selected_suites.end(), m_ListCtrl.GetItemText(pNMLV->iItem, 0));*/
			auto iter = std::find(selected_suites.begin(), selected_suites.end(), pNMLV->iItem);
		    if (iter != selected_suites.end())
				selected_suites.erase(iter);
			break;
		}
		default:
			break;
		}
	}
	*pResult = 0;
}



BOOL AddClockDlg::Init(std::vector<SuiteRoot> coll_, vector<bool> check, vector<CString> name_, int name_sel_, vector<CString> tag_, int tag_sel_, int thread_sel_)
{
	initialized = false;
	coll = coll_;
	is_check = check;
	if (!coll.size() || coll.size() != is_check.size())
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
