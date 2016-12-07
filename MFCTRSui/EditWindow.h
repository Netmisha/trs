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
	CString SuiteName_S;
	CString SuiteDesc_S;
	CString Head_Repeat_S;
	CString Head_MaxTime_S;
	CString Head_MaxThreads_S;
	CString Head_Priority_S;
	CString Head_Disable_S;
	CString Head_Tag_S;
	CString HeadRepeat_Pause;
	std::string Tag_S = "tag";
	std::string Repeat_S = "repeat";
	std::string Max_S = "maxTime";
	std::string maxThreads_S = "maxThreads";
	std::string Priority_S = "priority";
	std::string Disable_S = "disable";
	std::string Test_S = "test";
	//--------------end_of_block----------------//
	CEdit TagV;
	CEdit RepeatV;
	CEdit MaxThreadsV;
	CEdit PauseV;
	CEdit maxTimeV;
	CEdit PriorityV;
	CEdit DisableV;
	CEdit SuiteNameV;
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
	void CompareAndChangeFuncHeader(TiXmlElement *parent, std::string XmlTag, CEdit EditLine, CString EditStringLine);
	//----callbackstuf for the onProgramRefresh func----------//
	CMFCTRSuiDlg *poin;
	void changeTestData();
	//void(CMFCTRSuiDlg::*callback_refresh_func)(void);
	ShowDescription *dlg = NULL;
	CString D;
	//------------end of callbackstuff-----------//
};
extern TRSTest* TestForInfo;
//extern void(CMFCTRSuiDlg::*callback_refresh_func)();
//extern EditWindow *obj = new EditWindow;