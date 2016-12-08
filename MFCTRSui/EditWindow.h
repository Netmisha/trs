#pragma once
#include "Resource.h"
#include "TRSLibrary\TRSManager.h"
#include "afxwin.h"
#include "ShowDescription.h"
#include "MFCTRSuiDlg.h"
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
	bool compareData_andChange();
	
	CButton Save_button;
	
	afx_msg void OnEnChangeAuthor();
	afx_msg void OnBnClickedSaveb();
	
	void setMetadataFromXML();
	void setTestdataFromXML();
	CString test;
	CString Test_desc;
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
	std::string PathToFile;
	void CString_to_ascii(CString in, char** out);
	void ParseForHeaderData(); // get attributes from the .xml file + header of the file

	//--------------XML header data----------------//
	
	std::string Tag_S = "tag";
	std::string Repeat_S = "repeat";
	std::string Max_S = "maxTime";
	std::string maxThreads_S = "maxThreads";
	std::string Priority_S = "priority";
	std::string Disable_S = "disable";
	std::string Test_S = "test";
	//--------------end_of_block----------------//
	TiXmlDocument *doc;
	CString TempData;
	CString DescDataHeader;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnEnChangeCopyright();
	afx_msg void OnBnClickedHeaderdescshow();
	afx_msg void OnBnClickedTestdescshow();
	char *ascii_name;
	void WriteOnChangeToFile(std::string tag, CString new_data, std::string block);
	void WriteOnHeaderChange();
	ShowDescription *dlgT = NULL;
	CString D;
	BOOL OnInitDialog();
	
	//----callbackstuf for the onProgramRefresh func----------//
	//CMFCTRSuiDlg *poin = new CMFCTRSuiDlg;
	void changeTestData();
	// int c;
	//void(CMFCTRSuiDlg::*callback_refresh_func)(void);
	
	//------------end of callbackstuff-----------//
	afx_msg void OnBnClickedButtonRefresh();
};
extern TRSTest* TestForInfo;
//extern void(CMFCTRSuiDlg::*callback_refresh_func)();
