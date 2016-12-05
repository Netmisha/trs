// AddTest.cpp : implementation file
//

#include "stdafx.h"
#include "AddTest.h"
#include "afxdialogex.h"
#include <Windows.h>
#include <TRSLibrary\TinyXML\tinyxml.h>

// AddTest dialog

IMPLEMENT_DYNAMIC(AddTest, CDialogEx)

AddTest::AddTest(CWnd* pParent /*=NULL*/)
	: CDialogEx(AddTest::IDD, pParent)
	, sTName(_T(""))
	, sTDescription(_T(""))
	, sTPriority(_T(""))
	, sTTag(_T(""))
	, sTDisable(_T(""))
	, sTResult(_T(""))
	, sTExecution(_T(""))
	, sTParameters(_T(""))
	, sTRepeat(_T(""))
	, sTPause(_T(""))
	, sTWait(_T(""))
	, sTTime(_T(""))
{

}

AddTest::~AddTest()
{
}

void AddTest::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DTESTNAME, sTName);
	DDX_Text(pDX, IDC_DTESTNAME2, sTDescription);
	DDX_Text(pDX, IDC_DPRIORITYT, sTPriority);
	DDX_Text(pDX, IDC_DTAGT, sTTag);
	DDX_Text(pDX, IDC_DDISABLET, sTDisable);
	DDX_Text(pDX, IDC_DRESULT, sTResult);
	DDX_Text(pDX, IDC_DEXECUTION, sTExecution);
	DDX_Text(pDX, IDC_DPARAMETERS, sTParameters);
	DDX_Text(pDX, IDC_DREPEATT, sTParamRepeat);
	DDX_Text(pDX, IDC_DREPEATTP, sTRepeat);
	DDX_Text(pDX, IDC_DPAUSEPT, sTPause);
	DDX_Text(pDX, IDC_DWAITFORT, sTWait);
	DDX_Text(pDX, IDC_DMAXTIMET, sTTime);
	DDX_Control(pDX, IDC_DEXECUTION, cExecution);
}


BEGIN_MESSAGE_MAP(AddTest, CDialogEx)
	ON_BN_CLICKED(IDC_DBUTTON1, &AddTest::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &AddTest::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &AddTest::OnBnClickedCancel)
END_MESSAGE_MAP()


// AddTest message handlers


void AddTest::OnBnClickedButton1()
{
	CFileDialog fileDialog(TRUE);	//объект класса выбора файла
	OPENFILENAME& ofn = fileDialog.GetOFN();
	ofn.lpstrFilter = L"Programs (*.exe)\0*.exe\0";
	ofn.lpstrTitle = L"Select File";
	ofn.lpstrInitialDir = sPath_;
	int result = fileDialog.DoModal();	//запустить диалоговое окно
	if (result == IDOK)	//если файл выбран
	{
		cExecution.SetWindowTextW(fileDialog.GetPathName());
	}
}


void AddTest::OnBnClickedOk()
{
	UpdateData();
	TiXmlDocument doc_xml(CStringA(sPath_ + L""));
	doc_xml.LoadFile();
	TiXmlElement * test = new TiXmlElement("test");
	test->SetAttribute("name", CStringA(sTName));
	test->SetAttribute("description", CStringA(sTDescription));

	TiXmlElement * priority = new TiXmlElement("priority");
	if (!sTPriority.IsEmpty()){
		TiXmlText *priority_text = new TiXmlText(CStringA(sTPriority));
		priority->LinkEndChild(priority_text);
	}
	test->LinkEndChild(priority);

	TiXmlElement * tag = new TiXmlElement("tag");
	if (!sTTag.IsEmpty()){
		TiXmlText * tag_text = new TiXmlText(CStringA(sTTag));
		tag->LinkEndChild(tag_text);
	}
	test->LinkEndChild(tag);

	TiXmlElement * disable = new TiXmlElement("disable");
	if (!sTDisable.IsEmpty()){
		TiXmlText * disable_text = new TiXmlText(CStringA(sTDisable));
		disable->LinkEndChild(disable_text);
	}
	test->LinkEndChild(disable);

	TiXmlElement * execution = new TiXmlElement("execution");
	if (!sTExecution.IsEmpty()){
		TiXmlText * execution_text = new TiXmlText(CStringA(sTExecution));
		execution->LinkEndChild(execution_text);
	}
	test->LinkEndChild(execution);

	TiXmlElement * parameters = new TiXmlElement("parameters");
	parameters->SetAttribute("repeat", CStringA(sTParamRepeat));
	if (!sTParameters.IsEmpty()){
		TiXmlText * parameters_text = new TiXmlText(CStringA(sTParameters));
		parameters->LinkEndChild(parameters_text);
	}
	test->LinkEndChild(parameters);

	TiXmlElement * result = new TiXmlElement("result");
	if (!sTResult.IsEmpty()){
		TiXmlText * result_text = new TiXmlText(CStringA(sTResult));
		result->LinkEndChild(result_text);
	}
	test->LinkEndChild(result);

	TiXmlElement * repeat = new TiXmlElement("repeat");
	repeat->SetAttribute("pause", CStringA(sTPause));
	if (!sTRepeat.IsEmpty()){
		TiXmlText * repeat_text = new TiXmlText(CStringA(sTRepeat));
		repeat->LinkEndChild(repeat_text);
	}
	test->LinkEndChild(repeat);

	TiXmlElement * max_time = new TiXmlElement("maxTime");
	if (!sTTime.IsEmpty()){
		TiXmlText * max_time_text = new TiXmlText(CStringA(sTTime));
		max_time->LinkEndChild(max_time_text);
	}
	test->LinkEndChild(max_time);


	TiXmlElement * waitFor = new TiXmlElement("waitFor");
	if (!sTWait.IsEmpty()){
		TiXmlText * waitFor_text = new TiXmlText(CStringA(sTWait));
		waitFor->LinkEndChild(waitFor_text);
	}
	test->LinkEndChild(waitFor);

	doc_xml.RootElement()->LinkEndChild(test);
	doc_xml.SaveFile();
	CDialogEx::OnOK();
}


void AddTest::OnBnClickedCancel()
{
	sTName=sTDescription=sTPriority=sTTag=sTDisable=sTResult=sTExecution=sTParameters=sTParamRepeat= sTRepeat=sTPause=sTWait=sTTime="";
	CDialogEx::OnCancel();
}


void AddTest::setPath(CString path)
{
	sPath_ = path;
}
