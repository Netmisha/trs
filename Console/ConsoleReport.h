#ifndef CONSOLEREPORT_H_
#define CONSOLEREPORT_H_

#include "TRSLibrary\TRSReport.h"
#include <Windows.h>
#include <string>
class ConsoleReport :public TRSReport
{
public:
	ConsoleReport();
	~ConsoleReport();

	virtual void BeforeExecution(TRSInfo pInfo);
	virtual void AfterExecution(TRSInfo pInfo, TRSResult pResult);
	virtual void Begin();
	virtual void End();
	virtual void ErrorOutput(TRSResult& result,char* message);
	virtual void ErrorMessage( char* message);
	double getTime();
	double getAmount();
	double getPassedAmount();
	double getFailedAmount();
private:
	double time=0;
	double amount=0;
	double passedAmount=0;
	double failedAmount=0;
	int mCount = 1;
};
#endif