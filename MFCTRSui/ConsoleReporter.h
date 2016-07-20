#ifndef CONSOLEREPORTER_H_
#define CONSOLEREPORTER_H_
#include "TRSLibrary\TRSReport.h"


class ConsoleReporter :public  TRSReport
{
public:
	ConsoleReporter(CEdit*, CProgressCtrl*);
	~ConsoleReporter();

	virtual void BeforeExecution(TRSInfo pInfo);
	virtual void AfterExecution(TRSInfo pInfo, TRSResult pResult);
	virtual void Begin();
	virtual void End();
	virtual void ErrorOutput(TRSResult& result, char* message);
	virtual void ErrorMessage(char* message);
	double getTime();
	double getAmount();
	double getPassedAmount();
	double getFailedAmount();
private:
	double time = 0;
	double amount = 0;
	double passedAmount = 0;
	double failedAmount = 0;
	int mCount = 1;
	CEdit* console_output;
	CProgressCtrl* progress;
};

#endif