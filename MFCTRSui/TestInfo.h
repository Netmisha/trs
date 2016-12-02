#pragma once

#include "Resource.h"
#include "TRSLibrary\TRSManager.h"
#include "afxwin.h"
// TestInfo dialog

class TestInfo : public CDialogEx
{
	DECLARE_DYNAMIC(TestInfo)

public:
	TestInfo(CWnd* pParent = NULL);   // standard constructor
	virtual ~TestInfo();

// Dialog Data
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_TreeEdit;
};

extern TRSTest* TestForInfo;