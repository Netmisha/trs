#include "stdafx.h"
#include "TRSInfo.h"

TRSInfo::TRSInfo(char*TestName, char*Description, char*Tag, char*Repeat, char*MaxTime, char*MaxThreads, char* Name) :meta(Name)
{
	testName = new char[strlen(TestName)];
	strncpy_s(testName, strlen(TestName),TestName, strlen(TestName));
	description = new char[strlen(Description)];
	strncpy_s(description, strlen(Description),Description, strlen(Description));
	tag = new char[strlen(Tag)];
	strncpy_s(tag, strlen(Tag),Tag, strlen(Tag));
	repeat = new char[strlen(Repeat)];
	strncpy_s(repeat, strlen(Repeat),Repeat, strlen(Repeat));
	maxTime = new char[strlen(MaxTime)];
	strncpy_s(maxTime, strlen(MaxTime),MaxTime, strlen(MaxTime));
}