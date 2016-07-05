#include "stdafx.h"

#define TRSLibrary_EXPORT
#include "TRSTest.h"

TRSTest::TRSTest(char*Name, char*Description) :TRSInfo(Name,Description)
{

}

TRSTest::TRSTest() :TRSInfo()
{

}

TRSTest::~TRSTest()
{

}

bool TRSTest::Parse(TiXmlNode*pParent)
{
	if (TRSInfo::Parse(pParent))
	{
		return true;
	}
	else
	{
		return false;
	}
}