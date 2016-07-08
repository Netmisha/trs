#include "stdafx.h"

#ifndef ProcessCollection_HEADER
#define ProcessCollection_HEADER

#include "Suite.h"
#include "ProcessInfo.h"
#include "TRSResult.h"

#include <list>
#include <windows.h>

class ProcessCollection
{
public:
	ProcessCollection(const Suite&, HANDLE semaphore);
	ProcessCollection(const ProcessCollection&);
	~ProcessCollection();

	// I wiil reconsider this functions in ord
	inline bool is_undone()
	{
		return undone_tests_;
	}
	inline std::list<ProcessInfo> get_tests()
	{
		return tests_;
	}
	inline HANDLE get_semaphore()
	{
		return semaphores_[OWNED_SEMAPHORE];
	}

	bool TryRun();
private:
	// if name == nullptr - return 0
	int IsDone(char* name);

private:
	int undone_tests_;
	char* path_;
	HANDLE semaphores_[SEMAPHORES_AMOUNT];
	std::list<ProcessInfo> tests_;
};
#endif