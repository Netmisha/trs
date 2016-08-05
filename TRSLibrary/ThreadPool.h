#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <queue>
#include <Windows.h>

using std::queue;

typedef DWORD (WINAPI *routine)(PVOID);

//===================================================================
class Task
{
public:
	Task(routine, PVOID);

	DWORD ExecuteTask();

private:
	routine func_;
	PVOID args_;
};


//===================================================================
class TaskQueue
{
public:
	TaskQueue();
	~TaskQueue();

	VOID AddTask(routine, PVOID);
	DWORD ExecuteTask();

	inline VOID set_event(HANDLE event)
	{
		event_ = event;
	}
	inline DWORD size()
	{
		return tasks_.size();
	}
private:
	Task TakeTask();

	inline BOOL is_empty()
	{
		return tasks_.empty();
	}

private:
	queue<Task> tasks_;
	HANDLE event_ = NULL;
	CRITICAL_SECTION critical_section_;
};

//===================================================================

class ThreadPool
{
public:
	ThreadPool(DWORD threads);
	~ThreadPool();

	// adding task to the queue
	BOOL AddTask(routine, PVOID);
	BOOL JoinAll(DWORD max_time);
	BOOL TerminateAll();

	BOOL InitPool(DWORD max_queue_size);
	BOOL DestroyPool(bool ignore_queue);

private:

	static DWORD WINAPI ConfigurateThread(PVOID);

	VOID ProcessTasks();

private:
	BOOL is_running_ = TRUE;
	DWORD size_;
	HANDLE available_task_;
	HANDLE event_;
	TaskQueue tasks_;
	HANDLE* threads_;
};

#endif