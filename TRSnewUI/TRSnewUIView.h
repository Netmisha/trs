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

// TRSnewUIView.h : interface of the CTRSnewUIView class
//

#pragma once

#include "resource.h"
#include "afxwin.h"
#include "TRSnewUIDoc.h"
#include "afxcmn.h"

class CTRSnewUIView : public CFormView
{
protected: // create from serialization only
	CTRSnewUIView();
	DECLARE_DYNCREATE(CTRSnewUIView)

public:
	enum{ IDD = IDD_TRSNEWUI_FORM };

// Attributes
public:
	CTRSnewUIDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CTRSnewUIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnButtonadd();
	afx_msg void OnButtondelete();
	afx_msg void OnUpdateButtondelete(CCmdUI *pCmdUI);
	afx_msg void OnButtonrun();
	afx_msg void OnUpdateButtonrun(CCmdUI *pCmdUI);
protected:
	CListCtrl m_ListCtrl;
public:
	afx_msg void OnLvnItemchangedListRoot(NMHDR *pNMHDR, LRESULT *pResult);
};

#ifndef _DEBUG  // debug version in TRSnewUIView.cpp
inline CTRSnewUIDoc* CTRSnewUIView::GetDocument() const
   { return reinterpret_cast<CTRSnewUIDoc*>(m_pDocument); }
#endif

