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
	ON_LBN_SELCHANGE(ID_LISTROOT, &CTRSnewUIView::OnLbnSelchangeListroot)
	ON_COMMAND(ID_BUTTONDELETE, &CTRSnewUIView::OnButtondelete)
	ON_UPDATE_COMMAND_UI(ID_BUTTONDELETE, &CTRSnewUIView::OnUpdateButtondelete)
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

		char* pathA = nullptr;
		int size = WideCharToMultiByte(CP_ACP, 0, path, -1, pathA, 0, NULL, NULL);

		pathA = new char[size];
		WideCharToMultiByte(CP_ACP, 0, path, -1, pathA, size, NULL, NULL);

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


void CTRSnewUIView::OnLbnSelchangeListroot()
{
	int count = m_ListRoot.GetSelCount();
	int* array = new int[count];

	// making RunButton visible only when at least one element is selected
	/*if (count > 0)
	{
		if (m_Menu)
		{
			m_Menu->EnableMenuItem(TOOLBAR_DELETE, MF_BYCOMMAND | MF_ENABLED);
			m_Menu->EnableMenuItem(TOOLBAR_RUN, MF_BYCOMMAND | MF_ENABLED);
		}
	}
	else
	{
		if (m_Menu)
		{
			m_Menu->EnableMenuItem(TOOLBAR_DELETE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
			m_Menu->EnableMenuItem(TOOLBAR_RUN, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		}
	}*/

	m_ListRoot.GetSelItems(count, array);

	GetDocument()->m_SelectedRoots.clear();
	GetDocument()->m_SelectedRoots.reserve(count);

	for (int i = 0; i < count; ++i)
	{
		TCHAR root[MAX_PATH];
		m_ListRoot.GetText(array[i], root);
		GetDocument()->m_SelectedRoots.push_back(root);
	}

	/*if (count == 1)
		Info(GetDocument()->m_SelectedRoots.front().get_path());
	else
		m_Tree.DeleteAllItems();*/

	delete[] array;
}


void CTRSnewUIView::OnButtondelete()
{
	if (GetDocument()->m_SelectedRoots.size())
	{
		//if (m_Menu)
		//{
		//	//m_Menu->EnableMenuItem(TOOLBAR_RUN, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		//}
		//m_Tree.DeleteAllItems();
		for each (auto to_delete in GetDocument()->m_SelectedRoots)
		{
			int index = m_ListRoot.FindString(-1, to_delete.get_path());
			m_ListRoot.DeleteString(index);
		}
		GetDocument()->m_SelectedRoots.clear();
		//if (RootList.GetCount() == 0)
		//{
		//	m_Menu->EnableMenuItem(ID_Save_Project, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		//}
	}
}


void CTRSnewUIView::OnUpdateButtondelete(CCmdUI *pCmdUI)
{
	if (GetDocument()->m_SelectedRoots.size())
		pCmdUI->Enable();
	else
		pCmdUI->Enable(false);
}
