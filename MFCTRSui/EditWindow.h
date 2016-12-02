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
	CEdit date_V;
	CEdit Version_V;
	CEdit Mail_V;
	CEdit Copyrgiht_V;
	CEdit License_V;
	CEdit Info_V;
	afx_msg void OnEnChangeAuthor();
	afx_msg void OnBnClickedSaveb();
	CString Author;
	CString Date;
	CString Version;
	CString Mail;
	CString Copyright;
	CString License;
	CString Info;
	void setMetadataFromXML();
	void setTestdataFromXML();
	afx_msg void OnBnClickedRefresh();
	
	CString TestName_TS;
	CString Priority_TS;
	CString Tag_TS;
	CString Disable_TS;
	CString Execution_TS;
	CString Par_TS;
	CString Repeat_TS;
	CString Result_tS;
	CString Repeat_TMS;
	CString MaxTime_TS;
	CString WaitFor_TS;
	CString Pause_TRS;

	CEdit TestName_T;
	CEdit Priority_T;
	CEdit Tag_T;
	CEdit Disable_T;
	CEdit Execution_T;
	CEdit Par_T;
	CEdit Repeat_T;
	CEdit Result_t;
	CEdit Repeat_TM;
	CEdit MaxTime_T;
	CEdit WaitFor_T;
	CEdit Pause_TR;
};
extern TRSTest* TestForInfo;