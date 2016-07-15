#include "stdafx.h"
#include "ThreadPool.h"
#include "TRSManager.h"

using std::endl;


Task::Task(routine function, PVOID arguments) : func_(function), args_(arguments)
{
}

DWORD Task::ExecuteTask()
{
	return func_(args_);
}

//===================================================================
TaskQueue::TaskQueue()
{
	InitializeCriticalSection(&critical_section_);
}


TaskQueue::~TaskQueue()
{
	DeleteCriticalSection(&critical_section_);
}

void TaskQueue::AddTask(routine func, PVOID args)
{
	EnterCriticalSection(&critical_section_);

	Task new_task(func, args);
	tasks_.push(new_task);

	LeaveCriticalSection(&critical_section_);
}

DWORD TaskQueue::ExecuteTask()
{
	Task task = TakeTask();
	return task.ExecuteTask();
}

Task TaskQueue::TakeTask()
{
	EnterCriticalSection(&critical_section_);

	Task ret_task = tasks_.front();
	tasks_.pop();

	// if queue is empty -> signalling. If signal failed = an error occured
	if (!tasks_.size() && !SetEvent(event_))
		logger << "Signalling failed";

	LeaveCriticalSection(&critical_section_);

	return ret_task;
}

//===================================================================
ThreadPool::ThreadPool(DWORD size) : size_(size)
{
	threads_ = new HANDLE[size];
}

ThreadPool::~ThreadPool()
{
	delete[] threads_;
}


BOOL ThreadPool::InitPool(DWORD max_queue_size)
{
	available_task_ = CreateSemaphore(NULL, 0, max_queue_size + size_, NULL);
	if (available_task_ == NULL)
	{
		logger << "Semaphore creating error";
		return FALSE;
	}

	event_ = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (event_ == NULL)
	{
		logger << "Creating event failed";
		return FALSE;
	}

	tasks_.set_event(event_);

	for (INT i = 0; i < size_; ++i)
	{
		HANDLE thread = CreateThread(NULL, NULL, &ThreadPool::ConfigurateThread, this, NULL, NULL);
		if (thread == NULL)
		{
			logger << "Pthread creation error occured";
			return FALSE;
		}
		threads_[i] = thread;
	}

	return TRUE;
}


BOOL ThreadPool::DestroyPool()
{
	if (!ResetEvent(event_))
	{
		logger << "ResetEvent failed";
		std::cerr << "=====" << GetLastError() << "======" << endl;
		return FALSE;
	}
	// if for avoiding waiting for queue to become empty when it is already empty
	if (tasks_.size())
	{
		WaitForSingleObject(event_, INFINITE);
	}

	// only main thread will change this value
	// and it wouldn't cause any harm because
	// every thread would be waiting at this moment
	is_running_ = FALSE;


	// this code will force all worked threads exit their functions
	if (!ReleaseSemaphore(available_task_, size_, NULL))
	{
		logger << "Releasing semaphore failed";
		return FALSE;
	}

	// waiting for all threads exit their functions
	if (!JoinAll(INFINITE))
	{
		logger << "JoinAll failed";
		return FALSE;
	}

	for (int i = 0; i < size_; ++i)
	{
		if (!CloseHandle(threads_[i]))
		{
			logger << "Closing semaphore failed";
			return FALSE;
		}
	}


	if (!CloseHandle(available_task_))
	{
		logger << "Closing semaphore failed";
		return FALSE;
	}
	if (!CloseHandle(event_))
	{
		logger << "Closing event failed";
		return FALSE;
	}

	return TRUE;
}

BOOL ThreadPool::AddTask(routine func, PVOID args)
{
	tasks_.AddTask(func, args);
	if (!ReleaseSemaphore(available_task_, 1, NULL))
	{
		logger << "Releasing semaphore failed";
		return FALSE;
	}
	return TRUE;
}

BOOL ThreadPool::JoinAll(DWORD max_time)
{
	DWORD result = WaitForMultipleObjects(size_, threads_, TRUE, max_time);
	switch (result)
	{
	case WAIT_OBJECT_0:
		return TRUE;
	case WAIT_FAILED:
		logger << "WaitForMultipleObjects failed";
		return false;
	case WAIT_TIMEOUT:
		return false;
	}
}


DWORD WINAPI ThreadPool::ConfigurateThread(PVOID thr_pool)
{
	ThreadPool* thread_pool = (ThreadPool*)thr_pool;
	thread_pool->ProcessTasks();
	return 0;
}

VOID ThreadPool::ProcessTasks()
{
	const bool kRun = true;
	while (kRun)
	{
		WaitForSingleObject(available_task_, INFINITE);
		if (is_running_)
			tasks_.ExecuteTask();
		else return;
	}
}