#include "stdafx.h"
#include "TRSInfo.h"

TRSInfo::TRSInfo(char*TestName, char*Description,char*DirName) 
{
	if (directoryName)
	{
		delete[] directoryName;
		strncpy_s(directoryName, strlen(DirName), DirName, strlen(DirName));
	}
	else
	{
		strncpy_s(directoryName, strlen(DirName), DirName, strlen(DirName));
	}
	Name = new char[strlen(TestName)];
	strncpy_s(Name, strlen(TestName),TestName, strlen(TestName));
	description = new char[strlen(Description)];
	strncpy_s(description, strlen(Description),Description, strlen(Description));
}

TRSInfo::~TRSInfo()
{
	delete[] Name;
	delete[] description;
	if (tag)
	{
		delete[] tag;
	}
	if (repeat)
	{
		delete[] repeat;
	}
	if (maxTime)
	{
		delete[] maxTime;
	}
	if (maxThreads)
	{
		delete[] maxThreads;
	}
}

char* TRSInfo::getName()
{
	return Name;
}

char* TRSInfo::getDescription()
{
	return description;
}

char* TRSInfo::getMaxThreads()
{
	return maxThreads;
}