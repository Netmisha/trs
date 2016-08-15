#pragma once
#include "Resource.h"
#include "afxcmn.h"

// TestsTimerDialog dialog

class TestsTimerDialog : public CDialogEx
{
	DECLARE_DYNAMIC(TestsTimerDialog)

public:
	TestsTimerDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~TestsTimerDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl TimerHeadListCtrl;
};
