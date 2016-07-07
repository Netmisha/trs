#include"stdafx.h"
#define TRSLibrary_EXPORT

#include "ReportManager.h"

ReportManager::ReportManager()
{

}

ReportManager::~ReportManager()
{

}

void ReportManager::addReporter(TRSReport* reporter)
{
	reportList.push_back(reporter);
}

void ReportManager::beforeExecution(TRSInfo* pInfo)
{
	std::list<TRSReport*>::iterator it = reportList.begin();
	for (it; it != reportList.end(); ++it)
	{
		(*it)->BeforeExecution(pInfo);
	}
}

void ReportManager::afterExecution(TRSInfo* pInfo, TRSResult* pResult)
{
	std::list<TRSReport*>::iterator it = reportList.begin();
	for (it; it != reportList.end(); ++it)
	{
		(*it)->AfterExecution(pInfo,pResult);
	}
}

void ReportManager::Begin()
{
	std::list<TRSReport*>::iterator it = reportList.begin();
	for (it; it != reportList.end(); ++it)
	{
		(*it)->Begin();
	}
}

void ReportManager::End()
{
	std::list<TRSReport*>::iterator it = reportList.begin();
	for (it; it != reportList.end(); ++it)
	{
		(*it)->End();
	}
}