// EditWindow.cpp : implementation file
//

#include "stdafx.h"
#include "EditWindow.h"
#include "afxdialogex.h"
#include "TestInfo.h"
#include "ShowDescription.h"
// EditWindow dialog

IMPLEMENT_DYNAMIC(EditWindow, CDialogEx)

EditWindow::EditWindow(CWnd* pParent /*=NULL*/)
	: CDialogEx(EditWindow::IDD, pParent)
{

}

EditWindow::~EditWindow()
{
}

void EditWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_AUTHOR, Author_name);
	DDX_Control(pDX, ID_SAVEB, Save_button);
	DDX_Control(pDX, IDC_DATE, date_V);
	DDX_Control(pDX, IDC_VERSION, Version_V);
	DDX_Control(pDX, IDC_MAIL, Mail_V);
	DDX_Control(pDX, IDC_COPYRIGHT, Copyrgiht_V);
	DDX_Control(pDX, IDC_LICENSE, License_V);
	DDX_Control(pDX, IDC_INFO, Info_V);
	DDX_Control(pDX, IDC_TESTNAME, TestName_T);
	DDX_Control(pDX, IDC_PRIORITYT, Priority_T);
	DDX_Control(pDX, IDC_TAGT, Tag_T);
	DDX_Control(pDX, IDC_DISABLET, Disable_T);
	DDX_Control(pDX, IDC_EXECUTION, Execution_T);
	DDX_Control(pDX, IDC_PARAMETERS, Par_T);
	DDX_Control(pDX, IDC_REPEATTP, Repeat_T);
	DDX_Control(pDX, IDC_RESULT, Result_t);
	DDX_Control(pDX, IDC_REPEATT, Repeat_TM);
	DDX_Control(pDX, IDC_MAXTIMET, MaxTime_T);
	DDX_Control(pDX, IDC_WAITFORT, WaitFor_T);
	DDX_Control(pDX, IDC_PAUSEPT, Pause_TR);
	DDX_Control(pDX, IDC_TAGH, TagV);
	DDX_Control(pDX, IDC_REPEAT, RepeatV);
	DDX_Control(pDX, IDC_MAXTHREADS, MaxThreadsV);
	DDX_Control(pDX, IDC_PAUSE, PauseV);
	DDX_Control(pDX, IDC_MAXTIME, maxTimeV);
	DDX_Control(pDX, IDC_PRIORITY, PriorityV);
	DDX_Control(pDX, IDC_DISABLE, DisableV);
	DDX_Control(pDX, IDC_SUITENAME, SuiteNameV);
}


BEGIN_MESSAGE_MAP(EditWindow, CDialogEx)
	ON_BN_CLICKED(IDOK, &EditWindow::OnBnClickedOk)
//	ON_EN_CHANGE(IDC_EDIT20, &EditWindow::OnEnChangeEdit20)
//	ON_EN_CHANGE(IDC_EDIT26, &EditWindow::OnEnChangeEdit26)
ON_EN_CHANGE(IDC_AUTHOR, &EditWindow::OnEnChangeAuthor)
ON_BN_CLICKED(ID_SAVEB, &EditWindow::OnBnClickedSaveb)
ON_BN_CLICKED(IDC_REFRESH, &EditWindow::OnBnClickedRefresh)
ON_BN_CLICKED(IDC_BUTTON3, &EditWindow::OnBnClickedButton3)
ON_EN_CHANGE(IDC_COPYRIGHT, &EditWindow::OnEnChangeCopyright)
ON_BN_CLICKED(IDC_HEADERDESCSHOW, &EditWindow::OnBnClickedHeaderdescshow)
ON_BN_CLICKED(IDC_TESTDESCSHOW, &EditWindow::OnBnClickedTestdescshow)
END_MESSAGE_MAP()


// EditWindow message handlers


void EditWindow::OnBnClickedOk() // saveButton
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString strd = L"HELLO";
	//Author_name.GetWindowText(strd);
	Author_name.SetWindowTextW(strd);
	UpdateData(FALSE);
	//CDialogEx::OnOK();
}




void EditWindow::OnEnChangeAuthor()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
void EditWindow::setTestdataFromXML(){
	TestName_TS = TestForInfo->getName();
	Priority_TS = TestForInfo->getPriority();
	Tag_TS = TestForInfo->getTag();
	Disable_TS = TestForInfo->getDisable();
	Execution_TS = TestForInfo->get_executableName();
	Par_TS = TestForInfo->getParameters();
	Result_tS = TestForInfo->get_expectedResult();
	Repeat_TMS = TestForInfo->getRepeat();
	MaxTime_TS = TestForInfo->getMaxTime();
	WaitFor_TS = TestForInfo->getWaitFor();

}
void EditWindow::setMetadataFromXML(){
	Author = TestForInfo->getMetadata()->getName();
	Date = TestForInfo->getMetadata()->getDate();
	Version = TestForInfo->getMetadata()->getVersion();
	Mail = TestForInfo->getMetadata()->getMail();
	Copyright = TestForInfo->getMetadata()->getCopyright();
	License = TestForInfo->getMetadata()->getLicense();
	Info = TestForInfo->getMetadata()->getInfo();
	if (Author.IsEmpty()){ Author = L"EMPTY"; }
	if (Date.IsEmpty()){ Date = L"EMPTY"; }
	if (Version.IsEmpty()){ Version = L"EMPTY"; }
	if (Mail.IsEmpty()){ Mail = L"EMPTY"; }
	if (Copyright.IsEmpty()){ Copyright = L"EMPTY"; }
	if (License.IsEmpty()){ License = L"EMPTY"; }
	if (Info.IsEmpty()){ Info = L"EMPTY"; }
}
void EditWindow::ParseForHeaderData(){
	doc = new TiXmlDocument(PathToFile.c_str());
	bool OpenOk = doc->LoadFile(PathToFile.c_str());
	if (OpenOk){
		TiXmlElement *head;
		TiXmlElement *f = doc->RootElement();
		SuiteName_S = f->Attribute("name"); //      <----- sets Suites name 
		SuiteDesc_S = f->Attribute("description");
		TiXmlElement *el = doc->FirstChildElement();
		std::string getN;
		for (TiXmlElement *Parent = el->FirstChildElement(); Parent != 0; Parent = Parent->NextSiblingElement()){
			getN.assign(TestForInfo->getName());
			if (!Tag_S.compare(Parent->Value())){
				Head_Tag_S = Parent->GetText();
				continue;
			}
			else if (!Repeat_S.compare(Parent->Value())){
				Head_Repeat_S = Parent->GetText();
				HeadRepeat_Pause = Parent->Attribute("pause");
				continue;
			}
			else if (!Max_S.compare(Parent->Value())){
				Head_MaxTime_S = Parent->GetText();
				continue;
			}
			else if (!maxThreads_S.compare(Parent->Value())){
				Head_MaxThreads_S = Parent->GetText();
				continue;
			}
			else if (!Disable_S.compare(Parent->Value())){
				Head_Disable_S = Parent->GetText();
				continue;
			}
			else if (!Priority_S.compare(Parent->Value())){
				Head_Priority_S = Parent->GetText();
				continue;
			}
			else if (!Test_S.compare(Parent->Value()) && !getN.compare(Parent->Attribute("name"))){
				//-------this block will get the test attributes_such as (repeat) and (pause)-------//
				Test_desc = Parent->Attribute("description");
				for (TiXmlElement *child = Parent->FirstChildElement(); child != 0; child = child->NextSiblingElement()){
					if (child->Attribute("repeat")){ Repeat_TS = child->Attribute("repeat"); }
					else if (child->Attribute("pause")){ Pause_TRS = child->Attribute("pause"); }
				}
				break;

				//--------------------end_of_block---------------------------------//
			}
		}	
	}
	else{
		MessageBox(L".xml file cannot be loaded", L"Info", MB_OK);
		return;	
	}
}
void EditWindow::OnBnClickedSaveb()
{
	// TODO: Add your control notification handler code here

	doc->SaveFile();
}

void EditWindow::OnBnClickedHeaderdescshow()
{
	ShowDescription dlg;
	dlg.Description = SuiteDesc_S;
	dlg.DoModal();
}

void EditWindow::OnBnClickedTestdescshow()
{
	ShowDescription dlg;
	dlg.Description = Test_desc;
	dlg.DoModal();
}
void EditWindow::OnBnClickedRefresh()
{
	setMetadataFromXML();
	Author_name.SetWindowTextW(Author);
	date_V.SetWindowTextW(Date);
	Version_V.SetWindowTextW(Version);
	Mail_V.SetWindowTextW(Mail);
	Copyrgiht_V.SetWindowTextW(Copyright);
	License_V.SetWindowTextW(License);
	Info_V.SetWindowTextW(Info);

	setTestdataFromXML();
	TestName_T.SetWindowTextW(TestName_TS);
	Priority_T.SetWindowTextW(Priority_TS);
	Tag_T.SetWindowTextW(Tag_TS);
	Disable_T.SetWindowTextW(Disable_TS);
	Execution_T.SetWindowTextW(Execution_TS);
	Par_T.SetWindowTextW(Par_TS);
	Result_t.SetWindowTextW(Result_tS);
	Repeat_TM.SetWindowTextW(Repeat_TMS);
	MaxTime_T.SetWindowTextW(MaxTime_TS);
	WaitFor_T.SetWindowTextW(WaitFor_TS);
	
	ParseForHeaderData();
	TagV.SetWindowTextW(Head_Tag_S);
	RepeatV.SetWindowTextW(Head_Repeat_S);
	MaxThreadsV.SetWindowTextW(Head_MaxThreads_S);
	PauseV.SetWindowTextW(HeadRepeat_Pause);
	maxTimeV.SetWindowTextW(Head_MaxTime_S);
	PriorityV.SetWindowTextW(Head_Priority_S);
	DisableV.SetWindowTextW(Head_Disable_S);
	SuiteNameV.SetWindowTextW(SuiteName_S);
	Repeat_T.SetWindowTextW(Repeat_TS);
	Pause_TR.SetWindowTextW(Pause_TRS);
	// TODO: Add your control notification handler code here
}



void EditWindow::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
}


void EditWindow::OnEnChangeCopyright()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}




