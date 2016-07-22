
// MFCTRSuiDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCTRSui.h"
#include "MFCTRSuiDlg.h"
#include "afxdialogex.h"
#include "ConsoleReporter.h"
#include "TRSLibrary\TRSManager.h"
#include <list>
#include "ToRunParameters.h"
#include "RunParameters.h"
#include "Functionality.h"
#include <ctime>
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCTRSuiDlg dialog


bool RunEndCheck;


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
	DDX_Control(pDX, IDC_ListRoot, RootList);
	DDX_Control(pDX, IDC_RunSelected, RunButton);
	DDX_Control(pDX, IDC_DeleteButton, DeleteButton);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
	DDX_Control(pDX, IDC_PROGRESS3, subm_Progress);
	DDX_Control(pDX, IDC_EDIT1, Time_running_edit);
}

BEGIN_MESSAGE_MAP(CMFCTRSuiDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CMFCTRSuiDlg::OnTvnSelchangedTree1)
	ON_BN_CLICKED(IDC_ADDFOLDER, &CMFCTRSuiDlg::OnBnClickedAddfolder)
	ON_LBN_SELCHANGE(IDC_ListRoot, &CMFCTRSuiDlg::OnLbnSelchangeListroot)
	ON_BN_CLICKED(IDC_DeleteButton, &CMFCTRSuiDlg::OnBnClickedDeletebutton)
	ON_BN_CLICKED(IDC_RunSelected, &CMFCTRSuiDlg::OnBnClickedRunselected)
	ON_EN_CHANGE(IDC_EDIT3, &CMFCTRSuiDlg::OnEnChangeEdit3)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS1, &CMFCTRSuiDlg::OnNMCustomdrawProgress1)
	ON_COMMAND(ID_PROGRAM_ADDFOLDER, &CMFCTRSuiDlg::OnProgramAddfolder)
	ON_COMMAND(ID_PROGRAM_DELETESELECTEDITEMS, &CMFCTRSuiDlg::OnProgramDeleteselecteditems)
	ON_COMMAND(ID_PROGRAM_RUNSEL, &CMFCTRSuiDlg::OnProgramRunsel)
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

	LONG lStyle = GetWindowLong(m_hWnd, GWL_STYLE);
	lStyle &= ~WS_CHILD;        //remove the CHILD style
	lStyle &= ~WS_DISABLED;        //remove the DISABLED style

	lStyle |= WS_POPUP;            //Add the POPUP style
	//lStyle |= WS_VISIBLE;        //Add the VISIBLE style
	lStyle |= WS_SYSMENU;
	
	SetWindowLong(m_hWnd, GWL_STYLE, lStyle);

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	// TODO: Add extra initialization here
	RunButton.EnableWindow(false);
	DeleteButton.EnableWindow(false);
	RootList.ResetContent();

	// toolbar binding
	if (!m_ToolBar.Create(this) || !m_ToolBar.LoadToolBar(MYAMAZINGTOOLBAR))
	{
		TRACE0("Failed to Create Dialog Toolbar\n");
		EndDialog(IDCANCEL);
	}

	
	CRect	rcClientOld; // Old Client Rect
	CRect	rcClientNew; // New Client Rect with Tollbar Added
	GetClientRect(rcClientOld); // Retrive the Old Client WindowSize

	// Called to reposition and resize control bars in the client 
	// area of a window. The reposQuery FLAG does not really traw the 
	// Toolbar.  It only does the calculations. And puts the new 
	// ClientRect values in rcClientNew so we can do the rest of the 
	// Math.
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,
		AFX_IDW_CONTROLBAR_LAST, 0, reposQuery, rcClientNew);

	// All of the Child Windows (Controls) now need to be moved so 
	// the Tollbar does not cover them up. Offest to move all child 
	// controls after adding Tollbar
	CPoint ptOffset(rcClientNew.left - rcClientOld.left,
		rcClientNew.top - rcClientOld.top);
	CRect	rcChild;

	// Handle to the Dialog Controls
	CWnd*	pwndChild = GetWindow(GW_CHILD);
	while (pwndChild) // Cycle through all child controls
	{
		pwndChild->GetWindowRect(rcChild); // Get the child control RECT
		ScreenToClient(rcChild);
		// Changes the Child Rect by the values of the claculated offset
		rcChild.OffsetRect(ptOffset);
		pwndChild->MoveWindow(rcChild, FALSE); // Move the Child Control
		pwndChild = pwndChild->GetNextWindow();
	}
	CRect	rcWindow;
	GetWindowRect(rcWindow); // Get the RECT of the Dialog
	// Increase width to new Client Width
	rcWindow.right += rcClientOld.Width() - rcClientNew.Width();
	// Increase height to new Client Height
	rcWindow.bottom += rcClientOld.Height() - rcClientNew.Height();
	MoveWindow(rcWindow, FALSE); // Redraw Window
	// Now we REALLY Redraw the Toolbar
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,
		AFX_IDW_CONTROLBAR_LAST, 0);




	// toolbar image config
	return TRUE;  // return TRUE  unless you set the focus to a control
}


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




void CMFCTRSuiDlg::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}








DWORD WINAPI RunSuits(LPVOID arg)
{
	RunParameters param;
	param = *(RunParameters*)arg;
	std::list<Suite*> coll = *Manager.List(param.path, param.name, param.tag);
	int count = 0;
	for each(auto it in coll)
	{
		count += it->getList().size();
	}
	param.progress->SetRange(0, count);
	param.progress->SetStep(1);
	Manager.Run(param.path, param.name, param.tag, param.threads, param.reporter);
	return 0;
}

DWORD WINAPI ToRun(LPVOID arg)
{
	RunEndCheck = true;
	ToRunParameters* param = (ToRunParameters*)arg;
	param->manager->Begin();
	HANDLE hThread = 0;
	param->progress->ShowWindow(true);
	param->subProgress->ShowWindow(true);
	param->progress->SetRange(0, param->coll.size());
	param->progress->SetStep(1);
	for each(auto to_delete in param->coll)
	{
		char* path = convertToChar(to_delete.get_path());
		int Thread_amount=1;
		if (threads)
		{
			Thread_amount = atoi(threads);
		}
		RunParameters* parameters = new RunParameters(path, name, tag, Thread_amount, param->manager,param->subProgress);
		DWORD ident;
		hThread = CreateThread(NULL, 0, RunSuits, parameters, 0, &ident);
		WaitForSingleObject(hThread, INFINITE);
		CloseHandle(hThread);
		param->progress->StepIt();
		param->subProgress->SetPos(0);
	}
	param->manager->End();
	Manager.Destroy();
	delete param->manager;
	delete param;
	RunEndCheck = false;
	return 0;
}

DWORD WINAPI Timer(LPVOID arg)
{
	CEdit* edit = (CEdit*)arg;
	edit->ShowWindow(true);
	int count = 0;
	CString mes;
	int last;
	while (RunEndCheck)
	{
		last = edit->GetWindowTextLength();
		edit->SetSel(0,last);
		edit->ReplaceSel(L"Tests running: ");
		++count;
		if ((count / 3600) < 10)
		{
			edit->ReplaceSel(L"0");
			mes.Format(L"%d", count/3600);
			edit->ReplaceSel(mes);
		}
		else
		{
			mes.Format(L"%d", count);
			edit->ReplaceSel(mes);
		}
		edit->ReplaceSel(L":");
		if ((count / 60) < 10)
		{
			edit->ReplaceSel(L"0");
			mes.Format(L"%d", count/60);
			edit->ReplaceSel(mes);
		}
		else
		{
			mes.Format(L"%d", count);
			edit->ReplaceSel(mes);
		}
		edit->ReplaceSel(L":");
		if ((count ) < 10)
		{
			edit->ReplaceSel(L"0");
			mes.Format(L"%d", count);
			edit->ReplaceSel(mes);
		}
		else
		{
			mes.Format(L"%d", count);
			edit->ReplaceSel(mes);
		}
		edit->SetSel(0, 0);
		Sleep(1000);
	}
	edit->SetSel(0, last);
	edit->ReplaceSel(L"Tests running finished");
	return 0;
}


void CMFCTRSuiDlg::OnBnClickedAddfolder()
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
			RootList.AddString(path);
		else
			MessageBox(_T("Current path is invalid"), _T("Error"), MB_ICONERROR | MB_OK);

		delete[] pathA;
		// free memory used
		IMalloc * imalloc = 0;
		if (SUCCEEDED(SHGetMalloc(&imalloc)))
		{
			imalloc->Free(pidl);
			imalloc->Release();
		}
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
							*hSuite = m_Tree->InsertItem(buf, *hHead);
							++count;
							HTREEITEM hTest;
							std::list<TRSTest*>::iterator iter = (*it)->getList().begin();
							for (iter; iter != (*it)->getList().end(); ++iter)
							{
								TCHAR* subBuf = new TCHAR[strlen((*iter)->getName()) + 1];
								convertToTCHAR(subBuf, (*iter)->getName());
								m_Tree->InsertItem(subBuf, *hSuite);
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
							*hSuite = m_Tree->InsertItem(buf, *hHead);
							++count;
							HTREEITEM hTest;
							std::list<TRSTest*>::iterator iter = (*it)->getList().begin();
							for (iter; iter != (*it)->getList().end(); ++iter)
							{
								TCHAR* subBuf = new TCHAR[strlen((*iter)->getName()) + 1];
								convertToTCHAR(subBuf, (*iter)->getName());
								m_Tree->InsertItem(subBuf, *hSuite);
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
	char* pathA = nullptr;
	int size = WideCharToMultiByte(CP_ACP, 0, path, -1, pathA, 0, NULL, NULL);
	pathA = new char[size];
	WideCharToMultiByte(CP_ACP, 0, path, -1, pathA, size, NULL, NULL);

	std::list<Suite*>* suiteColl = Manager.List(pathA, nullptr, nullptr);
	HTREEITEM hHead;
	hHead = m_Tree.InsertItem(L"Suites", TVI_ROOT);
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
	delete[] pathA;
}

void CMFCTRSuiDlg::OnLbnSelchangeListroot()
{
	int count = RootList.GetSelCount();
	int* array = new int[count];

	// making RunBuuon visible only when at least one element is selected
	if (count > 0)
	{
		RunButton.EnableWindow(true);
		DeleteButton.EnableWindow(true);
	}
	else
	{
		RunButton.EnableWindow(false);
		DeleteButton.EnableWindow(false);
	}
	 
	RootList.GetSelItems(count,	array);

	dRoots.clear(); 
	dRoots.reserve(count);

	for (int i = 0; i < count; ++i)
	{
		TCHAR root[MAX_PATH];
		RootList.GetText(array[i], root);
		dRoots.push_back(root);
	}

	if (count == 1)
		Info(dRoots.front().get_path());
	else
		m_Tree.DeleteAllItems();

	delete[] array;
}


void CMFCTRSuiDlg::OnBnClickedDeletebutton()
{
	RunButton.EnableWindow(false);
	DeleteButton.EnableWindow(false);
	for each (auto to_delete in dRoots)
	{
		int index = RootList.FindString(-1, to_delete.get_path());
		RootList.DeleteString(index);
	}
}


void CMFCTRSuiDlg::OnBnClickedRunselected()
{
	RunDialog Dlg;
	Dlg.DoModal();
	if (ifCancelPressed)
	{
		ReportManager* reportManag = new ReportManager;
		ConsoleReporter* reporter = new ConsoleReporter(&console_output, &subm_Progress);
		reportManag->addReporter(reporter);
		ToRunParameters* to_run = new ToRunParameters(dRoots, reportManag, &m_Progress, &subm_Progress);
		HANDLE hThread = CreateThread(NULL, 0, ToRun, to_run, 0, 0);
		HANDLE hTimer = CreateThread(NULL, 0, Timer, &Time_running_edit, 0, 0);
	}
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
			RootList.AddString(path);
		else
			MessageBox(_T("Current path is invalid"), _T("Error"), MB_ICONERROR | MB_OK);

		delete[] pathA;
		// free memory used
		IMalloc * imalloc = 0;
		if (SUCCEEDED(SHGetMalloc(&imalloc)))
		{
			imalloc->Free(pidl);
			imalloc->Release();
		}
	}
}


void CMFCTRSuiDlg::OnProgramDeleteselecteditems()
{
	for each (auto to_delete in dRoots)
	{
		int index = RootList.FindString(-1, to_delete.get_path());
		RootList.DeleteString(index);
	}
}


void CMFCTRSuiDlg::OnProgramRunsel()
{
	RunDialog Dlg;
	Dlg.DoModal();
	if (ifCancelPressed)
	{
		ReportManager* reportManag = new ReportManager;
		ConsoleReporter* reporter = new ConsoleReporter(&console_output, &subm_Progress);
		reportManag->addReporter(reporter);
		ToRunParameters* to_run = new ToRunParameters(dRoots, reportManag, &m_Progress, &subm_Progress);
		HANDLE hThread = CreateThread(NULL, 0, ToRun, to_run, 0, 0);
		CloseHandle(hThread);
	}
}