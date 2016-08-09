
// MFCTRSuiDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCTRSui.h"
#include "MFCTRSuiDlg.h"
#include "afxdialogex.h"
#include <list>

#include "ConsoleReporter.h"
#include "TRSLibrary\TRSManager.h"
#include "ToRunParameters.h"
#include "RunParameters.h"
#include "Functionality.h"
#include <ctime>
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define RAW_RESIZIBLE 2
// CMFCTRSuiDlg dialog

bool ifCancelPressed;
bool RunEndCheck;
bool SaveAsPressed = true;
CToolBar* ToolBar;
CToolBar* Bar;
CComboBox* Tag;
CComboBox* Threads;
CComboBox* Name;
CMFCTRSuiDlg::CMFCTRSuiDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCTRSuiDlg::IDD, pParent)
	
{
	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	Manager.Init();
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
	ON_NOTIFY_EX(TTN_NEEDTEXTW, 0, &CMFCTRSuiDlg::OnTtnNeedText)
	
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CMFCTRSuiDlg::OnLvnItemchangedList1)
END_MESSAGE_MAP()


// CMFCTRSuiDlg message handlers

BOOL CMFCTRSuiDlg::OnInitDialog()
{

	CDialogEx::OnInitDialog();

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
	m_NameBox.AddString(L"All");
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	
	//SetIcon(m_hIcon, TRUE);			// Set big icon
	//SetIcon(m_hIcon, FALSE);		// Set small icon
	// TODO: Add extra initialization here
	//RootList.ResetContent();

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

		hIcon_1 = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON9));
		pList->Replace(4, hIcon_1); // not 5 as a separate is not an image
	
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

	CBitmap m_Bitmap1,m_Bitmap2;

	
	m_ImageList.Create(16, 16, ILC_COLORDDB , 2, 2);

	m_Bitmap1.LoadBitmap(IDB_BITMAP1);
	m_Bitmap2.LoadBitmap(IDB_BITMAP2);

	m_ImageList.Add(&m_Bitmap1, RGB(0,0,0));
	m_ImageList.Add(&m_Bitmap2, RGB(0, 0, 0));

	/*m_Tree.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP |
		TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT |
		TVS_SINGLEEXPAND | TVS_SHOWSELALWAYS |
		TVS_TRACKSELECT,
		CRect(10, 10, 200, 240), this, 0x1221);*/

	m_Tree.SetImageList(&m_ImageList, TVSIL_NORMAL);
	dRoots.clear();
	UpdateToolbar(PROJECT_NOTLOADED);

//	HICON icon;

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
	return TRUE;  // return TRUE  unless you set the focus to a control
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
	}

	if (mask & PROJECT_UPLOADED)
	{// mask = PROJECT_UPLOADED | ...
		m_ToolBar.GetToolBarCtrl().HideButton(TOOLBAR_SAVE, false);
		m_ToolBar.GetToolBarCtrl().HideButton(TOOLBAR_SAVEAS, false);
		m_ToolBar.GetToolBarCtrl().HideButton(TOOLBAR_ADD, false);

		m_ToolBar.GetToolBarCtrl().HideButton(TOOLBAR_ADDGREY);
		m_ToolBar.GetToolBarCtrl().HideButton(TOOLBAR_SAVE_GREY);
		m_ToolBar.GetToolBarCtrl().HideButton(TOOLBAR_SAVEAS_GREY);


		m_Menu->EnableMenuItem(TOOLBAR_SAVE, MF_BYCOMMAND | MF_ENABLED);
		m_Menu->EnableMenuItem(TOOLBAR_SAVEAS, MF_BYCOMMAND | MF_ENABLED);
	}
	else if (mask & PROJECT_NOTLOADED)
	{
		m_ToolBar.GetToolBarCtrl().HideButton(TOOLBAR_SAVE);
		m_ToolBar.GetToolBarCtrl().HideButton(TOOLBAR_SAVEAS);

		m_ToolBar.GetToolBarCtrl().HideButton(TOOLBAR_SAVE_GREY, false);
		m_ToolBar.GetToolBarCtrl().HideButton(TOOLBAR_SAVEAS_GREY, false);

		m_Menu->EnableMenuItem(TOOLBAR_SAVE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		m_Menu->EnableMenuItem(TOOLBAR_SAVEAS, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);

		m_secondToolBar.GetToolBarCtrl().HideButton(TOOLBAR_STOP);
		m_ToolBar.GetToolBarCtrl().HideButton(TOOLBAR_ADD);
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
		if (!Manager.Verify(pathA, nullptr, nullptr))
		{
			int index = RootList.InsertItem(RootList.GetItemCount(), path);
			if (index >= 0)
				RootList.SetCheck(index);
			else
				MessageBox(_T("Can not insert the item!"), _T("Error"), MB_ICONERROR | MB_OK);
		}
		else
		{
			MessageBox(_T("Current path is invalid!"), _T("Error"), MB_ICONERROR | MB_OK);
		}

		delete[] pathA;
		// free memory used
		IMalloc * imalloc = 0;
		m_Menu->EnableMenuItem(ID_Save_Project, MF_BYCOMMAND | MF_ENABLED);
		if (SUCCEEDED(SHGetMalloc(&imalloc)))
		{
			imalloc->Free(pidl);
			imalloc->Release();
		}
	}
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
	std::sort(dRoots.begin(), dRoots.end(), std::greater<int>());
	for (auto iter = dRoots.begin(); iter != dRoots.end(); ++iter)
	{
		RootList.DeleteItem(*iter);
	}
	UpdateToolbar();
	dRoots.clear();
}


void CMFCTRSuiDlg::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

DWORD WINAPI RunSuits(LPVOID arg)
{
	//RunParameters param;
	//param = *(RunParameters*)arg;
	//std::list<Suite*> coll = *Manager.List(param.path, param.name, param.tag);
	//int count = 0;
	//for each(auto it in coll)
	//{
	//	count += it->getList().size();
	//	for each(auto iter in it->getList())
	//	{
	//		if (iter->getRepeat())
	//		{
	//			count += atoi(iter->getRepeat());
	//			--count;
	//		}
	//	}
	//}
	//param.progress->SetRange(0, count);
	//param.progress->SetStep(1);
	//Manager.Run(param.path, param.name, param.tag, param.threads, param.reporter);
	return 0;
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
	for each(auto var in param->coll)
	{
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
	}
	param->manager->End();
	delete param->manager;
	param->dialog->UpdateToolbar(RUN_UNCLICKED);
	delete param;
	RunEndCheck = false;
	return 0;
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
	if (dRoots.size())
	{
		m_Progress.SetPos(0);

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

void TreeParse(std::list<Suite*>::iterator& it, std::list<Suite*>* suiteColl, CTreeCtrl* m_Tree, int& count, HTREEITEM* hHead,std::list<Suite*>* checkList)
{
	if (count != suiteColl->size())
	{
		char* rootPath = new char[strlen((*it)->get_path()) + 1];
		strncpy_s(rootPath, strlen((*it)->get_path()) + 1, (*it)->get_path(), strlen((*it)->get_path()));
		char* rootName = new char[strlen((*it)->getName()) + 1];
		strncpy_s(rootName, strlen((*it)->getName()) + 1, (*it)->getName(), strlen((*it)->getName()));
		HTREEITEM* hSuite=new HTREEITEM;
		std::list<Suite*>::iterator itHelp = it;
		for (it; it != suiteColl->end(); ++it)
		{
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
							TreeParse(it, suiteColl, m_Tree, count, hSuite, checkList);
					}

				}
				else
				{
					if (!strncmp(rootPath, (*it)->get_path(), strlen(rootPath)) && !strncmp((*it)->getName(), rootName, strlen(rootName)))
					{
						TCHAR* buf = new TCHAR[strlen((*it)->getName()) + 1];
						convertToTCHAR(buf, (*it)->getName());
						*hSuite = m_Tree->InsertItem(buf, 0,0,*hHead);
						++count;
						HTREEITEM hTest;
						std::list<TRSTest*>::iterator iter = (*it)->getList().begin();
						for (iter; iter != (*it)->getList().end(); ++iter)
						{
							TCHAR* subBuf = new TCHAR[strlen((*iter)->getName()) + 1];
							convertToTCHAR(subBuf, (*iter)->getName());
							m_Tree->InsertItem(subBuf, 3,3,*hSuite);
							delete[] subBuf;
						}
						checkList->push_back((*it));
						delete[] buf;
					}

				}
			}
		}
		--it;
		for (it; it != suiteColl->begin(); --it)
		{
			
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
						TreeParse(it, suiteColl, m_Tree, count, hSuite, checkList);
					}
					
				}
				else
				{
						if (!strncmp(rootPath, (*it)->get_path(), strlen(rootPath)) && !strncmp((*it)->getName(), rootName, strlen(rootName)))
						{
							TCHAR* buf = new TCHAR[strlen((*it)->getName()) + 1];
							convertToTCHAR(buf, (*it)->getName());
							*hSuite = m_Tree->InsertItem(buf, 0,0,*hHead);
							++count;
							HTREEITEM hTest;
							std::list<TRSTest*>::iterator iter = (*it)->getList().begin();
							for (iter; iter != (*it)->getList().end(); ++iter)
							{
								TCHAR* subBuf = new TCHAR[strlen((*iter)->getName()) + 1];
								convertToTCHAR(subBuf, (*iter)->getName());
								m_Tree->InsertItem(subBuf, 3,3,*hSuite);
								delete[] subBuf;
							}
							checkList->push_back((*it));
							delete[] buf;
						}
					
				}
			}
		}
		
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
						TreeParse(it, suiteColl, m_Tree, count, hSuite, checkList);
					}
				}
				else
				{
					
						if (!strncmp(rootPath, (*it)->get_path(), strlen(rootPath)) && !strncmp((*it)->getName(), rootName, strlen(rootName)))
						{
							TCHAR* buf = new TCHAR[strlen((*it)->getName()) + 1];
							convertToTCHAR(buf, (*it)->getName());
							*hSuite = m_Tree->InsertItem(buf,0,0, *hHead);
							++count;
							HTREEITEM hTest;
							std::list<TRSTest*>::iterator iter = (*it)->getList().begin();
							for (iter; iter != (*it)->getList().end(); ++iter)
							{
								TCHAR* subBuf = new TCHAR[strlen((*iter)->getName()) + 1];
								convertToTCHAR(subBuf, (*iter)->getName());
								m_Tree->InsertItem(subBuf, 3,3,*hSuite);
								delete[] subBuf;
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
}


void CMFCTRSuiDlg::Info(TCHAR* path)
{
	TagColl.clear();
	NameColl.clear();
	DropDown.ResetContent();
	DropDown.AddString(L"All");
	m_NameBox.ResetContent();
	m_NameBox.AddString(L"All");
	char* pathA = nullptr;
	int size = WideCharToMultiByte(CP_ACP, 0, path, -1, pathA, 0, NULL, NULL);
	pathA = new char[size];
	WideCharToMultiByte(CP_ACP, 0, path, -1, pathA, size, NULL, NULL);
	HIMAGELIST imList=0;
	int Flag = ILC_COLOR24;
	imList = ImageList_Create(5, 5, Flag, 2, 0);
	
	std::list<Suite*>* suiteColl = Manager.List(pathA, nullptr, nullptr);
	HTREEITEM hHead;
	hHead = m_Tree.InsertItem(L"Suites", 0,0,TVI_ROOT);
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
	for(it; it != suiteColl->begin(); --it)
	{
		if (strlen((*it)->get_path()) == count)
		{
			TreeParse(it, suiteColl, &m_Tree, lic, &hHead,&checkList);
		}
	}
	if (strlen((*it)->get_path()) == count)
	{
		TreeParse(it, suiteColl, &m_Tree, lic, &hHead, &checkList);
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
//						dRoots.push_back(atoi(node->Value()));
						//??????????????????????????????????????????????????????????????????????????????????????????
					}
				//	CMFCTRSuiDlg::OnLbnSelchangeListroot();

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
	Bar = ToolBar;
	List = &RootList;
	// TODO: Add your command handler code here
}

void CMFCTRSuiDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if (nID == SC_CLOSE)
	{
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
					int res = MessageBox(_T("Save project ?"), _T("Save"), MB_ICONINFORMATION | MB_YESNO);
					if (res == IDYES)
					{
						pro_.SaveProject(&RootList);
						delete[] path;
						delete[] buf;
						CDialogEx::OnOK();
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

					if (!CheckForModification(path, pro_.getName(), &RootList, &DropDown, &ThreadsComboBox, &m_NameBox, console_output.IsWindowVisible()))
					{
						if (SaveAsPressed)
						{
							int res = MessageBox(_T("Save project ?"), _T("Save"), MB_ICONINFORMATION | MB_YESNO);
							if (res == IDYES)
							{
								pro_.SaveProject(&RootList);
								delete[] path;
								delete[] buf;
								CDialogEx::OnOK();
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
	if (nID == SC_ZOOM)
	{

	}

	CWnd::OnSysCommand(nID, lParam);
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
	}
	SaveAsPressed = false;
	// TODO: Add your command handler code here
}


void CMFCTRSuiDlg::OnCbnSelchangeCombo1()
{
	int count = DropDown.GetCurSel();
	int lic = 2;
	while (count /= 10)
	{
		++lic;
	}
	char* tag_ = new char[lic];
	sprintf_s(tag_, lic,"%d", DropDown.GetCurSel());
	pro_.setTag(tag_);
	delete[] tag_;
	// TODO: Add your control notification handler code here
}


void CMFCTRSuiDlg::OnCbnSelchangeCombo2()
{
	int count = ThreadsComboBox.GetCurSel();
	int lic = 2;
	while (count /= 10)
	{
		++lic;
	}
	char* threads_ = new char[lic];
	sprintf_s(threads_, lic, "%d", ThreadsComboBox.GetCurSel());
	pro_.setThreads(threads_);
	delete[] threads_;
	// TODO: Add your control notification handler code here
}


void CMFCTRSuiDlg::OnStopButtonClicked()
{
	Manager.Stop();
}

void CMFCTRSuiDlg::OnCbnSelchangeCombo3()
{
	int count = m_NameBox.GetCurSel();
	int lic = 2;
	while (count /= 10)
	{
		++lic;
	}
	char* name_ = new char[lic];
	sprintf_s(name_, lic, "%d", m_NameBox.GetCurSel());
	pro_.setTestName(name_);
	delete[] name_;
	// TODO: Add your control notification handler code here
}


void CMFCTRSuiDlg::OnNewProject()
{
	
	if (pro_.getName() && pro_.getPath())
	{
		char* path = pro_.getProjPath();
		if (!CheckForModification(path, pro_.getName(), List, Tag, Threads, Name, console_output.IsWindowVisible()))
		{
			int res = MessageBox( _T("Do you want to save current project?"), _T("Not saved"), MB_ICONINFORMATION | MB_YESNO);
			if (res == IDYES)
			{
				pro_.SaveProject(List);
				MessageBox( _T("Project was saved"), _T("Info"), MB_ICONINFORMATION | MB_OK);
			}
		}
		delete[] path;
	}

	BROWSEINFO bi = { 0 };
	bi.lpszTitle = _T("Select Folder");
	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
	if (pidl != 0)
	{
		// get the name of the folder
		TCHAR path[MAX_PATH];
		SHGetPathFromIDList(pidl, path);
		char* pathA = convertToChar(path);
		pro_.setPath(pathA);
		ProjNameEdit NameDlg;
		int res = NameDlg.DoModal();
		if (res == IDOK)
		{
//			List->ResetContent();
			IMalloc * imalloc = 0;
			if (SUCCEEDED(SHGetMalloc(&imalloc)))
			{
				imalloc->Free(pidl);
				imalloc->Release();
			}
		}


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
								sw = "Add Folder";
								lstrcpynW(ttext->szText, sw, sizeof(ttext->szText) / sizeof(wchar_t));
								break;
		}
		case TOOLBAR_DELETEGREY:
		case TOOLBAR_DELETE:
		{
								sw = "Delete Folder";
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
								sw = "Settings";
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
							sa = "Add Folder";
							lstrcpynA(ttext->szText, sa, sizeof(ttext->szText));
							break;
		}
		case TOOLBAR_DELETEGREY:
		case TOOLBAR_DELETE:
		{
							   sa = "Delete Folder";
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
								 sa = "Settings";
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

	if (pNMLV->uChanged & LVIF_STATE) // item state has been changed
	{
		switch (pNMLV->uNewState & LVIS_STATEIMAGEMASK)
		{
		case INDEXTOSTATEIMAGEMASK(BST_CHECKED + 1): // new state: checked
		{
			dRoots.push_back(pNMLV->iItem);
			break;
		}
		case INDEXTOSTATEIMAGEMASK(BST_UNCHECKED + 1): // new state: unchecked
		{
			auto iter = std::find(dRoots.begin(), dRoots.end(), pNMLV->iItem);
			if (iter != dRoots.end())
			   dRoots.erase(iter);
			break;
		}
		default:
			m_Tree.DeleteAllItems();
			CString str = RootList.GetItemText(pNMLV->iItem, 0);
			Info((TCHAR*)str.GetString());
			break;
		}
	}
	UpdateToolbar();
	*pResult = 0;
}
