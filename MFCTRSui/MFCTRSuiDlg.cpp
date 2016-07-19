
// MFCTRSuiDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCTRSui.h"
#include "MFCTRSuiDlg.h"
#include "afxdialogex.h"
#include "ConsoleReporter.h"
#include "TRSLibrary\TRSManager.h"
#include <list>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCTRSuiDlg dialog
void convertToTCHAR(TCHAR*dest, char* path)
{
	if (dest != nullptr && path != nullptr)
	{
		TCHAR help = path[0];
		int i = 0;
		while (help)
		{
			dest[i] = help;
			++i;
			help = path[i];
		}
		dest[i] = '\0';
	}
}

char* convertToChar(TCHAR*path)//create buffer to set info to tinyXML doc constructor
{
	char* buf = new char[MAX_PATH];
	char help = path[0];
	int i = 0;
	while (help)//i tried to use memcpy,but it didn't work so i used while=(
	{
		buf[i] = help;
		++i;
		help = path[i];
	}
	buf[i] = '\0';
	return buf;
}



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
	DDX_Control(pDX, IDC_EDIT1, C_edit);
	DDX_Control(pDX, IDC_BUTTON2, Run_button);
	DDX_Control(pDX, IDC_EDIT3, console_output);

	DDX_Control(pDX, IDC_ListRoot, RootList);
}

BEGIN_MESSAGE_MAP(CMFCTRSuiDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT1, &CMFCTRSuiDlg::OnEnChangeEdit1)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CMFCTRSuiDlg::OnTvnSelchangedTree1)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCTRSuiDlg::OnBnClickedButton1)
	ON_BN_CLICKED(Run_BUTTON, &CMFCTRSuiDlg::RunButtonClicked)
	ON_BN_CLICKED(IDC_ADDFOLDER, &CMFCTRSuiDlg::OnBnClickedAddfolder)
	ON_LBN_SELCHANGE(IDC_ListRoot, &CMFCTRSuiDlg::OnLbnSelchangeListroot)
	ON_BN_CLICKED(IDC_DeleteButton, &CMFCTRSuiDlg::OnBnClickedDeletebutton)
	ON_BN_CLICKED(IDC_RunSelected, &CMFCTRSuiDlg::OnBnClickedRunselected)
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
	AllocConsole();
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



void CMFCTRSuiDlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO:  Add your control notification handler code here
}


void CMFCTRSuiDlg::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void CMFCTRSuiDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	CString message;
	
	C_edit.GetWindowTextW(message);
	//C_edit.SetWindowTextW(message);
	CT2A buffer(message);
	DWORD fFile = GetFileAttributesA(buffer);
	if (fFile == INVALID_FILE_ATTRIBUTES && !(fFile == ERROR_FILE_NOT_FOUND))
	{
		C_edit.SetSel(0, -1);
		C_edit.Clear();
		MessageBox(_T("Current path is invalid"), _T("Error"), MB_ICONERROR | MB_OK);

	}
	else
	{
		std::list<Suite*>* suiteColl = Manager.List(buffer.m_psz, nullptr, nullptr);
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
			Run_button.EnableWindow(true);
		}
		else
		{
			m_Tree.DeleteAllItems();
			Run_button.EnableWindow(false);
		}
	}
}



void CMFCTRSuiDlg::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}




void CMFCTRSuiDlg::RunButtonClicked()
{
	// TODO: Add your control notification handler code here
	CString message;
	ReportManager* manager = new ReportManager;
	ConsoleReporter reporter(&console_output);
	manager->addReporter(&reporter);
	C_edit.GetWindowTextW(message);
	CT2A buffer(message);
	manager->Begin();
	Manager.Run(buffer.m_psz, nullptr, nullptr, 10, manager);
	manager->End();
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
	ReportManager* manager = new ReportManager;
	ConsoleReporter reporter(&console_output);
	manager->addReporter(&reporter);

	for each (auto to_delete in dRoots)
	{
		manager->Begin();
		char* pathA = convertToChar(to_delete.get_path());
		Manager.Run(pathA, nullptr, nullptr, 10, manager);
		delete[] pathA;
		manager->End();
	}
}
