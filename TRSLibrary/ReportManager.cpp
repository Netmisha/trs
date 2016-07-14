#include"stdafx.h"
#define TRSLibrary_EXPORT

#include "ReportManager.h"

ReportManager::ReportManager()
{
	InitializeCriticalSection(&critical_section_);
}

ReportManager::~ReportManager()
{
	std::list<TRSReport*>::iterator it = reportList.begin();
	for (it; it != reportList.end(); ++it)
	{
		(*it)->~TRSReport();
	}

	DeleteCriticalSection(&critical_section_);
}

void ReportManager::addReporter(TRSReport* reporter)
{
	reportList.push_back(reporter);
}

void ReportManager::beforeExecution(TRSInfo info)
{
	EnterCriticalSection(&critical_section_);
	std::list<TRSReport*>::iterator it = reportList.begin();
	for (it; it != reportList.end(); ++it)
	{
		(*it)->BeforeExecution(info);
	}
	LeaveCriticalSection(&critical_section_);
}

void ReportManager::afterExecution(TRSInfo info, TRSResult result)
{
	EnterCriticalSection(&critical_section_);
	std::list<TRSReport*>::iterator it = reportList.begin();
	for (it; it != reportList.end(); ++it)
	{
		(*it)->AfterExecution(info,result);
	}
	LeaveCriticalSection(&critical_section_);
}

void ReportManager::Begin()
{
	EnterCriticalSection(&critical_section_);
	std::list<TRSReport*>::iterator it = reportList.begin();
	for (it; it != reportList.end(); ++it)
	{
		(*it)->Begin();
	}
	LeaveCriticalSection(&critical_section_);
}

void ReportManager::End()
{
	EnterCriticalSection(&critical_section_);
	std::list<TRSReport*>::iterator it = reportList.begin();
	for (it; it != reportList.end(); ++it)
	{
		(*it)->End();
	}
	LeaveCriticalSection(&critical_section_);
}

void ReportManager::errorOutput()
{
	EnterCriticalSection(&critical_section_);
	std::list<TRSReport*>::iterator it = reportList.begin();
	for (it; it != reportList.end(); ++it)
	{
		(*it)->ErrorOutput();
	}
	LeaveCriticalSection(&critical_section_);
}