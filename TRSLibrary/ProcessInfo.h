#ifndef ProcessInfo_HEADER
#define ProcessInfo_HEADER

#define SEMAPHORES_AMOUNT 2
#define OWNED_SEMAPHORE 0
#define MANAGING_SEMAPHORE 1


#include "stdafx.h"
#include "TRSTest.h"
#include "TRSResult.h"
#include "ReportManager.h"

#include <chrono>

enum class Status{ Waiting, Done, Running };

class ProcessInfo;

class ProcessInfo
{
public:
	ProcessInfo(const TRSTest&, char*, HANDLE[SEMAPHORES_AMOUNT], ReportManager* pReporter = nullptr);
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
	bool IsDone();
	bool ReleaseResources();
	bool IsDisable();

	operator TRSResult() const;

//	friend struct ProcessData;
private:
	bool RecordDuration();
	static DWORD WINAPI StartThread(LPVOID);
private:
	bool result_;
	TRSTest test_;
	Status status_;
	HANDLE semaphores_[SEMAPHORES_AMOUNT];
	HANDLE work_thread_;
	char* path_;
	wchar_t* command_line_;
	ReportManager* pReporter_;
	PROCESS_INFORMATION process_information_;
	std::chrono::duration<long long, std::milli> duration_;
};

struct ProcessData
{
	ProcessData(ProcessInfo, PROCESS_INFORMATION*, HANDLE s[SEMAPHORES_AMOUNT]);
	~ProcessData(){}

	PROCESS_INFORMATION* process_information;
	HANDLE semaphores[SEMAPHORES_AMOUNT];
	ProcessInfo running_process;
};

#endif