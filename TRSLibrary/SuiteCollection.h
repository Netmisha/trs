#ifndef SUITE_COLLECTION_HEADER
#define SUITE_COLLECTION_HEADER

#include "ProcessInfo.h"
#include "Suite.h"
#include "ProcessCollection.h"
#include "TRSManager.h"

#include <list>

class SuiteCollection
{
public:
	SuiteCollection(const std::list<Suite>&, unsigned threads_amount);
	~SuiteCollection();

	bool Run();
private:
	bool IsUndone();
private:
	std::list<ProcessCollection> suits_;
	HANDLE global_semaphore_;
};

#endif