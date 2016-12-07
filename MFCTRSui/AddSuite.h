#pragma once
#include "Resource.h"
#include "afxwin.h"

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
	CString getPath();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString sSuiteName;
	CString sPath_;
	afx_msg void OnBnClickedOk();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);

	CString sMDAuthor;
	CString sMDDate;
	CString sMDVersion;
	CString sMDMail;
	CString sMDCopyright;
	CString sMDLicense;
	CString sMDInfo;
	CString sHTag;
	CString sHRepeat;
	CString sHThread;
	CString sHTime;
	CString sHPriority;
	CString sHDisable;
	CString sHSuiteName;
	CString sHPause;
	afx_msg void OnBnClickedCancel();
	CString sHDescription;
};
