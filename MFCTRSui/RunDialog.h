#pragma once
#ifndef RUNDIALOG_H_
#define RUNDIALOG_H_
#include "resource.h"
#include "afxwin.h"
#include "Functionality.h"
// RunDialog dialog

class RunDialog : public CDialogEx
{
	DECLARE_DYNAMIC(RunDialog)

public:
	RunDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~RunDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit Tag_edit;
	CEdit Name_edit;
	afx_msg void OnBnClickedOk();
	CEdit Threads_edit;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCancel();
};

extern bool ifCancelPressed;
extern char* tag;
extern char* name;
extern char* threads;
extern char* testName;
#endif