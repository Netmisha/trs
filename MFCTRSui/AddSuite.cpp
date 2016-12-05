// AddSuite.cpp : implementation file
//

#include "stdafx.h"
#include "AddSuite.h"
#include "afxdialogex.h"
#include <Windows.h>
#include <fstream>
#include <TRSLibrary\TinyXML\tinyxml.h>

// AddSuite dialog

IMPLEMENT_DYNAMIC(AddSuite, CDialogEx)

AddSuite::AddSuite(CWnd* pParent /*=NULL*/)
	: CDialogEx(AddSuite::IDD, pParent)
	, sSuiteName(_T(""))
	, sMDAuthor(_T(""))
	, sMDDate(_T(""))
	, sMDVersion(_T(""))
	, sMDMail(_T(""))
	, sMDLicense(_T(""))
	, sMDInfo(_T(""))
	, sHTag(_T(""))
	, sHRepeat(_T(""))
	, sHThread(_T(""))
	, sHTime(_T(""))
	, sHPriority(_T(""))
	, sHDisable(_T(""))
	, sHSuiteName(_T(""))
	, sHPause(_T(""))
	, sHDescription(_T(""))
{

}

AddSuite::~AddSuite()
{
}

void AddSuite::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SUITENAME, sSuiteName);
	DDX_Text(pDX, IDC_AUTHOR, sMDAuthor);
	DDX_Text(pDX, IDC_DATE, sMDDate);
	DDX_Text(pDX, IDC_VERSION, sMDVersion);
	DDX_Text(pDX, IDC_MAIL, sMDMail);
	DDX_Text(pDX, IDC_COPYRIGHT, sMDCopyright);
	DDX_Text(pDX, IDC_LICENSE, sMDLicense);
	DDX_Text(pDX, IDC_INFO, sMDInfo);
	DDX_Text(pDX, IDC_TAGH, sHTag);
	DDX_Text(pDX, IDC_REPEAT, sHRepeat);
	DDX_Text(pDX, IDC_MAXTHREADS, sHThread);
	DDX_Text(pDX, IDC_MAXTIME, sHTime);
	DDX_Text(pDX, IDC_PRIORITY, sHPriority);
	DDX_Text(pDX, IDC_DISABLE, sHDisable);
	DDX_Text(pDX, IDC_SUITENAME, sHSuiteName);
	DDX_Text(pDX, IDC_PAUSE, sHPause);
	DDX_Text(pDX, IDC_SUITENAME2, sHDescription);
}


BEGIN_MESSAGE_MAP(AddSuite, CDialogEx)
	ON_BN_CLICKED(IDOK, &AddSuite::OnBnClickedOk)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &AddSuite::OnTcnSelchangeTab1)
	ON_BN_CLICKED(IDCANCEL, &AddSuite::OnBnClickedCancel)
END_MESSAGE_MAP()


// AddSuite message handlers

void AddSuite::setPath(CString & sPath) {
	sPath_ = sPath;
}
CString AddSuite::getPathToFile() {
	return sPath_ + sSuiteName + "\\" + sSuiteName + ".xml";
}
void AddSuite::OnBnClickedOk()
{
	UpdateData();
	CreateDirectory(sPath_ + sSuiteName, NULL);
	HANDLE hFile;
	hFile = CreateFile(sPath_ + sSuiteName+"\\"+sSuiteName+".xml", FILE_APPEND_DATA, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	CloseHandle(hFile);
	TiXmlDocument doc(CStringA(sPath_ + sSuiteName + L"\\" + sSuiteName + L".xml"));
	TiXmlDeclaration * decl = new TiXmlDeclaration("1.0", "", "");
	doc.LinkEndChild(decl);
	
	TiXmlElement * suite = new TiXmlElement("suite");
	suite->SetAttribute("name", CStringA(sHSuiteName));
	suite->SetAttribute("description", CStringA(sHDescription));
	doc.LinkEndChild(suite);
	
	TiXmlElement * tag = new TiXmlElement("tag");
	TiXmlText * tag_text = new TiXmlText(CStringA(sHTag));
	tag->LinkEndChild(tag_text);
	suite->LinkEndChild(tag);
	
	TiXmlElement * repeat = new TiXmlElement("repeat");
	repeat->SetAttribute("pause", CStringA(sHPause));
	TiXmlText * repeat_text = new TiXmlText(CStringA(sHRepeat));
	repeat->LinkEndChild(repeat_text);
	suite->LinkEndChild(repeat);
	
	TiXmlElement * max_time = new TiXmlElement("maxTime");
	TiXmlText * max_time_text = new TiXmlText(CStringA(sHTime));
	max_time->LinkEndChild(max_time_text);
	suite->LinkEndChild(max_time);
	
	TiXmlElement * max_thread = new TiXmlElement("maxThreads");
	TiXmlText * max_thread_text = new TiXmlText(CStringA(sHThread));
	max_thread->LinkEndChild(max_thread_text);
	suite->LinkEndChild(max_thread);
	
	TiXmlElement * priority = new TiXmlElement("priority");
	TiXmlText *priority_text = new TiXmlText(CStringA(sHPriority));
	priority->LinkEndChild(priority_text);
	suite->LinkEndChild(priority);
	
	TiXmlElement * disable = new TiXmlElement("disable");
	TiXmlText * disable_text = new TiXmlText(CStringA(sHDisable));
	disable->LinkEndChild(disable_text);
	suite->LinkEndChild(disable);
	
	TiXmlElement * metadata = new TiXmlElement("metadata");
	suite->LinkEndChild(metadata);
	
	TiXmlElement * author = new TiXmlElement("author");
	TiXmlText * author_text = new TiXmlText(CStringA(sMDAuthor));
	author->LinkEndChild(author_text);
	metadata->LinkEndChild(author);
	
	TiXmlElement * date = new TiXmlElement("date");
	TiXmlText * date_text = new TiXmlText(CStringA(sMDDate));
	date->LinkEndChild(date_text);
	metadata->LinkEndChild(date);
	
	TiXmlElement * version = new TiXmlElement("version");
	TiXmlText * version_text = new TiXmlText(CStringA(sMDVersion));
	version->LinkEndChild(version_text);
	metadata->LinkEndChild(version);
	
	TiXmlElement * mail = new TiXmlElement("mail");
	TiXmlText * mail_text = new TiXmlText(CStringA(sMDMail));
	mail->LinkEndChild(mail_text);
	metadata->LinkEndChild(mail);
	
	TiXmlElement * copyright = new TiXmlElement("copyright");
	TiXmlText * copyright_text = new TiXmlText(CStringA(sMDCopyright));
	copyright->LinkEndChild(copyright_text);
	metadata->LinkEndChild(copyright);
	
	TiXmlElement * license = new TiXmlElement("license");
	TiXmlText * license_text = new TiXmlText(CStringA(sMDLicense));
	license->LinkEndChild(license_text);
	metadata->LinkEndChild(license);
	
	TiXmlElement * info = new TiXmlElement("info");
	TiXmlText * info_text = new TiXmlText(CStringA(sMDInfo));
	info->LinkEndChild(info_text);
	metadata->LinkEndChild(info);


	TiXmlPrinter printer;
	doc.Accept(&printer);
	CStringA s_data;
	s_data = printer.CStr();
	/*std::fstream f;
	f.open(CStringA(sPath_ + sSuiteName + "L\\" + sSuiteName + L".xml").GetBuffer(), std::ios_base::out);
	f.write(s_data.GetBuffer(), s_data.GetLength());
	f.close();*/
	doc.SaveFile();
	CDialogEx::OnOK();
}


void AddSuite::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void AddSuite::OnBnClickedCancel()
{
	sSuiteName=sMDAuthor=sMDDate=sMDVersion=sMDMail=sMDCopyright=sMDLicense=sMDInfo=sHTag=sHRepeat=
		sHThread=sHTime=sHPriority=sHDisable=sHSuiteName=sHPause="";
	UpdateData(false);
	CDialogEx::OnCancel();
}
