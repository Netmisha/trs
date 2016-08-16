#pragma once

#include "Resource.h"
#include "SuiteRoot.h"
#include <vector>
// AddClockDlg dialog

class AddClockDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AddClockDlg)

public:
	AddClockDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~AddClockDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	char* clock_name;
	std::vector<SuiteRoot> list_items;
	CString tag;
	CString name;
	CString threads;

};
