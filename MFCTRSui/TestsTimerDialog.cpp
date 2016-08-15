// TestsTimerDialog.cpp : implementation file
//

#include "stdafx.h"
#include "TestsTimerDialog.h"
#include "afxdialogex.h"


// TestsTimerDialog dialog
CListCtrl* List;
IMPLEMENT_DYNAMIC(TestsTimerDialog, CDialogEx)

TestsTimerDialog::TestsTimerDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(TestsTimerDialog::IDD, pParent)
{

}

TestsTimerDialog::~TestsTimerDialog()
{
}

void TestsTimerDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, TimerHeadListCtrl);
}

BOOL TestsTimerDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	for (int i = 0; i < List->GetItemCount(); ++i)
	{
		TimerHeadListCtrl.InsertItem(TimerHeadListCtrl.GetItemCount(), List->GetItemText(i, 0));
	}
	return true;
}

BEGIN_MESSAGE_MAP(TestsTimerDialog, CDialogEx)
END_MESSAGE_MAP()


// TestsTimerDialog message handlers
