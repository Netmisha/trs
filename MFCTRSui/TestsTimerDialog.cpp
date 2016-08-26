// TestsTimerDialog.cpp : implementation file
//

#include "stdafx.h"
#include "TestsTimerDialog.h"
#include "afxdialogex.h"
#include "Clock.h"
#include "Functionality.h"

#include <list>
#include <algorithm>
#include <vector>
// TestsTimerDialog dialog
CListCtrl* List;
IMPLEMENT_DYNAMIC(TestsTimerDialog, CDialogEx)

HANDLE hTimerThread;
DWORD WINAPI TimeRunning(LPVOID arg);
CDialogEx* DIAL;

TestsTimerDialog::TestsTimerDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(TestsTimerDialog::IDD, pParent)
{

}

TestsTimerDialog::~TestsTimerDialog()
{
}

void TestsTimerDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
	DDX_Control(pDX, IDC_BUTTON1, m_ButtonAdd);
	DDX_Control(pDX, IDC_BUTTON2, m_ButtonEdit);
	DDX_Control(pDX, IDC_BUTTON3, m_ButtonRemove);
}

BOOL TestsTimerDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_ListCtrl.SetExtendedStyle(m_ListCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	CRect rect;
	m_ListCtrl.GetClientRect(&rect);
	int nColInterval = rect.Width() / 4;

	m_ListCtrl.InsertColumn(0, _T("Name"), LVCFMT_CENTER, nColInterval);
	m_ListCtrl.InsertColumn(1, _T("Time"), LVCFMT_CENTER, nColInterval);
	m_ListCtrl.InsertColumn(2, _T("Days"), LVCFMT_CENTER, nColInterval);
	m_ListCtrl.InsertColumn(3, _T("Repeat"), LVCFMT_CENTER, rect.Width() - 3 * nColInterval);

	m_ButtonEdit.EnableWindow(false);
	m_ButtonRemove.EnableWindow(false);

	for each (auto item in list_items)
		AddToList(item);

	if (call_add_dlg)
		OnAddClicked();
	return true;
}

BEGIN_MESSAGE_MAP(TestsTimerDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &TestsTimerDialog::OnAddClicked)
	ON_BN_CLICKED(IDC_BUTTON2, &TestsTimerDialog::OnEditClicked)
	ON_BN_CLICKED(IDC_BUTTON3, &TestsTimerDialog::OnRemoveClicked)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &TestsTimerDialog::OnListItemchanged)
END_MESSAGE_MAP()


// TestsTimerDialog message handlers


void TestsTimerDialog::OnAddClicked()
{
	if (clock_dlg.DoModal() == IDCANCEL)
		return;
	vector<SuiteRoot> selected_suites = clock_dlg.get_selected_suites();

	ClockInstance item{ clock_dlg.get_selected_suites(), clock_dlg.get_days(), clock_dlg.get_clock_name(), clock_dlg.get_tag(),
		clock_dlg.get_name(), clock_dlg.get_threads(), clock_dlg.get_hour(), clock_dlg.get_minute(), clock_dlg.is_weekly(), UniqueNumber() };

	list_items.push_back(item);
	timersCollection->Add(item);

	AddToList(item);
}

void TestsTimerDialog::AddToList(const ClockInstance& item)
{
	AddToList(item.clock_name, item.hour, item.minute, item.repeat, item.days);
}


void TestsTimerDialog::AddToList(CString clock_name, CString hour, CString minute, bool repeat, DWORD days)
{
	LVITEM lvi;
	CString strItem;
	
	lvi.mask = LVIF_TEXT;
	strItem.Format(_T("%s"), clock_name);
	lvi.iItem = m_ListCtrl.GetItemCount();
	lvi.iSubItem = 0;
	lvi.pszText = (LPTSTR)(LPCTSTR)(strItem);
	m_ListCtrl.InsertItem(&lvi);

	strItem.Format(_T("%s:%s"), hour, minute);
	lvi.iSubItem = 1;
	lvi.pszText = (LPTSTR)(LPCTSTR)(strItem);
	m_ListCtrl.SetItem(&lvi);

	strItem.Format(_T("%s"), GetDayByIndex(days));
	lvi.iSubItem = 2;
	lvi.pszText = (LPTSTR)(LPCTSTR)(strItem);
	m_ListCtrl.SetItem(&lvi);

	if (repeat)
	{
		strItem.Format(_T("%s"), "X");
		lvi.iSubItem = 3;
		lvi.pszText = (LPTSTR)(LPCTSTR)(strItem);
		m_ListCtrl.SetItem(&lvi);
	}
}

void TestsTimerDialog::ChangeListItem(CString clock_name, CString hour, CString minute, bool repeat, DWORD days, DWORD pos)
{
	LVITEM lvi;
	CString strItem;

	lvi.mask = LVIF_TEXT;
	strItem.Format(_T("%s"), clock_name);
	lvi.iItem = selection;
	lvi.iSubItem = 0;
	lvi.pszText = (LPTSTR)(LPCTSTR)(strItem);
	m_ListCtrl.SetItem(&lvi);

	strItem.Format(_T("%s:%s"), hour, minute);
	lvi.iSubItem = 1;
	lvi.pszText = (LPTSTR)(LPCTSTR)(strItem);
	m_ListCtrl.SetItem(&lvi);

	strItem.Format(_T("%s"), GetDayByIndex(days));
	lvi.iSubItem = 2;
	lvi.pszText = (LPTSTR)(LPCTSTR)(strItem);
	m_ListCtrl.SetItem(&lvi);

	if (repeat)
		strItem.Format(_T("%s"), "X");
	else
		strItem.Format(_T("%s"), "");
	lvi.iSubItem = 3;
	lvi.pszText = (LPTSTR)(LPCTSTR)(strItem);
	m_ListCtrl.SetItem(&lvi);
}


void TestsTimerDialog::OnEditClicked()
{
	if (selection >= list_items.size() || selection < 0)
	{
		logger << "selection is not within list_items range in TestsTimerDialog::OnEditClicked()";
		return;
	}
	AddClockDlg edit_clock_dlg;
	edit_clock_dlg.Init(list_items[selection].suites, vector<bool>(list_items[selection].suites.size(), true), list_items[selection].name, list_items[selection].tag,
		list_items[selection].threads, list_items[selection].hour, list_items[selection].minute, list_items[selection].clock_name, list_items[selection].repeat, list_items[selection].days);
	//int res = CloseHandle(hTimerThread);
	ResumeThread(hTimerThread);
	SuspendThread(hTimerThread);
	if (edit_clock_dlg.DoModal() == IDOK)
	{
		
		//timersCollection->Init();
		timersCollection->Remove(list_items[selection]);

		ClockInstance item{ edit_clock_dlg.get_clock_collection().front().get_suites(), edit_clock_dlg.get_days(), edit_clock_dlg.get_clock_name(), edit_clock_dlg.get_tag(),
			edit_clock_dlg.get_name(), edit_clock_dlg.get_threads(), edit_clock_dlg.get_hour(), edit_clock_dlg.get_minute(), edit_clock_dlg.is_weekly(), UniqueNumber() };

		list_items[selection] = item;
		ChangeListItem(item.clock_name, item.hour, item.minute, item.repeat, item.days, selection);
		timersCollection->Add(item);
		
	//	hTimerThread = CreateThread(NULL, 0, TimeRunning, DIAL, 0, 0);
	}
	ResumeThread(hTimerThread);
}


void TestsTimerDialog::OnRemoveClicked()
{
	if (selection >= list_items.size() || selection < 0)
	{
		logger << "selection is not within list_items range in TestsTimerDialog::OnRemoveClicked()";
		return;
	}
	timersCollection->Remove(list_items[selection]);
	list_items.erase(list_items.begin() + selection);

	// after DeleteItem system calls TestsTimerDialog::UpdateControls and assigns selection to -1
	m_ListCtrl.DeleteItem(selection);
}


void TestsTimerDialog::OnListItemchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	POSITION pos = m_ListCtrl.GetFirstSelectedItemPosition();
	UpdateControls(pos);
	
	*pResult = 0;
}

void TestsTimerDialog::UpdateControls(POSITION pos)
{
	if (pos == NULL)
	{
		selection = -1;
		m_ButtonEdit.EnableWindow(false);
		m_ButtonRemove.EnableWindow(false);
	}
	else
	{
		selection = (int)pos - 1;
		m_ButtonEdit.EnableWindow();
		m_ButtonRemove.EnableWindow();
	}
}

CString TestsTimerDialog::GetDayByIndex(int day)
{
	CString ret_str = L"";
	CString day_to_str;

	if (day & 1)
	{
		day_to_str.Format(_T("%s "), _T("Mon "));
		ret_str += day_to_str;
	}
	if (day & 2)
	{
		day_to_str.Format(_T("%s "), _T("Tue "));
		ret_str += day_to_str;
	}
	if (day & 4)
	{
		day_to_str.Format(_T("%s "), _T("Wed "));
		ret_str += day_to_str;
	}
	if (day & 8)
	{
		day_to_str.Format(_T("%s "), _T("Thu "));
		ret_str += day_to_str;
	}
	if (day & 16)
	{
		day_to_str.Format(_T("%s "), _T("Fri "));
		ret_str += day_to_str;
	}
	if (day & 32)
	{
		day_to_str.Format(_T("%s "), _T("Sat "));
		ret_str += day_to_str;
	}
	if (day & 64)
	{
		day_to_str.Format(_T("%s "), _T("Sun "));
		ret_str += day_to_str;
	}

	return ret_str;
}