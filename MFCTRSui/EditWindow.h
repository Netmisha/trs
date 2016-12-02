#pragma once
#include "Resource.h"
#include "TRSLibrary\TRSManager.h"
#include "afxwin.h"

// EditWindow dialog

class EditWindow : public CDialogEx
{
	DECLARE_DYNAMIC(EditWindow)

public:
	EditWindow(CWnd* pParent = NULL);   // standard constructor
	virtual ~EditWindow();

// Dialog Data
	enum { IDD = IDD_EDITTAG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	
	CEdit Author_name;
	CButton Save_button;
	afx_msg void OnEnChangeAuthor();
};
