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
	
	DDX_Control(pDX, ID_SAVEB, Save_button);
	
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
}


BEGIN_MESSAGE_MAP(EditWindow, CDialogEx)
	ON_BN_CLICKED(IDOK, &EditWindow::OnBnClickedOk)
	ON_EN_CHANGE(IDC_AUTHOR, &EditWindow::OnEnChangeAuthor)
	ON_BN_CLICKED(ID_SAVEB, &EditWindow::OnBnClickedSaveb)
	ON_BN_CLICKED(IDC_BUTTON3, &EditWindow::OnBnClickedButton3)
	ON_EN_CHANGE(IDC_COPYRIGHT, &EditWindow::OnEnChangeCopyright)
	ON_BN_CLICKED(IDC_TESTDESCSHOW, &EditWindow::OnBnClickedTestdescshow)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, &EditWindow::OnBnClickedButtonRefresh)
END_MESSAGE_MAP()


// EditWindow message handlers


void EditWindow::OnBnClickedOk() // saveButton
{
	// TODO: Add your control notification handler code here
	
	//CDialogEx::OnOK();
}



BOOL EditWindow::OnInitDialog(){
	CDialogEx::OnInitDialog();
	OnBnClickedButtonRefresh();
	return TRUE;
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

void EditWindow::ParseForHeaderData(){
	doc = new TiXmlDocument(PathToFile.c_str());
	bool OpenOk = doc->LoadFile(PathToFile.c_str());
	if (OpenOk){
		
		TiXmlElement *el = doc->FirstChildElement();
		std::string getN;
		for (TiXmlElement *Parent = el->FirstChildElement(); Parent != 0; Parent = Parent->NextSiblingElement()){
			getN.assign(TestForInfo->getName());
			if (!Test_S.compare(Parent->Value()) && !getN.compare(Parent->Attribute("name"))){
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
	compareData_andChange();
}
void EditWindow::WriteOnChangeToFile(std::string tag, CString new_data, std::string block){
	TiXmlElement *el = doc->FirstChildElement();
	for (TiXmlElement *parent = el->FirstChildElement(); parent != 0; parent = parent->NextSiblingElement()){
		for (TiXmlElement *child = parent->FirstChildElement(); child != 0; child = child->NextSiblingElement()){
			if (!tag.compare(child->Value())){
				child->Clear();
				CT2A ascii_tempData(new_data);
				char *name = ascii_tempData;
				child->LinkEndChild(new TiXmlText(ascii_tempData));
				doc->SaveFile();
				break;
			}
		}
	}
}
bool EditWindow::compareData_andChange(){ 
	changeTestData();
	return 0;
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
#define CheckAndChangeTestData(StrData,child,EditLine,DataString) \
if (!StrData.compare(child->Value())){\
EditLine.GetWindowText(TempData); \
if (TempData.Compare(DataString)){\
	child->Clear(); CT2A ascii(TempData); \
	char *name = ascii; \
	child->LinkEndChild(new TiXmlText(name)); \
	TempData.Empty(); \
	doc->SaveFile(); continue;}\
	continue; \
}

void EditWindow::changeTestData(){
	TiXmlElement *head = doc->FirstChildElement();
	std::string ex = "execution";
	std::string par = "parameters";
	std::string res = "result";
	std::string rep = "repeat";
	std::string pa = "pause";
	std::string wa = "waitFor";
	TempData.Empty();
	std::string name;
	name = TestForInfo->getName();
	for (TiXmlElement *parent = head->FirstChildElement(); parent != 0; parent = parent->NextSiblingElement()){
		if (!Test_S.compare(parent->Value()) && !name.compare(parent->Attribute("name"))){
			TestName_T.GetWindowText(TempData);
			CT2A a(TempData);
			char *t = a;
			std::string tn = parent->Attribute("name");
			if (tn.compare(t)){
				parent->SetAttribute("name", t);
				TempData.Empty();
				doc->SaveFile();
			}

			for (TiXmlElement *child = parent->FirstChildElement(); child != 0; child = child->NextSiblingElement()){
				CheckAndChangeTestData(wa, child, WaitFor_T, WaitFor_TS)
					CheckAndChangeTestData(Priority_S, child, Priority_T, Priority_TS)
					CheckAndChangeTestData(Tag_S, child, Tag_T, Tag_TS)
					CheckAndChangeTestData(Disable_S, child, Disable_T, Disable_TS)
					CheckAndChangeTestData(ex, child, Execution_T, Execution_TS)
					CheckAndChangeTestData(res, child, Result_t, Result_tS)
					CheckAndChangeTestData(Max_S, child, MaxTime_T, MaxTime_TS)
				if (!par.compare(child->Value())){
					Par_T.GetWindowText(TempData);
					if (TempData.Compare(Par_TS)){
						child->Clear();
						CT2A ascii_tempData(TempData);
						char *name = ascii_tempData;
						child->LinkEndChild(new TiXmlText(ascii_tempData));
						TempData.Empty();
						doc->SaveFile();
					}
					Repeat_T.GetWindowText(TempData);
					std::string t = child->Attribute("repeat");
					CT2A ascii_tempData(TempData);
					char *name = ascii_tempData;
					if (t.compare(name)){
						child->SetAttribute("repeat", name);
						TempData.Empty();
						doc->SaveFile();
					}
					continue;
				}

				if (!Repeat_S.compare(child->Value())){
					Repeat_TM.GetWindowText(TempData);
					if (TempData.Compare(Repeat_TMS)){
						child->Clear();
						CT2A ascii_tempData(TempData);
						char *name = ascii_tempData;
						child->LinkEndChild(new TiXmlText(ascii_tempData));
						TempData.Empty();
						doc->SaveFile();
					}
					Pause_TR.GetWindowText(TempData);
					std::string t = child->Attribute("pause");
					CT2A ascii_tempData(TempData);
					char *name = ascii_tempData;
					if (t.compare(name)){
						child->SetAttribute("pause", name);
						TempData.Empty();
						doc->SaveFile();
					}
					continue;
				}

			}
		}
	}

}
void EditWindow::OnBnClickedTestdescshow()
{
	dlgT = new ShowDescription;
	dlgT->Description = Test_desc;
	dlgT->DoModal();
	if (!dlgT == NULL){
		if (dlgT->r == true){
			D = dlgT->getDescriptionData();
			TiXmlElement *parent = doc->RootElement();
			for (TiXmlElement *el = parent->FirstChildElement(); el != 0; el = el->NextSiblingElement()){
				if (!Test_S.compare(el->Value())){
					std::string Tname = el->Attribute("name");
					char *Tn = TestForInfo->getName();
					if (!Tname.compare(Tn)){
						CT2A ascii_tempData(D);
						char *name = ascii_tempData;
						el->SetAttribute("description", name);
						doc->SaveFile();
						D.Empty();
						delete dlgT; dlgT = NULL;
					}
				}
			}
		}
	}

}

void EditWindow::OnBnClickedButtonRefresh()
{
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




