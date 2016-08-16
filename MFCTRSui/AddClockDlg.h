#pragma once

#include "Resource.h"
#include "SuiteRoot.h"
#include <vector>
#include "afxcmn.h"
#include "afxwin.h"
// AddClockDlg dialog

class AddClockDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AddClockDlg)

public:
	AddClockDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~AddClockDlg();

	BOOL OnInitDialog();
	BOOL SetList(std::vector<SuiteRoot>);
	// Dialog Data
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


private:
	char* clock_name;
	std::vector<SuiteRoot> list_items;
	CString tag;
	CString name;
	CString threads;


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
};
