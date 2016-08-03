
// MFCTRSui.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MFCTRSui.h"
#include "MFCTRSuiDlg.h"
#include "Functionality.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CListBox* List;

// CMFCTRSuiApp

BEGIN_MESSAGE_MAP(CMFCTRSuiApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
	ON_BN_CLICKED(IDOK, &CMFCTRSuiApp::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT1, &CMFCTRSuiApp::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCTRSuiApp::OnBnClickedButton2)
	ON_COMMAND(ID_New_Project, &CMFCTRSuiApp::OnNewProject)
	ON_COMMAND(ID_Save_Project, &CMFCTRSuiApp::OnSaveProject)
END_MESSAGE_MAP()


// CMFCTRSuiApp construction

CMFCTRSuiApp::CMFCTRSuiApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CMFCTRSuiApp object

CMFCTRSuiApp theApp;


// CMFCTRSuiApp initialization

BOOL CMFCTRSuiApp::InitInstance()
{
	CWinApp::InitInstance();


	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CMFCTRSuiDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	// Delete the shell manager created above.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}



void CMFCTRSuiApp::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
}


void CMFCTRSuiApp::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CWinApp::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO:  Add your control notification handler code here
}


void CMFCTRSuiApp::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
}



void CMFCTRSuiApp::OnNewProject()
{
	if (pro_.getName()&&pro_.getPath())
	{
		int res = MessageBox(NULL,_T("Do you want to save current project?"), _T("Not saved"), MB_ICONINFORMATION|MB_YESNO);
		if (res == IDYES)
		{
			pro_.SaveProject(List);
			MessageBox(NULL, _T("Project was saved"), _T("Info"), MB_ICONINFORMATION|MB_OK);
		}
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
		NameDlg.DoModal();
		Bar->GetToolBarCtrl().HideButton(TOOLBAR_ADDGREY);
		Bar->GetToolBarCtrl().HideButton(TOOLBAR_ADD, false);
		Bar->GetToolBarCtrl().HideButton(TOOLBAR_RUN);
		Bar->GetToolBarCtrl().HideButton(TOOLBAR_RUNGREY, false);
		Bar->GetToolBarCtrl().HideButton(TOOLBAR_DELETE);
		Bar->GetToolBarCtrl().HideButton(TOOLBAR_DELETEGREY, false);
		List->ResetContent();
		IMalloc * imalloc = 0;
		if (SUCCEEDED(SHGetMalloc(&imalloc)))
		{
			imalloc->Free(pidl);
			imalloc->Release();
		}
	}
	
	// TODO: Add your command handler code here
}

void CMFCTRSuiApp::OnSaveProject()
{
	MessageBox(NULL, _T("Project was saved"), _T("Note:"), MB_ICONINFORMATION | MB_OK);
	pro_.SaveProject(List);
	// TODO: Add your command handler code here
}
