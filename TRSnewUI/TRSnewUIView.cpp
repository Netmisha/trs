// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// TRSnewUIView.cpp : implementation of the CTRSnewUIView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "TRSnewUI.h"
#endif

#include "TRSnewUIDoc.h"
#include "TRSnewUIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTRSnewUIView

IMPLEMENT_DYNCREATE(CTRSnewUIView, CFormView)

BEGIN_MESSAGE_MAP(CTRSnewUIView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_BUTTONADD, &CTRSnewUIView::OnButtonadd)
END_MESSAGE_MAP()

// CTRSnewUIView construction/destruction

CTRSnewUIView::CTRSnewUIView()
	: CFormView(CTRSnewUIView::IDD)
{
	// TODO: add construction code here

}

CTRSnewUIView::~CTRSnewUIView()
{
}

void CTRSnewUIView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, ID_LISTROOT, m_ListRoot);
}

BOOL CTRSnewUIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CTRSnewUIView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

void CTRSnewUIView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTRSnewUIView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CTRSnewUIView diagnostics

#ifdef _DEBUG
void CTRSnewUIView::AssertValid() const
{
	CFormView::AssertValid();
}

void CTRSnewUIView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CTRSnewUIDoc* CTRSnewUIView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTRSnewUIDoc)));
	return (CTRSnewUIDoc*)m_pDocument;
}
#endif //_DEBUG


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

void CTRSnewUIView::OnButtonadd()
{
	BROWSEINFO bi = { 0 };
	bi.lpszTitle = _T("Select Folder");
	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
	if (pidl != 0)
	{
		// get the name of the folder
		TCHAR path[MAX_PATH];
		SHGetPathFromIDList(pidl, path);

	/*	char* pathA = nullptr;
		int size = WideCharToMultiByte(CP_ACP, 0, path, -1, pathA, 0, NULL, NULL);

		pathA = new char[size];
		WideCharToMultiByte(CP_ACP, 0, path, -1, pathA, size, NULL, NULL);
	*/	char* pathA = convertToChar(path);

		if (!Manager.Verify(pathA, nullptr, nullptr))
			m_ListRoot.AddString(path);
		else
			MessageBox(_T("Current path is invalid"), _T("Error"), MB_ICONERROR | MB_OK);

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
