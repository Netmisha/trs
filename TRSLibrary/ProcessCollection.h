#include "stdafx.h"

#ifndef ProcessCollection_HEADER
#define ProcessCollection_HEADER

#include "Suite.h"
#include "ProcessInfo.h"
#include "TRSResult.h"
#include "ReportManager.h"

#include <vector>
#include <windows.h>

// ProcessCollection consist of ProcessInfo collection ( which is TRSTest with additional information)
// ProcessCollection is respnsible not only for relasing its own resources ( except of semaphore kernel object ),
// but it also close process handles which are owned by ProcessInfo
class ProcessCollection
{
public:
	ProcessCollection(const Suite&, HANDLE semaphore, ReportManager* pReport = nullptr);
	ProcessCollection(const ProcessCollection&);
	~ProcessCollection();

	// I wiil reconsider this functions in ord
	inline bool is_undone()
	{
		return undone_tests_;
	}
	inline std::vector<ProcessInfo> get_tests()
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
	std::vector<ProcessInfo> tests_;
};
#endif