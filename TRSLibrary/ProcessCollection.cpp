#include "stdafx.h"
#include "ProcessCollection.h"
#include "TRSManager.h"

#include <list>

using std::list;

// futher implementation of priority will be added
ProcessCollection::ProcessCollection(const Suite& suite)
{
	int max_threads = atoi(suite.getMaxThreads());
	semaphore_ = CreateSemaphore(nullptr, max_threads, max_threads, nullptr);
	if (semaphore_ == NULL)
	{
		logger << "Creation of semaphore failed";
	}

	int path_len = strlen(suite.get_path());
	path_ = new char[path_len + 1];
	strcpy_s(path_, path_len + 1, suite.get_path());

	for each (TRSTest* var in suite.getList())
		tests_.push_back(ProcessInfo(*var, path_));

	undone_tests_ = tests_.size();
}

ProcessCollection::~ProcessCollection()
{
	if (!CloseHandle(semaphore_))
		logger << "Closing semaphore's handle failed";

	delete[] path_;
}



list<TRSResult> ProcessCollection::RunAll()
{
	while (undone_tests_)
	{
		int wait_result = WaitForSingleObject(semaphore_, INFINITE);
		if (wait_result == WAIT_FAILED)
		{
			logger << "Wait for semaphore failed";
			return list<TRSResult>();
		}

		for each(ProcessInfo var in tests_)
		{
			if (var.get_status() == Status::Running && var.ReleaseResources())
			{
				break;
			}
			else if (var.get_status() == Status::Waiting)
			{
				char* name = var.ProcessTest();
				// if this test is waiting for test, which is already done 
				if (IsDone(name))
				{
					// one more iteration will be if this test is already done but we do not release its resources
					// its made in order to simplify code
					var.ProcessTest(true);
					break;
				}
				else if (name == nullptr)
				{
					// test was not wasiting for anything and it is running now
					break;
				}
				// this test is wating fo another test which is still runnig.
				// so it was not a test, which signaled to maint thread. Continue searching
			}
		}
	}
	return list<TRSResult>(tests_.begin(), tests_.end());
}