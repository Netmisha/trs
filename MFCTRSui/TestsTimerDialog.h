#pragma once
#include "Resource.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "AddClockDlg.h"

#include <vector>
// TestsTimerDialog dialog
using std::vector;
class TestsTimerDialog : public CDialogEx
{
	DECLARE_DYNAMIC(TestsTimerDialog)

public:
	TestsTimerDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~TestsTimerDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG4 };

	inline BOOL Init(std::vector<SuiteRoot> roots, vector<bool> is_check, vector<CString> name, int name_sel, vector<CString> tag, int tag_sel, int threads_sel);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
private:
	CListCtrl m_ListCtrl;
	CButton m_ButtonAdd;
	CButton m_ButtonEdit;
	CButton m_ButtonRemove;

	vector<int> selected_suites;
	AddClockDlg clock_dlg;

	afx_msg void OnAddClicked();
	afx_msg void OnEditClicked();
	afx_msg void OnRemoveClicked();
	afx_msg void OnListItemchanged(NMHDR *pNMHDR, LRESULT *pResult);
	int selection = -1;

	void UpdateControls(POSITION);
	CString GetDayByIndex(int);
};

// =====================================================================================================================

inline BOOL TestsTimerDialog::Init(std::vector<SuiteRoot> roots, vector<bool> is_check, vector<CString> name, int name_sel, vector<CString> tag, int tag_sel, int threads_sel)
{
	return clock_dlg.Init(roots, is_check, name, name_sel, tag, tag_sel, threads_sel);
}