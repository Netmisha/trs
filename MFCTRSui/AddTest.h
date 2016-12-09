#pragma once
#include "afxwin.h"
#include "Resource.h"
#include <string>
#include <fstream>

// AddTest dialog

class AddTest : public CDialogEx
{
	DECLARE_DYNAMIC(AddTest)

public:
	AddTest(CWnd* pParent = NULL);   // standard constructor
	virtual ~AddTest();

// Dialog Data
	enum { IDD = IDD_DIALOG_ADDTEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	BOOL OnInitDialog();
	CString sTName;
	CString sTDescription;
	CString sTPriority;
	CString sTTag;
	CString sTDisable;
	CString sTResult;
	CString sTExecution;
	CString sTParameters;
	CString sTParamRepeat;
	CString sTRepeat;
	CString sTPause;
	CString sTWait;
	CString sTTime;
	CString sPath_;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CEdit cExecution;
	void setPath(CString path);
	void setDefault();
};
