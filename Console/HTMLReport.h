#ifndef HTMLREPORT_H_
#define HTMLREPORT_H_

#include "TRSLibrary\TRSReport.h"
#include <fstream>
#include <Windows.h>

class HTMLReport:public TRSReport
{
public:
	HTMLReport();
	~HTMLReport();

	virtual void BeforeExecution(TRSInfo pInfo);
	virtual void AfterExecution(TRSInfo pInfo, TRSResult pResult);
	virtual void Begin();
	virtual void End();
	virtual void ErrorOutput(TRSResult& result, std::string message);
	virtual void ErrorMessage(std::string message);
private:
	std::ofstream output;
	double time_ = 0;
	double amount = 0;
	double passedAmount = 0;
	double failedAmount = 0;
	int mCount = 1;
};

#endif