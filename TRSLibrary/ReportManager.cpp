#include"stdafx.h"
#define TRSLibrary_EXPORT

#include "ReportManager.h"

ReportManager::ReportManager()
{

}

ReportManager::~ReportManager()
{
	std::list<TRSReport*>::iterator it = reportList.begin();
	for (it; it != reportList.end(); ++it)
	{
		(*it)->~TRSReport();
	}
}

void ReportManager::addReporter(TRSReport* reporter)
{
	reportList.push_back(reporter);
}

void ReportManager::beforeExecution(TRSInfo info)
{
	std::list<TRSReport*>::iterator it = reportList.begin();
	for (it; it != reportList.end(); ++it)
	{
		(*it)->BeforeExecution(info);
	}
}

void ReportManager::afterExecution(TRSInfo info, TRSResult result)
{
	std::list<TRSReport*>::iterator it = reportList.begin();
	for (it; it != reportList.end(); ++it)
	{
		(*it)->AfterExecution(info,result);
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