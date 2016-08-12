
// MFCTRSuiDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include <vector>
#include "Resource.h"
#include "RunDialog.h"
#include "ProjNameEdit.h"

#include "afxdialogex.h"
#include "TRSLibrary\TRSManager.h"

#define PROJECT_UPLOADED 1
#define PROJECT_NOTLOADED 2
#define RUN_CLICKED 4
#define RUN_UNCLICKED 8

#define SPACE_BETWEEN_CONTROLERS 5
#define CONTROL_AMOUNT 6
#define RUN_CONTROL_AMOUNT 3

#define DEFAULT_IMAGE 0
#define FAILED_IMAGE 1
#define PASSED_IMAGE 2

class SuiteRoot
{
public:
	SuiteRoot()
	{
		dRoot = nullptr;
	}
	SuiteRoot(TCHAR* path)
	{
		int size = wcslen(path);
		dRoot = new TCHAR[size + 1];
		wcscpy_s(dRoot, size + 1, path);
	}
	SuiteRoot(CString path)
	{
		int size = _tcslen(path);
		dRoot = new TCHAR[size + 1];
		_tcscpy_s(dRoot, size + 1, path);
	}
	SuiteRoot(const SuiteRoot& var)
	{
		int size = wcslen(var.dRoot);
		dRoot = new TCHAR[size + 1];
		wcscpy_s(dRoot, size + 1, var.dRoot);
	}
	inline TCHAR* get_path()
	{
		return dRoot;
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
	~CMFCTRSuiDlg();
// Dialog Data
	enum { IDD = IDD_MFCTRSUI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	std::vector<char*> TagColl;
	std::vector<char*> NameColl;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO *mx);
	afx_msg void OnSize(UINT nType, int cxx, int cyy);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_Tree;
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);


	afx_msg void OnEnChangeEdit2();
	CEdit report_edit;

	afx_msg void OnBnClickedButton2();
	CEdit console_output;

	afx_msg void OnBnClickedButton();
protected:
//	CListBox RootList;
//	std::vector<SuiteRoot> dRoots;
	std::vector<int> dRoots;
	std::vector<int> m_SelectedRoots;
	CImageList m_ImageList;
	CImageList m_PathImageList;
	void Info(TCHAR* path);
	std::vector<HTREEITEM*> TreeControlsList;
	CToolBar m_ToolBar;
	CToolBar m_secondToolBar;
	CMenu* m_Menu;
	ProjectProperties properties;
///	afx_msg void OnLbnSelchangeListroot();
	int resizible_raw = 2;
	int resizible_column = 2;

	CRect old_rect;
public:
	void UpdateToolbar(int = 0);


	afx_msg void OnEnChangeEdit3();
	CProgressCtrl m_Progress;
	afx_msg void OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult);

	CProgressCtrl subm_Progress;
	CEdit Time_running_edit;

	afx_msg void OnProgramRefresh();
	afx_msg void OnProgramAddfolder();
	afx_msg void OnProgramDeleteselecteditems();
	afx_msg void OnProgramRunsel();
	afx_msg void OnStopButtonClicked();
	afx_msg void OnPauseButtonClicked();
	afx_msg void OnBnClickedOk();
	afx_msg void OnLoadProject();
	afx_msg void OnSaveProject();
	afx_msg void OnProjectLastprojects();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnViewConsole();

	afx_msg BOOL OnTtnNeedText(UINT id, NMHDR *pNMHDR, LRESULT *pResult);
	
protected:
	void ConsoleHide();
	void ConsoleShow();
	void RunToolsHide();
	void RunToolsShow();

	afx_msg void OnSaveAs();
	CComboBox DropDown;
	CComboBox ThreadsComboBox;
	ReportManager* reportManag;

	std::list<Suite*>* suiteColl; // $$$ I founded the code where you check size and iterate this list, but I did not find where you initialize it. EDIT: now I found it
	bool is_running = false;
//	CImageList* m_ImageList;
public:
	CComboBox m_NameBox;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();
	void SetListItemImage(DWORD index, DWORD image);
	bool SetListItemState(bool state, SuiteRoot text);
	bool ExistInList(TCHAR* path);

	CListCtrl m_ListCtrl;

	afx_msg void OnCbnSelchangeCombo3();
	afx_msg void OnNewProject();

	CListCtrl RootList;

	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnInfoInfo();
	afx_msg void OnExit();
};

//extern CListBox* List;
extern CListCtrl* List;
extern bool checkRunParameters;