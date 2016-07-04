
#include"stdafx.h"
#include "Suite.h"

Suite::Suite(char*TestName, char*Description,char* DirName) :TRSInfo(TestName,Description,DirName)
{

}

Suite::~Suite()
{

}

bool Suite::addTest(TRSTest& currentTest)
{
	testList.push_back(currentTest);
	return true;
}

bool Suite::removeTest(char*testName)
{
	std::list<TRSTest>::iterator it= testList.begin();
	for (it; it != testList.end(); ++it)
	{
		if (!strncmp(testName, it->getName(), strlen(testName)))
		{
			testList.erase(it);
			return true;
		}
	}
	return false;
}

std::list<TRSTest>& Suite::getList()
{
	return testList;
}