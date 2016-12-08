// AddSuite.cpp : implementation file
//

#include "stdafx.h"
#include "AddSuite.h"
#include "afxdialogex.h"
#include <Windows.h>
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
	DDX_Control(pDX, IDC_AUTHOR, Author_EditLine);
	DDX_Control(pDX, IDC_DATE, Date_EditLine);
	DDX_Control(pDX, IDC_VERSION, Version_EditLine);
	DDX_Control(pDX, IDC_MAIL, Mail_EditLine);
	DDX_Control(pDX, IDC_COPYRIGHT, Copyright_EditLine);
	DDX_Control(pDX, IDC_LICENSE, License_EditLine);
	DDX_Control(pDX, IDC_INFO, Info_EditLine);
	DDX_Control(pDX, IDC_TAGH, TTag_EditLine);
	DDX_Control(pDX, IDC_REPEAT, TRepeat_EditLine);
	DDX_Control(pDX, IDC_MAXTHREADS, TMaxThreads_EditLine);
	DDX_Control(pDX, IDC_MAXTIME, TmaxTime_EditLine);
	DDX_Control(pDX, IDC_PRIORITY, TPriority_EditLine);
	DDX_Control(pDX, IDC_DISABLE, TDisable_EditLine);
	DDX_Control(pDX, IDC_PAUSE, TAPause_EditLine);
	DDX_Control(pDX, IDC_SUITENAME, TASuiteName_EditLine);
	DDX_Control(pDX, IDC_SUITENAME2, ATDescription_EditLine);
}


BEGIN_MESSAGE_MAP(AddSuite, CDialogEx)
	ON_BN_CLICKED(IDOK, &AddSuite::OnBnClickedOk)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &AddSuite::OnTcnSelchangeTab1)
	ON_BN_CLICKED(IDCANCEL, &AddSuite::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_SaveButton, &AddSuite::OnBnClickedSavebutton)
END_MESSAGE_MAP()


// AddSuite message handlers

void AddSuite::setPath(CString & sPath) {
	sPath_ = sPath;
}
CString AddSuite::getPathToFile() {
	return sPath_ + sSuiteName + "\\" + sSuiteName + ".xml";
}
CString AddSuite::getPath() {
	return sPath_ + sSuiteName;
}
void AddSuite::OnBnClickedOk()
{
	UpdateData();
	if (sHRepeat.IsEmpty() || sHTime.IsEmpty() || sHThread.IsEmpty() || sHTag.IsEmpty() || sMDMail.IsEmpty() || sSuiteName.IsEmpty() ||
		sMDVersion.IsEmpty() || sMDDate.IsEmpty() || sMDAuthor.IsEmpty() || sHDisable.IsEmpty() || sHPriority.IsEmpty()) {
		MessageBox(_T("Fill all fields correctly !"), _T("Worning"), MB_ICONINFORMATION | MB_OK);
		return;
	}
	if (CreateDirectory(sPath_ + sSuiteName, NULL) == ERROR_ALREADY_EXISTS) {
		MessageBox(_T("Directory already exists! Enter another name."), _T("Worning"), MB_ICONINFORMATION | MB_OK);
		return;
	}
	HANDLE hFile;
	hFile = CreateFile(sPath_ + sSuiteName + "\\" + sSuiteName + ".xml", FILE_APPEND_DATA, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
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
	if (!sMDCopyright.IsEmpty()) {
		TiXmlText * copyright_text = new TiXmlText(CStringA(sMDCopyright));
		copyright->LinkEndChild(copyright_text);
	}
	metadata->LinkEndChild(copyright);

	TiXmlElement * license = new TiXmlElement("license");
	if (!sMDLicense.IsEmpty()) {
		TiXmlText * license_text = new TiXmlText(CStringA(sMDLicense));
		license->LinkEndChild(license_text);
	}
	metadata->LinkEndChild(license);

	TiXmlElement * info = new TiXmlElement("info");
	if (!sMDInfo.IsEmpty()) {
		TiXmlText * info_text = new TiXmlText(CStringA(sMDInfo));
		info->LinkEndChild(info_text);
	}
	metadata->LinkEndChild(info);
	doc.SaveFile();
	MessageBox(_T("Suite added!"), _T("Message"), MB_ICONINFORMATION | MB_OK);
	CDialogEx::OnOK();
}


void AddSuite::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
}
#define SetDataFromXML(tag,string,PC) if(!tag.compare(PC->Value())){string = PC->GetText();}
void AddSuite::SetMetaDataAndHeaderDataFromXML(){	
	doc = new TiXmlDocument(PathToFile.c_str());
	bool loadok = doc->LoadFile(PathToFile.c_str());
	if (!loadok) MessageBox(_T("Could not load test data"), _T("Message"), MB_ICONINFORMATION | MB_OK);
	TiXmlElement *el = doc->FirstChildElement();
	std::string a = "author";
	std::string d = "date";
	std::string v = "version";
	std::string m = "mail";
	std::string c = "copyright";
	std::string l = "license";
	std::string i = "info";
	std::string me = "metadata";
	
	TiXmlElement *f = doc->RootElement();
	sHSuiteName = f->Attribute("name");
	sHDescription = f->Attribute("description");
	for (TiXmlElement *parent = el->FirstChildElement(); parent != 0; parent = parent->NextSiblingElement()){
		if (!me.compare(parent->Value())){
			for (TiXmlElement *child = parent->FirstChildElement(); child != 0; child = child->NextSiblingElement()){
					SetDataFromXML(a, sMDAuthor,child)
					SetDataFromXML(d, sMDDate,child)
					SetDataFromXML(v, sMDVersion,child)
					SetDataFromXML(m, sMDMail,child)
					SetDataFromXML(c, sMDCopyright,child)
					SetDataFromXML(l, sMDLicense,child)
					SetDataFromXML(i, sMDInfo,child)					
			}
			break;
		}
	}
	{
		std::string t = "tag";
		std::string r = "repeat";
		std::string p = "pause";
		std::string mT = "maxTime";
		std::string mTh = "maxThreads";
		std::string pr = "priority";
		std::string d = "disable";
		for (TiXmlElement *parent = el->FirstChildElement(); parent != 0; parent = parent->NextSiblingElement()){
				SetDataFromXML(t,sHTag,parent)
				if (!r.compare(parent->Value())){ sHPause = parent->Attribute("pause"); sHRepeat = parent->GetText(); }
				SetDataFromXML(mT, sHTime, parent)
				SetDataFromXML(mTh, sHThread, parent)
				SetDataFromXML(pr, sHPriority, parent)
				SetDataFromXML(d, sHDisable, parent)
		}
	}
		
}
void AddSuite::WriteOnChangeToFile(std::string tag, CString new_data, std::string block){
	TiXmlElement *el = doc->FirstChildElement();
	for (TiXmlElement *parent = el->FirstChildElement(); parent != 0; parent = parent->NextSiblingElement()){
		for (TiXmlElement *child = parent->FirstChildElement(); child != 0; child = child->NextSiblingElement()){
			if (!tag.compare(child->Value())){
				child->Clear();
				CT2A ascii_tempData(new_data);
				char *name = ascii_tempData;
				child->LinkEndChild(new TiXmlText(ascii_tempData));
				//TempData.Empty();
				doc->SaveFile();
				break;
			}
		}
	}
}
void AddSuite::CompareAndChangeDataXML(){

	std::string a = "author";
	std::string d = "date";
	std::string v = "version";
	std::string m = "mail";
	std::string c = "copyright";
	std::string l = "license";
	std::string i = "info";
	std::string me = "metadata";
	
	Author_EditLine.GetWindowText(TempData);
	if (TempData.Compare(sMDAuthor)){
	WriteOnChangeToFile(a, TempData, me);

	}
	Version_EditLine.GetWindowText(TempData);
	if (TempData.Compare(sMDVersion)){
	WriteOnChangeToFile(v, TempData, me);
	}
	Date_EditLine.GetWindowText(TempData);
	if (TempData.Compare(sMDDate)){
	WriteOnChangeToFile(d, TempData, me);
	}
	Mail_EditLine.GetWindowText(TempData);
	if (TempData.Compare(sMDMail)){
	WriteOnChangeToFile(m, TempData, me);
	}
	Copyright_EditLine.GetWindowText(TempData);
	if (TempData.Compare(sMDCopyright)){
	WriteOnChangeToFile(c, TempData, me);
	}
	License_EditLine.GetWindowText(TempData);
	if (TempData.Compare(sMDLicense)){
	WriteOnChangeToFile(l, TempData, me);
	}
	Info_EditLine.GetWindowText(TempData);
	if (TempData.Compare(sMDInfo)){
	WriteOnChangeToFile(i, TempData, me);
	}
	WriteOnHeaderChange();
}
#define CompareAndChange(StrData,parent,EditLine,DataString) \
if (!StrData.compare(parent->Value())){\
	EditLine.GetWindowText(TempData); \
if (DataString.Compare(TempData)){\
	parent->Clear(); CT2A ascii(TempData); \
	char *name = ascii; \
	parent->LinkEndChild(new TiXmlText(name)); \
	TempData.Empty(); \
	doc->SaveFile();}\
}

void AddSuite::WriteOnHeaderChange(){
	TiXmlElement *el = doc->RootElement();
	TASuiteName_EditLine.GetWindowText(TempData);
	CT2A a(TempData);
	char *t = a;
	std::string tn = el->Attribute("name");
	if (tn.compare(t)){
		el->SetAttribute("name", t);
		TempData.Empty();
		doc->SaveFile();
	}
	std::string tg = "tag";
	std::string rr = "repeat";
	std::string pa = "pause";
	std::string mT = "maxTime";
	std::string mTh = "maxThreads";
	std::string pr = "priority";
	std::string di = "disable";
	for (TiXmlElement *parent = el->FirstChildElement(); parent != 0; parent = parent->NextSiblingElement()){
			CompareAndChange(tg, parent, TTag_EditLine, sHTag)
			CompareAndChange(mT, parent, TmaxTime_EditLine, sHTime)
			CompareAndChange(mTh, parent, TMaxThreads_EditLine, sHThread)
			CompareAndChange(pr, parent, TPriority_EditLine, sHPriority)
			CompareAndChange(di, parent, TDisable_EditLine, sHDisable)
		if (!rr.compare(parent->Value())){
			TRepeat_EditLine.GetWindowText(TempData);
			if (sHRepeat.Compare(TempData)){
				parent->Clear();
				CT2A ascii_tempData(TempData);
				char *name = ascii_tempData;
				parent->LinkEndChild(new TiXmlText(ascii_tempData));
				TempData.Empty();
				doc->SaveFile();
			}
			TAPause_EditLine.GetWindowText(TempData);
			if (sHPause.Compare(TempData)){ 
				CT2A ascii_tempData(TempData);
				char *name = ascii_tempData;
				parent->SetAttribute("pause", name);
				TempData.Empty();
				doc->SaveFile();

			}
		}
	}
}
BOOL AddSuite::OnInitDialog(){
	CDialogEx::OnInitDialog();
	GetDlgItem(IDOK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_SUITENAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC)->ShowWindow(SW_HIDE);
	
	SetMetaDataAndHeaderDataFromXML();
	Author_EditLine.SetWindowTextW(sMDAuthor);
	Date_EditLine.SetWindowTextW(sMDDate);
	Version_EditLine.SetWindowTextW(sMDVersion);
	Mail_EditLine.SetWindowTextW(sMDMail);
	Copyright_EditLine.SetWindowTextW(sMDCopyright);
	License_EditLine.SetWindowTextW(sMDLicense);
	Info_EditLine.SetWindowTextW(sMDInfo);
	TTag_EditLine.SetWindowTextW(sHTag);
	TRepeat_EditLine.SetWindowTextW(sHRepeat);
	TMaxThreads_EditLine.SetWindowTextW(sHThread);
	TmaxTime_EditLine.SetWindowTextW(sHTime);
	TPriority_EditLine.SetWindowTextW(sHPriority);
	TDisable_EditLine.SetWindowTextW(sHDisable);
	TAPause_EditLine.SetWindowTextW(sHPause);
	TASuiteName_EditLine.SetWindowTextW(sHSuiteName);	
	ATDescription_EditLine.SetWindowTextW(sHDescription);

	return TRUE;
}
void AddSuite::OnBnClickedCancel()
{
	sSuiteName = sMDAuthor = sMDDate = sMDVersion = sMDMail = sMDCopyright = sMDLicense = sMDInfo = sHTag = sHRepeat =
		sHThread = sHTime = sHPriority = sHDisable = sHSuiteName = sHPause = "";
	UpdateData(false);
	CDialogEx::OnCancel();
}


void AddSuite::OnBnClickedSavebutton()
{
	CompareAndChangeDataXML();
	// TODO: Add your control notification handler code here
}
