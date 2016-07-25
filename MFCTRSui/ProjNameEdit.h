#pragma once
#include "Resource.h"
#include "afxwin.h"
#include "ProjectProperties.h"
#include "Functionality.h"
// ProjNameEdit dialog

class ProjNameEdit : public CDialogEx
{
	DECLARE_DYNAMIC(ProjNameEdit)

public:
	ProjNameEdit(CWnd* pParent = NULL);   // standard constructor
	virtual ~ProjNameEdit();

// Dialog Data
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit name_edit;
	bool SaveProject();
};

extern ProjectProperties pro_;
extern CToolBar* ToolBar;