#ifndef TRSTEST_H_
#define TRSTEST_H_
#include "TRSInfo.h"

class TRSTest :public TRSInfo
{
	char* directoryName;
public:
	TRSTest(char*Name,char*Description,char*DirName);
	~TRSTest();
	bool Run();
};

#endif