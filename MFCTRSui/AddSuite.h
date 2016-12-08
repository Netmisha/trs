#pragma once
#include "Resource.h"
#include "afxwin.h"
#include "ShowDescription.h"
#include "resource.h"
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
	std::string PathToFile;
	CString sHDescription;
	BOOL OnInitDialog();
	void SetMetaDataAndHeaderDataFromXML();
	TiXmlDocument *doc;
	std::string XMLPath;
	char tempTextXML;

	CEdit Author_EditLine;
	CEdit Date_EditLine;
	CEdit Version_EditLine;
	CEdit Mail_EditLine;
	CEdit Copyright_EditLine;
	CEdit License_EditLine;
	CEdit Info_EditLine;
	afx_msg void OnBnClickedSavebutton();
	CEdit TTag_EditLine;
	CEdit TRepeat_EditLine;
	CEdit TMaxThreads_EditLine;
	CEdit TmaxTime_EditLine;
	CEdit TPriority_EditLine;
	CEdit TDisable_EditLine;
	CEdit TAPause_EditLine;
	CEdit TASuiteName_EditLine;
	CEdit ATDescription_EditLine;
	void CompareAndChangeDataXML();
	CString TempData;
	void WriteOnChangeToFile(std::string tag, CString new_data, std::string block);
	void WriteOnHeaderChange();
};
