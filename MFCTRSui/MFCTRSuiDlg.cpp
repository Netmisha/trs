
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
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCTRSuiDlg dialog




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
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
	DDX_Control(pDX, IDC_PROGRESS3, subm_Progress);
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
END_MESSAGE_MAP()


// CMFCTRSuiDlg message handlers

BOOL CMFCTRSuiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	// TODO: Add extra initialization here
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
	ToRunParameters* param = (ToRunParameters*)arg;
	param->manager->Begin();
	HANDLE hThread = 0;
	param->progress->ShowWindow(true);
	param->subProgress->ShowWindow(true);
	param->progress->SetRange(0, param->coll.size());
	param->progress->SetStep(1);
	for each(auto to_delete in param->coll)
	{
		param->subProgress->EnableWindow(true);
		char* path = convertToChar(to_delete.get_path());
		RunParameters* parameters = new RunParameters(path, nullptr, nullptr, 10, param->manager,param->subProgress);
		DWORD ident;
		hThread = CreateThread(NULL, 0, RunSuits, parameters, 0, &ident);
		WaitForSingleObject(hThread, INFINITE);
		param->progress->StepIt();
		param->subProgress->ShowWindow(false);
	}
	param->manager->End();
	Manager.Destroy();
	delete param->manager;
	delete param;
	
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

void CMFCTRSuiDlg::Info(TCHAR* path)
{
	char* pathA = nullptr;
	int size = WideCharToMultiByte(CP_ACP, 0, path, -1, pathA, 0, NULL, NULL);
	pathA = new char[size];
	WideCharToMultiByte(CP_ACP, 0, path, -1, pathA, size, NULL, NULL);

	std::list<Suite*>* suiteColl = Manager.List(pathA, nullptr, nullptr);
	if (suiteColl->size() > 0)
	{
		HTREEITEM hHead, hSuites, hTests;
		std::list<Suite*>::iterator it = suiteColl->begin();
		hHead = m_Tree.InsertItem(L"Suites", TVI_ROOT);
		for (it; it != suiteColl->end(); ++it)
		{
			TCHAR bufName[MAX_PATH];
			convertToTCHAR(bufName, (*it)->getName());
			hSuites = m_Tree.InsertItem(bufName, hHead);
			std::list<TRSTest*>::iterator iter = (*it)->getList().begin();
			for (iter; iter != (*it)->getList().end(); ++iter)
			{
				TCHAR testName[MAX_PATH];
				convertToTCHAR(testName, (*iter)->getName());
				hTests = m_Tree.InsertItem(testName, hSuites);
			}
		}
	}

	delete[] pathA;
}

void CMFCTRSuiDlg::OnLbnSelchangeListroot()
{
	int count = RootList.GetSelCount();
	int* array = new int[count];
	 
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
	for each (auto to_delete in dRoots)
	{
		int index = RootList.FindString(-1, to_delete.get_path());
		RootList.DeleteString(index);
	}
}


void CMFCTRSuiDlg::OnBnClickedRunselected()
{
	ReportManager* reportManag = new ReportManager;
	ConsoleReporter* reporter = new ConsoleReporter(&console_output,&subm_Progress);
	reportManag->addReporter(reporter);
	ToRunParameters* to_run=new ToRunParameters(dRoots, reportManag,&m_Progress,&subm_Progress);
	HANDLE hThread = CreateThread(NULL, 0, ToRun, to_run, 0, 0);
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



