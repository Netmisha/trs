#ifndef ProcessInfo_HEADER
#define ProcessInfo_HEADER

#include "stdafx.h"
#include "TRSTest.h"
#include "TRSResult.h"

#include <chrono>

enum class Status{ Waiting, Done, Running };

struct ProcessData
{
	ProcessData(wchar_t*, PROCESS_INFORMATION*, HANDLE);
	~ProcessData();

	wchar_t* command_line;
	PROCESS_INFORMATION* process_information;
	HANDLE semaphore;
};

class ProcessInfo
{
public:
	ProcessInfo(const TRSTest&, char*, HANDLE);
	ProcessInfo(const ProcessInfo&);
	~ProcessInfo();

	inline Status get_status() const
	{
		return status_;
	}
	inline char* get_name() const
	{
		return test_.getName();
	}

	char* ProcessTest(bool ignore_wait = false);
	bool ReleaseResources();

	operator TRSResult() const;
private:
	bool RecordDuration();
	static DWORD WINAPI StartThread(LPVOID);
private:
	bool result_;
	TRSTest test_;
	Status status_;
	HANDLE semaphore_;
	HANDLE work_thread_;
	char* path_;
	wchar_t* command_line_;
	PROCESS_INFORMATION process_information_;
	std::chrono::duration<long long, std::milli> duration_;
};
#endif