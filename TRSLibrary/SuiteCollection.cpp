#include "stdafx.h"
#include "SuiteCollection.h"

SuiteCollection::SuiteCollection(const std::list<Suite>& list, unsigned thread_amount)
{
	global_semaphore_ = CreateSemaphore(NULL, thread_amount, thread_amount, NULL);
	if (global_semaphore_ == NULL)
	{
		logger << "Creation of semaphore failed";
	}

	for (auto var = list.begin(); var != list.end(); ++var)
	{
		suits_.push_back(ProcessCollection(*var, global_semaphore_));
	}
}

SuiteCollection::~SuiteCollection()
{
	// output will be erased when reported will be integrated
	for each(auto var in suits_)
	{
		for each(auto var_1 in var.get_tests())
			std::cout << (TRSResult)var_1 << std::endl;
	}

	for (auto var = suits_.begin(); var != suits_.end(); ++var)
	{
		if (!CloseHandle(var->get_semaphore()))
		logger << "Closing semaphore's handle failed";
	}

	
	if (!CloseHandle(global_semaphore_))
		logger << "Closing semaphore's handle failed";
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
				if (var->is_undone() && var->TryRun())
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


// I will change it later
bool SuiteCollection::IsUndone()
{
	for (auto var = suits_.begin(); var != suits_.end(); ++var)
	{
		if (var->is_undone())
			return true;
	}
	return false;
}