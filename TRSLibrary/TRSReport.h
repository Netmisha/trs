#ifndef TRSREPORT_H_
#define TRSREPORT_H_

#ifdef TRSLibrary_EXPORT
#define TRSReport_API  __declspec(dllexport) 
#else
#define TRSReport_API  __declspec(dllimport) 
#endif

#include "TRSInfo.h"

#include "TRSLibrary\TRSResult.h"

class TRSReport_API TRSReport
{
public:
	TRSReport();
	virtual~TRSReport();
	virtual void BeforeExecution(TRSInfo pInfo) = 0;
	virtual void AfterExecution(TRSInfo pInfo, TRSResult pResult) = 0;
	virtual void ErrorOutput(TRSResult& result,char* message) = 0;
	virtual void ErrorMessage(char* message) = 0;
	virtual void Begin()=0;
	virtual void End()=0;
};

#endif