#include "stdafx.h"
#include "ProcessInfo.h"
#include "FunctionalityForXML.h"
#include "TRSManager.h"
#include "TRSTest.h"

#include <chrono>
using namespace std::chrono;

ProcessData::ProcessData(wchar_t* cmd, PROCESS_INFORMATION* pi, HANDLE h[2]) : process_information(pi)
{
	semaphores[OWNED_SEMAPHORE] = h[OWNED_SEMAPHORE];
	semaphores[MANAGING_SEMAPHORE] = h[MANAGING_SEMAPHORE];

	int cmd_len = wcslen(cmd);
	command_line = new wchar_t[cmd_len + 1];
	wcscpy_s(command_line, cmd_len + 1, cmd);
}
ProcessData::~ProcessData()
{
	delete[] command_line;
}


ProcessInfo::ProcessInfo(const TRSTest& test, char* path, HANDLE semaphores[2]) : 
test_(test), status_(Status::Waiting), result_(false), duration_(0)
{
	semaphores_[OWNED_SEMAPHORE] = semaphores[OWNED_SEMAPHORE];
	semaphores_[MANAGING_SEMAPHORE] = semaphores[MANAGING_SEMAPHORE];

	work_thread_ = NULL;

	int path_len = strlen(path);
	path_ = new char[path_len + 1];
	strcpy_s(path_, path_len + 1, path);

	// parameter also be added here
	int exe_path_size = strlen(path) + strlen(test_.get_executableName());
	command_line_ = new wchar_t[exe_path_size + 1];

	
	char executable_directory_A[MAX_PATH + 1];
	executable_directory_A[0] = 0;
	strcat_s(executable_directory_A, MAX_PATH + 1, path);
	strcat_s(executable_directory_A, MAX_PATH + 1, test_.get_executableName());

	convertToTCHAR(command_line_, executable_directory_A);
	
	ZeroMemory(&process_information_, sizeof(process_information_));
}

ProcessInfo::ProcessInfo(const ProcessInfo& instance):
test_(instance.test_), status_(instance.status_), work_thread_(instance.work_thread_),
	result_(instance.result_), process_information_(instance.process_information_), duration_(instance.duration_)
{
	semaphores_[OWNED_SEMAPHORE] = instance.semaphores_[OWNED_SEMAPHORE];
	semaphores_[MANAGING_SEMAPHORE] = instance.semaphores_[MANAGING_SEMAPHORE];


	int path_len = strlen(instance.path_);
	path_ = new char[path_len + 1];
	strcpy_s(path_, path_len + 1, instance.path_);

	int cmd_len = wcslen(instance.command_line_);
	command_line_ = new wchar_t[cmd_len + 1];
	wcscpy_s(command_line_, cmd_len + 1, instance.command_line_);
}

ProcessInfo::~ProcessInfo()
{
	delete[] path_;
	delete[] command_line_;
}


DWORD WINAPI ProcessInfo::StartThread(LPVOID parameters)
{
	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	ProcessData data = *((ProcessData*)parameters);

	STARTUPINFO startup_info;
	ZeroMemory(&startup_info, sizeof(startup_info));

	startup_info.cb = sizeof(startup_info);

	bool create_result = CreateProcess(NULL, data.command_line, NULL, NULL, FALSE, CREATE_NO_WINDOW,
		NULL, NULL, &startup_info, data.process_information);

	if (!create_result)
	{
		delete parameters;
		logger << "Create process failed";
		return -1;
	}

	// Successfully created the process.  Wait for it to finish.
	int wait_result = WaitForSingleObject(data.process_information->hProcess, INFINITE);
	if (wait_result != WAIT_OBJECT_0)
	{
		delete parameters;
		logger << "Waiting for the process failed";
		return -1;
	}


	if (!ReleaseSemaphore(data.semaphores[OWNED_SEMAPHORE], 1, NULL))
	{
		logger << "Incrementing OWNED_SEMAPHORE semaphore count is failed";
		return -1;
	}
	if (!ReleaseSemaphore(data.semaphores[MANAGING_SEMAPHORE], 1, NULL))
	{
		logger << "Incrementing MANAGING_SEMAPHORE semaphore count is failed";
		return -1;
	}

	delete parameters;


	// TODO: make there a reporter support
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	
	return duration_cast<milliseconds>(t2 - t1).count();
}


char* ProcessInfo::ProcessTest(bool ignore_wait)
{
	// assuming that test is waiting
	if (!ignore_wait && test_.getWaitFor() != nullptr)
	{
		return test_.getWaitFor();
	}

	ProcessData* parameters = new ProcessData( command_line_, &process_information_, semaphores_ );

	work_thread_ = CreateThread(NULL, NULL, &ProcessInfo::StartThread, parameters, NULL, NULL);
	if (work_thread_ == NULL)
	{
		logger << "Creating thread in ProcessTest failded";
		return nullptr;
	}

	status_ = Status::Running;
	return nullptr;
}





// WILL BE CHANGED AFTER REPORTER'S INTEGRATION
bool ProcessInfo::ReleaseResources()
{
	if (status_ != Status::Running)
		return status_ == Status::Done;

	int wait_process = WaitForSingleObject(process_information_.hProcess, NULL);

	// how to write this if blocks more readable?
	if (wait_process == WAIT_FAILED && process_information_.hProcess != 0)
	{
		logger << "Wait for process termination failed";
		return false;
	}
	if (wait_process == WAIT_OBJECT_0)
	{
		DWORD returned_value;

		bool get_result = GetExitCodeProcess(process_information_.hProcess, &returned_value);

		CloseHandle(process_information_.hProcess);
		CloseHandle(process_information_.hThread);
		ZeroMemory(&process_information_, sizeof(process_information_));

		if (!get_result)
		{
			logger << "Process executed but an error occured while getting its exit code";
			return false;
		}
		else
		{
			int expected_value = atoi(test_.get_expectedResult());
			result_ = (expected_value == returned_value);
			status_ = Status::Done;

			RecordDuration();

			return true;
		}
	}
	else
	{
		// process is still running
		return false;
	}
}

// WILL BE ERASED AFTER REPORTER'S INTEGRATION
bool ProcessInfo::RecordDuration()
{
	int wait_thread = WaitForSingleObject(work_thread_, INFINITE);
	
	if (wait_thread == WAIT_FAILED && work_thread_ != NULL)
	{
		logger << "Wait for thread termination failed";
		return false;
	}
	if (wait_thread == WAIT_OBJECT_0)
	{
		DWORD returned_value;

		bool get_result = GetExitCodeThread(work_thread_, &returned_value);

		CloseHandle(work_thread_);

		ZeroMemory(&work_thread_, sizeof(work_thread_));

		if (!get_result)
		{
			logger << "Thread terminated but an error occured while getting its exit code";
			return false;
		}
		else
		{
			duration<long long, std::milli> test_duration(returned_value);
			duration_ = test_duration;
			return true;
		}
	}
	else
	{
		// thread is still running
		return false;
	}
}

ProcessInfo::operator TRSResult() const
{
	return TRSResult(path_, test_.getName(), result_, duration_);
}
