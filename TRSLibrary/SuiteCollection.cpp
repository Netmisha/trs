#include "stdafx.h"
#include "SuiteCollection.h"

SuiteCollection::SuiteCollection(const std::list<Suite>& list, unsigned thread_amount, ReportManager* pReport) : threads_(thread_amount)
{
	global_semaphore_ = CreateSemaphore(NULL, thread_amount, thread_amount, NULL);
	if (global_semaphore_ == NULL)
		logger << "Creation of semaphore failed";

	int tests_counter = 0;
	for (auto var = list.begin(); var != list.end(); ++var)
	{
		ProcessCollection collection(*var, global_semaphore_, &threads_, pReport); 
		suits_.push_back(collection);
		tests_counter += collection.is_undone();
	}

	if (!threads_.InitPool(tests_counter))
		logger << "Initialization of threadPool failed";
}

SuiteCollection::~SuiteCollection()
{
	for (auto var = suits_.begin(); var != suits_.end(); ++var)
	{
		if (!CloseHandle(var->get_semaphore()))
			logger << "Closing semaphore's handle failed";
	}
	
	if (!CloseHandle(global_semaphore_))
		logger << "Closing semaphore's handle failed";

	if (!threads_.DestroyPool())
		logger << "DestroyPool failed";
}

bool SuiteCollection::Run()
{
	while (IsUndone())
	{
		int wait_result = WaitForSingleObject(global_semaphore_, INFINITE);

		if (wait_result == WAIT_OBJECT_0)
		{
			for (auto var = suits_.begin(); var != suits_.end(); ++var)
			{
				if (var->TryRun())
				{
					break;
				}
			}
		}
		else
		{
			logger << "Wait for semaphore failed _1";
			return false;
		}
	}

	return true;
}

// may be optimized
bool SuiteCollection::IsUndone()
{
	for (auto var = suits_.begin(); var != suits_.end(); ++var)
	{
		if (var->is_undone())
			return true;
	}

	return false;
}