#include "stdafx.h"
#include "ProcessCollection.h"
#include "TRSManager.h"

#include <iostream>


// futher implementation of priority will be added
ProcessCollection::ProcessCollection(const Suite& suite, HANDLE semaphore, ReportManager* pReport)
{
	int max_threads = atoi(suite.getMaxThreads());
	if (max_threads < 0)
		logger << "Negative value in max_threas field";

	semaphores_[OWNED_SEMAPHORE] = CreateSemaphore(NULL, max_threads, max_threads, NULL);
	if (semaphores_[OWNED_SEMAPHORE] == NULL)
	{
		logger << "Creation of semaphore failed";
	}
	semaphores_[MANAGING_SEMAPHORE] = semaphore;

	int path_len = strlen(suite.get_path());
	path_ = new char[path_len + 1];
	strcpy_s(path_, path_len + 1, suite.get_path());

	undone_tests_ = 0;
	for each (TRSTest* var in suite.getList())
	{
		ProcessInfo info(*var, path_, semaphores_, pReport);
		int repeat = atoi(var->getRepeat());
		for (int i = 0; i < repeat; ++i)
		{
			tests_.push_back(info);
			undone_tests_ += !info.IsDisable();
		}
	}
	//sorting collection by priority

	//	require move constructor and assigment operators which now works incorrectly
	//	sort(tests_.begin(), tests_.end());

	int j;
	for (int i = 0; i < tests_.size(); ++i){
		j = i;

		while (j > 0 && tests_[j] < tests_[j - 1]){
			auto temp = tests_[j];
			tests_[j] = tests_[j - 1];
			tests_[j - 1] = temp;
			j--;
		}
	}
}


ProcessCollection::ProcessCollection(const ProcessCollection& var) : undone_tests_(var.undone_tests_), tests_(var.tests_)
{
	// TODO: made all operation with array in loops && made all unclear indexes initialized by macros
	semaphores_[OWNED_SEMAPHORE] = var.semaphores_[OWNED_SEMAPHORE];
	semaphores_[MANAGING_SEMAPHORE] = var.semaphores_[MANAGING_SEMAPHORE];


	int path_len = strlen(var.path_);
	path_ = new char[path_len + 1];
	strcpy_s(path_, path_len + 1, var.path_);
}

ProcessCollection::~ProcessCollection()
{
	for (auto iter = tests_.begin(); iter != tests_.end(); ++iter)
		iter->ReleaseResources();
	delete[] path_;
}

bool ProcessCollection::TryRun()
{
	if (!undone_tests_)
		return false;
	
	int wait_result = WaitForSingleObject(semaphores_[OWNED_SEMAPHORE], NULL);
	
		if (wait_result == WAIT_OBJECT_0)
		{
			auto var = tests_.begin();
			for (; var != tests_.end(); ++var)
			{
				if (var->IsDisable())
				{
					// this test is disable, we do not need to check it 
					continue;
				}
				else if (var->get_status() == Status::Running && var->IsDone())
				{
					// this test is already "Done", so decrement the counter
					--undone_tests_;
					continue;
				}
				else if (var->get_status() == Status::Waiting)
				{
					// ProcessInfo owns the name resource so it must properly create and release it
					char* name = var->ProcessTest();
					if (name == nullptr)
					{
						// test was not waiting for anything and it is running now
						break;
					}
					// if this test is waiting for test, which is already done
					bool is_done;
					int result = IsDone(name, is_done);
					if (result >= 0)
					{
						undone_tests_ -= result;
					}
					else
					{
						logger << "Waitfor name is not exist in current namespace";
						return false;
					}

					if (is_done)
					{
						var->ProcessTest(true);
						break;
					}
					// So, this test is wating fo another test which is still runnig.
					// so it was not a test, which signaled to main thread. Continue searching
				}
			}
			// if it is false - it means that test in another ProcessCollection signaled to main thread
			// and we must continue searching
			return var != tests_.end();
		}
		else if (wait_result == WAIT_TIMEOUT)
		{
			return false;
		}
		else 
		{
			logger << "Wait for semaphore failed _2";
			return false;
		}
}

// returns:
// -1 - error: this test is not exist in current suite
// val >= 0 - we release resources of val tests and change their status to Done
// in all_done output parameter we will write whether all specified tests are done or not
int ProcessCollection::IsDone(char* name, _Outptr_ bool &all_done)
{
	all_done = true;
	int ret_val = 0;

	if (name == nullptr)
		return ret_val;

	bool name_exist = false;
	for (auto var = tests_.begin(); var != tests_.end(); ++var)
	{
		if (!strcmp(name, var->get_name()))
		{
			name_exist = true;
			// test is diasable, so we might execute all tests which are waiting on it
			if (var->IsDisable())
			{
				continue;
			}

			switch (var->get_status())
			{
			case Status::Done:
			{
				 continue;
			}

			case Status::Running:
			{
				// if it is finished
				if (var->IsDone())
				{
					++ret_val;
					break;
				}
				else
				{
					all_done = false;
					return ret_val;
				}
			}
			case Status::Waiting:
			{
				all_done = false;
				return ret_val;
			}
			}

		}
	}

	if (name_exist)
		return ret_val;
	else
		return -1;
}