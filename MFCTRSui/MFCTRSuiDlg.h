
// MFCTRSuiDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include <vector>
#include "Resource.h"
#include "RunDialog.h"
#include "ProjNameEdit.h"
#include "TestsTimerDialog.h"
#include "afxdialogex.h"
#include "SuiteRoot.h"
#include "TRSLibrary\TRSManager.h"
#include "TimerADD.h"
#include "TimerAddCollection.h"
#include "AddSuite.h"
#include "AddTest.h"
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
	INT_PTR CALLBACK DialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
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
	bool auto_del = false;
	std::map<CString, std::vector<TRSInfo>> PasMap;
	std::map<CString, std::vector<TRSInfo>> FailMap;
	CToolBar m_ToolBar;
	CToolBar m_secondToolBar;
	int lastSelected;
	CMenu* m_Menu;
	ProjectProperties properties;
	std::map<CString, std::vector<HTREEITEM*>> mapOfColls;
	std::map<HTREEITEM, CString> mapOfSuite;
///	afx_msg void OnLbnSelchangeListroot();
	int resizible_raw = 2;
	int resizible_column = 2;

	CRect old_rect;
public:
	void UpdateToolbar(int = 0);


	afx_msg void OnEnChangeEdit3();
	CProgressCtrl m_Progress;
	afx_msg void OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult);
	std::vector<HTREEITEM*> Info(TCHAR* path);
	CProgressCtrl subm_Progress;
	CEdit Time_running_edit;
	afx_msg void JustRunTimerTests(char* path, char* tag, char* name, int threads);
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
	//afx_msg void OnNotifyIcon();
	afx_msg BOOL OnTtnNeedText(UINT id, NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClock();
	afx_msg void OnAddClock();
protected:
	void ConsoleHide();
	void ConsoleShow();
	void RunToolsHide();
	void RunToolsShow();

	afx_msg void OnSaveAs();
	CComboBox DropDown;
	CComboBox ThreadsComboBox;
	ReportManager* reportManag;
	/*static  LRESULT WindowProc(
		UINT message,
		WPARAM wParam,
		LPARAM lParam
		);*/
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
	void setDisableTrue(TiXmlNode *Parent);
	CListCtrl m_ListCtrl;

	afx_msg void OnCbnSelchangeCombo3();
	afx_msg void OnNewProject();

	CListCtrl RootList;

	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnInfoInfo();
	afx_msg void OnExit();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg void OnMenu();
	afx_msg void OnInfoClose();
	afx_msg void OnInfoDisable();
	
	afx_msg void OnInfoDisableall();
	afx_msg void OnInfoEnable();
	afx_msg void OnInfoEnablefolder();
	bool FindPathToObject();
	void LeftMouseClick();
	CString sCurrentFileName;
	CString sCurrentPathToFile;
	CString sNewSuiteName;
	afx_msg void OnInfoEdit();
	afx_msg void OnInfoAddsuite();
	afx_msg void OnInfoAddcase();
	afx_msg void OnInfoDelete();

	//void(CMFCTRSuiDlg::*callback_refresh_func)();
	bool DeleteAllTestInTree(HTREEITEM);
};

//extern CListBox* List;
extern CListCtrl* List;
extern bool checkRunParameters;
//extern void(CMFCTRSuiDlg::*callback_refresh_func)();
