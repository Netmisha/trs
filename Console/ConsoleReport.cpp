#include "stdafx.h"
#include "ConsoleReport.h"

void ConsoleReport::BeforeExecution(TRSInfo* pInfo)
{
	std::cout << pInfo->getName() << " started\n";
}

void ConsoleReport::AfterExecution(TRSInfo* pInfo, TRSResult* pResult)
{
	std::cout << pInfo->getName() << " finished\n" << pResult->get_result() << std::endl;
}

void ConsoleReport::Begin()
{

}

void ConsoleReport::End()
{

}