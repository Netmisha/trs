#pragma once
#include "Resource.h"

// AddSuite dialog

class AddSuite : public CDialogEx
{
	DECLARE_DYNAMIC(AddSuite)

public:
	AddSuite(CWnd* pParent = NULL);   // standard constructor
	virtual ~AddSuite();
// Dialog Data
	enum { IDD = IDD_DIALOG_ADDSUITE };
	void setPath(CString &);
	CString getPathToFile();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString sSuiteName;
	CString sPath_;
	afx_msg void OnBnClickedOk();
};
