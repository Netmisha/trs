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
	if (sTPriority.IsEmpty() || sTTag.IsEmpty() || sTDisable.IsEmpty() || sTExecution.IsEmpty() || sTParameters.IsEmpty() ||
		sTResult.IsEmpty() || sTRepeat.IsEmpty() || sTTime.IsEmpty() || sTParamRepeat.IsEmpty()) {
		MessageBox(_T("Fill all fields correctly !"), _T("Worning"), MB_ICONINFORMATION | MB_OK);
		return;
	}
	TiXmlDocument doc_xml(CStringA(sPath_ + L""));
	doc_xml.LoadFile();
	TiXmlElement * test = new TiXmlElement("test");
	test->SetAttribute("name", CStringA(sTName));
	test->SetAttribute("description", CStringA(sTDescription));

	TiXmlElement * priority = new TiXmlElement("priority");
	TiXmlText *priority_text = new TiXmlText(CStringA(sTPriority));
	priority->LinkEndChild(priority_text);
	test->LinkEndChild(priority);

	TiXmlElement * tag = new TiXmlElement("tag");
	TiXmlText * tag_text = new TiXmlText(CStringA(sTTag));
	tag->LinkEndChild(tag_text);
	test->LinkEndChild(tag);

	TiXmlElement * disable = new TiXmlElement("disable");
	TiXmlText * disable_text = new TiXmlText(CStringA(sTDisable));
	disable->LinkEndChild(disable_text);
	test->LinkEndChild(disable);

	TiXmlElement * execution = new TiXmlElement("execution");
	TiXmlText * execution_text = new TiXmlText(CStringA(sTExecution));
	execution->LinkEndChild(execution_text);
	test->LinkEndChild(execution);

	TiXmlElement * parameters = new TiXmlElement("parameters");
	parameters->SetAttribute("repeat", CStringA(sTParamRepeat));
	TiXmlText * parameters_text = new TiXmlText(CStringA(sTParameters));
	parameters->LinkEndChild(parameters_text);
	test->LinkEndChild(parameters);

	TiXmlElement * result = new TiXmlElement("result");
	TiXmlText * result_text = new TiXmlText(CStringA(sTResult));
	result->LinkEndChild(result_text);
	test->LinkEndChild(result);

	TiXmlElement * repeat = new TiXmlElement("repeat");
	repeat->SetAttribute("pause", CStringA(sTPause));
	TiXmlText * repeat_text = new TiXmlText(CStringA(sTRepeat));
	repeat->LinkEndChild(repeat_text);
	test->LinkEndChild(repeat);

	TiXmlElement * max_time = new TiXmlElement("maxTime");
	TiXmlText * max_time_text = new TiXmlText(CStringA(sTTime));
	max_time->LinkEndChild(max_time_text);
	test->LinkEndChild(max_time);


	TiXmlElement * waitFor = new TiXmlElement("waitFor");
	if (!sTWait.IsEmpty()){
		TiXmlText * waitFor_text = new TiXmlText(CStringA(sTWait));
		waitFor->LinkEndChild(waitFor_text);
	}
	test->LinkEndChild(waitFor);

	doc_xml.RootElement()->LinkEndChild(test);
	doc_xml.SaveFile();
	MessageBox(_T("Test added!"), _T("Message"), MB_ICONINFORMATION | MB_OK);
	CDialogEx::OnOK();
}


void AddTest::OnBnClickedCancel()
{
	sTName = sTDescription = sTPriority = sTTag = sTDisable = sTResult = sTExecution = sTParameters = sTParamRepeat = sTRepeat = sTPause = sTWait = sTTime = "";
	CDialogEx::OnCancel();
}


void AddTest::setPath(CString path)
{
	sPath_ = path;
}
BOOL AddTest::OnInitDialog(){
	CDialogEx::OnInitDialog();
	UpdateData(false);
	return TRUE;
}
void AddTest::setDefault() {
	sTName = L"Test";
	sTDescription=L"Test description";
	sTPriority=L"4";
	sTTag=L"Debug";
	sTDisable=L"false";
	sTResult=L"0";
	sTParameters=L"1000";
	sTParamRepeat=L"32";
	sTRepeat=L"1";
	sTPause=L"100";
	sTWait=L"";
	sTTime=L"2s";
	sTExecution = L"";
	CStringA path(sPath_);
	char *p = path.GetBuffer() + path.GetLength() - 1;
	while (*(--p) != '\\');
	*(p+1) = '\0';
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	hFind = FindFirstFile(CString(path.GetBuffer()) + L"*.exe", &FindFileData);
	if (hFind != INVALID_HANDLE_VALUE) {
		sTExecution = CString(FindFileData.cFileName);
	}
	FindClose(hFind);
	CString name = sTName;
	int i = 1;
	std::fstream local_file;
	CStringA file(sPath_);
	local_file.open(file.GetBuffer(), std::ios_base::in);
	CStringA data;
	while (!local_file.eof()) {
		char buff[256];
		memset(buff, 0, 256);
		local_file.read(buff, sizeof(buff)-1);
		data += buff;
	}
	local_file.close();
	while (i<1000) {
		name = sTName + L" " +CString(std::to_string(i++).c_str());
		CStringA line("name=\"" + CStringA(name));
		if (!strstr(data.GetBuffer(), line)) {
			sTName = name;
			break;
		}
	}
}
