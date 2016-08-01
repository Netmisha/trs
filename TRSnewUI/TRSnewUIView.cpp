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
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTRSnewUIView

IMPLEMENT_DYNCREATE(CTRSnewUIView, CFormView)

BEGIN_MESSAGE_MAP(CTRSnewUIView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_BUTTONADD, &CTRSnewUIView::OnButtonadd)
	ON_COMMAND(ID_BUTTONDELETE, &CTRSnewUIView::OnButtondelete)
	ON_UPDATE_COMMAND_UI(ID_BUTTONDELETE, &CTRSnewUIView::OnUpdateButtondelete)
	ON_COMMAND(ID_BUTTONRUN, &CTRSnewUIView::OnButtonrun)
	ON_UPDATE_COMMAND_UI(ID_BUTTONRUN, &CTRSnewUIView::OnUpdateButtonrun)
	ON_NOTIFY(LVN_ITEMCHANGED, ID_LIST_ROOT, &CTRSnewUIView::OnLvnItemchangedListRoot)
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
	DDX_Control(pDX, ID_LIST_ROOT, m_ListCtrl);
}

BOOL CTRSnewUIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	//m_ListCtrl.SetExtendedStyle(m_ListCtrl.GetExtendedStyle() | LVS_EX_CHECKBOXES);

	return CFormView::PreCreateWindow(cs);
}


void CTRSnewUIView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();


	m_ListCtrl.SetExtendedStyle(m_ListCtrl.GetExtendedStyle() | LVS_EX_CHECKBOXES | LVS_EX_TRANSPARENTSHADOWTEXT);
	m_ListCtrl.InsertItem(0, _T("First raw"));
	m_ListCtrl.InsertItem(0, _T("Second raw"));
	m_ListCtrl.InsertItem(0, _T("Third raw"));
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
			m_ListCtrl.InsertItem(0, path);
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

void CTRSnewUIView::OnButtondelete()
{
	// due to the fact, that we indentify elements by index, and after each deletion they shifted - we are forced delete from the biggest index.
	std::sort(GetDocument()->m_SelectedRoots.begin(), GetDocument()->m_SelectedRoots.end(), std::greater<int>());
	for (auto iter = GetDocument()->m_SelectedRoots.begin();
		iter != GetDocument()->m_SelectedRoots.end(); 
		++iter)
	{
		m_ListCtrl.DeleteItem(*iter);
	}

	GetDocument()->m_SelectedRoots.clear();
}


void CTRSnewUIView::OnUpdateButtondelete(CCmdUI *pCmdUI)
{
	if (GetDocument()->m_SelectedRoots.size())
		pCmdUI->Enable();
	else
		pCmdUI->Enable(false);
}


void CTRSnewUIView::OnButtonrun()
{
	// TODO: Add your command handler code here
}


void CTRSnewUIView::OnUpdateButtonrun(CCmdUI *pCmdUI)
{
	if (GetDocument()->m_SelectedRoots.size())
		pCmdUI->Enable();
	else
		pCmdUI->Enable(false);
}


void CTRSnewUIView::OnLvnItemchangedListRoot(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW  pNMLV = reinterpret_cast<LPNMLISTVIEW >(pNMHDR);

	if (pNMLV->uChanged & LVIF_STATE) // item state has been changed
	{
		CString str;
		switch (pNMLV->uNewState & LVIS_STATEIMAGEMASK)
		{
		case INDEXTOSTATEIMAGEMASK(BST_CHECKED + 1): // new state: checked
		{ 
			GetDocument()->m_SelectedRoots.push_back(pNMLV->iItem);
			break;
		}
		case INDEXTOSTATEIMAGEMASK(BST_UNCHECKED + 1): // new state: unchecked
		{
			auto iter = std::find(GetDocument()->m_SelectedRoots.begin(), GetDocument()->m_SelectedRoots.end(), pNMLV->iItem);
			if (iter != GetDocument()->m_SelectedRoots.end())
				GetDocument()->m_SelectedRoots.erase(iter);
			break;
		}
		}
	}
	*pResult = 0;
}