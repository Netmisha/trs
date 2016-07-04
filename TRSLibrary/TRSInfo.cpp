#include "stdafx.h"
#include "TRSInfo.h"

TRSInfo::TRSInfo(char*TestName, char*Description, char* Name) :meta(Name)
{
	testName = new char[strlen(TestName)];
	strncpy_s(testName, strlen(TestName),TestName, strlen(TestName));
	description = new char[strlen(Description)];
	strncpy_s(description, strlen(Description),Description, strlen(Description));
}

TRSInfo::~TRSInfo()
{
	delete[] testName;
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