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
#include "OutputWnd.h"
#include "TRSnewUIDoc.h"
#include "TRSnewUIView.h"
#include <algorithm>
#include "Functionality.h"
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
	ON_UPDATE_COMMAND_UI(ID_EDIT2, &CTRSnewUIView::OnUpdateEdit2)
	ON_UPDATE_COMMAND_UI(ID_EDIT3, &CTRSnewUIView::OnUpdateEdit3)
	ON_UPDATE_COMMAND_UI(ID_SPIN2, &CTRSnewUIView::OnUpdateSpin2)

	//ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CTRSnewUIView::NiceTry)
//	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CTRSnewUIView::UpdateNiceTry)
	ON_NOTIFY(NM_THEMECHANGED, ID_LIST_ROOT, &CTRSnewUIView::OnNMThemeChangedListRoot)
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
	DDX_Control(pDX, IDC_PROGRESS1, Progress_upper);
	DDX_Control(pDX, IDC_PROGRESS3, Progress_lower);
	DDX_Control(pDX, IDC_TREE1, Tree_control);
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
	COutputWnd output;
	
	
	m_ListCtrl.SetExtendedStyle(m_ListCtrl.GetExtendedStyle() | LVS_EX_CHECKBOXES | LVS_EX_TRANSPARENTSHADOWTEXT);
//	m_ListCtrl.InsertItem(0, _T("D:\\Repository\\trs\\TestData"));
//	m_ListCtrl.InsertItem(0, _T("D:\\Repository\\Suite root"));
//	m_ListCtrl.InsertItem(0, _T("D:\\Repository\\Suite root\\Suite 2"));
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

LRESULT CTRSnewUIView::OnMyThemeChanged(WPARAM wParam, LPARAM lParam)
{
	// do something useful

	return (LRESULT)1;
};

//void CTRSnewUIView::NiceTry(UINT id)
//{
//
//}
//
void CTRSnewUIView::UpdateNiceTry(STYLE style)
{
	switch (style)
	{
	case STYLE::AQUA:
		m_ListCtrl.SetBkColor(RGB(0, 255, 255));
		break;
	case STYLE::BLACK:
		m_ListCtrl.SetBkColor(RGB(0, 0, 0));
		break;
	case STYLE::BLUE:
		m_ListCtrl.SetBkColor(RGB(0, 0, 255));
		break;
	case STYLE::SILVER:
		m_ListCtrl.SetBkColor(RGB(224, 224, 224));
		break;
	case STYLE::WIN7:
		m_ListCtrl.SetBkColor(RGB(255, 178, 102));
		break;
	}
}
void CTRSnewUIView::OnButtonadd()
{
	m_ListCtrl.SetBkColor(RGB(0, 0, 0));
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

void TreeParse(std::list<Suite*>::iterator& it, std::list<Suite*>* suiteColl, CTreeCtrl* Tree_control, int& count, HTREEITEM* hHead, std::list<Suite*>* checkList)
{
	if (count != suiteColl->size())
	{
		char* rootPath = new char[strlen((*it)->get_path()) + 1];
		strncpy_s(rootPath, strlen((*it)->get_path()) + 1, (*it)->get_path(), strlen((*it)->get_path()));
		char* rootName = new char[strlen((*it)->getName()) + 1];
		strncpy_s(rootName, strlen((*it)->getName()) + 1, (*it)->getName(), strlen((*it)->getName()));
		HTREEITEM* hSuite = new HTREEITEM;
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
							TreeParse(it, suiteColl, Tree_control, count, hSuite, checkList);
					}

				}
				else
				{
					if (!strncmp(rootPath, (*it)->get_path(), strlen(rootPath)) && !strncmp((*it)->getName(), rootName, strlen(rootName)))
					{
						TCHAR* buf = new TCHAR[strlen((*it)->getName()) + 1];
						convertToTCHAR(buf, (*it)->getName());
						*hSuite = Tree_control->InsertItem(buf, *hHead);
						++count;
						HTREEITEM hTest;
						std::list<TRSTest*>::iterator iter = (*it)->getList().begin();
						for (iter; iter != (*it)->getList().end(); ++iter)
						{
							TCHAR* subBuf = new TCHAR[strlen((*iter)->getName()) + 1];
							convertToTCHAR(subBuf, (*iter)->getName());
							Tree_control->InsertItem(subBuf, *hSuite);
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
							TreeParse(it, suiteColl, Tree_control, count, hSuite, checkList);
					}

				}
				else
				{
					if (!strncmp(rootPath, (*it)->get_path(), strlen(rootPath)) && !strncmp((*it)->getName(), rootName, strlen(rootName)))
					{
						TCHAR* buf = new TCHAR[strlen((*it)->getName()) + 1];
						convertToTCHAR(buf, (*it)->getName());
						*hSuite = Tree_control->InsertItem(buf, *hHead);
						++count;
						HTREEITEM hTest;
						std::list<TRSTest*>::iterator iter = (*it)->getList().begin();
						for (iter; iter != (*it)->getList().end(); ++iter)
						{
							TCHAR* subBuf = new TCHAR[strlen((*iter)->getName()) + 1];
							convertToTCHAR(subBuf, (*iter)->getName());
							Tree_control->InsertItem(subBuf, *hSuite);
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
							TreeParse(it, suiteColl, Tree_control, count, hSuite, checkList);
					}
				}
				else
				{

					if (!strncmp(rootPath, (*it)->get_path(), strlen(rootPath)) && !strncmp((*it)->getName(), rootName, strlen(rootName)))
					{
						TCHAR* buf = new TCHAR[strlen((*it)->getName()) + 1];
						convertToTCHAR(buf, (*it)->getName());
						*hSuite = Tree_control->InsertItem(buf, *hHead);
						++count;
						HTREEITEM hTest;
						std::list<TRSTest*>::iterator iter = (*it)->getList().begin();
						for (iter; iter != (*it)->getList().end(); ++iter)
						{
							TCHAR* subBuf = new TCHAR[strlen((*iter)->getName()) + 1];
							convertToTCHAR(subBuf, (*iter)->getName());
							Tree_control->InsertItem(subBuf, *hSuite);
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

void CTRSnewUIView::Info(TCHAR* path,HTREEITEM& hHead)
{
	char* pathA = nullptr;
	int size = WideCharToMultiByte(CP_ACP, 0, path, -1, pathA, 0, NULL, NULL);
	pathA = new char[size];
	WideCharToMultiByte(CP_ACP, 0, path, -1, pathA, size, NULL, NULL);

	std::list<Suite*>* suiteColl = Manager.List(pathA, nullptr, nullptr);
	hHead = Tree_control.InsertItem(L"Suites", TVI_ROOT);
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
			TreeParse(it, suiteColl, &Tree_control, lic, &hHead, &checkList);
		}
	}
	if (strlen((*it)->get_path()) == count)
	{
		TreeParse(it, suiteColl, &Tree_control, lic, &hHead, &checkList);
	}
	delete[] pathA;
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
	{
		pCmdUI->Enable(false);
	}
}


void CTRSnewUIView::AddToTree(char* path,int Item)
{
	TCHAR* buf = new TCHAR[strlen(path) + 1];
	convertToTCHAR(buf, path);
	HTREEITEM* hHead = new HTREEITEM;

	if (TreeItemsColl.size() < Item)
	{
		TreeItemsColl.resize(Item);
	}
	std::vector<HTREEITEM*>::iterator iterator = TreeItemsColl.begin();
	TreeItemsColl.insert(iterator + Item, hHead);
	Info(buf, *hHead);
}

void CTRSnewUIView::DeleteFromTree(int item)
{
	if (TreeItemsColl.size()>0)
	if (*TreeItemsColl[item])
	{
		Tree_control.DeleteItem(*TreeItemsColl[item]);
		auto it = std::find(TreeItemsColl.begin(), TreeItemsColl.end(), TreeItemsColl[item]);
		if (it != TreeItemsColl.end())
		{
			delete *it;

		}
	}
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
			char* path = fromCStringToChar(m_ListCtrl.GetItemText(pNMLV->iItem, 0));
			AddToTree(path, pNMLV->iItem);
			break;
		}
		case INDEXTOSTATEIMAGEMASK(BST_UNCHECKED + 1): // new state: unchecked
		{
			auto iter = std::find(GetDocument()->m_SelectedRoots.begin(), GetDocument()->m_SelectedRoots.end(), pNMLV->iItem);
			if (iter != GetDocument()->m_SelectedRoots.end())
				GetDocument()->m_SelectedRoots.erase(iter);
			DeleteFromTree(pNMLV->iItem);
			break;
		}
		}
	}
	*pResult = 0;
}

void CTRSnewUIView::OnUpdateEdit2(CCmdUI *pCmdUI)
{
	if (GetDocument()->m_SelectedRoots.size())
		pCmdUI->Enable();
	else
	{
		pCmdUI->Enable(false);
	}
	// TODO: Add your command update UI handler code here
}


void CTRSnewUIView::OnUpdateEdit3(CCmdUI *pCmdUI)
{
	if (GetDocument()->m_SelectedRoots.size())
		pCmdUI->Enable();
	else
	{
		pCmdUI->Enable(false);
	}
	// TODO: Add your command update UI handler code here
}


void CTRSnewUIView::OnUpdateSpin2(CCmdUI *pCmdUI)
{
	if (GetDocument()->m_SelectedRoots.size())
		pCmdUI->Enable();
	else
	{
		pCmdUI->Enable(false);
	}
	// TODO: Add your command update UI handler code here
}



void CTRSnewUIView::OnNMThemeChangedListRoot(NMHDR *pNMHDR, LRESULT *pResult)
{
	// This feature requires Windows XP or greater.
	// The symbol _WIN32_WINNT must be >= 0x0501.
	// TODO: Add your control notification handler code here
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

	*pResult = 0;
}
