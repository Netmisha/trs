#include "stdafx.h"

#define TRSLibrary_EXPORT
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

bool TRSInfo::setTag(char*Tag)
{
	if (tag)
	{
		delete[] tag;
		tag = new char[strlen(Tag)];
		strncpy_s(tag, strlen(Tag), Tag, strlen(Tag));
		return true;
	}
	else
	{
		if (tag = new char[strlen(Tag)])
		{
			strncpy_s(tag, strlen(Tag), Tag, strlen(Tag));
			return true;
		}
	}
	return false;
}

bool TRSInfo::setRepeat(char*Repeat)
{
	if (repeat)
	{
		delete[] repeat;
		repeat = new char[strlen(Repeat)];
		strncpy_s(repeat, strlen(Repeat), Repeat, strlen(Repeat));
		return true;
	}
	else
	{
		if (repeat = new char[strlen(Repeat)])
		{
			strncpy_s(repeat, strlen(Repeat), Repeat, strlen(Repeat));
			return true;
		}
		else
		{
			return false;
		}
	}
}