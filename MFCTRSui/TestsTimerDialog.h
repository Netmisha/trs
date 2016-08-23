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

	inline BOOL Init(std::vector<SuiteRoot> roots, vector<bool> is_check, DWORD name_sel, DWORD tag_sel, DWORD threads_sel);
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

	afx_msg void OnAddClicked();
	afx_msg void OnEditClicked();
	afx_msg void OnRemoveClicked();
	afx_msg void OnListItemchanged(NMHDR *pNMHDR, LRESULT *pResult);
	int selection = -1;

	void UpdateControls(POSITION);
	CString GetDayByIndex(int);
	void AddToList(CString clock_name, CString hour, CString minute, bool repeat, DWORD days);
	void AddToList(const ClockInstance&);

	vector<ClockInstance> list_items;
};

// =====================================================================================================================

inline BOOL TestsTimerDialog::Init(std::vector<SuiteRoot> roots, vector<bool> is_check, DWORD name_sel, DWORD tag_sel, DWORD threads_sel)
{
	
	return clock_dlg.Init(roots, is_check, name_sel, tag_sel, threads_sel);
}