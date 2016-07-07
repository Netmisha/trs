#include "stdafx.h"
#include "ConsoleReport.h"


ConsoleReport::ConsoleReport()
{
	time = 0;
	amount = 0;
	passedAmount = 0;
	failedAmount = 0;
}

ConsoleReport::~ConsoleReport()
{
	std::cout << std::endl << std::endl;
	std::cout << "Summary:\n";
	std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
	std::cout << "Tests amount:\t" << (int)amount << std::endl;
	std::cout << "Passed:\t" << (int)passedAmount << "(" << int((passedAmount / amount) * 100) << "%)\n";
	std::cout << "Failed:\t" << (int)failedAmount << "(" << int((failedAmount / amount) * 100) << "%)\n";
	std::cout << "Total time:\t" << (int)time << "ms\n";
}

double ConsoleReport::getTime()
{
	return time;
}

double ConsoleReport::getAmount()
{
	return amount;
}

double ConsoleReport::getPassedAmount()
{
	return passedAmount;
}

double ConsoleReport::getFailedAmount()
{
	return failedAmount;
}

void ConsoleReport::BeforeExecution(TRSInfo* pInfo)
{

}

void ConsoleReport::AfterExecution(TRSInfo* pInfo, TRSResult* pResult)
{
	
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	
	std::cout <<"'"<< pInfo->getName()<<"' ";
	if (pResult->get_result())
	{
		SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN);
		std::cout << "Passed";
		++passedAmount;
		SetConsoleTextAttribute(hStdout, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
	else
	{
		SetConsoleTextAttribute(hStdout, FOREGROUND_RED );
		std::cout << "Failed";
		++failedAmount;
		SetConsoleTextAttribute(hStdout, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
	time += pResult->get_duration().count();
	++amount;
	std::cout << " " << pResult->get_path() << std::endl;
}

void ConsoleReport::Begin()
{

	SYSTEMTIME time;
	
	GetLocalTime(&time);
	SYSTEM_INFO siSysInfo;
	GetSystemInfo(&siSysInfo);
	std::cout << "System info: \n\n" << "Processor: " << siSysInfo.dwProcessorType << " Number of processors: " << siSysInfo.dwNumberOfProcessors << std::endl;
	std::cout << "Processor mask: " << siSysInfo.dwActiveProcessorMask << " Processor architecture: " << siSysInfo.wProcessorArchitecture << " Processor level: " << siSysInfo.wProcessorLevel << std::endl << std::endl;
	std::cout << "Tests were run :\n";
	if (time.wDay < 10)
	{
		std::cout << "0" << time.wDay;
	}
	else
	{
		std::cout << time.wDay;
	}
	std::cout << ".";
	if (time.wMonth < 10)
	{
		std::cout << "0" << time.wMonth;
	}
	else
	{
		std::cout << time.wMonth;
	}
	std::cout << "." << time.wYear << " at " << time.wHour << ":" << time.wMinute << ":" << time.wSecond << std::endl << std::endl;
	
}

void ConsoleReport::End()
{

}