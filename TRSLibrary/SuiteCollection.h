#ifndef SUITE_COLLECTION_HEADER
#define SUITE_COLLECTION_HEADER

#include "ProcessInfo.h"
#include "Suite.h"
#include "ProcessCollection.h"
#include "TRSManager.h"
#include "ReportManager.h"

#include <list>

// SuiteCollection contains of ProcessCollection(Suits with additional information such as kernel objects etc.)
// SuiteCollection is respnsible not only for relasing its own resources, but also it close semaphore handles
// which are owned by ProcessCollection
class SuiteCollection
{
public:
	SuiteCollection(const std::list<Suite>&, unsigned threads_amount, ReportManager* pReport = nullptr);
	~SuiteCollection();

	bool Run();
private:
	bool IsUndone();
private:
	std::list<ProcessCollection> suits_;
	HANDLE global_semaphore_;
};

#endif