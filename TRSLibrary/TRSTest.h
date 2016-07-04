#ifndef TRSTEST_H_
#define TRSTEST_H_
#include "TRSInfo.h"

class TRSTest :public TRSInfo
{
public:
	TRSTest(char*Name,char*Description);
	~TRSTest();
	bool Run();
};

#endif