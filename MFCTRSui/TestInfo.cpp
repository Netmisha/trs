// TestInfo.cpp : implementation file
//

#include "stdafx.h"
#include "TestInfo.h"
#include "afxdialogex.h"


// TestInfo dialog
TRSTest* TestForInfo;
IMPLEMENT_DYNAMIC(TestInfo, CDialogEx)

TestInfo::TestInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(TestInfo::IDD, pParent)
{

}

TestInfo::~TestInfo()
{
}
void TestInfo::ClearEditBox(){
	EditWindowCall = true;
}
void TestInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_TreeEdit);
}


BEGIN_MESSAGE_MAP(TestInfo, CDialogEx)
END_MESSAGE_MAP()

BOOL TestInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetWindowText(L"Test Info");
	CString mes;
	mes.Format(L"%S", TestForInfo->getName());
	m_TreeEdit.ReplaceSel(L"Test name: ");
	int end = m_TreeEdit.GetWindowTextLength();
	m_TreeEdit.SetSel(end, end);
	m_TreeEdit.ReplaceSel(mes);
	end = m_TreeEdit.GetWindowTextLength();
	m_TreeEdit.SetSel(end, end);
	m_TreeEdit.ReplaceSel(L"\r\n");
	m_TreeEdit.ReplaceSel(L"Tag: ");
	mes.Format(L"%S", TestForInfo->getTag());
	end = m_TreeEdit.GetWindowTextLength();
	m_TreeEdit.SetSel(end, end);
	m_TreeEdit.ReplaceSel(mes);
	if (TestForInfo->getMaxThreads())
	{
		m_TreeEdit.ReplaceSel(L"\r\n Threads Amount for current test: ");
		mes.Format(L"%S", TestForInfo->getMaxThreads());
		end = m_TreeEdit.GetWindowTextLength();
		m_TreeEdit.ReplaceSel(mes);
	}
	if (TestForInfo->getMaxTime())
	{
		m_TreeEdit.ReplaceSel(L"\r\n Time is needed: ");
		mes.Format(L"%S", TestForInfo->getMaxTime());
		end = m_TreeEdit.GetWindowTextLength();
		m_TreeEdit.ReplaceSel(mes);
	}
	m_TreeEdit.ReplaceSel(L"\r\n Test path: ");
	mes.Format(L"%S", TestForInfo->getPath());
	end = m_TreeEdit.GetWindowTextLength();
	m_TreeEdit.ReplaceSel(mes);
	m_TreeEdit.ReplaceSel(L"\r\n Path for test exe file: ");
	mes.Format(L"%S", TestForInfo->getPathForExe());
	end = m_TreeEdit.GetWindowTextLength();
	m_TreeEdit.ReplaceSel(mes);
	if (TestForInfo->get_expectedResult())
	{
		m_TreeEdit.ReplaceSel(L"\r\n Expected result of running: ");
		mes.Format(L"%S", TestForInfo->get_expectedResult());
		end = m_TreeEdit.GetWindowTextLength();
		m_TreeEdit.ReplaceSel(mes);
	}
	m_TreeEdit.ReplaceSel(L"\r\n If test is waiting for other tests: ");
	if (TestForInfo->getWaitFor())
	{
		end = m_TreeEdit.GetWindowTextLength();
		m_TreeEdit.ReplaceSel(L"TRUE -> ");
		mes.Format(L"%S", TestForInfo->getWaitFor());
		end = m_TreeEdit.GetWindowTextLength();
		m_TreeEdit.ReplaceSel(mes);
	}
	else
	{
		end = m_TreeEdit.GetWindowTextLength();
		m_TreeEdit.ReplaceSel(L"FALSE ");
	}
	m_TreeEdit.ReplaceSel(L"\r\n If test needs to be repeated: ");
	if (TestForInfo->getRepeat())
	{
		end = m_TreeEdit.GetWindowTextLength();
		m_TreeEdit.ReplaceSel(L"TRUE -> ");
		mes.Format(L"%S", TestForInfo->getRepeat());
		end = m_TreeEdit.GetWindowTextLength();
		m_TreeEdit.ReplaceSel(mes);
	}
	else
	{
		end = m_TreeEdit.GetWindowTextLength();
		m_TreeEdit.ReplaceSel(mes);
		m_TreeEdit.ReplaceSel(L"FALSE ");
	}
	if (TestForInfo->getMetadata())
	{
		m_TreeEdit.ReplaceSel(L"\r\n");
		m_TreeEdit.ReplaceSel(L"\r\n Test's author: ");
		mes.Format(L"%S", TestForInfo->getMetadata()->getName());
		end = m_TreeEdit.GetWindowTextLength();
		m_TreeEdit.ReplaceSel(mes);
		if (TestForInfo->getMetadata()->getDate())
		{
			m_TreeEdit.ReplaceSel(L"\r\n Date: ");
			mes.Format(L"%S", TestForInfo->getMetadata()->getDate());
			end = m_TreeEdit.GetWindowTextLength();
			m_TreeEdit.ReplaceSel(mes);
		}
		if (TestForInfo->getMetadata()->getCopyright())
		{
			m_TreeEdit.ReplaceSel(L"\r\n Copyright: ");
			mes.Format(L"%S", TestForInfo->getMetadata()->getCopyright());
			end = m_TreeEdit.GetWindowTextLength();
			m_TreeEdit.ReplaceSel(mes);
		}
		if (TestForInfo->getMetadata()->getLicense())
		{
			m_TreeEdit.ReplaceSel(L"\r\n License: ");
			mes.Format(L"%S", TestForInfo->getMetadata()->getLicense());
			end = m_TreeEdit.GetWindowTextLength();
			m_TreeEdit.ReplaceSel(mes);
		}
		if (TestForInfo->getMetadata()->getMail())
		{
			m_TreeEdit.ReplaceSel(L"\r\n Mail: ");
			mes.Format(L"%S", TestForInfo->getMetadata()->getMail());
			end = m_TreeEdit.GetWindowTextLength();
			m_TreeEdit.ReplaceSel(mes);
		}
		if (TestForInfo->getMetadata()->getVersion())
		{
			m_TreeEdit.ReplaceSel(L"\r\n Version: ");
			mes.Format(L"%S", TestForInfo->getMetadata()->getVersion());
			end = m_TreeEdit.GetWindowTextLength();
			m_TreeEdit.ReplaceSel(mes);
		}
	}
	return TRUE;
}
// TestInfo message handlers
