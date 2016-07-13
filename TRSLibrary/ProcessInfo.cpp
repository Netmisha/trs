#include "stdafx.h"
#include "ProcessInfo.h"
#include "FunctionalityForXML.h"
#include "TRSManager.h"
#include "TRSTest.h"

#include <chrono>
using namespace std::chrono;

// =========================================================================================================================================================

ProcessData::ProcessData( ProcessInfo info, PROCESS_INFORMATION* pi, HANDLE handles[SEMAPHORES_AMOUNT]) : process_information(pi), running_process(info)
{
	semaphores[OWNED_SEMAPHORE] = handles[OWNED_SEMAPHORE];
	semaphores[MANAGING_SEMAPHORE] = handles[MANAGING_SEMAPHORE];
}


// =========================================================================================================================================================

ProcessInfo::ProcessInfo(const TRSTest& test, char* path, HANDLE semaphores[SEMAPHORES_AMOUNT], ReportManager* pReporter) : 
test_(test), status_(Status::Waiting), result_(false), duration_(0), pReporter_(pReporter), work_thread_(NULL), description_(nullptr)
{
	semaphores_[OWNED_SEMAPHORE] = semaphores[OWNED_SEMAPHORE];
	semaphores_[MANAGING_SEMAPHORE] = semaphores[MANAGING_SEMAPHORE];

	max_time_ = ParseMaxTime();


	int path_len = strlen(path);
	path_ = new char[path_len + 1];
	strcpy_s(path_, path_len + 1, path);

	
	int exe_path_size = strlen(path) + strlen(test_.get_executableName());
	if (test_.getParameters() != nullptr)
		exe_path_size += strlen(test_.getParameters()) + 1;

	command_line_ = new wchar_t[exe_path_size + 1];

	char executable_directory_A[MAX_PATH + 1];
	executable_directory_A[0] = 0;
	strcat_s(executable_directory_A, MAX_PATH + 1, path);
	strcat_s(executable_directory_A, MAX_PATH + 1, test_.get_executableName());
	
	if (test_.getParameters() != nullptr)
	{
		strcat_s(executable_directory_A, MAX_PATH + 1, " ");
		strcat_s(executable_directory_A, MAX_PATH + 1, test_.getParameters());
	}
	convertToTCHAR(command_line_, executable_directory_A);
	
	ZeroMemory(&process_information_, sizeof(process_information_));
}

ProcessInfo::ProcessInfo(const ProcessInfo& instance):
test_(instance.test_), status_(instance.status_), work_thread_(instance.work_thread_), pReporter_(instance.pReporter_), description_(instance.description_),
result_(instance.result_), process_information_(instance.process_information_), duration_(instance.duration_), max_time_(instance.max_time_)
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
	if (description_)
		delete[] description_;
}

// =========================================================================================================================================================

long long ProcessInfo::ParseMaxTime()
{
	char* str = test_.getMaxTime();
	int size = strlen(str);

	char* sequence_end;

	bool default = true;
	for (int i = 0; i < size; ++i)
	{
		if (isalpha(str[i]))
		{
			default = false;
			break;
		}
	}

	if (default)
		return strtol(str, nullptr, NUMERIC_BASE);

	char identificator[MAX_IDEN_LENGHT + 1];

	duration<long, std::milli> total_time;
	while (*str != '\0')
	{
		long time = strtol(str, &sequence_end, NUMERIC_BASE);
		while (isspace(*sequence_end))
			++sequence_end;

		int identificator_len = 0;
		for (; isalpha(sequence_end[identificator_len]); ++identificator_len)
		{
			// empty body
		}
		if (identificator_len > MAX_IDEN_LENGHT)
		{
			logger << "Max_time identificator is too long";
			return -1;
		}

		for (int i = 0; i < identificator_len; ++i)
			identificator[i] = sequence_end[i];
		identificator[identificator_len] = 0;


		if (!_stricmp(identificator, "D"))
		{
			duration<long, std::ratio<60 * 60 * 24>> days(time);
			total_time += duration_cast<milliseconds>(days);
		}
		else if (!_stricmp(identificator, "H"))
		{
			duration<long, std::ratio<60 * 60>> hours(time);
			total_time += duration_cast<milliseconds>(hours);
		}
		else if (!_stricmp(identificator, "M"))
		{
			duration<long, std::ratio<60>> minutes(time);
			total_time += duration_cast<milliseconds>(minutes);
		}
		else if (!_stricmp(identificator, "S"))
		{
			duration<long> seconds(time);
			total_time += duration_cast<milliseconds>(seconds);
		}
		else if (!_stricmp(identificator, "MS"))
		{
			duration<long, std::milli> milliseconds(time);
			total_time += milliseconds;
		}
		else
		{
			logger << "Unrecognised max_time identificator";
			return -1;
		}

		str = sequence_end + identificator_len;
		while (isspace(*str))
			++str;
	}

	return total_time.count();
}


bool ProcessInfo::IsDisable() const
{
	if (test_.getDisable() == nullptr)
		return false;

	return _stricmp(test_.getDisable(), "false");
}


int ProcessInfo::GetPriority() const
{
	if (test_.getPriority() == nullptr)
		return -1;

	return atoi(test_.getPriority());
}

char* ProcessInfo::ProcessTest(bool ignore_wait)
{
	// assuming that test is waiting
	if (!ignore_wait && test_.getWaitFor() != nullptr)
	{
		return test_.getWaitFor();
	}

	ProcessData* parameters = new ProcessData(*this, &process_information_, semaphores_);

	HANDLE work_thread = CreateThread(NULL, NULL, &ProcessInfo::StartThread, parameters, NULL, NULL);
	if (work_thread == NULL)
	{
		logger << "Creating thread in ProcessTest failded";
		return nullptr;
	}
	CloseHandle(work_thread);
	status_ = Status::Running;
	return nullptr;
}


DWORD WINAPI ProcessInfo::StartThread(LPVOID parameters)
{
	// recording time in order to evaluate function duration
	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	ProcessData data = *((ProcessData*)parameters);
	// recording time for reporter
	data.running_process.pReporter_->beforeExecution(data.running_process.test_);

	STARTUPINFO startup_info;
	ZeroMemory(&startup_info, sizeof(startup_info));
	startup_info.cb = sizeof(startup_info);

	// starting our desirable executable file
	bool create_result = CreateProcess(NULL, data.running_process.command_line_, NULL, NULL, FALSE, CREATE_NO_WINDOW,
		NULL, NULL, &startup_info, data.process_information);

	if (!create_result)
	{
		delete parameters;
		logger << "Create process failed";
		return -1;
	}

	// Successfully created the process.  Wait for it to finish no more than MAX_TIME
	int wait_result = WaitForSingleObject(data.process_information->hProcess, data.running_process.max_time_);

	if (wait_result != WAIT_FAILED)
	{
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

		high_resolution_clock::time_point t2 = high_resolution_clock::now();
		data.running_process.duration_ = duration_cast<milliseconds>(t2 - t1);

		char* message;
		if (wait_result == WAIT_OBJECT_0)
		{
			DWORD returned_value;
			bool get_result = GetExitCodeProcess(data.process_information->hProcess, &returned_value);
			// setting apropriate description
			if (!get_result)
			{
				logger << "Process executed but an error occured while getting its exit code";
				return 1;
			}
			else
			{
				int expected_value = atoi(data.running_process.test_.get_expectedResult());
				data.running_process.result_ = (expected_value == returned_value);

				if (data.running_process.result_)
					message = "Succeeded";
				else
					message = "Returned value is not mathing with expecting one";

			}
		}
		else
		{
			TerminateProcess(data.process_information->hProcess, -1);
			message = "Timeout";
			
			data.running_process.result_ = false;
		}
		Sleep(1000);
		std::cout << WaitForSingleObject(data.process_information->hProcess, NULL) << std::endl;
		int size = strlen(message);
		data.running_process.description_ = new char[size + 1];
		strcpy_s(data.running_process.description_, size + 1, message);

		//data.running_process.pReporter_->afterExecution(data.running_process.test_, data.running_process);

		delete parameters;
		return 0;
	}
	else
	{
		delete parameters;
		logger << "Waiting for the process failed";
		return -1;
	}
}


bool ProcessInfo::ReleaseResources()
{
	CloseHandle(process_information_.hThread);
	CloseHandle(process_information_.hProcess);
	return true;
}

// WILL BE CHANGED AFTER REPORTER'S INTEGRATION
bool ProcessInfo::IsDone()
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
	/*	CloseHandle(process_information_.hProcess);
		CloseHandle(process_information_.hThread);
		ZeroMemory(&process_information_, sizeof(process_information_));*/

		status_ = Status::Done;
		return true;
	}
	else
	{
		// process is still running
		return false;
	}
}

// WILL BE ERASED AFTER REPORTER'S INTEGRATION
//bool ProcessInfo::RecordDuration()
//{
//	int wait_thread = WaitForSingleObject(work_thread_, INFINITE);
//	
//	if (wait_thread == WAIT_FAILED && work_thread_ != NULL)
//	{
//		logger << "Wait for thread termination failed";
//		return false;
//	}
//	if (wait_thread == WAIT_OBJECT_0)
//	{
//		DWORD returned_value;
//
//		bool get_result = GetExitCodeThread(work_thread_, &returned_value);
//
//		CloseHandle(work_thread_);
//
//		ZeroMemory(&work_thread_, sizeof(work_thread_));
//
//		if (!get_result)
//		{
//			logger << "Thread terminated but an error occured while getting its exit code";
//			return false;
//		}
//		else
//		{
//			duration<long long, std::milli> test_duration(returned_value);
//			duration_ = test_duration;
//			return true;
//		}
//	}
//	else
//	{
//		// thread is still running
//		return false;
//	}
//}

ProcessInfo::operator TRSResult() const
{
	return TRSResult(path_, test_.getName(), description_,  result_, duration_);
}
