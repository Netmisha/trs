#include"stdafx.h"
#define TRSLibrary_EXPORT

#include "ReportManager.h"
int ReportManager::count = 0;

ReportManager::ReportManager()
{
	InitializeCriticalSection(&critical_section_);
	++count;
}

ReportManager::~ReportManager()
{
	DeleteCriticalSection(&critical_section_);

	std::list<TRSReport*>::iterator it = reportList->begin();
	for (it; it != reportList->end(); ++it)
	{
		TRSReport* ptr = *it;
//		delete ptr;
		
	}
	delete reportList;
}

void ReportManager::addReporter(TRSReport* reporter)
{
	reportList->push_back(reporter);
}

void ReportManager::beforeExecution(TRSInfo info)
{
	EnterCriticalSection(&critical_section_);
	std::list<TRSReport*>::iterator it = reportList->begin();
	for (it; it != reportList->end(); ++it)
	{
		(*it)->BeforeExecution(info);
	}
	LeaveCriticalSection(&critical_section_);
}

void ReportManager::afterExecution(TRSInfo info, TRSResult result)
{
	EnterCriticalSection(&critical_section_);
	std::list<TRSReport*>::iterator it = reportList->begin();
	for (it; it != reportList->end(); ++it)
	{
		(*it)->AfterExecution(info,result);
	}
	LeaveCriticalSection(&critical_section_);
}

void ReportManager::Begin()
{
//	EnterCriticalSection(&critical_section_);
	std::list<TRSReport*>::iterator it = reportList->begin();
	for (it; it != reportList->end(); ++it)
	{
		(*it)->Begin();
	}
//	LeaveCriticalSection(&critical_section_);
}

void ReportManager::End()
{
//	EnterCriticalSection(&critical_section_);
	std::list<TRSReport*>::iterator it = reportList->begin();
	for (it; it != reportList->end(); ++it)
	{
		(*it)->End();
	}
//	LeaveCriticalSection(&critical_section_);
}

void ReportManager::errorOutput(TRSResult& res,char* errorMessage)
{
	EnterCriticalSection(&critical_section_);
	std::list<TRSReport*>::iterator it = reportList->begin();
	for (it; it != reportList->end(); ++it)
	{
		(*it)->ErrorOutput(res,errorMessage);
	}
	LeaveCriticalSection(&critical_section_);
}

void ReportManager::errorMessage(char* mes)
{
	EnterCriticalSection(&critical_section_);
	std::list<TRSReport*>::iterator it = reportList->begin();
	for (it; it != reportList->end(); ++it)
	{
		(*it)->ErrorMessage(mes);
	}
	LeaveCriticalSection(&critical_section_);
}