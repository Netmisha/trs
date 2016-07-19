#include "stdafx.h"
#include "ConsoleReporter.h"

ConsoleReporter::ConsoleReporter(CEdit*edit)
{
	time = 0;
	amount = 0;
	passedAmount = 0;
	failedAmount = 0;
	console_output = edit;
}

ConsoleReporter::~ConsoleReporter()
{
	int end = console_output->GetWindowTextLength();
	console_output->SetSel(end, end);
	console_output->ReplaceSel(L"\r\n\r\n");
	end = console_output->GetWindowTextLength();
	console_output->SetSel(end, end);
	console_output->ReplaceSel(L"Summary:");
	end = console_output->GetWindowTextLength();
	console_output->SetSel(end, end);
	console_output->ReplaceSel(L"Test amount:\t");
	end = console_output->GetWindowTextLength();
	console_output->SetSel(end, end);
	CString mess;
	mess.Format(L"%d", (int)amount);
	console_output->ReplaceSel(mess);
	end = console_output->GetWindowTextLength();
	console_output->SetSel(end, end);
	console_output->ReplaceSel(L"\r\nPassed Amount: ");
	mess.Format(L"%d", (int)passedAmount);
	console_output->ReplaceSel(mess);
	end = console_output->GetWindowTextLength();
	console_output->SetSel(end, end);
	console_output->ReplaceSel(L"(");
	mess.Format(L"%d", (int)((passedAmount / amount) * 100));
	console_output->SetSel(end, end);
	console_output->ReplaceSel(mess);
	end = console_output->GetWindowTextLength();
	console_output->SetSel(end, end);
	console_output->ReplaceSel(L"%)\r\nFailed Amount: ");
	mess.Format(L"%d", (int)failedAmount);
	console_output->SetSel(end, end);
	console_output->ReplaceSel(mess);
	end = console_output->GetWindowTextLength();
	console_output->SetSel(end, end);
	console_output->ReplaceSel(L"(");
	mess.Format(L"%d", (int)((failedAmount / amount) * 100));
	console_output->SetSel(end, end);
	console_output->ReplaceSel(mess);
	end = console_output->GetWindowTextLength();
	console_output->SetSel(end, end);
	console_output->ReplaceSel(L"%)\r\nTotal time: ");
	mess.Format(L"%d", (int)((time / 1000) / 600));
	console_output->SetSel(end, end);
	console_output->ReplaceSel(mess);
	end = console_output->GetWindowTextLength();
	console_output->SetSel(end, end);
	console_output->ReplaceSel(L"min\r\n");

}

double ConsoleReporter::getTime()
{
	return time;
}

void ConsoleReporter::ErrorOutput(TRSResult& res, char* message)
{
	//HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	//SetConsoleTextAttribute(hStdout, FOREGROUND_RED);
	int end = console_output->GetWindowTextLength();
	console_output->SetSel(end, end);
	console_output->ReplaceSel(L"\r\nAn error occured! \r\n");
	//SetConsoleTextAttribute(hStdout, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void ConsoleReporter::ErrorMessage(char* message)
{
	int end = console_output->GetWindowTextLength();
	console_output->SetSel(end, end);
	CString mess;
	mess.Format(L"%d", message);
	console_output->ReplaceSel(mess);
}

double ConsoleReporter::getAmount()
{
	return amount;
}

double ConsoleReporter::getPassedAmount()
{
	return passedAmount;
}

double ConsoleReporter::getFailedAmount()
{
	return failedAmount;
}

void ConsoleReporter::BeforeExecution(TRSInfo pInfo)
{

}

void ConsoleReporter::End()
{

}

void ConsoleReporter::Begin()
{

	SYSTEMTIME time;

	GetLocalTime(&time);
	SYSTEM_INFO siSysInfo;
	GetSystemInfo(&siSysInfo);
	int end = console_output->GetWindowTextLength();
	console_output->SetSel(end, end);
	console_output->ReplaceSel(L"System info: ");
	CString mess;
	mess.Format(L"%d", siSysInfo.dwProcessorType);
	console_output->ReplaceSel(mess);
	console_output->SetSel(end, end);
	console_output->ReplaceSel(L"\r\n");
	end = console_output->GetWindowTextLength();
	console_output->SetSel(end, end);
	console_output->ReplaceSel(L" Number of processors: ");
	mess.Format(L"%d", siSysInfo.dwNumberOfProcessors);
	console_output->ReplaceSel(mess);
	console_output->SetSel(end, end);
	console_output->ReplaceSel(L" \r\n ");
	console_output->SetSel(end, end);
	console_output->ReplaceSel(L" Processor mask: ");
	mess.Format(L"%d", siSysInfo.dwActiveProcessorMask);
	console_output->ReplaceSel(mess);
	console_output->SetSel(end, end);
	console_output->ReplaceSel(L" \r\n ");
	console_output->SetSel(end, end);
	console_output->ReplaceSel(L" Processor architecture: ");
	mess.Format(L"%d", siSysInfo.wProcessorArchitecture);
	console_output->ReplaceSel(mess);
	console_output->SetSel(end, end);
	console_output->ReplaceSel(L" Processor level: ");
	mess.Format(L"%d", siSysInfo.wProcessorLevel);
	console_output->ReplaceSel(mess);
	console_output->ReplaceSel(L"\r\n");
	console_output->SetSel(end, end);
	console_output->ReplaceSel(L"\r\n\r\n ");
	console_output->ReplaceSel(L"  Tests were run: ");
	if (time.wDay < 10)
	{
		console_output->ReplaceSel(L"0");
		mess.Format(L"%d", time.wDay);
		console_output->ReplaceSel(mess);
	}
	else
	{
		mess.Format(L"%d", time.wDay);
		console_output->ReplaceSel(mess);
	}
	console_output->ReplaceSel(L".");
	if (time.wMonth < 10)
	{
		console_output->ReplaceSel(L"0");
		mess.Format(L"%d", time.wMonth);
		console_output->ReplaceSel(mess);
	}
	else
	{
		mess.Format(L"%d", time.wMonth);
		console_output->ReplaceSel(mess);
	}
	console_output->ReplaceSel(L".");
	mess.Format(L"%d", time.wYear);
	console_output->ReplaceSel(mess);
	console_output->ReplaceSel(L" at ");
	mess.Format(L"%d", time.wHour);
	console_output->ReplaceSel(mess);
	console_output->ReplaceSel(L":");
	mess.Format(L"%d", time.wMinute);
	console_output->ReplaceSel(mess);
	console_output->ReplaceSel(L":");
	mess.Format(L"%d", time.wSecond);
	console_output->ReplaceSel(mess);
	console_output->ReplaceSel(L"\r\n\r\n");

}

void ConsoleReporter::AfterExecution(TRSInfo pInfo, TRSResult pResult)
{

	//HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	int end = console_output->GetWindowTextLength();
	console_output->SetSel(end, end);
	CString mess;
	mess.Format(L"%d", mCount);
	console_output->ReplaceSel(mess);
	console_output->SetSel(end, end);
	console_output->ReplaceSel(L" '");
	console_output->SetSel(end, end);
	mess.Format(L"%d", pInfo.getName());
	console_output->ReplaceSel(mess);
	console_output->SetSel(end, end);
	console_output->ReplaceSel(L"' ");
	mCount++;
	if (pResult.get_result())
	{
		//SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN);
		console_output->SetSel(end, end);
		console_output->ReplaceSel(L"Passed");
		++passedAmount;
		//SetConsoleTextAttribute(hStdout, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
	else
	{
		//SetConsoleTextAttribute(hStdout, FOREGROUND_RED);
		console_output->SetSel(end, end);
		console_output->ReplaceSel(L"Failed");
		console_output->SetSel(end, end);
		mess.Format(L"%d", pResult.get_description());
		console_output->ReplaceSel(mess);
		++failedAmount;
		//SetConsoleTextAttribute(hStdout, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
	time += pResult.get_duration().count();
	++amount;
	console_output->SetSel(end, end);
	console_output->ReplaceSel(L" ");
	console_output->SetSel(end, end);
	mess.Format(L"%d", pResult.get_path());
	console_output->ReplaceSel(mess);
	console_output->SetSel(end, end);
	console_output->ReplaceSel(L"\r\n");
}