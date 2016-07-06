#ifndef CONSOLEREPORT_H_
#define CONSOLEREPORT_H_

#include "TRSLibrary\TRSReport.h"

class ConsoleReport :public TRSReport
{
public:
	virtual void BeforeExecution(TRSInfo* pInfo);
	virtual void AfterExecution(TRSInfo* pInfo, TRSResult* pResult);
	virtual void Begin();
	virtual void End();
};
#endif