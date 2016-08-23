
// MFCTRSuiDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCTRSui.h"
#include "MFCTRSuiDlg.h"
#include "afxdialogex.h"
#include <list>
#define MYWM_NOTIFYICON (WM_APP+100)
#include "ConsoleReporter.h"
#include "TRSLibrary\TRSManager.h"
#include "ToRunParameters.h"
#include "TestInfo.h"
#include "RunParameters.h"
#include "Functionality.h"
#include <ctime>
#include <algorithm>
#include <shellapi.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define RAW_RESIZIBLE 2
// CMFCTRSuiDlg dialog

// $$$ you are using this variable only inside two CMFCTRSuiDlg methods.
// It will be better to hide it inside the CMFCTRSuiDlg class
AddClockDlg* curDialog;
static bool ifFirstTimeRunned = true; 
bool ifCancelPressed;
bool RunEndCheck;
bool SaveAsPressed = true;
int ListSelection;
CToolBar* ToolBar;
TimerAddCollection timersCollection;
//CListCtrl* List;
CToolBar* Bar;
CComboBox* Tag;
NOTIFYICONDATA nid;
CComboBox* Threads;
CTreeCtrl* TREECTRL;
CComboBox* Name;
std::vector<TRSInfo> PassedC;
std::vector<TRSInfo> FailedC;
std::vector<HTREEITEM*>* TREE;
std::map<CString,std::vector<HTREEITEM*>>* COLL;
std::map<CString, std::vector<TRSInfo>>* FAIL;
std::map<CString, std::vector<TRSInfo>>* PASS;
CMFCTRSuiDlg* MainDialog;
CMFCTRSuiDlg::CMFCTRSuiDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCTRSuiDlg::IDD, pParent)
	
{
	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	Manager.Init("D:\\");
	
}

CMFCTRSuiDlg::~CMFCTRSuiDlg()
{
	Manager.Destroy();
}


void CMFCTRSuiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_Tree);
	DDX_Control(pDX, IDC_EDIT3, console_output);
//	DDX_Control(pDX, IDC_ListRoot, RootList);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
	DDX_Control(pDX, IDC_PROGRESS3, subm_Progress);
	DDX_Control(pDX, IDC_EDIT1, Time_running_edit);
	DDX_Control(pDX, IDC_COMBO1, DropDown);
	DDX_Control(pDX, IDC_COMBO2, ThreadsComboBox);
	DDX_Control(pDX, IDC_COMBO3, m_NameBox);
	DDX_Control(pDX, IDC_LIST1, RootList);
}

BEGIN_MESSAGE_MAP(CMFCTRSuiDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO(MINMAXINFO *)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CMFCTRSuiDlg::OnTvnSelchangedTree1)
//	ON_LBN_SELCHANGE(IDC_ListRoot, &CMFCTRSuiDlg::OnLbnSelchangeListroot)
	ON_EN_CHANGE(IDC_EDIT3, &CMFCTRSuiDlg::OnEnChangeEdit3)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS1, &CMFCTRSuiDlg::OnNMCustomdrawProgress1)
	ON_COMMAND(ID_PROGRAM_ADDFOLDER, &CMFCTRSuiDlg::OnProgramAddfolder)
	ON_COMMAND(TOOLBAR_STOP, &CMFCTRSuiDlg::OnStopButtonClicked)
	ON_COMMAND(ID_PROGRAM_DELETESELECTEDITEMS, &CMFCTRSuiDlg::OnProgramDeleteselecteditems)
	ON_COMMAND(ID_PROGRAM_RUNSEL, &CMFCTRSuiDlg::OnProgramRunsel)
	ON_COMMAND(TOOLBAR_REFRESH, &CMFCTRSuiDlg::OnProgramRefresh)
	//ON_REGISTERED_MESSAGE(MYWM_NOTIFYICON, &CMFCTRSuiDlg::OnNotifyIcon)
	ON_WM_SYSCOMMAND(SC_CLOSE, &CMFCTRSuiDlg::OnSysCommand(UINT , LPARAM))
	ON_COMMAND(ID_Load_Project, &CMFCTRSuiDlg::OnLoadProject)
	ON_COMMAND(ID_PROJECT_LASTPROJECTS, &CMFCTRSuiDlg::OnProjectLastprojects)
	ON_COMMAND(ID_VIEW_CONSOLE, &CMFCTRSuiDlg::OnViewConsole)
	ON_COMMAND(TOOLBAR_SAVEAS, &CMFCTRSuiDlg::OnSaveAs)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMFCTRSuiDlg::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CMFCTRSuiDlg::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CMFCTRSuiDlg::OnCbnSelchangeCombo3)
	ON_COMMAND(ID_New_Project, &CMFCTRSuiDlg::OnNewProject)
	ON_NOTIFY_EX(TTN_NEEDTEXTA, 0, &CMFCTRSuiDlg::OnTtnNeedText)
	ON_COMMAND(TOOLBAR_SAVE, &CMFCTRSuiDlg::OnSaveProject)
	ON_COMMAND(TOOLBAR_CLOCK_GREY, &CMFCTRSuiDlg::OnTest)
	ON_COMMAND(TOOLBAR_CLOCK, &CMFCTRSuiDlg::OnTest)
	ON_NOTIFY_EX(TTN_NEEDTEXTW, 0, &CMFCTRSuiDlg::OnTtnNeedText)
	
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CMFCTRSuiDlg::OnLvnItemchangedList1)
	ON_NOTIFY(NM_RCLICK, IDC_TREE1, &CMFCTRSuiDlg::OnNMRClickTree1)
	ON_COMMAND(ID_INFO_INFO, &CMFCTRSuiDlg::OnInfoInfo)
	ON_COMMAND(ID_EXIT, &CMFCTRSuiDlg::OnExit)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEHOVER()
	ON_COMMAND(ID_Menu, &CMFCTRSuiDlg::OnMenu)
	ON_COMMAND(ID_INFO_CLOSE, &CMFCTRSuiDlg::OnInfoClose)
END_MESSAGE_MAP()


// CMFCTRSuiDlg message handlers

BOOL CMFCTRSuiDlg::OnInitDialog()
{

	CDialogEx::OnInitDialog();
	TREECTRL = &m_Tree;
	CRect rectFrame, rectDlg;
	CWnd* pMainWnd = AfxGetMainWnd();
	if (pMainWnd != NULL)
	{
		pMainWnd->GetClientRect(rectFrame);
		pMainWnd->ClientToScreen(rectFrame);
		GetWindowRect(rectDlg);

		int nXPos = rectFrame.left + (rectFrame.Width() / 2)
			- (rectDlg.Width() / 2);
		int nYPos = rectFrame.top + (rectFrame.Height() / 2)
			- (rectDlg.Height() / 2);

		//When setting window's position, we make 
		//it the TOP Window. Making it the TOPMOST may
		//not be such a good idea and may annoy some people!!
		//The most important thing to keep in mind here 
		//is to specify SWP_NOCOPYBITS as the 
		//the window sizing and positioning flag, 
		//otherwise all valid contents of the client area
		//of the previous window position are copied 
		//into the client area after the window is 
		//sized or repositioned.

		::SetWindowPos(m_hWnd, HWND_TOP, nXPos, nYPos,
			rectDlg.Width(), rectDlg.Height(), SWP_NOCOPYBITS);

	}
	
	CFont *myFont = new CFont();
	myFont->CreateFont(15, 0, 0, 0, FW_NORMAL, FALSE, false,
		0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		FIXED_PITCH | FF_MODERN, _T("Courier New"));
	m_Tree.SetFont(myFont);
	RootList.SetFont(myFont);
	DropDown.ModifyStyle(0, CBS_DROPDOWN);
	console_output.ShowWindow(false);
	LONG lStyle = GetWindowLong(m_hWnd, GWL_STYLE);
	lStyle &= ~WS_CHILD;        //remove the CHILD style
	lStyle &= ~WS_DISABLED;        //remove the DISABLED style

	lStyle |= WS_POPUP;            //Add the POPUP style
	//lStyle |= WS_VISIBLE;        //Add the VISIBLE style
	lStyle |= WS_SYSMENU;
	lStyle |= WS_BORDER;
	lStyle |= WS_MINIMIZEBOX;
	lStyle |= WS_MAXIMIZEBOX;
	
	SetWindowLong(m_hWnd, GWL_STYLE, lStyle);
	DropDown.AddString(L"All");
	//DropDown.SetCurSel(0);
	m_NameBox.AddString(L"All");
	//m_NameBox.SetCurSel(0);
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	
	//SetIcon(m_hIcon, TRUE);			// Set big icon
	//SetIcon(m_hIcon, FALSE);		// Set small icon
	// TODO: Add extra initialization here
	//RootList.ResetContent();
	MainDialog = this;
	// menu hiding
	m_Menu = GetMenu();
	if (!m_Menu)
	{
		TRACE0("Failed to upload Menu\n");
		EndDialog(IDCANCEL);
	}

	// toolbar binding

	if (!m_ToolBar.Create(this) || !m_ToolBar.LoadToolBar(MYAMAZINGTOOLBAR))
	{
		TRACE0("Failed to Create Dialog Toolbar\n");
		EndDialog(IDCANCEL);
	}
	
	
	//CRect	rcClientOld; // Old Client Rect
	//CRect	rcClientNew; // New Client Rect with Tollbar Added
	//GetClientRect(rcClientOld); // Retrive the Old Client WindowSize
	//// Called to reposition and resize control bars in the client 
	//// area of a window. The reposQuery FLAG does not really traw the 
	//// Toolbar.  It only does the calculations. And puts the new 
	//// ClientRect values in rcClientNew so we can do the rest of the 
	//// Math.
	//RepositionBars(AFX_IDW_CONTROLBAR_FIRST,
	//	AFX_IDW_CONTROLBAR_LAST, 0, reposQuery, rcClientNew);
	//
	//// All of the Child Windows (Controls) now need to be moved so 
	//// the Tollbar does not cover them up. Offest to move all child 
	//// controls after adding Tollbar
	//CPoint ptOffset(rcClientNew.left - rcClientOld.left,
	//	rcClientNew.top - rcClientOld.top);
	//CRect	rcChild;
	//
	//// Handle to the Dialog Controls
	//CWnd*	pwndChild = GetWindow(GW_CHILD);
	//while (pwndChild) // Cycle through all child controls
	//{
	//	pwndChild->GetWindowRect(rcChild); // Get the child control RECT
	//	ScreenToClient(rcChild);
	//	// Changes the Child Rect by the values of the claculated offset
	//	rcChild.OffsetRect(ptOffset);
	//	pwndChild->MoveWindow(rcChild, FALSE); // Move the Child Control
	//	pwndChild = pwndChild->GetNextWindow();
	//}
	//CRect	rcWindow;
	//GetWindowRect(rcWindow); // Get the RECT of the Dialog
	//// Increase width to new Client Width
	//rcWindow.right += rcClientOld.Width() - rcClientNew.Width();
	//// Increase height to new Client Height
	//rcWindow.bottom += rcClientOld.Height() - rcClientNew.Height();
	//MoveWindow(rcWindow, FALSE); // Redraw Window
	// //Now we REALLY Redraw the Toolbar

	if (!m_secondToolBar.Create(this) || !m_secondToolBar.LoadToolBar(IDR_TOOLBAR1))
	{
		TRACE0("Failed to Create Dialog Toolbar\n");
		EndDialog(IDCANCEL);
	} 

	CRect	rcClientOld;
	GetClientRect(&rcClientOld);
	rcClientOld.right = 600;
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0, 0, 0, &rcClientOld);

	CRect rect1, rect2;
	m_ToolBar.GetWindowRect(&rect1);
	ScreenToClient(&rect1);

	m_secondToolBar.GetWindowRect(&rect2);
	ScreenToClient(&rect2);

	m_secondToolBar.GetToolBarCtrl().MoveWindow(rect1.right, rect1.top, rect2.Width(), rect2.Height());
//	GetDlgItem(IDR_TOOLBAR1)->SetWindowPos(NULL, rect1.right, rect1.top, rect2.Width(), rect2.Height(), SWP_NOZORDER | SWP_NOMOVE | SWP_SHOWWINDOW);


	// ====================================================================================================================================
	// image setting
	CToolBarCtrl& bar = m_ToolBar.GetToolBarCtrl();

	CImageList *pList = bar.GetImageList();

	HICON hIcon_1 = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON4));
	pList->Replace(0, hIcon_1); // not 5 as a separate is not an image

	hIcon_1 = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON5));
	pList->Replace(1, hIcon_1);

	hIcon_1 = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_SAVE));
	pList->Replace(2, hIcon_1);

	hIcon_1 = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_SAVE_DISABLED));
	pList->Replace(3, hIcon_1);

	hIcon_1 = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_SAVEAS));
	pList->Replace(4, hIcon_1);

	hIcon_1 = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_SAVEAS_DISABLED));
	pList->Replace(5, hIcon_1);

	hIcon_1 = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON6));
	pList->Replace(6, hIcon_1);

	hIcon_1 = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON13));
	pList->Replace(7, hIcon_1);

	hIcon_1 = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_DELETE));
	pList->Replace(8, hIcon_1);

	hIcon_1 = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON14));
	pList->Replace(9, hIcon_1);

	bar.SetImageList(pList);

	m_ToolBar.Invalidate();


	{
		CToolBarCtrl& bar = m_secondToolBar.GetToolBarCtrl();

		CImageList *pList = bar.GetImageList();

		HICON hIcon_1 = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON11));
		pList->Replace(0, hIcon_1); // not 5 as a separate is not an image

		hIcon_1 = LoadIconW(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON12));
		pList->Replace(1, hIcon_1); // not 5 as a separate is not an image

		hIcon_1 = LoadIconW(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON3));
		pList->Replace(2, hIcon_1); // not 5 as a separate is not an image

		hIcon_1 = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON7));
		pList->Replace(3, hIcon_1); // not 5 as a separate is not an image

		hIcon_1 = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON10));
		pList->Replace(4, hIcon_1); // not 5 as a separate is not an image

		hIcon_1 = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON17));
		pList->Replace(5, hIcon_1); // not 5 as a separate is not an image

		hIcon_1 = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON16));
		pList->Replace(6, hIcon_1); // not 5 as a separate is not an image

		hIcon_1 = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON8));
		pList->Replace(7, hIcon_1); // not 5 as a separate is not an image
	
		bar.SetImageList(pList);

		m_secondToolBar.Invalidate();
	}
	m_ToolBar.SetBarStyle(m_ToolBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

	m_secondToolBar.SetBarStyle(m_secondToolBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	EnableToolTips(TRUE);
	// =======================================================================================================================================
	RootList.SetExtendedStyle(RootList.GetExtendedStyle() | LVS_EX_CHECKBOXES | LVS_EX_TRANSPARENTSHADOWTEXT);
	List = &RootList;
	// toolbar image config
	CString mes;
	CString helpMes;

	
	for (int i = 0; i < 100; ++i)
	{
		if (i < 9)
		{
			mes.Format(L"%S", "0");
			helpMes.Format(L"%d", i + 1);
			mes += helpMes;
			ThreadsComboBox.AddString(mes);
		}
		else
		{
			mes.Format(L"%d", int(i + 1));
			ThreadsComboBox.AddString(mes);
		}
	}

	CBitmap m_Bitmap1,m_Bitmap2,m_Bitmap3,m_Bitmap4,m_Bitmap6;

	
	m_ImageList.Create(16, 16, ILC_COLORDDB , 3, 3);

	m_Bitmap1.LoadBitmap(IDB_BITMAP1);
	m_Bitmap2.LoadBitmap(IDB_BITMAP2);
	m_Bitmap3.LoadBitmap(IDB_BITMAP3);
	m_Bitmap4.LoadBitmap(IDB_BITMAP4);
	m_Bitmap6.LoadBitmap(IDB_BITMAP6);
	m_ImageList.Add(&m_Bitmap1, RGB(0,0,0));

	m_ImageList.Add(&m_Bitmap2, RGB(0, 0, 0));
	m_ImageList.Add(&m_Bitmap3, RGB(0, 0, 0));
	m_ImageList.Add(&m_Bitmap4, RGB(0, 0, 0));
	m_ImageList.Add(&m_Bitmap6, RGB(0, 0, 0));
	/*m_Tree.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP |
		TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT |
		TVS_SINGLEEXPAND | TVS_SHOWSELALWAYS |
		TVS_TRACKSELECT,
		CRect(10, 10, 200, 240), this, 0x1221);*/

	m_Tree.SetImageList(&m_ImageList, TVSIL_NORMAL);

	m_PathImageList.Create(32, 32, ILC_COLORDDB, 2, 2);

	CBitmap m_Bitmap5;
	m_Bitmap5.LoadBitmap(IDB_BITMAP5);
	m_PathImageList.Add(&m_Bitmap5, RGB(0, 0, 0));

	RootList.SetImageList(&m_PathImageList, LVSIL_SMALL);

	
	UpdateToolbar(PROJECT_NOTLOADED);

	//HICON icon;

	//HICON hIcon = AfxGetApp()->LoadIcon(MAKEINTRESOURCE(IDI_ICON2));
	//SetIcon(hIcon, FALSE);
	//this->SetBackgroundColor(RGB(32, 32, 32));
	//SetSysColors(2, aElements, aOldColors);

	
	HICON hIcon = AfxGetApp()->LoadIcon(MAKEINTRESOURCE(IDI_ICON2));
	SetIcon(hIcon, FALSE);
	SetWindowText(L"Test manager");
	Tag = &DropDown;
	Threads = &ThreadsComboBox;
	ToolBar = &m_ToolBar;
	Name = &m_NameBox;
	Bar = ToolBar;
	COLL = &mapOfColls;
	FAIL = &FailMap;
	PASS = &PasMap;
	timersCollection.Init();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

VOID CALLBACK TimerAPCProc(
	LPVOID lpArg,               // Data value
	DWORD dwTimerLowValue,      // Timer low value
	DWORD dwTimerHighValue)    // Timer high value

{
	// Formal parameters not used in this example.
	UNREFERENCED_PARAMETER(dwTimerLowValue);
	UNREFERENCED_PARAMETER(dwTimerHighValue);
//	CMFCTRSuiDlg* pointer = (CMFCTRSuiDlg*)lpArg;
//	pointer->OnProgramRunsel();
	
	//MessageBeep(0);

}


DWORD WINAPI TimeRunning(LPVOID arg)
{
	CMFCTRSuiDlg* dlg = (CMFCTRSuiDlg*)arg;
	HANDLE hTimer = CreateWaitableTimer(NULL, FALSE, NULL);
	LARGE_INTEGER large = { 15000 };
	
	SetWaitableTimer(hTimer, &large, 15000, TimerAPCProc, dlg, 0);
	for (int i = 0; i < 1000;++i)
	SleepEx(
		INFINITE,     // Wait forever
		TRUE);
	return 0;
}
#pragma region stuff
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCTRSuiDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCTRSuiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//void CMFCTRSuiDlg::OnLbnSelchangeListroot()
//{
//	int count = RootList.GetSelCount();
//	int* array = new int[count];
//
//	RootList.GetSelItems(count, array);
//
//	dRoots.clear();
//	dRoots.reserve(count);
//
//	for (int i = 0; i < count; ++i)
//	{
//		TCHAR root[MAX_PATH];
//		RootList.GetText(array[i], root);
//		dRoots.push_back(root);
//	}
//
//	// making RunButton visible only when at least one element is selected
//	UpdateToolbar();
//	if (count == 1)
//		Info(dRoots.front().get_path());
//	else
//		m_Tree.DeleteAllItems();
//
//	DropDown.SetCurSel(0);
//	m_NameBox.SetCurSel(0);
//	ThreadsComboBox.SetCurSel(9);
//	CMFCTRSuiDlg::OnCbnSelchangeCombo1();
//	CMFCTRSuiDlg::OnCbnSelchangeCombo2();
//	CMFCTRSuiDlg::OnCbnSelchangeCombo3();
//	delete[] array;
//}

void CMFCTRSuiDlg::UpdateToolbar(int mask)
{
	static bool first_initialization = true;

	if (first_initialization)
	{
		first_initialization = false;

		WIN32_FIND_DATA FindFileData;
		HANDLE handle = FindFirstFile(L"Last Project.xml", &FindFileData);

		if (handle != INVALID_HANDLE_VALUE)
		{
			m_Menu->EnableMenuItem(ID_PROJECT_LASTPROJECTS, MF_BYCOMMAND | MF_ENABLED);
		}
		m_Menu->EnableMenuItem(ID_New_Project, MF_BYCOMMAND | MF_ENABLED);
		m_Menu->EnableMenuItem(ID_Load_Project, MF_BYCOMMAND | MF_ENABLED);

		m_secondToolBar.GetToolBarCtrl().HideButton(TOOLBAR_REFRESH);
		m_ToolBar.GetToolBarCtrl().HideButton(TOOLBAR_ADD, false);
		m_ToolBar.GetToolBarCtrl().HideButton(TOOLBAR_ADDGREY);
	}

	if (mask & PROJECT_UPLOADED)
	{// mask = PROJECT_UPLOADED | ...
	//	m_ToolBar.GetToolBarCtrl().HideButton(TOOLBAR_SAVE, false);
	//	m_ToolBar.GetToolBarCtrl().HideButton(TOOLBAR_SAVEAS, false);
	////	m_ToolBar.GetToolBarCtrl().HideButton(TOOLBAR_ADD, false);

	////	m_ToolBar.GetToolBarCtrl().HideButton(TOOLBAR_ADDGREY);
	//	m_ToolBar.GetToolBarCtrl().HideButton(TOOLBAR_SAVE_GREY);
	//	m_ToolBar.GetToolBarCtrl().HideButton(TOOLBAR_SAVEAS_GREY);


	//	m_Menu->EnableMenuItem(TOOLBAR_SAVE, MF_BYCOMMAND | MF_ENABLED);
	//	m_Menu->EnableMenuItem(TOOLBAR_SAVEAS, MF_BYCOMMAND | MF_ENABLED);
		m_secondToolBar.GetToolBarCtrl().HideButton(TOOLBAR_CLOCK_GREY);
		m_secondToolBar.GetToolBarCtrl().HideButton(TOOLBAR_CLOCK, false);
		if (RootList.GetItemCount())
		{
			RootList.SetSelectionMark(0);
			RootList.SetItemState(0, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
		}	//RootList.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);
	}
	else if (mask & PROJECT_NOTLOADED)
	{
		//m_ToolBar.GetToolBarCtrl().HideButton(TOOLBAR_SAVE);
		//m_ToolBar.GetToolBarCtrl().HideButton(TOOLBAR_SAVEAS);

		//m_ToolBar.GetToolBarCtrl().HideButton(TOOLBAR_SAVE_GREY, false);
		//m_ToolBar.GetToolBarCtrl().HideButton(TOOLBAR_SAVEAS_GREY, false);

		//m_Menu->EnableMenuItem(TOOLBAR_SAVE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		//m_Menu->EnableMenuItem(TOOLBAR_SAVEAS, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);

		m_secondToolBar.GetToolBarCtrl().HideButton(TOOLBAR_STOP);
//		m_ToolBar.GetToolBarCtrl().HideButton(TOOLBAR_ADD);

		m_secondToolBar.GetToolBarCtrl().HideButton(TOOLBAR_CLOCK_GREY, false);
		m_secondToolBar.GetToolBarCtrl().HideButton(TOOLBAR_CLOCK);


		dRoots.clear();
		RootList.DeleteAllItems();

		ConsoleHide();
		RunToolsHide();
	}

	if (mask & RUN_CLICKED)
	{// mask = RUN_CLICKED | ...
		is_running = true;
		RunToolsShow();
		m_secondToolBar.GetToolBarCtrl().HideButton(TOOLBAR_RUN);
		m_secondToolBar.GetToolBarCtrl().HideButton(TOOLBAR_RUNGREY);

		m_secondToolBar.GetToolBarCtrl().HideButton(TOOLBAR_STOP, false);

		m_Menu->EnableMenuItem(TOOLBAR_DELETE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		m_Menu->EnableMenuItem(TOOLBAR_RUN, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	}
	else if (mask & RUN_UNCLICKED)
	{
		is_running = false;
		RunToolsHide();
		m_secondToolBar.GetToolBarCtrl().HideButton(TOOLBAR_STOP);

		m_Menu->EnableMenuItem(TOOLBAR_DELETE, MF_BYCOMMAND | MF_ENABLED);
		m_Menu->EnableMenuItem(TOOLBAR_RUN, MF_BYCOMMAND | MF_ENABLED);
	}
	if (!is_running)
	{
		if (dRoots.size())
		{
			m_secondToolBar.GetToolBarCtrl().HideButton(TOOLBAR_RUN, false);
			m_ToolBar.GetToolBarCtrl().HideButton(TOOLBAR_DELETE, false);

			m_secondToolBar.GetToolBarCtrl().HideButton(TOOLBAR_RUNGREY);
			m_ToolBar.GetToolBarCtrl().HideButton(TOOLBAR_DELETEGREY);

			m_Menu->EnableMenuItem(TOOLBAR_DELETE, MF_BYCOMMAND | MF_ENABLED);
			m_Menu->EnableMenuItem(TOOLBAR_RUN, MF_BYCOMMAND | MF_ENABLED);
		}
		else
		{
			m_secondToolBar.GetToolBarCtrl().HideButton(TOOLBAR_RUN);
			m_ToolBar.GetToolBarCtrl().HideButton(TOOLBAR_DELETE);

			m_secondToolBar.GetToolBarCtrl().HideButton(TOOLBAR_RUNGREY, false);
			m_ToolBar.GetToolBarCtrl().HideButton(TOOLBAR_DELETEGREY, false);

			m_Menu->EnableMenuItem(TOOLBAR_DELETE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
			m_Menu->EnableMenuItem(TOOLBAR_RUN, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);

			m_Tree.DeleteAllItems();
		}
		int index = -1;
		for (int i = 0; i < RootList.GetItemCount(); ++i)
		{
			if (RootList.GetItemState(i, LVIS_SELECTED))
			{
				index = i;
				break;
			}
		}

		if (index < 0)
			m_secondToolBar.GetToolBarCtrl().HideButton(TOOLBAR_REFRESH);
		else
			m_secondToolBar.GetToolBarCtrl().HideButton(TOOLBAR_REFRESH, false);
	}
	if (RootList.GetItemCount())
	{
		m_secondToolBar.GetToolBarCtrl().HideButton(TOOLBAR_ADDCLOCK, false);
		m_ToolBar.GetToolBarCtrl().HideButton(TOOLBAR_SAVE, false);
		m_ToolBar.GetToolBarCtrl().HideButton(TOOLBAR_SAVEAS, false);
		//	m_ToolBar.GetToolBarCtrl().HideButton(TOOLBAR_ADD, false);

		//	m_ToolBar.GetToolBarCtrl().HideButton(TOOLBAR_ADDGREY);
		m_ToolBar.GetToolBarCtrl().HideButton(TOOLBAR_SAVE_GREY);
		m_ToolBar.GetToolBarCtrl().HideButton(TOOLBAR_SAVEAS_GREY);


		m_Menu->EnableMenuItem(TOOLBAR_SAVE, MF_BYCOMMAND | MF_ENABLED);
		m_Menu->EnableMenuItem(TOOLBAR_SAVEAS, MF_BYCOMMAND | MF_ENABLED);
	}
	else
	{
		m_secondToolBar.GetToolBarCtrl().HideButton(TOOLBAR_ADDCLOCK);
		m_ToolBar.GetToolBarCtrl().HideButton(TOOLBAR_SAVE);
		m_ToolBar.GetToolBarCtrl().HideButton(TOOLBAR_SAVEAS);

		m_ToolBar.GetToolBarCtrl().HideButton(TOOLBAR_SAVE_GREY, false);
		m_ToolBar.GetToolBarCtrl().HideButton(TOOLBAR_SAVEAS_GREY, false);

		m_Menu->EnableMenuItem(TOOLBAR_SAVE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		m_Menu->EnableMenuItem(TOOLBAR_SAVEAS, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	}
}


void CMFCTRSuiDlg::OnProgramAddfolder()
{
	BROWSEINFO bi = { 0 };
	bi.lpszTitle = _T("Select Folder");
	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
	if (pidl != 0)
	{
		// get the name of the folder
		TCHAR path[MAX_PATH];
		SHGetPathFromIDList(pidl, path);
		char* pathA = convertToChar(path);
		if (ExistInList(path))
		{
			MessageBox(_T("This item is already in the list!"), _T("Error"), MB_ICONERROR | MB_OK);
			delete[] pathA;
			return;
		}
		if (!Manager.Verify(pathA, nullptr, nullptr))
		{
			int index = RootList.InsertItem(RootList.GetItemCount(), path);
			if (index >= 0)
			{
				RootList.SetCheck(index);
				if (RootList.GetItemCount() == 1)
				{
					RootList.SetSelectionMark(0);
					RootList.SetItemState(0, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
				}
				char* Way = fromCStringToChar(RootList.GetItemText(index, index));
				TCHAR* buf = new TCHAR[strlen(Way)+1];
				convertToTCHAR(buf, Way);
				//collOfColls.push_back(Info(buf));
				CreateThread(NULL, 0, TimeRunning, this, 0, 0);
				delete[] buf;
				delete[] Way;
			}
			else
			{
				MessageBox(_T("Can not insert the item!"), _T("Error"), MB_ICONERROR | MB_OK);
			}
		}
		else
		{
			MessageBox(_T("Current path is invalid!"), _T("Error"), MB_ICONERROR | MB_OK);
		}

		delete[] pathA;
		// free memory used
		IMalloc * imalloc = 0;
//		m_Menu->EnableMenuItem(ID_Save_Project, MF_BYCOMMAND | MF_ENABLED);
		if (SUCCEEDED(SHGetMalloc(&imalloc)))
		{
			imalloc->Free(pidl);
			imalloc->Release();
		}
	}
}

bool CMFCTRSuiDlg::ExistInList(TCHAR* path)
{
	for (int i = 0; i < RootList.GetItemCount(); ++i)
	{
		if (!_tcsicmp(path, RootList.GetItemText(i, 0)))
			return true;
	}
	return false;
}


void CMFCTRSuiDlg::OnProgramDeleteselecteditems()
{
	//if (dRoots.size())
	//{
	//	for each (auto to_delete in dRoots)
	//	{
	//		int index = RootList.FindString(-1, to_delete.get_path());
	//		RootList.DeleteString(index);
	//	}
	//	dRoots.clear();
	//	UpdateToolbar();
	//}
	// due to the fact, that we indentify elements by index, and after each deletion they shifted - we are forced delete from the biggest index.
	int res = MessageBox(L"Do you really want to delete this item?", L"Confirmation", MB_ICONINFORMATION | MB_YESNO);
	if (res == IDYES)
	{
		std::sort(dRoots.begin(), dRoots.end(), std::greater<int>());
		for (auto iter = dRoots.begin(); iter != dRoots.end(); ++iter)
		{
			RootList.DeleteItem(*iter);
		}
		if (RootList.GetItemCount())
		{
			bool marked = false;
			for (int i = 0; i < RootList.GetItemCount(); ++i)
			{
				if (RootList.GetItemState(i, LVIS_SELECTED))
					marked = true;
			}
			if (!marked)
			{
				RootList.SetSelectionMark(0);
				RootList.SetItemState(0, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
			}
			char* PA = fromCStringToChar(RootList.GetItemText(ListSelection, 0));
			TCHAR* buf = new TCHAR[strlen(PA) + 1];
			convertToTCHAR(buf, PA);
			Info(buf);
			delete[] buf;
			delete[] PA;
		}
		else
		{
			m_Tree.DeleteAllItems();
		}
		UpdateToolbar();
		dRoots.clear();
	}
}


void CMFCTRSuiDlg::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

DWORD WINAPI ToRun(LPVOID arg)
{
	RunEndCheck = true;
	ToRunParameters* param = (ToRunParameters*)arg;
	param->manager->Begin();
	param->dialog->UpdateToolbar(RUN_CLICKED);

	HANDLE hThread = 0;
//	param->progress->ShowWindow(true);
//	param->subProgress->ShowWindow(true);
	param->progress->SetRange(0, param->coll.size());
	param->progress->SetStep(1);
	

	int prev = 0;
	int last = 0;
	
	for each(auto var in param->coll)
	{
		PassedC.clear();
		FailedC.clear();
		
		std::map<CString, std::vector<HTREEITEM*>>::iterator iter = (*COLL).find(var.get_path());
		TREE = &iter->second;

		char* path = convertToChar(var.get_path());
		int Thread_amount = 1;
		if (threads)
		{
			Thread_amount = atoi(threads);
		}
		/*
		RunParameters* parameters = new RunParameters(path, testName, tag, Thread_amount, param->manager,param->subProgress);
		DWORD ident;
		hThread = CreateThread(NULL, 0, RunSuits, parameters, 0, &ident);

		WaitForSingleObject(hThread, INFINITE);
		CloseHandle(hThread);*/
		std::list<Suite*> coll = *Manager.List(path , testName, tag);
		int count = 0;
		for each(auto it in coll)
		{
			count += it->getList().size();
			for each(auto iter in it->getList())
			{
				if (iter->getRepeat())
				{
					count += atoi(iter->getRepeat());
					--count;
				}
			}
		}

		param->subProgress->SetRange(0, count);
		param->subProgress->SetStep(1);
		Manager.Run(path, testName, tag, Thread_amount, param->manager);
		param->progress->StepIt();
		param->subProgress->SetPos(0);
		
		param->dialog->SetListItemState(!(FailedC.size()), var);
		prev = FailedC.size();
		
		
		FAIL->insert(std::pair<CString,std::vector<TRSInfo>>(List->GetItemText(ListSelection,0),FailedC));
		PASS->insert(std::pair<CString, std::vector<TRSInfo>>(List->GetItemText(ListSelection, 0), PassedC));

		
		
		for (int i = ListSelection; i < List->GetItemCount(); ++i)
		{
			if (List->GetCheck(i))
			{
				if (i != ListSelection)
				{
					ListSelection = i;
					
				}
			}
		}
		TREECTRL->DeleteAllItems();
		MainDialog->Info(var.get_path());
		

	}
	
	
	


	param->manager->End();
	delete param->manager;
	param->dialog->UpdateToolbar(RUN_UNCLICKED);
	delete param;
	RunEndCheck = false;

//	FailedC.clear();
//	PassedC.clear();
	return 0;
}



bool CMFCTRSuiDlg::SetListItemState(bool state, SuiteRoot text)
{
	int index = -1;
	for (int i = 0; i < RootList.GetItemCount(); ++i)
	{
		if (!_tcsicmp(text.get_path(), RootList.GetItemText(i, 0)))
		{
			index = i;
			break;
		}
	}
	if (index == -1)
		return false;

	SetListItemImage(index, (int)state + 1);
	return true;
}


DWORD WINAPI Timer(LPVOID arg)
{
	CEdit* edit = (CEdit*)arg;
//	edit->ShowWindow(true);
	int count = 0;
	CString mes;
	int last=0;
	while (RunEndCheck)
	{
		last = edit->GetWindowTextLength();
		edit->SetSel(0,last);
		edit->ReplaceSel(L"Tests running: ");
		++count;
		if (count < 3600)
		{
			edit->ReplaceSel(L"00:");
			if ((count / 60)>0)
			{
				if ((count / 60) > 9)
				{
					mes.Format(L"%d", count / 60);
					edit->ReplaceSel(mes);
					edit->ReplaceSel(L":");
					int res = count - (count / 60) * 60;
					if (res > 10)
					{
						mes.Format(L"%d", res);
						edit->ReplaceSel(mes);
					}
					else
					{
						edit->ReplaceSel(L"0");
						mes.Format(L"%d", res);
						edit->ReplaceSel(mes);
					}
				}
				else
				{
					edit->ReplaceSel(L"0");
					mes.Format(L"%d", count / 60);
					edit->ReplaceSel(mes);
					edit->ReplaceSel(L":");
					int res = count - (count / 60) * 60;
					if (res > 9)
					{
						mes.Format(L"%d", res);
						edit->ReplaceSel(mes);
						
					}
					else
					{
						edit->ReplaceSel(L"0");
						mes.Format(L"%d", res);
						edit->ReplaceSel(mes);
					}
				}
			}
			else
			{
				edit->ReplaceSel(L"00:");
				if (count > 9)
				{
					mes.Format(L"%d", count);
					edit->ReplaceSel(mes);
				}
				else
				{
					edit->ReplaceSel(L"0");
					mes.Format(L"%d", count);
					edit->ReplaceSel(mes);
				}
			}
		}
		else
		{
			if ((count / 3600) > 9)
			{
				mes.Format(L"%d", count/3600);
				edit->ReplaceSel(mes);
				edit->ReplaceSel(L":");
				int res = count - (count / 3600) * 3600;
				if (res/60 > 9)
				{
					mes.Format(L"%d", res/60);
					edit->ReplaceSel(mes);
					edit->ReplaceSel(L":");
					int sec = res - (res / 60) * 60;
					if (sec > 10)
					{
						mes.Format(L"%d", sec);
						edit->ReplaceSel(mes);
					}
					else
					{
						edit->ReplaceSel(L"0");
						mes.Format(L"%d", sec);
						edit->ReplaceSel(mes);
					}
				}
				else
				{
					edit->ReplaceSel(L"0");
					mes.Format(L"%d", res/60);
					edit->ReplaceSel(mes);
					edit->ReplaceSel(L":");
					int sec = res - (res / 60) * 60;
					if (sec > 9)
					{
						mes.Format(L"%d", sec);
						edit->ReplaceSel(mes);
					}
					else
					{
						edit->ReplaceSel(L"0");
						mes.Format(L"%d", sec);
						edit->ReplaceSel(mes);
					}
				}
			}
			else
			{
				edit->ReplaceSel(L"0");
				mes.Format(L"%d", count/3600);
				edit->ReplaceSel(mes);
				edit->ReplaceSel(L":");
				int res = count - (count / 3600) * 3600;
				if (res / 60 > 9)
				{
					mes.Format(L"%d", res / 60);
					edit->ReplaceSel(mes);
					edit->ReplaceSel(L":");
					int sec = res - (res / 60) * 60;
					if (sec > 9)
					{
						mes.Format(L"%d", sec);
						edit->ReplaceSel(mes);
					}
					else
					{
						edit->ReplaceSel(L"0");
						mes.Format(L"%d", sec);
						edit->ReplaceSel(mes);
					}
				}
				else
				{
					edit->ReplaceSel(L"0");
					mes.Format(L"%d", res / 60);
					edit->ReplaceSel(mes);
					edit->ReplaceSel(L":");
					int sec = res - (res / 60) * 60;
					if (sec > 9)
					{
						mes.Format(L"%d", sec);
						edit->ReplaceSel(mes);
					}
					else
					{
						edit->ReplaceSel(L"0");
						mes.Format(L"%d", sec);
						edit->ReplaceSel(mes);
					}
				}
			}
		}
		edit->SetSel(0, 0);
		Sleep(1000);
	}
	edit->SetSel(0, last);
	edit->ReplaceSel(L"Time spent: ");
	if (count < 3600)
	{
		edit->ReplaceSel(L"00:");
		if ((count / 60)>0)
		{
			if ((count / 60) > 9)
			{
				mes.Format(L"%d", count / 60);
				edit->ReplaceSel(mes);
				edit->ReplaceSel(L":");
				int res = count - (count / 60) * 60;
				if (res > 9)
				{
					mes.Format(L"%d", res);
					edit->ReplaceSel(mes);
				}
				else
				{
					edit->ReplaceSel(L"0");
					mes.Format(L"%d", res);
					edit->ReplaceSel(mes);
				}
			}
			else
			{
				edit->ReplaceSel(L"0");
				mes.Format(L"%d", count / 60);
				edit->ReplaceSel(mes);
				edit->ReplaceSel(L":");
				int res = count - (count / 60) * 60;
				if (res > 9)
				{
					mes.Format(L"%d", res);
					edit->ReplaceSel(mes);

				}
				else
				{
					edit->ReplaceSel(L"0");
					mes.Format(L"%d", res);
					edit->ReplaceSel(mes);
				}
			}
		}
		else
		{
			edit->ReplaceSel(L"00:");
			if (count > 9)
			{
				mes.Format(L"%d", count );
				edit->ReplaceSel(mes);
			}
			else
			{
				edit->ReplaceSel(L"0");
				mes.Format(L"%d", count );
				edit->ReplaceSel(mes);
			}
		}
	}
	else
	{
		if ((count / 3600) > 9)
		{
			mes.Format(L"%d", count / 3600);
			edit->ReplaceSel(mes);
			edit->ReplaceSel(L":");
			int res = count - (count / 3600) * 3600;
			if (res / 60 > 9)
			{
				mes.Format(L"%d", res / 60);
				edit->ReplaceSel(mes);
				edit->ReplaceSel(L":");
				int sec = res - (res / 60) * 60;
				if (sec > 10)
				{
					mes.Format(L"%d", sec);
					edit->ReplaceSel(mes);
				}
				else
				{
					edit->ReplaceSel(L"0");
					mes.Format(L"%d", sec);
					edit->ReplaceSel(mes);
				}
			}
			else
			{
				edit->ReplaceSel(L"0");
				mes.Format(L"%d", res / 60);
				edit->ReplaceSel(mes);
				edit->ReplaceSel(L":");
				int sec = res - (res / 60) * 60;
				if (sec > 9)
				{
					mes.Format(L"%d", sec);
					edit->ReplaceSel(mes);
				}
				else
				{
					edit->ReplaceSel(L"0");
					mes.Format(L"%d", sec);
					edit->ReplaceSel(mes);
				}
			}
		}
		else
		{
			edit->ReplaceSel(L"0");
			mes.Format(L"%d", count / 3600);
			edit->ReplaceSel(mes);
			edit->ReplaceSel(L":");
			int res = count - (count / 3600) * 3600;
			if (res / 60 > 9)
			{
				mes.Format(L"%d", res / 60);
				edit->ReplaceSel(mes);
				edit->ReplaceSel(L":");
				int sec = res - (res / 60) * 60;
				if (sec > 9)
				{
					mes.Format(L"%d", sec);
					edit->ReplaceSel(mes);
				}
				else
				{
					edit->ReplaceSel(L"0");
					mes.Format(L"%d", sec);
					edit->ReplaceSel(mes);
				}
			}
			else
			{
				edit->ReplaceSel(L"0");
				mes.Format(L"%d", res / 60);
				edit->ReplaceSel(mes);
				edit->ReplaceSel(L":");
				int sec = res - (res / 60) * 60;
				if (sec > 9)
				{
					mes.Format(L"%d", sec);
					edit->ReplaceSel(mes);
				}
				else
				{
					edit->ReplaceSel(L"0");
					mes.Format(L"%d", sec);
					edit->ReplaceSel(mes);
				}
			}
		}
	}
	return 0;
}

void CMFCTRSuiDlg::OnProgramRunsel()
{
	TestsTimerDialog dlg;
	//dlg.DoModal();
	if (dRoots.size())
	{
		m_Progress.SetPos(0);


		if (!(pro_.getName() && pro_.getPath()))
		{
			MessageBox(TEXT("You must create a new project!"), TEXT(""), MB_ICONINFORMATION | MB_OK);
			OnNewProject();
			if (!(pro_.getName() && pro_.getPath()))
				return;
		}


		short cIndex;
		cIndex = DropDown.GetCurSel();
		CString fontName;
		DropDown.GetLBText(cIndex, fontName);
		if (fontName != L"All")
		{
			tag = fromCStringToChar(fontName);
		}
		else
		{
			tag = nullptr;
		}
		cIndex = ThreadsComboBox.GetCurSel();
		ThreadsComboBox.GetLBText(cIndex, fontName);
		if (fontName != "")
		{
			threads = fromCStringToChar(fontName);
		}

		cIndex = m_NameBox.GetCurSel();
		m_NameBox.GetLBText(cIndex, fontName);
		if (fontName != "All")
		{
			testName = fromCStringToChar(fontName);
		}
		else
		{
			testName = nullptr;
		}

		reportManag = new ReportManager;
		ConsoleReporter* reporter = new ConsoleReporter(&console_output, &subm_Progress);
		reporter->setPasCol(&PassedC);
		reporter->setFailCol(&FailedC);
		reportManag->addReporter(reporter);
		std::vector<SuiteRoot> roots;
		roots.reserve(dRoots.size());
		for (auto iter = dRoots.begin(); iter != dRoots.end(); ++iter)
		{
			roots.push_back(SuiteRoot(RootList.GetItemText(*iter, 0)));
		}
		ToRunParameters* to_run = new ToRunParameters{roots, reportManag, &m_Progress, &subm_Progress, this};
		HANDLE hThread = CreateThread(NULL, 0, ToRun, to_run, 0, 0);
		HANDLE hTimer = CreateThread(NULL, 0, Timer, &Time_running_edit, 0, 0);
		CloseHandle(hThread);
		CloseHandle(hTimer);

	}
}

// $$$ isStraightSubdirectory(int begin, char* source) - is more approprate
bool checkDiff(int begin, char* source)
{
	int count = 0;
	for (int i = begin; i < strlen(source); ++i)
	{
		if (source[i] == '\\')
		{
			++count;
		}
	}
	return count == 1;
}

// $$$ Do you really need a reference to a count parameter???
void TreeParse(std::list<Suite*>::iterator& it, std::list<Suite*>* suiteColl, CTreeCtrl* m_Tree, int& count, HTREEITEM* hHead, std::list<Suite*>* checkList, std::vector<HTREEITEM*>* TreeControlsList)
{
	// $$$ as I understood it is kind of a guard for redrawing Tree on exactly the same one?! 
	if (count != suiteColl->size())
	{
		// $$$ Warning: if we change our code from using pointers to list to simple list this code crashes
		// $$$ It is better to avoid calling strlen on the same string twice
		// $$$ Not for sure, but, maybe, it will be better to use there strcpy_s instead of strncpy_s?!
		//char* rootPath = new char[strlen((*it)->get_path()) + 1];
		//strncpy_s(rootPath, strlen((*it)->get_path()) + 1, (*it)->get_path(), strlen((*it)->get_path()));
		//char* rootName = new char[strlen((*it)->getName()) + 1];
		//strncpy_s(rootName, strlen((*it)->getName()) + 1, (*it)->getName(), strlen((*it)->getName()));
	
		unsigned path_lenght = strlen((*it)->get_path());
		char* rootPath = new char[path_lenght + 1];
		strcpy_s(rootPath, path_lenght + 1, (*it)->get_path());

		unsigned name_lenght = strlen((*it)->getName());
		char* rootName = new char[name_lenght + 1];
		strcpy_s(rootName, name_lenght + 1, (*it)->getName());

		HTREEITEM* hSuite = new HTREEITEM;

		// $$$ I left it as it was for you with comments to see what are you doing all the time
		// $$$ It is not harm productivity as far as I know, but all code-styles which I read order to 
		// keep variable in the smallest possible scope and the most closest to the code, where it used
		// $$$ I did not remember, that some code-styles reccomended to use auto keyword instead of
		// explicit iterator name and writing it explicitly is truly speeds up compilation time, but
		// it is more readable and for sure save you from overtyping :)
		// P.S. When you read code in notepad without intellisence this suggestion isn't working)
		// EDIT: second suggestion is irrelavent in this situation because I incorectly thought that you are using this
		// iterator to iterate the loop. But you done something like this before, so suggestion is still actual
		// And try to name variable relavently because it is harder to understand what variables such as itHelper and helper
		// must do.
		std::list<Suite*>::iterator itHelp = it;

		// $$$ writing variable name in the initializing section of for-statement is useless and just slowing the program
		for (/*$$$ it*/; it != suiteColl->end(); ++it)
		{
			// $$$ I suggest you to move this checking into for-statement's condition expression in the same order, as I wrote lower
			//  count == suiteColl->size() && it != suiteColl->end()
			if (count == suiteColl->size())
			{
				break;
			}

			std::list<Suite*>::iterator helper = std::find(checkList->begin(), checkList->end(), *it);
			// @ if this suite is already in the list
			if (helper == (checkList->end()))
			{
				// @ checking whether we are not iterating the root path
				if (strlen((*it)->get_path()) != strlen(rootPath))
				{
					if (!strncmp(rootPath, (*it)->get_path(), strlen(rootPath)))
					{
						if (checkDiff(strlen(rootPath), (*it)->get_path()))
							TreeParse(it, suiteColl, m_Tree, count, hSuite, checkList, TreeControlsList);
					}

				}
				else
				{
					// $$$ again, despite the path checking is correct, because this else is executed only when path sizes are equal
					// there might be bugs when comparing names using strncmp function instead of strcmp
					// $$$ What is the purpose to compare names when pathes are identical and it is imposible for two folders to have the same path. 
					if (!strncmp(rootPath, (*it)->get_path(), strlen(rootPath)) && !strncmp((*it)->getName(), rootName, strlen(rootName)))
					{
						TCHAR* buf = new TCHAR[strlen((*it)->getName()) + 1];
						convertToTCHAR(buf, (*it)->getName());

						*hSuite = m_Tree->InsertItem(buf, 0, 0, *hHead);
						m_Tree->Expand(*hSuite, TVE_EXPAND);
						++count;
						
						// $$$ the same suggestion about loops
						// @ inserting all test to the tree-view
						std::list<TRSTest*>::iterator iter = (*it)->getList().begin();
						for (iter; iter != (*it)->getList().end(); ++iter)
						{
							// $$$ The code, which is repeated, should not repetead! (c)
							//if (tag)
							//{
							//	// $$$ again, this code will have a bug when (*iter)->getTag() is a substring of a tag
							//	if (!strncmp(tag, (*iter)->getTag(), strlen(tag)))
							//	{
							//		HTREEITEM* hTest = new HTREEITEM;
							//		TCHAR* subBuf = new TCHAR[strlen((*iter)->getName()) + 1];
							//		convertToTCHAR(subBuf, (*iter)->getName());
							//		if (!strncmp((*iter)->getDisable(),"false",strlen("false")))
							//			*hTest = m_Tree->InsertItem(subBuf, 3, 3, *hSuite);
							//		if (!strncmp((*iter)->getDisable(), "true", strlen("true")))
							//			*hTest = m_Tree->InsertItem(subBuf, 12, 12, *hSuite);
							//		//m_Tree->Expand(*hTest, TVE_EXPAND);
							//		m_Tree->SetItemData(*hTest, (DWORD)(*iter));
							//		TreeControlsList->push_back(hTest);
							//		delete[] subBuf;
							//	}
							//}
							//else
							//{
							//	HTREEITEM* hTest = new HTREEITEM;
							//	TCHAR* subBuf = new TCHAR[strlen((*iter)->getName()) + 1];
							//	convertToTCHAR(subBuf, (*iter)->getName());
							//	if (!strncmp((*iter)->getDisable(), "false", strlen("false")))
							//		*hTest = m_Tree->InsertItem(subBuf, 3, 3, *hSuite);
							//	if (!strncmp((*iter)->getDisable(), "true", strlen("true")))
							//		*hTest = m_Tree->InsertItem(subBuf, 12, 12, *hSuite);
							//	m_Tree->SetItemData(*hTest, (DWORD)(*iter));
							//	//m_Tree->Expand(*hTest, TVE_EXPAND);
							//	TreeControlsList->push_back(hTest);
							//	delete[] subBuf;
							//}

							if (!tag || !strcmp(tag, (*iter)->getTag()))
							{
								// @ releasing this memory is a TreeControlsList duty
								HTREEITEM* hTest = new HTREEITEM;

								// $$$ looping allocation/reallocation is a very hrinovyj style.
								// You should consider some statical array and override it on each iteration
								TCHAR* subBuf = new TCHAR[strlen((*iter)->getName()) + 1];
								convertToTCHAR(subBuf, (*iter)->getName());

								// $$$ there also was strncmp. I changed it to strcmp

								// $$$ Does you xml-verify check wheather in disable field there is either "true" or "false"?
								// If yes, this code ispossible to change to faster-one with if-else construction
								// If no, test wont be added to the list-control but to the TreeControlsList - will be. 
								// So, it may cause serious consequences.
								if (!strcmp((*iter)->getDisable(), "false"))
									*hTest = m_Tree->InsertItem(subBuf, 3, 3, *hSuite);
								if (!strcmp((*iter)->getDisable(), "true"))
									*hTest = m_Tree->InsertItem(subBuf, 12, 12, *hSuite);
								
								//m_Tree->Expand(*hTest, TVE_EXPAND);
								m_Tree->SetItemData(*hTest, (DWORD)(*iter));
								TreeControlsList->push_back(hTest);
								delete[] subBuf;
							}
						}
						checkList->push_back((*it));
						delete[] buf;
					}

				}
			}
		}
		// $$$ you intentionally isn't iterating throught the first element of a suiteColl?
		// $$$ when you need the reverse loop you just can create another iterator and do this
		// for (auto it = suiteColl->rbegin(); it != suiteColl->rend(); ++it
		--it;

		// $$$ For what reason your function looping within collection twice???
		for (/*$$$ it*/; it != suiteColl->begin(); --it)
		{
			// $$$ the same remark as to the loop above
			if (count == suiteColl->size())
			{
				break;
			}

			std::list<Suite*>::iterator helper = std::find(checkList->begin(), checkList->end(), *it);
			if (helper == (checkList->end()))
			{
				if (strlen((*it)->get_path()) != strlen(rootPath))
				{
					if (!strncmp(rootPath, (*it)->get_path(), strlen(rootPath)))
					{
						if (checkDiff(strlen(rootPath), (*it)->get_path()))
							TreeParse(it, suiteColl, m_Tree, count, hSuite, checkList, TreeControlsList);
					}
					
				}
				else
				{
						if (!strncmp(rootPath, (*it)->get_path(), strlen(rootPath)) && !strncmp((*it)->getName(), rootName, strlen(rootName)))
						{
							TCHAR* buf = new TCHAR[strlen((*it)->getName()) + 1];
							convertToTCHAR(buf, (*it)->getName());
							*hSuite = m_Tree->InsertItem(buf, 0, 0, *hHead);
							m_Tree->Expand(*hSuite, TVE_EXPAND);
							++count;
							
							std::list<TRSTest*>::iterator iter = (*it)->getList().begin();
							for (iter; iter != (*it)->getList().end(); ++iter)
							{
								// $$$ the same, sa above
								//if (tag)
								//{
								//	if (!strncmp(tag, (*iter)->getTag(), strlen(tag)))
								//	{
								//		HTREEITEM* hTest = new HTREEITEM;
								//		TCHAR* subBuf = new TCHAR[strlen((*iter)->getName()) + 1];
								//		convertToTCHAR(subBuf, (*iter)->getName());
								//		if (!strncmp((*iter)->getDisable(), "false", strlen("false")))
								//			*hTest = m_Tree->InsertItem(subBuf, 3, 3, *hSuite);
								//		if (!strncmp((*iter)->getDisable(), "true", strlen("true")))
								//			*hTest = m_Tree->InsertItem(subBuf, 12, 12, *hSuite);
								//		m_Tree->SetItemData(*hTest, (DWORD)(*iter));
								//		//m_Tree->Expand(*hTest, TVE_EXPAND);
								//		TreeControlsList->push_back(hTest);
								//		delete[] subBuf;
								//	}
								//}
								//else
								//{
								//	HTREEITEM* hTest = new HTREEITEM;
								//	TCHAR* subBuf = new TCHAR[strlen((*iter)->getName()) + 1];
								//	convertToTCHAR(subBuf, (*iter)->getName());
								//	if (!strncmp((*iter)->getDisable(), "false", strlen("false")))
								//		*hTest = m_Tree->InsertItem(subBuf, 3, 3, *hSuite);
								//	if (!strncmp((*iter)->getDisable(), "true", strlen("true")))
								//		*hTest = m_Tree->InsertItem(subBuf, 12, 12, *hSuite);
								//	m_Tree->SetItemData(*hTest, (DWORD)(*iter));
								//	//m_Tree->Expand(*hTest, TVE_EXPAND);
								//	TreeControlsList->push_back(hTest);
								//	delete[] subBuf;
								//}
								if (!tag || !strncmp(tag, (*iter)->getTag(), strlen(tag)))
								{
									HTREEITEM* hTest = new HTREEITEM;
									TCHAR* subBuf = new TCHAR[strlen((*iter)->getName()) + 1];
									convertToTCHAR(subBuf, (*iter)->getName());
									if (!strncmp((*iter)->getDisable(), "false", strlen("false")))
										*hTest = m_Tree->InsertItem(subBuf, 3, 3, *hSuite);
									if (!strncmp((*iter)->getDisable(), "true", strlen("true")))
										*hTest = m_Tree->InsertItem(subBuf, 12, 12, *hSuite);
									m_Tree->SetItemData(*hTest, (DWORD)(*iter));
									//m_Tree->Expand(*hTest, TVE_EXPAND);
									TreeControlsList->push_back(hTest);
									delete[] subBuf;

								}
							}
							checkList->push_back((*it));
							delete[] buf;
						}
					
				}
			}
		}
		// $$$ Eventually, I made your loop above using reverse iterator, because you yet need to process first element too)
		// EDIT: I reconsider my descision =D
		if (count != suiteColl->size())
		{
			std::list<Suite*>::iterator helper = std::find(checkList->begin(), checkList->end(), *it);
			if (helper == checkList->end())
			{
				
				if (strlen((*it)->get_path()) != strlen(rootPath))
				{
					if (!strncmp(rootPath, (*it)->get_path(), strlen(rootPath)))
					{
						if (checkDiff(strlen(rootPath), (*it)->get_path()))
							TreeParse(it, suiteColl, m_Tree, count, hSuite, checkList, TreeControlsList);
					}
				}
				else
				{
					
						if (!strncmp(rootPath, (*it)->get_path(), strlen(rootPath)) && !strncmp((*it)->getName(), rootName, strlen(rootName)))
						{
							TCHAR* buf = new TCHAR[strlen((*it)->getName()) + 1];
							convertToTCHAR(buf, (*it)->getName());
							*hSuite = m_Tree->InsertItem(buf,0,0, *hHead);
							//m_Tree->Expand(*hSuite, TVE_EXPAND);
							++count;
							
							std::list<TRSTest*>::iterator iter = (*it)->getList().begin();
							for (iter; iter != (*it)->getList().end(); ++iter)
							{
								if (tag)
								{
									if (!strncmp(tag, (*iter)->getTag(), strlen(tag)))
									{
										HTREEITEM* hTest = new HTREEITEM;
										TCHAR* subBuf = new TCHAR[strlen((*iter)->getName()) + 1];
										convertToTCHAR(subBuf, (*iter)->getName());
										if (!strncmp((*iter)->getDisable(), "false", strlen("false")))
											*hTest = m_Tree->InsertItem(subBuf, 3, 3, *hSuite);
										if (!strncmp((*iter)->getDisable(), "true", strlen("true")))
											*hTest = m_Tree->InsertItem(subBuf, 12, 12, *hSuite);
										m_Tree->SetItemData(*hTest, (DWORD)(*iter));
										//m_Tree->Expand(*hTest, TVE_EXPAND);
										TreeControlsList->push_back(hTest);
										delete[] subBuf;
									}
								}
								else
								{
									HTREEITEM* hTest = new HTREEITEM;
									TCHAR* subBuf = new TCHAR[strlen((*iter)->getName()) + 1];
									convertToTCHAR(subBuf, (*iter)->getName());
									if (!strncmp((*iter)->getDisable(), "false", strlen("false")))
										*hTest = m_Tree->InsertItem(subBuf, 3, 3, *hSuite);
									if (!strncmp((*iter)->getDisable(), "true", strlen("true")))
										*hTest = m_Tree->InsertItem(subBuf, 12, 12, *hSuite);
									m_Tree->SetItemData(*hTest, (DWORD)(*iter));
									//m_Tree->Expand(*hTest, TVE_EXPAND);
									TreeControlsList->push_back(hTest);
									delete[] subBuf;
								}
							}
							checkList->push_back((*it));
							delete[] buf;
						}
					}
				
			}
		}
		it = itHelp;
		delete hSuite;
		delete[] rootName;
		delete[] rootPath;
	}
	TREE = TreeControlsList;
}

void ExpandTree(CTreeCtrl& m_Tree, HTREEITEM& hHead)
{
	for (HTREEITEM hNext = m_Tree.GetChildItem(hHead); hNext != 0; hNext = m_Tree.GetNextItem(hNext, TVGN_NEXT))
	{
		m_Tree.Expand(hNext, TVE_EXPAND);
		ExpandTree(m_Tree, hNext);
	}
}

std::vector<HTREEITEM*> CMFCTRSuiDlg::Info(TCHAR* path)
{
	
	TagColl.clear();
	NameColl.clear();
	DropDown.ResetContent();
	DropDown.AddString(L"All");
	DropDown.SetCurSel(0);
	m_NameBox.ResetContent();
	m_NameBox.AddString(L"All");
	m_NameBox.SetCurSel(0);

	char* pathA = nullptr;
	int size = WideCharToMultiByte(CP_ACP, 0, path, -1, pathA, 0, NULL, NULL);
	pathA = new char[size];
	WideCharToMultiByte(CP_ACP, 0, path, -1, pathA, size, NULL, NULL);
	HIMAGELIST imList=0;
	int Flag = ILC_COLOR24;
	imList = ImageList_Create(5, 5, Flag, 2, 0);
	CString mes(path);
	
	std::map<CString, std::vector<HTREEITEM*>>::iterator iter = mapOfColls.find(mes);
		std::vector<HTREEITEM*> TreeControlsList;
		suiteColl = Manager.List(pathA, nullptr, nullptr);
		HTREEITEM hHead;
		hHead = m_Tree.InsertItem(path, 0, 0, TVI_ROOT);
		int count = 0;
		std::list<Suite*>::iterator it = suiteColl->begin();
		count = strlen((*it)->get_path());
		for (it; it != suiteColl->end(); ++it)
		{
			if (strlen((*it)->get_path()) < count)
			{
				count = strlen((*it)->get_path());
			}
		}
		--it;
		int lic = 0;
		std::list<Suite*> checkList;
		for (it; it != suiteColl->begin(); --it)
		{
			if (strlen((*it)->get_path()) == count)
			{
				TreeParse(it, suiteColl, &m_Tree, lic, &hHead, &checkList, &TreeControlsList);
			}
		}
		if (strlen((*it)->get_path()) == count)
		{
			TreeParse(it, suiteColl, &m_Tree, lic, &hHead, &checkList, &TreeControlsList);
		}
		for (it; it != suiteColl->end(); ++it)
		{
			std::list<TRSTest*>::iterator iter = (*it)->getList().begin();

			for (iter; iter != (*it)->getList().end(); ++iter)
			{
				std::vector<char*>::iterator iterator = TagColl.begin();
				if (TagColl.size() == 0)
				{
					if ((*iter)->getTag())
					{
						TagColl.push_back((*iter)->getTag());
					}
				}
				else
				{
					bool check = false;
					for (iterator; iterator != TagColl.end(); ++iterator)
					{
						if (!strncmp(*iterator, (*iter)->getTag(), strlen((*iter)->getTag())))
						{
							check = true;
							break;
						}

					}
					if (!check)
					{
						TagColl.push_back((*iter)->getTag());
					}
				}
				std::vector<char*>::iterator Nameit = NameColl.begin();
				if (NameColl.size() == 0)
				{
					if ((*iter)->getName())
					{
						NameColl.push_back((*iter)->getName());
					}
				}
				else
				{
					bool checkSecond = false;
					for (Nameit; Nameit != NameColl.end(); ++Nameit)
					{
						if (!strncmp(*Nameit, (*iter)->getName(), strlen((*iter)->getName())))
						{
							checkSecond = true;
							break;
						}

					}
					if (!checkSecond)
					{
						NameColl.push_back((*iter)->getName());
					}
				}
			}

		}
		for (int i = 0; i < TagColl.size(); ++i)
		{
			TCHAR*buf = new TCHAR[strlen(TagColl[i]) + 1];
			convertToTCHAR(buf, TagColl[i]);
			DropDown.AddString(buf);
			delete[] buf;
		}
		for (int i = 0; i < NameColl.size(); ++i)
		{
			TCHAR*buf = new TCHAR[strlen(NameColl[i]) + 1];
			convertToTCHAR(buf, NameColl[i]);
			m_NameBox.AddString(buf);
			delete[] buf;
		}
		delete[] pathA;
		m_Tree.Expand(hHead, TVE_EXPAND);
		ExpandTree(m_Tree, hHead);
		if (iter != mapOfColls.end())
		{
			CString mes(path);
			std::map<CString, std::vector<TRSInfo>>::iterator Fiter = FailMap.find(mes);
			std::map<CString, std::vector<TRSInfo>>::iterator Piter = PasMap.find(mes);
			if (Fiter != FailMap.end() && Piter != PasMap.end())
			{
				for (int i = 0; i < TreeControlsList.size(); ++i)
				{
					for (int j = 0; j < Fiter->second.size(); ++j)
					{
						TRSInfo* cur = (TRSInfo*)m_Tree.GetItemData(*TreeControlsList[i]);
						if (cur)
						{
							if (*cur == Fiter->second[j])
							{
								m_Tree.SetItemImage(*TreeControlsList[i], 9, 9);
							}
						}
					}
					for (int j = 0; j < Piter->second.size(); ++j)
					{
						TRSInfo* cur = (TRSInfo*)m_Tree.GetItemData(*TreeControlsList[i]);
						if (cur)
						{
							if (*cur == Piter->second[j])
							{
								m_Tree.SetItemImage(*TreeControlsList[i], 6, 6);
							}
						}
					}
				}
			}
		}
		mapOfColls.insert(std::pair<CString,std::vector<HTREEITEM*>>(mes, TreeControlsList));
		return TreeControlsList;

		
	
	// ! expanding tree
	
}



void CMFCTRSuiDlg::OnEnChangeEdit3()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CMFCTRSuiDlg::OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

#pragma endregion stuff


void CMFCTRSuiDlg::OnSize(UINT nType, int cxx, int cyy)
{
	CRect new_rect;
	this->GetWindowRect(&new_rect);
	ScreenToClient(&new_rect);
//	if (!validate(nType, cxx, cyy)) return;
	long left_diff = new_rect.left - old_rect.left;
	long right_diff = new_rect.right - old_rect.right;
	long bottom_diff = new_rect.bottom - old_rect.bottom;
	long top_diff = new_rect.top - old_rect.top;

	long width_diff = left_diff + right_diff;
	long height_diff = bottom_diff + top_diff;

	CRect frame;
	long new_x;
	long new_y;
	long new_height;
	long new_width;
	if (::IsWindow(RootList.m_hWnd))
	{
		RootList.GetWindowRect(&frame);
		ScreenToClient(&frame);
		new_x = frame.left + left_diff;
		new_y = frame.top + top_diff;

		new_width = frame.Width() + width_diff/2;
		new_height = frame.Height() + height_diff;
		RootList.MoveWindow(new_x, new_y, new_width, new_height);
	}

	if (::IsWindow(m_Tree.m_hWnd))
	{
		m_Tree.GetWindowRect(&frame);
		ScreenToClient(&frame);
		new_x = frame.left + left_diff + width_diff / 2;
		new_y = frame.top + top_diff;
		
		new_width = frame.Width() + width_diff - width_diff / 2;
		new_height = frame.Height() + height_diff;

		m_Tree.MoveWindow(new_x, new_y, new_width, new_height);
	}

	if (::IsWindow(console_output.m_hWnd))
	{
		console_output.GetWindowRect(&frame);
		ScreenToClient(&frame);
		new_x = frame.left + left_diff;
		new_y = frame.top + height_diff;

		new_width = frame.Width() + width_diff;
		new_height = frame.Height();

		console_output.MoveWindow(new_x, new_y, new_width, new_height);
		
		if (console_output.IsWindowVisible())
			ConsoleShow();
	}

	if (::IsWindow(subm_Progress.m_hWnd))
	{
		subm_Progress.GetWindowRect(&frame);
		ScreenToClient(&frame);
		new_x = frame.left + left_diff;
		new_y = frame.top + height_diff;

		new_width = frame.Width() + width_diff ;

		subm_Progress.MoveWindow(new_x, new_y, new_width, frame.Height());
	}

	if (::IsWindow(m_Progress.m_hWnd))
	{
		m_Progress.GetWindowRect(&frame);
		ScreenToClient(&frame);
		new_x = frame.left + left_diff;
		new_y = frame.top + height_diff;

		new_width = frame.Width() + width_diff;

		m_Progress.MoveWindow(new_x, new_y, new_width, frame.Height());
	}

	if (::IsWindow(Time_running_edit.m_hWnd))
	{
		Time_running_edit.GetWindowRect(&frame);
		ScreenToClient(&frame);
		new_x = frame.left + left_diff;
		new_y = frame.top + height_diff;

		Time_running_edit.MoveWindow(new_x, new_y, frame.Width(), frame.Height());
	}

	old_rect = new_rect;
}


void CMFCTRSuiDlg::OnGetMinMaxInfo(MINMAXINFO *mx)
{
	mx->ptMinTrackSize.x = 770;
	mx->ptMinTrackSize.y = 500;
	CDialogEx::OnGetMinMaxInfo(mx);
}

void CMFCTRSuiDlg::OnLoadProject()
{
	UpdateToolbar(PROJECT_NOTLOADED);
	if (pro_.getName() && pro_.getPath())
	{
		char* path = pro_.getProjPath();
		if (!CheckForModification(path, pro_.getName(), List, Tag, Threads, Name,console_output.IsWindowVisible()))
		{
			int res = MessageBox(_T("Do you want to save current project?"), _T("Not saved"), MB_ICONINFORMATION | MB_YESNO);
			if (res == IDYES)
			{
				pro_.SaveProject(List);
				MessageBox(_T("Project was saved"), _T("Info"), MB_ICONINFORMATION | MB_OK);
			}
		}
		delete[] path;
	}
	CString filePath;
	CFileDialog dlgFile(TRUE);
	OPENFILENAME& ofn = dlgFile.GetOFN();
	wchar_t* p = filePath.GetBuffer(260);
	ofn.lpstrFile = p;
	Bar = ToolBar;
	List = &RootList;
	dlgFile.DoModal();
	char* path = convertToChar(p);
	if (ValidateProjXML(path))
	{
//		RootList.ResetContent();
		TiXmlDocument doc(path);
		doc.LoadFile();
		TiXmlNode* first = doc.FirstChild();
		while (first->Type() != TiXmlNode::TINYXML_ELEMENT)
		{
			first = first->NextSibling();
		}
		if (!strncmp(first->Value(), "TRSProject", strlen(first->Value())))
		{
			TiXmlAttribute* atr = first->ToElement()->FirstAttribute();
			pro_.setName(atr->Value());
			char* proPath = new char[strlen(path) - strlen(pro_.getName()) - 3];
			strncpy_s(proPath, strlen(path) - strlen(pro_.getName()) - 3, path, strlen(path) - strlen(pro_.getName()) - 4);
			pro_.setPath(proPath);
			delete[] proPath;
			TiXmlNode* head = first->FirstChild();
			for (head; head != 0; head = head->NextSibling())
			{
				if (!strncmp(head->Value(), "path", strlen(head->Value())))
				{
					TiXmlNode* text = head->FirstChild();
					while (text->Type() != TiXmlNode::TINYXML_TEXT)
					{
						text = text->NextSibling();
					}
					TCHAR* buf = new TCHAR[strlen(text->Value() + 1)];
					convertToTCHAR(buf, text->Value());
					RootList.InsertItem(RootList.GetItemCount(), buf);
				}
				if (!strncmp(head->Value(), "ListSelection", strlen("ListSelection")))
				{
					TiXmlNode* subList = head->FirstChild();
					dRoots.clear();

					for (subList; subList != 0; subList = subList->NextSibling())
					{
						TiXmlNode* node = subList->FirstChild();

						//??????????????????????????????????????????????????????????????????????????????????????????
						List->SetCheck(atoi(node->Value()));
					//	dRoots.push_back(atoi(node->Value()));
						//??????????????????????????????????????????????????????????????????????????????????????????
					}
					//CMFCTRSuiDlg::OnLbnSelchangeListroot();

				}
				int count = 0;
				for (int i = 0; i < List->GetItemCount(); ++i)
					count += List->GetCheck(i);
				if (!strncmp(head->Value(), "tag", strlen("tag"))&&count)
				{
					TiXmlNode* node = head->FirstChild();
					DropDown.SetCurSel(atoi(node->Value()));
					CMFCTRSuiDlg::OnCbnSelchangeCombo1();
				}
				if (!strncmp(head->Value(), "threads", strlen("threads")))
				{
					TiXmlNode* node = head->FirstChild();
					ThreadsComboBox.SetCurSel(atoi(node->Value()));
					CMFCTRSuiDlg::OnCbnSelchangeCombo2();
				}
				if (!strncmp(head->Value(), "testName", strlen("testName")))
				{
					TiXmlNode* node = head->FirstChild();
					m_NameBox.SetCurSel(atoi(node->Value()));
					CMFCTRSuiDlg::OnCbnSelchangeCombo3();
				}
				if (!strncmp(head->Value(), "console", strlen("console")))
				{
					TiXmlNode* node = head->FirstChild();
					if (!strncmp(node->Value(), "visible", strlen("visible")))
					{
						console_output.ShowWindow(true);
						CMFCTRSuiDlg::ConsoleShow();
					}
					else
					{
						console_output.ShowWindow(false);
						CMFCTRSuiDlg::ConsoleHide();
					}
				}
			}
		}
		
		UpdateToolbar(PROJECT_UPLOADED);
		DropDown.EnableWindow(true);
		ThreadsComboBox.EnableWindow(true);
		m_NameBox.EnableWindow(true);
		RootList.SetItemState(0, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
		RootList.SetSelectionMark(0);
		RootList.RedrawItems(0, 0);
		RootList.UpdateWindow();
	}
	else
	{
		MessageBox(_T("Current project file is invalid!"), _T("Erorr"), MB_ICONERROR | MB_OK);
	}
	// TODO: Add your command handler code here
}

void CMFCTRSuiDlg::OnProjectLastprojects()
{
	if (pro_.getName() && pro_.getPath())
	{
		char* path = pro_.getProjPath();
		if (!CheckForModification(path, pro_.getName(), List, Tag, Threads, Name, console_output.IsWindowVisible()))
		{
			int res = MessageBox(_T("Do you want to save current project?"), _T("Not saved"), MB_ICONINFORMATION | MB_YESNO);
			if (res == IDYES)
			{
				pro_.SaveProject(List);
				MessageBox(_T("Project was saved"), _T("Info"), MB_ICONINFORMATION | MB_OK);
			}
		}
		delete[] path;
	}
	m_Menu->EnableMenuItem(ID_Save_Project, MF_BYCOMMAND | MF_ENABLED);
	m_Menu->EnableMenuItem(ID_Save_AS, MF_BYCOMMAND | MF_ENABLED);
	m_ToolBar.GetToolBarCtrl().HideButton(TOOLBAR_ADDGREY);
	m_ToolBar.GetToolBarCtrl().HideButton(TOOLBAR_ADD, false);
//	RootList.ResetContent();
	
	TiXmlDocument doc("Last Project.xml");
	doc.LoadFile();
	TiXmlNode* first = doc.FirstChild();
	while (first->Type() != TiXmlNode::TINYXML_ELEMENT)
	{
		first = first->NextSibling();
	}
	if (!strncmp(first->Value(), "TRSProject", strlen(first->Value())))
	{
		TiXmlAttribute* atr = first->ToElement()->FirstAttribute();
		pro_.setName(atr->Value());
		
		atr = atr->Next();
		pro_.setPath(atr->Value());
		
		TiXmlNode* head = first->FirstChild();
		for (head; head != 0; head = head->NextSibling())
		{
			if (!strncmp(head->Value(), "path", strlen(head->Value())))
			{
				TiXmlNode* text = head->FirstChild();
				while (text->Type() != TiXmlNode::TINYXML_TEXT)
				{
					text = text->NextSibling();
				}
				TCHAR* buf = new TCHAR[strlen(text->Value() + 1)];
				convertToTCHAR(buf, text->Value());
				RootList.InsertItem(RootList.GetItemCount(), buf);
			}
			if (!strncmp(head->Value(), "ListSelection", strlen("ListSelection")))
			{
				TiXmlNode* subList = head->FirstChild();
				dRoots.clear();
				for (subList; subList != 0; subList = subList->NextSibling())
				{
					TiXmlNode* node = subList->FirstChild();
					// ???????????????????????????????????????????????????????????????????????????
					List->SetCheck(atoi(node->Value()));
					// ???????????????????????????????????????????????????????????????????????????
		//			dRoots.push_back(atoi(node->Value()));
				}
	//			CMFCTRSuiDlg::OnLbnSelchangeListroot();
			}
			int count = 0;
			for (int i = 0; i < List->GetItemCount(); ++i)
				count += List->GetCheck(i);
			if (!strncmp(head->Value(), "tag", strlen("tag")) && count)
			{
				TiXmlNode* node = head->FirstChild();
				DropDown.SetCurSel(atoi(node->Value()));
				CMFCTRSuiDlg::OnCbnSelchangeCombo1();
			}
			if (!strncmp(head->Value(), "threads", strlen("threads")))
			{
				TiXmlNode* node = head->FirstChild();
				ThreadsComboBox.SetCurSel(atoi(node->Value()));
				CMFCTRSuiDlg::OnCbnSelchangeCombo2();
			}
			if (!strncmp(head->Value(), "testName", strlen("testName")))
			{
				TiXmlNode* node = head->FirstChild();
				m_NameBox.SetCurSel(atoi(node->Value()));
				CMFCTRSuiDlg::OnCbnSelchangeCombo3();
			}
			if (!strncmp(head->Value(), "console", strlen("console")))
			{
				TiXmlNode* node = head->FirstChild();
				if (!strncmp(node->Value(), "visible", strlen("visible")))
				{
					console_output.ShowWindow(true);
					CMFCTRSuiDlg::ConsoleShow();
				}
				else
				{
					console_output.ShowWindow(false);
					CMFCTRSuiDlg::ConsoleHide();
				}
			}
		}

	}
	DropDown.EnableWindow(true);
	ThreadsComboBox.EnableWindow(true);
	m_NameBox.EnableWindow(true);
	Bar = ToolBar;
	List = &RootList;
	// TODO: Add your command handler code here
}

void CMFCTRSuiDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if (nID == SC_CLOSE)
	{


		// Note: This is an example GUID only and should not be used.
		// Normally, you should use a GUID-generating tool to provide the value to
		// assign to guidItem.
		Shell_NotifyIcon(NIM_DELETE, &nid);
		nid = {};
		nid.cbSize = sizeof(nid);

		nid.hWnd = m_hWnd;
		nid.uFlags = NIF_ICON | NIF_TIP | NIF_GUID | NIF_INFO | NIF_MESSAGE | NIF_SHOWTIP;
		nid.uCallbackMessage = MYWM_NOTIFYICON;
		nid.uVersion = NOTIFYICON_VERSION_4;

		static GUID myGuid;
		CoCreateGuid(&myGuid);
		nid.guidItem = myGuid;
		// This text will be shown as the icon's tooltip.
		StringCchCopy(nid.szTip, ARRAYSIZE(nid.szTip), L"Test managment");
		StringCchCopy(nid.szInfo, ARRAYSIZE(nid.szInfo), L"I am here");
		// Load the icon for high DPI.
		LoadIconMetric(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON2), LIM_SMALL, &(nid.hIcon));

		// Show the notification.


		Shell_NotifyIcon(NIM_ADD, &nid);
		Shell_NotifyIcon(NIM_SETVERSION, &nid);
		ShowWindow(SW_HIDE); // hide the window
		long style = GetWindowLong(m_hWnd, GWL_STYLE);
		SetWindowLong(m_hWnd, GWL_STYLE, style); // set the style
		ShowWindow(SW_SHOW); // show the window for the new style to come into effect
		ShowWindow(SW_HIDE); // hide the window so we can't see it


		/*BOOL bRet;

		WNDCLASSEX wnd = { 0 };

		wnd.hInstance = GetModuleHandle(NULL);
		wnd.lpszClassName = L"CMFCTRSuiDlg";
		wnd.lpfnWndProc = WindowProcedure;
		wnd.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
		wnd.cbSize = sizeof (WNDCLASSEX);

		wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wnd.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
		wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
		wnd.hbrBackground = (HBRUSH)COLOR_APPWORKSPACE;

		if (!RegisterClassEx(&wnd))
		{
		FatalAppExit(0, TEXT("Couldn't register window class!"));
		}


		*/
		
		/*while ((bRet = GetMessage(&msg, m_hWnd, 0, 0)) != 0)
		{
		if (bRet == -1)
		{
		// handle the error and possibly exit
		}
		else
		{

		TranslateMessage(&msg);
		DispatchMessage(&msg);
		switch (msg.message)
		{
		case MYWM_NOTIFYICON:
		MessageBox(_T("TTTTT"), _T("idsbv"), MB_OK);
		break;
		}
		}
		}*/
		//CWnd::OnSysCommand(nID, lParam);
		/*SetWindowLong(m_hWnd, GWL_EXSTYLE,
			GetWindowLong(m_hWnd, GWL_EXSTYLE) | WS_EX_APPWINDOW);
			long style = GetWindowLong(m_hWnd, GWL_STYLE);
			style &= ~(WS_VISIBLE);    // this works - window become invisible

			style |= WS_EX_TOOLWINDOW;   // flags don't work - windows remains in taskbar
			style &= ~(WS_EX_APPWINDOW);

			ShowWindow(SW_HIDE); // hide the window
			SetWindowLong(m_hWnd, GWL_STYLE, style); // set the style
			ShowWindow(SW_SHOW); // show the window for the new style to come into effect
			ShowWindow(SW_HIDE); // hide the window so we can't see it


			}*/

		}

	
	else
	{
		CWnd::OnSysCommand(nID, lParam);
	}
	
	
	
}

void CMFCTRSuiDlg::OnViewConsole()
{
	if (console_output.IsWindowVisible())
	{
		ConsoleHide();
		pro_.setConsole(false);
	}
	else
	{
		ConsoleShow();
		pro_.setConsole(true);
	}
}

void CMFCTRSuiDlg::ConsoleHide()
{
	console_output.ShowWindow(false);
	CRect console_rect;
	console_output.GetWindowRect(&console_rect);
	ScreenToClient(&console_rect);

	CRect list_rect;
	RootList.GetWindowRect(&list_rect);
	ScreenToClient(&list_rect);

	RootList.MoveWindow(list_rect.left, list_rect.top, list_rect.Width(), console_rect.bottom - list_rect.top);

	CRect tree_rect;
	m_Tree.GetWindowRect(&tree_rect);
	ScreenToClient(&tree_rect);

	m_Tree.MoveWindow(tree_rect.left, tree_rect.top, tree_rect.Width(), console_rect.bottom - tree_rect.top);
}

void CMFCTRSuiDlg::ConsoleShow()
{
	CRect console_rect;
	console_output.GetWindowRect(&console_rect);
	ScreenToClient(&console_rect);

	CRect list_rect;
	RootList.GetWindowRect(&list_rect);
	ScreenToClient(&list_rect);

	RootList.MoveWindow(list_rect.left, list_rect.top, list_rect.Width(), console_rect.top - list_rect.top - SPACE_BETWEEN_CONTROLERS);

	CRect tree_rect;
	m_Tree.GetWindowRect(&tree_rect);
	ScreenToClient(&tree_rect);

	m_Tree.MoveWindow(tree_rect.left, tree_rect.top, tree_rect.Width(), console_rect.top - tree_rect.top - SPACE_BETWEEN_CONTROLERS);

	console_output.ShowWindow(true);
}

void CMFCTRSuiDlg::RunToolsHide()
{
	m_Progress.ShowWindow(false);
	subm_Progress.ShowWindow(false);
	Time_running_edit.ShowWindow(false);

	CRect lowest_run_tool;
	m_Progress.GetWindowRect(&lowest_run_tool);
	ScreenToClient(&lowest_run_tool);

	CWnd* windows[CONTROL_AMOUNT - RUN_CONTROL_AMOUNT];

	windows[0] = &RootList;
	windows[1] = &m_Tree;
	windows[2] = &console_output;

	CRect control;
	for (int i = 0; i < CONTROL_AMOUNT - RUN_CONTROL_AMOUNT; ++i)
	{
		windows[i]->GetWindowRect(&control);
		ScreenToClient(&control);

		if (i == CONTROL_AMOUNT - RUN_CONTROL_AMOUNT - 1)
		{
			windows[i]->MoveWindow(control.left, control.top + (lowest_run_tool.bottom - control.bottom), control.Width(), control.Height());
			break;
		}

		windows[i]->MoveWindow(control.left, control.top, control.Width(), lowest_run_tool.bottom - control.top);
	}
	// just a little magic :)
	console_output.IsWindowVisible() ? ConsoleShow() : ConsoleHide();
}

void CMFCTRSuiDlg::RunToolsShow()
{
	CRect higher_run_tool;
	subm_Progress.GetWindowRect(&higher_run_tool);
	ScreenToClient(&higher_run_tool);

	CRect lowest_run_tool;
	m_Progress.GetWindowRect(&lowest_run_tool);
	ScreenToClient(&lowest_run_tool);

	CWnd* windows[CONTROL_AMOUNT - RUN_CONTROL_AMOUNT];

	windows[0] = &RootList;
	windows[1] = &m_Tree;
	windows[2] = &console_output;

	CRect control;
	for (int i = 0; i < CONTROL_AMOUNT - RUN_CONTROL_AMOUNT; ++i)
	{
		windows[i]->GetWindowRect(control);
		ScreenToClient(control);

		if (i == CONTROL_AMOUNT - RUN_CONTROL_AMOUNT - 1)
		{
			windows[i]->MoveWindow(control.left, control.top - (lowest_run_tool.bottom - higher_run_tool.top) - SPACE_BETWEEN_CONTROLERS, control.Width(), control.Height());
			break;
		}

		int new_height = control.Height() - (lowest_run_tool.bottom - higher_run_tool.top) - SPACE_BETWEEN_CONTROLERS;
		windows[i]->MoveWindow(control.left, control.top, control.Width(), new_height);
	}

	m_Progress.ShowWindow(true);
	subm_Progress.ShowWindow(true);
	Time_running_edit.ShowWindow(true);
}


void CMFCTRSuiDlg::OnSaveAs()
{
	CString filePath;
	
	CFileDialog dlgFile(FALSE);
	dlgFile.m_ofn.lpstrTitle = L"Save XML File As";
	if (dlgFile.DoModal() == IDOK)
	{
		filePath = dlgFile.GetPathName();
		char* name = new char[filePath.GetLength()];
		char help = filePath[filePath.GetLength() - 1];
		int i = 0;
		while (help != '\\')
		{
			name[i] = help;
			++i;
			help = filePath[filePath.GetLength() - i - 1];
		}
		name[i] = '\0';
		for (int j = 0; j < strlen(name) / 2; ++j)
		{
			char time = name[j];
			name[j] = name[strlen(name) - j - 1];
			name[strlen(name) - j - 1] = time;
		}
		properties.setName(name);
		char* path = new char[filePath.GetLength()];
		for (int j = 0; j < filePath.GetLength() - strlen(name); ++j)
		{
			path[j] = help;
			help = filePath[filePath.GetLength() - j - strlen(name)-1];
		}
		path[filePath.GetLength() - strlen(name)] = help;
		path[filePath.GetLength() - strlen(name)+1 ] = '\0';
		for (int j = 0; j < strlen(path)/2; ++j)
		{
			char time = path[j];
			path[j] = path[strlen(path) - 1 - j];
			path[strlen(path) - 1 - j] = time;
		}
		properties.setPath(path);
		delete[] path;
		delete[] name;

		properties.SaveProject(&RootList);
		UpdateToolbar(PROJECT_UPLOADED);
	}
	SaveAsPressed = false;
	// TODO: Add your command handler code here
}


void CMFCTRSuiDlg::OnCbnSelchangeCombo1()
{
	int count = DropDown.GetCurSel();
	if (count > -1) // $$$ (count != CB_ERR) 
	{
		int lic = 2; // $$$ int digits_amount = 1; ( or simply digits )
		while (count /= 10)
		{
			++lic;
		}
		char* tag_ = new char[lic]; // $$$ char* tag = new char[digits + 1]; name tag_ with underscore is seems to belong to a class' data member
		sprintf_s(tag_, lic, "%d", DropDown.GetCurSel()); // $$$ digits + 1
		pro_.setTag(tag_);
		
		if (!ifFirstTimeRunned)
		{
			m_Tree.DeleteAllItems();
			// $$$ I deleted this: int amount = 0;

			// $$$ HTREEITEM hHead; I moved thise declarations closer to code where they are using
			// $$$ char* pathA = nullptr;
			
			// @ will hold value of the last checked list item
			int check = -1;
			for (int i = 0; i < RootList.GetItemCount(); ++i)
			{
				if (RootList.GetCheck(i))
				{
					check = i;
				}
			}

			if (check > -1 && suiteColl) // $$$ (check>-1&&suiteColl) - you did not make spaces between logical conditions and operators. It is really hard to read
			{
				CString str = RootList.GetItemText(check, 0);
				// $$$
				//std::vector<HTREEITEM*>::iterator iteratorr = TreeControlsList.begin();
				//for (iteratorr; iteratorr != TreeControlsList.end(); ++iteratorr)
				//{
				//	delete *iteratorr;
				//}
				//for (auto iterator = collOfColls[lastSelected].begin(); iterator != collOfColls[lastSelected].end(); ++iterator)
				//{
				//	delete *iterator;
				//}
				//collOfColls[lastSelected].clear();

				char* pathA = nullptr;// $$$ moved declaration there 
				int size = WideCharToMultiByte(CP_ACP, 0, (TCHAR*)str.GetString(), -1, pathA, 0, NULL, NULL);
				pathA = new char[size];
				WideCharToMultiByte(CP_ACP, 0, (TCHAR*)str.GetString(), -1, pathA, size, NULL, NULL);
				
				// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				// $$$ set Suite's path here
				HTREEITEM hHead = m_Tree.InsertItem(str.GetString(), 0, 0, TVI_ROOT);// $$$ moved declaration there
				// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

				// $$$ moved it lower : int count = 0;
				//CString TAG;
				//DropDown.GetLBText(atoi(tag_), TAG);
				//char* search = fromCStringToChar(TAG);

				// $$$
				if (suiteColl)
				{
					std::list<Suite*>::iterator Delit = suiteColl->begin();
					for (Delit; Delit != suiteColl->end(); ++Delit)
					{
						delete (*Delit);
					}
				}
				delete suiteColl;
				// ===============================================================================
				// $$$ you are constantly using code to delete pointed by container objects and then the container by itself
				// It will be greate to move all this repeated code into separete function 
				//for (auto iterator = suiteColl->begin(); iterator != suiteColl->end(); ++iterator)
				//{
				//	delete (*iterator);
				//}
				//delete suiteColl;
				// ===============================================================================

				CString TAG;
				DropDown.GetLBText(atoi(tag_), TAG);
				char* search = fromCStringToChar(TAG);

				// $$$ I commented you if-condition, because it will fail as soon as some tag will start with "All" substring
				//if (!strncmp(search, "All", strlen("All")))
				if (!strcmp(search, "All"))
				{
					suiteColl = Manager.List(pathA, nullptr, nullptr);
				}
				else
				{
					suiteColl = Manager.List(pathA, nullptr, search);
				}
				delete[] search;
				// $$$ your previous code is going to crash when Manager.List returns an empty list
				// so I reccomend to add here the check-statement

				//if (!suiteColl->size())
				//	return;


				// $$$ this algorithm is really unreadable and unsufficient. You wrote it with O(2n) time complexity
				// but with a price of one additional iterator

				std::list<Suite*>::iterator it = suiteColl->begin();
				//// $$$ I commented your declarition code of count variable but, as for me, you can freely use it
				//// there because variable with the same name exust in the higher scope, which you are not using anymore
 
				count = strlen((*it)->get_path()); 
				for (it; it != suiteColl->end(); ++it)
				{
					if (strlen((*it)->get_path()) < count)
					{
						count = strlen((*it)->get_path());
					}
				}
				--it;

				std::list<Suite*> checkList;
				int chtoeto = 0; // I really love you, man)) Perfect variable)
				for (it; it != suiteColl->begin(); --it)
				{
					if (strlen((*it)->get_path()) == count)
					{
						std::vector<HTREEITEM*> coll;
						TreeParse(it, suiteColl, &m_Tree, chtoeto, &hHead, &checkList, &coll);
						mapOfColls.insert(std::pair<CString,std::vector<HTREEITEM*>>(RootList.GetItemText(check, 0), coll));
					}
				}

				if (strlen((*it)->get_path()) == count)
				{
					std::vector<HTREEITEM*> coll;
					TreeParse(it, suiteColl, &m_Tree, chtoeto, &hHead, &checkList, &coll);
					mapOfColls.insert(std::pair<CString, std::vector<HTREEITEM*>>(RootList.GetItemText(check, 0), coll));
				}

				auto root_suite = suiteColl->begin();
				unsigned min_lenght = INT_MAX;

				for (auto suite = suiteColl->begin(); suite != suiteColl->end(); ++suite)
				{
					if (strlen((*suite)->get_path()) < min_lenght)
					{
						min_lenght = strlen((*suite)->get_path());
						root_suite = suite;
					}
				}
				// $$$ if you create both this variable only to force TreeParse run, it will be better to 
				// reconsider roles of TreeParse parameters and made some of them unnecessary
				//std::list<Suite*> checkList;
				//int chtoeto = 0;
				//TreeParse(root_suite, suiteColl, &m_Tree, chtoeto, &hHead, &checkList, &collOfColls[lastSelected]);
				
				delete[] tag_;
			}
		}

		ifFirstTimeRunned = false;
	}
	// TODO: Add your control notification handler code here
}


void CMFCTRSuiDlg::OnCbnSelchangeCombo2()
{
	int count = ThreadsComboBox.GetCurSel();
	if (count > -1) // $$$ (count != CB_ERR)
	{
		// $$$ the same suggestions as in OnCbnSelchangeCombo1 method
		int lic = 2;
		while (count /= 10)
		{
			++lic;
		}
		char* threads_ = new char[lic];
		sprintf_s(threads_, lic, "%d", ThreadsComboBox.GetCurSel());
		pro_.setThreads(threads_);
		delete[] threads_;
	}
	// TODO: Add your control notification handler code here
}


void CMFCTRSuiDlg::OnStopButtonClicked()
{
	Manager.Stop();
}

void CMFCTRSuiDlg::OnSaveProject()
{
	if (!(pro_.getName() && pro_.getPath()))
	{
		OnSaveAs();
	}
	else
	{
		pro_.SaveProject(List);
		UpdateToolbar(PROJECT_UPLOADED);
		MessageBox(_T("Project was saved"), _T(""), MB_ICONINFORMATION | MB_OK);
	}
}


void CMFCTRSuiDlg::OnCbnSelchangeCombo3()
{
	// $$$ the same suggestions as in OnCbnSelchangeCombo1 method
	int count = m_NameBox.GetCurSel();
	if (count > -1)
	{
		int lic = 2;
		while (count /= 10)
		{
			++lic;
		}
		char* name_ = new char[lic];
		sprintf_s(name_, lic, "%d", m_NameBox.GetCurSel());
		pro_.setTestName(name_);
		delete[] name_;
	}
	// TODO: Add your control notification handler code here
}


void CMFCTRSuiDlg::OnNewProject()
{
	int res=0;
	if (pro_.getName() && pro_.getPath())
	{
		char* path = pro_.getProjPath();
		if (!CheckForModification(path, pro_.getName(), List, Tag, Threads, Name, console_output.IsWindowVisible()))
		{
			res = MessageBox( _T("Do you want to save current project?"), _T("Not saved"), MB_ICONINFORMATION | MB_YESNOCANCEL);
			if (res == IDYES)
			{
				pro_.SaveProject(List);
				MessageBox( _T("Project was saved"), _T("Info"), MB_ICONINFORMATION | MB_OK);
			}
		}
		delete[] path;
		UpdateToolbar(PROJECT_NOTLOADED);
	}

	if (res != IDCANCEL)
	{
			ProjNameEdit NameDlg;
			int res = NameDlg.DoModal();
			if (res != IDOK)
				return;

			int size = strlen("Test manager : ");
			char* WindowLine = new char[size + strlen(pro_.getName()) + 1];
			strncpy_s(WindowLine, size + 1, "Test manager : ", size);
			strncpy_s(WindowLine + size, strlen(pro_.getName()) + 1, pro_.getName(), strlen(pro_.getName()));
			TCHAR* WinBuf = new TCHAR[strlen(WindowLine) + 1];
			convertToTCHAR(WinBuf, WindowLine);
			SetWindowText(WinBuf);
			delete[] WindowLine;
			delete[] WinBuf;

			UpdateToolbar(PROJECT_UPLOADED);
			DropDown.EnableWindow(true);
			ThreadsComboBox.EnableWindow(true);
			m_NameBox.EnableWindow(true);
	}
	// TODO: Add your command handler code here
}

BOOL CMFCTRSuiDlg::OnTtnNeedText(UINT id, NMHDR *pNMHDR, LRESULT *pResult)
{
	UNREFERENCED_PARAMETER(id);

	NMTTDISPINFO *pTTT = (NMTTDISPINFO *)pNMHDR;
	UINT_PTR nID = pNMHDR->idFrom;

	if (pNMHDR->code == TTN_NEEDTEXTW)
	{
		TOOLTIPTEXTW* ttext = (TOOLTIPTEXTW*)pNMHDR;
		CStringW sw;
		switch (nID)
		{
		case ID_New_Project:
		{
			sw = "New Project";
			lstrcpynW(ttext->szText, sw, sizeof(ttext->szText) / sizeof(wchar_t));
			break;
		}
		case ID_Load_Project:
		{
			sw = "Load Project";
			lstrcpynW(ttext->szText, sw, sizeof(ttext->szText) / sizeof(wchar_t));
			break;
		}
		case TOOLBAR_SAVE_GREY:
		case TOOLBAR_SAVE:
		{
								sw = "Save Project";
								lstrcpynW(ttext->szText, sw, sizeof(ttext->szText) / sizeof(wchar_t));
								break;
		}
		case TOOLBAR_SAVEAS_GREY:
		case TOOLBAR_SAVEAS:
		{
								sw = "Save As..";
								lstrcpynW(ttext->szText, sw, sizeof(ttext->szText) / sizeof(wchar_t));
								break;
		}
		case TOOLBAR_ADDGREY:
		case TOOLBAR_ADD:
		{
								sw = "Add Suite";
								lstrcpynW(ttext->szText, sw, sizeof(ttext->szText) / sizeof(wchar_t));
								break;
		}
		case TOOLBAR_DELETEGREY:
		case TOOLBAR_DELETE:
		{
								sw = "Delete Suite";
								lstrcpynW(ttext->szText, sw, sizeof(ttext->szText) / sizeof(wchar_t));
								break;
		}
		case TOOLBAR_RUNGREY:
		case TOOLBAR_RUN:
		{
								sw = "Run";
								lstrcpynW(ttext->szText, sw, sizeof(ttext->szText) / sizeof(wchar_t));
								break;
		}
		case TOOLBAR_STOP:
		{
								sw = "Stop";
								lstrcpynW(ttext->szText, sw, sizeof(ttext->szText) / sizeof(wchar_t));
								break;
		}
		case ID_VIEW_CONSOLE:
		{
								sw = "Show/Hide Console";
								lstrcpynW(ttext->szText, sw, sizeof(ttext->szText) / sizeof(wchar_t));
								break;
		}
		case TOOLBAR_SETTINGS:
		{
								sw = "Refresh";
								lstrcpynW(ttext->szText, sw, sizeof(ttext->szText) / sizeof(wchar_t));
								break;
		}
		default:
			break;
		}
	}
	else
	{
		TOOLTIPTEXTA* ttext = (TOOLTIPTEXTA*)pNMHDR;
		CStringA sa;
		switch (nID)
		{
		case ID_New_Project:
		{
							   sa = "New Project";
							   lstrcpynA(ttext->szText, sa, sizeof(ttext->szText));
							   break;
		}
		case ID_Load_Project:
		{
								sa = "Load Project";
								lstrcpynA(ttext->szText, sa, sizeof(ttext->szText));
								break;
		}
		case TOOLBAR_SAVE_GREY:
		case TOOLBAR_SAVE:
		{
							 sa = "Save Project";
							 lstrcpynA(ttext->szText, sa, sizeof(ttext->szText));
							 break;
		}
		case TOOLBAR_SAVEAS_GREY:
		case TOOLBAR_SAVEAS:
		{
							   sa = "Save As..";
							   lstrcpynA(ttext->szText, sa, sizeof(ttext->szText));
							   break;
		}
		case TOOLBAR_ADDGREY:
		case TOOLBAR_ADD:
		{
							sa = "Add Suite";
							lstrcpynA(ttext->szText, sa, sizeof(ttext->szText));
							break;
		}
		case TOOLBAR_DELETEGREY:
		case TOOLBAR_DELETE:
		{
							   sa = "Delete Suite";
							   lstrcpynA(ttext->szText, sa, sizeof(ttext->szText));
							   break;
		}
		case TOOLBAR_RUNGREY:
		case TOOLBAR_RUN:
		{
							sa = "Run";
							lstrcpynA(ttext->szText, sa, sizeof(ttext->szText));
							break;
		}
		case TOOLBAR_STOP:
		{
							 sa = "Stop";
							 lstrcpynA(ttext->szText, sa, sizeof(ttext->szText));
							 break;
		}
		case ID_VIEW_CONSOLE:
		{
								sa = "Show/Hide Console";
								lstrcpynA(ttext->szText, sa, sizeof(ttext->szText));
								break;
		}
		case TOOLBAR_SETTINGS:
		{
								 sa = "Refresh";
								 lstrcpynA(ttext->szText, sa, sizeof(ttext->szText));
								 break;
		}
		default:
			break;
		}
	}
	*pResult = 0;

	return true;
}
//char* path = fromCStringToChar(m_ListCtrl.GetItemText(pNMLV->iItem, 0));
void CMFCTRSuiDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW  pNMLV = reinterpret_cast<LPNMLISTVIEW >(pNMHDR);

	bool check = false;
	for (int i = 0; i < RootList.GetItemCount(); ++i)
	{
		if (RootList.GetCheck(i))
		{
			check = true;
			break;
		}
	}

	UINT state = pNMLV->uOldState ^ pNMLV->uNewState;
	if (pNMLV->uChanged & LVIF_STATE) // item state has been changed
	{
		switch (pNMLV->uNewState & LVIS_STATEIMAGEMASK)
		{
		case INDEXTOSTATEIMAGEMASK(BST_CHECKED + 1): // new state: checked
		{
			dRoots.push_back(pNMLV->iItem);

			// $$$ Where you add appropriate names and tags to the comboboxes?
			TagColl.clear();
			DropDown.ResetContent();
			DropDown.AddString(L"All");
			DropDown.SetCurSel(0);

			NameColl.clear();
			m_NameBox.ResetContent();
			m_NameBox.AddString(L"All");
			
			m_NameBox.SetCurSel(0);
			
			ThreadsComboBox.SetCurSel(9);
			lastSelected = pNMLV->iItem;

			CString str = RootList.GetItemText(pNMLV->iItem, 0);
			std::vector<HTREEITEM*> vec = Info((TCHAR*)str.GetString());


			mapOfColls.insert(std::pair<CString, std::vector<HTREEITEM*>>(RootList.GetItemText(pNMLV->iItem, 0), vec));
			std::map<CString, std::vector<HTREEITEM*>>::iterator iter = mapOfColls.find(RootList.GetItemText(pNMLV->iItem, 0));

			CMFCTRSuiDlg::OnCbnSelchangeCombo1();
			CMFCTRSuiDlg::OnCbnSelchangeCombo2();
			CMFCTRSuiDlg::OnCbnSelchangeCombo3();
			break;
		}
		case INDEXTOSTATEIMAGEMASK(BST_UNCHECKED + 1): // new state: unchecked
		{
			auto iter = std::find(dRoots.begin(), dRoots.end(), pNMLV->iItem);
			if (iter != dRoots.end())
			   dRoots.erase(iter);
			if (!check)
			{
				if (DropDown.GetCurSel() > 0)
				{
					DropDown.SetCurSel(-1);
					CMFCTRSuiDlg::OnCbnSelchangeCombo1();
				}
				if (m_NameBox.GetCurSel() > 0)
				{
					m_NameBox.SetCurSel(-1);
					CMFCTRSuiDlg::OnCbnSelchangeCombo2();
				}
				if (ThreadsComboBox.GetCurSel() > 0)
				{
					ThreadsComboBox.SetCurSel(-1);
					CMFCTRSuiDlg::OnCbnSelchangeCombo3();
				}
				ifFirstTimeRunned = true;
				for (int i = 0; i < RootList.GetItemCount(); ++i)
				{
					if (RootList.GetCheck(i))
					{
						lastSelected = i;
						std::map<CString,std::vector<HTREEITEM*>>::iterator iter=mapOfColls.find(RootList.GetItemText(i,0));
						TREE = &iter->second;
						break;
					}
				}
				ListSelection = pNMLV->iItem;
			}
			break;
		}
		default:
			m_Tree.DeleteAllItems();
			CString str;
			int res=pNMLV->iSubItem;
			str = RootList.GetItemText(pNMLV->iItem, 0);
			std::vector<HTREEITEM*> vec = Info((TCHAR*)str.GetString());
			
			
			mapOfColls.insert(std::pair<CString,std::vector<HTREEITEM*>>(RootList.GetItemText(pNMLV->iItem, 0), vec));
			std::map<CString, std::vector<HTREEITEM*>>::iterator iter = mapOfColls.find(RootList.GetItemText(pNMLV->iItem, 0));

			TREE = &iter->second;
			
			break;
		}
	}
	UpdateToolbar();
	*pResult = 0;
}


void CMFCTRSuiDlg::OnNMRClickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	CMenu *mnuPopupSubmit = new CMenu;
	mnuPopupSubmit->LoadMenu(IDR_MENU4);
	CMenu* nextMenu = mnuPopupSubmit->GetSubMenu(0);
	ASSERT(nextMenu);
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	HTREEITEM hTest = m_Tree.GetSelectedItem();
	std::map<CString, std::vector<HTREEITEM*>>::iterator iter = mapOfColls.find(RootList.GetItemText(lastSelected, 0));
	for (int i = 0; i < iter->second.size(); ++i)
	{
		if (*iter->second[i] == hTest)
		{
			TestForInfo = (TRSTest*)m_Tree.GetItemData(*iter->second[i]);
		}
	}
	POINT mousePos;
	GetCursorPos(&mousePos);
	nextMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, mousePos.x, mousePos.y, this);
	*pResult = 0;
}


void CMFCTRSuiDlg::OnInfoInfo()
{
	if (TestForInfo)
	{
		TestInfo dlg;
		dlg.DoModal();
		TestForInfo = nullptr;
	}
	else
	{
		MessageBox(L"Please, select test, not folder!", L"Info", MB_OK);
	}
	// TODO: Add your command handler code here
}

void CMFCTRSuiDlg::OnProgramRefresh()
{
	if (RootList.GetItemCount())
	{
		int index = -1;
		for (int i = 0; i < RootList.GetItemCount(); ++i)
		{
			if (RootList.GetItemState(i, LVIS_SELECTED))
			{
				index = i;
				break;
			}
		}
		if (index < 0)
			return;

		m_Tree.DeleteAllItems();

		CString str = RootList.GetItemText(index, 0);
		auto iterator = mapOfColls.find(str);
		if (iterator != mapOfColls.end())
		{
			for (int i = 0; i < iterator->second.size(); ++i)
			{
				delete[] iterator->second[i];
			}
			mapOfColls.erase(iterator);
		}
		for (auto iterator = suiteColl->begin(); iterator != suiteColl->end(); ++iterator)
		{
			delete (*iterator);
		}
		delete suiteColl;
		char* PA = fromCStringToChar(str);
		TCHAR* buf = new TCHAR[strlen(PA) + 1];
		convertToTCHAR(buf, PA);
		Info(buf);
		delete[] buf;
		delete[] PA;

		char path[MAX_PATH];
		WideCharToMultiByte(CP_ACP, 0, (TCHAR*)str.GetString(), -1, path, MAX_PATH, NULL, NULL);


		//HTREEITEM hHead = m_Tree.InsertItem(str.GetString(), 0, 0, TVI_ROOT);


		// ===============================================================================

	}
		
}

void CMFCTRSuiDlg::SetListItemImage(DWORD index, DWORD image)
{
	LVITEMW pitem{ LVIF_IMAGE };
	pitem.iItem = index;
	RootList.GetItem(&pitem);

	pitem.iImage = image;
	RootList.SetItem(&pitem);
}

void CMFCTRSuiDlg::OnExit()
{
	OnSysCommand(SC_CLOSE, NULL);
//	EndDialog(IDCANCEL);
}

// ======================================================================================================================
#include "AddClockDlg.h"
#include "ClockCollection.h"
#include "TestsTimerDialog.h"

// ======================================================================================================================

void CMFCTRSuiDlg::OnTest()
{
	//AddClockDlg dlg;
	std::vector<SuiteRoot> coll;
	std::vector<bool> is_check;
	is_check.resize(RootList.GetItemCount());
	for (int i = 0; i < RootList.GetItemCount(); ++i)
	{
		coll.push_back(SuiteRoot(RootList.GetItemText(i, 0)));
		is_check[i] = RootList.GetCheck(i);
	}
	TestsTimerDialog dlg;

	dlg.Init(coll, is_check, m_NameBox.GetCurSel(), DropDown.GetCurSel(), ThreadsComboBox.GetCurSel());

	if (dlg.DoModal() == IDOK)
	{
		
	}
}

void CMFCTRSuiDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnMouseMove(nFlags, point);
}


void CMFCTRSuiDlg::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnMouseHover(nFlags, point);
}


LRESULT CMFCTRSuiDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	switch (message)
	{
	case MYWM_NOTIFYICON:
		switch (lParam)
		{
		case WM_RBUTTONUP:
			CMenu *mnuPopupSubmit = new CMenu;
			mnuPopupSubmit->LoadMenu(IDR_MENU5);
			CMenu* nextMenu = mnuPopupSubmit->GetSubMenu(0);
			ASSERT(nextMenu); 
			POINT mousePos;
			GetCursorPos(&mousePos);
			nextMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, mousePos.x, mousePos.y, this); 
			break;
		}
	}
	return CDialogEx::WindowProc(message, wParam, lParam);
}


void CMFCTRSuiDlg::OnMenu()
{
	// TODO: Add your command handler code here
	
	ShowWindow(SW_HIDE); // hide the window
	long style = GetWindowLong(m_hWnd, GWL_STYLE);
	SetWindowLong(m_hWnd, GWL_STYLE, style); // set the style
	ShowWindow(SW_SHOW); // show the window for the new style to come into effect
	//ShowWindow(SW_HIDE); // hide the window so we can't see it
}


void CMFCTRSuiDlg::OnInfoClose()
{
	// TODO: Add your command handler code here
	if (RootList.GetItemCount() > 0)
	{
		char* path = pro_.getProjPath();
		if (path)
		{
			WIN32_FIND_DATA FindFileData;
			TCHAR* buf = new TCHAR[strlen(path) + 1];
			convertToTCHAR(buf, path);
			HANDLE handle = FindFirstFile(buf, &FindFileData);
			int found = handle != INVALID_HANDLE_VALUE;
			if (!found)
			{
				int res = MessageBox(_T("Save project ?"), _T("Save"), MB_ICONINFORMATION | MB_YESNOCANCEL);
				if (res == IDYES)
				{
					pro_.SaveProject(&RootList);
					delete[] path;
					delete[] buf;
					CDialogEx::OnOK();
				}
				if (res == IDNO)
				{
					delete[] path;
					delete[] buf;
					CDialogEx::OnOK();
				}
				if (res == IDCANCEL)
				{
					delete[] path;
					delete[] buf;
					return;
				}
			}
			else
			{

				if (!CheckForModification(path, pro_.getName(), &RootList, &DropDown, &ThreadsComboBox, &m_NameBox, console_output.IsWindowVisible()))
				{
					if (SaveAsPressed)
					{
						int res = MessageBox(_T("Save project ?"), _T("Save"), MB_ICONINFORMATION | MB_YESNOCANCEL);
						if (res == IDYES)
						{
							pro_.SaveProject(&RootList);
							delete[] path;
							delete[] buf;
							CDialogEx::OnOK();
						}
						if (res == IDNO)
						{
							delete[] path;
							delete[] buf;
							CDialogEx::OnOK();
						}
						if (res == IDCANCEL)
						{
							delete[] path;
							delete[] buf;
							return;
						}
					}
					else
					{
						delete[] path;
						delete[] buf;
						CDialogEx::OnOK();
					}
				}
				else
				{
					delete[] buf;
					delete[] path;
					CDialogEx::OnOK();
				}
			}
		}
	}
	else
	{
		CDialogEx::OnOK();
	}
}