
// MFCTRSui.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"	
#include "ProjNameEdit.h"
// main symbols


// CMFCTRSuiApp:
// See MFCTRSui.cpp for the implementation of this class
//

class CMFCTRSuiApp : public CWinApp
{
public:
	CMFCTRSuiApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnNewProject();
	afx_msg void OnSaveProject();
};
extern CTreeCtrl m_Tree;
extern CMFCTRSuiApp theApp;
extern CToolBar* Bar;