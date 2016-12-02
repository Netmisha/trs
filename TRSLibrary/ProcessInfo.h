#ifndef ProcessInfo_HEADER
#define ProcessInfo_HEADER

#define SEMAPHORES_AMOUNT 2
#define OWNED_SEMAPHORE 0
#define MANAGING_SEMAPHORE 1

#define NUMERIC_BASE 10
#define MAX_IDEN_LENGHT 2

#include "stdafx.h"
#include "TRSTest.h"
#include "TRSResult.h"
#include "ReportManager.h"
#include "ThreadPool.h"

#include <chrono>

enum class Status{ Waiting, Done, Running, Closed };

//class ProcessInfo;

class ProcessInfo
{
public:
	ProcessInfo(const TRSTest&, char*, HANDLE[SEMAPHORES_AMOUNT], ThreadPool*, bool* running,  ReportManager* pReporter = nullptr);
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
	inline void set_status(Status val)
	{
		EnterCriticalSection(&crt_);
		status_ = val;
		LeaveCriticalSection(&crt_);
	}
	bool IsDisable() const;
	int GetPriority() const;
	char* ProcessTest(bool ignore_wait = false);

	ProcessInfo& operator=(const ProcessInfo&);
	operator TRSResult() const;
	bool operator<(const ProcessInfo&);

private:
	bool ReleaseResources();
	long ParseMaxTime();
	bool RecordDuration();
	static DWORD WINAPI StartThread(LPVOID);

private:
	TRSTest test_;
	bool result_;
	Status status_;

	long max_time_;
	char* result_description_;
	HANDLE semaphores_[SEMAPHORES_AMOUNT];

	bool* running_;
	char* path_;
	wchar_t* command_line_;

	ReportManager* pReporter_;
	PROCESS_INFORMATION process_information_;
	std::chrono::duration<long long, std::milli> duration_;

	CRITICAL_SECTION crt_;
	ThreadPool* threads_;
};

struct ProcessData
{
	ProcessData(ProcessInfo*, HANDLE s[SEMAPHORES_AMOUNT]);
	~ProcessData(){}

	HANDLE semaphores[SEMAPHORES_AMOUNT];
	ProcessInfo* running_process;
};

#endif