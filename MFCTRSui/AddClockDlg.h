#pragma once

#include "Resource.h"
#include "SuiteRoot.h"
#include <vector>
#include <list>
#include "afxcmn.h"
#include "afxwin.h"
#include "ClockCollection.h"
// AddClockDlg dialog
using std::vector;

class AddClockDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AddClockDlg)

public:
	AddClockDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~AddClockDlg();

	BOOL OnInitDialog();
	BOOL Init(std::vector<SuiteRoot>, vector<bool> is_check, vector<CString> name, int name_sel, vector<CString> tag, int tag_sel, int threads_sel);

	inline CString get_clock_name() const;
	inline CString get_name() const;
	inline CString get_tag() const;
	inline CString get_threads() const;
	inline int get_hour() const;
	inline int get_minute() const;
	inline std::list<Clock> get_clock_collection() const;
	
	// Dialog Data
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


private:
	CString clock_name;
	std::vector<SuiteRoot> list_items;
	CString tag;
	CString name;
	CString threads;
	ClockCollection schedule;

	int hour;
	int minute;
	bool weekly;

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedOk();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	
protected:
	CListCtrl m_ListCtrl;
	CEdit m_EditClockName;
	CComboBox m_EditTag;
	CComboBox m_EditName;
	CComboBox m_EditThreads;
	CComboBox m_EditHour;
	CComboBox m_EditMinute;
	CButton m_CheckRepeat;
	CButton m_ButtonMonday;
	CButton m_ButtonTuesday;
	CButton m_ButtonWednesday;
	CButton m_ButtonThursday;
	CButton m_ButtonFriday;
	CButton m_ButtonSaturday;
	CButton m_ButtonSunday;
	CButton* days[DAYS_IN_WEEK];

//	vector<SuiteRoot> selected_suites;
	vector<int> selected_suites;
	vector<SuiteRoot> coll;
	vector<CString> coll_name;
	vector<CString> coll_tag;
	vector<bool> is_check;

	CImageList m_PathImageList;
	bool first_called = true;

	int name_sel;
	int tag_sel;
	int thread_sel;
	bool initialized = false;
};


// =========================================================================

inline CString AddClockDlg::get_clock_name() const
{
	return clock_name;
}
inline CString AddClockDlg::get_name() const
{
	return name;
}
inline CString AddClockDlg::get_tag() const
{
	return tag;
}
inline CString AddClockDlg::get_threads() const
{
	return threads;
}
inline std::list<Clock> AddClockDlg::get_clock_collection() const
{
	return schedule.get_schedule();
}

extern AddClockDlg* curDialog;


inline int AddClockDlg::get_hour() const
{
	return hour;
}
inline int AddClockDlg::get_minute() const
{
	return minute;
}

