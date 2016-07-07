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
	ProcessCollection(const Suite&);
	~ProcessCollection();

	std::list<TRSResult> RunAll();
private:
	// if name == nullptr - return false
	bool IsDone(char* name);

private:
	int undone_tests_;
	char* path_;
	HANDLE semaphore_;
	std::list<ProcessInfo> tests_;
};
#endif