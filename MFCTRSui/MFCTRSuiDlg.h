
// MFCTRSuiDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include <list>

class SuiteRoot
{
public:
	SuiteRoot(TCHAR* path)
	{
		int size = wcslen(path);
		dRoot = new TCHAR[size + 1];
		wcscpy_s(dRoot, size + 1, path);
	}
	~SuiteRoot()
	{
		delete[] dRoot;
	}
private:
	TCHAR* dRoot;
};


// CMFCTRSuiDlg dialog
class CMFCTRSuiDlg : public CDialogEx
{
// Construction
public:
	CMFCTRSuiDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MFCTRSUI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	std::list<SuiteRoot> roots;
public:
	CTreeCtrl m_Tree;
	afx_msg void OnEnChangeEdit1();
	CEdit C_edit;
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton1();
	char AddFolder;
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedButton2();
	CListCtrl ListVariable;
};
