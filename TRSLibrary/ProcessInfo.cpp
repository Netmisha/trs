#include "stdafx.h"
#include "ProcessInfo.h"
#include "FunctionalityForXML.h"
#include "TRSManager.h"
#include "TRSTest.h"

ProcessData::ProcessData(wchar_t* cmd, PROCESS_INFORMATION* pi, HANDLE h) : process_information(pi), semaphore(h)
{
	int cmd_len = wcslen(cmd);
	command_line = new wchar_t[cmd_len + 1];
	wcscpy_s(command_line, cmd_len + 1, cmd);
}
ProcessData::~ProcessData()
{
	delete[] command_line;
}


ProcessInfo::ProcessInfo(const TRSTest& test, char* path, HANDLE semaphore) : 
test_(test), semaphore_(semaphore), status_(Status::Waiting), result_(false), duration_(0)
{

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
	test_(instance.test_), semaphore_(instance.semaphore_), status_(instance.status_),
	result_(instance.result_), process_information_(instance.process_information_), duration_(0)
{
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
		return 1;
	}

	// Successfully created the process.  Wait for it to finish.
	int wait_result = WaitForSingleObject(data.process_information->hProcess, INFINITE);
	if (wait_result != WAIT_OBJECT_0)
	{
		delete parameters;
		logger << "Waiting for the process failed";
		return 1;
	}

	delete parameters;
	if (!ReleaseSemaphore(data.semaphore, 1, NULL))
	{
		logger << "Incrementing semaphore count is failed";
		return 1;
	}
	return 0;
}


char* ProcessInfo::ProcessTest(bool ignore_wait)
{
	// assuming that test is waiting
	if (!ignore_wait && test_.getWaitFor() != nullptr)
	{
		return test_.getWaitFor();
	}

	ProcessData* parameters = new ProcessData( command_line_, &process_information_, semaphore_ );

	HANDLE work_thread = CreateThread(NULL, NULL, &ProcessInfo::StartThread, parameters, NULL, NULL);
	if (work_thread == NULL)
	{
		logger << "Creating thread in ProcessTest failded";
		return nullptr;
	}

	if (!CloseHandle(work_thread))
	{
		logger << "Closing thread in ProcessTest handle failed";
	}

	status_ = Status::Running;
	return nullptr;
}

bool ProcessInfo::ReleaseResources()
{
	if (status_ != Status::Running)
		return false;

	int wait_result = WaitForSingleObject(process_information_.hProcess, NULL);

	// how to write this if blocks more readable?
	if (wait_result == WAIT_FAILED &&process_information_.hProcess != 0)
	{
		logger << "Wait for process termination failed";
		return false;
	}
	if (wait_result == WAIT_OBJECT_0)
	{
		DWORD returned_value;

		bool get_result = GetExitCodeProcess(process_information_.hProcess, &returned_value);

		CloseHandle(process_information_.hProcess);
		CloseHandle(process_information_.hThread);

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
			return true;
		}
	}
	else
	{
		// process is still running
		return false;
	}
}


ProcessInfo::operator TRSResult() const
{
	return TRSResult(path_, test_.getName(), result_, duration_);
}