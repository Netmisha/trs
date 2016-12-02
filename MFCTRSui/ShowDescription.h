#pragma once
#include "afxwin.h"
#include "Resource.h"
#include "TRSLibrary\TRSManager.h"


// ShowDescription dialog

class ShowDescription : public CDialogEx
{
	DECLARE_DYNAMIC(ShowDescription)

public:
	ShowDescription(CWnd* pParent = NULL);   // standard constructor
	virtual ~ShowDescription();

// Dialog Data
	enum { IDD = IDD_SHOWDESC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit DesDataBox;
};
