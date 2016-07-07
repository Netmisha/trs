#ifndef ProcessInfo_HEADER
#define ProcessInfo_HEADER

#include "stdafx.h"
#include "TRSTest.h"
#include "TRSResult.h"

enum class Status{Done, Waiting, Running };

class ProcessInfo
{
public:
	ProcessInfo(const TRSTest&, char*){}
	ProcessInfo(const ProcessInfo&){}

	inline Status get_status() const
	{
		return status_;
	}
	inline char* get_suite_path() const
	{
		return suite_path_;
	}
	inline char* get_name() const
	{
		return test_.getName();
	}

	char* ProcessTest(bool ignore_wait = false){ return 0; }

	bool ReleaseResources(){ return false; }
	operator TRSResult() const{
#include <chrono>
		std::chrono::duration<long long, std::milli> ar;
		return TRSResult(NULL, NULL, NULL, ar); 
	}
private:
	TRSTest test_;
	Status status_;
	char* suite_path_;
	wchar_t* executable_path_;
	PROCESS_INFORMATION process_information_;
};
#endif