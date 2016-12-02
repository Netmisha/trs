#ifndef TRSTEST_H_
#define TRSTEST_H_
#include "TRSInfo.h"

#ifdef TRSLibrary_EXPORT
#define TRSTest_API  __declspec(dllexport) 
#else
#define TRSTest_API  __declspec(dllimport) 
#endif

class TRSTest_API TRSTest : public TRSInfo
{
public:
	TRSTest(char*Name,char*Description);
	TRSTest();
	~TRSTest();
	bool Run();
	bool Parse(TiXmlNode*pParent);
};

#endif