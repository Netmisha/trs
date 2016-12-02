#pragma once
#include "Resource.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "TimerADD.h"
#include "AddClockDlg.h"
#include "ClockInstance.h"
#include "TRSLibrary\TRSManager.h"
#include "TimerAddCollection.h"

#include <vector>
using std::vector;

class TestsTimerDialog : public CDialogEx
{
	DECLARE_DYNAMIC(TestsTimerDialog)

public:
	TestsTimerDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~TestsTimerDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG4 };

	inline BOOL Init(std::vector<SuiteRoot> roots, vector<bool> is_check, CString name_sel, CString tag_sel, CString threads_sel, bool call_add_dlg = false);
	afx_msg void OnAddClicked();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
private:
	CListCtrl m_ListCtrl;
	CButton m_ButtonAdd;
	CButton m_ButtonEdit;
	CButton m_ButtonRemove;

	AddClockDlg clock_dlg;

	afx_msg void OnEditClicked();
	afx_msg void OnRemoveClicked();
	afx_msg void OnListItemchanged(NMHDR *pNMHDR, LRESULT *pResult);
	int selection = -1;

	void UpdateControls(POSITION);
	CString GetDayByIndex(int);
	void AddToList(CString clock_name, CString hour, CString minute, bool repeat, DWORD days);
	void AddToList(const ClockInstance&);
	void ChangeListItem(CString clock_name, CString hour, CString minute, bool repeat, DWORD days, DWORD pos);


	vector<ClockInstance> list_items;
	bool call_add_dlg = false;
};

// =====================================================================================================================

inline BOOL TestsTimerDialog::Init(std::vector<SuiteRoot> roots, vector<bool> is_check, CString name_sel, CString tag_sel, CString threads_sel, bool call_dlg)
{
	list_items = timersCollection->getTimers();
	call_add_dlg = call_dlg;
	return clock_dlg.Init(roots, is_check, name_sel, tag_sel, threads_sel, CString("00"), CString("00"));
}