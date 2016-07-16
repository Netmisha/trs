#include "stdafx.h"
#include "ProcessInfo.h"
#include "FunctionalityForXML.h"
#include "TRSManager.h"
#include "TRSTest.h"

#include <chrono>
using namespace std::chrono;

// =========================================================================================================================================================

ProcessData::ProcessData( ProcessInfo* info, HANDLE handles[SEMAPHORES_AMOUNT]) : running_process(info)
{
	semaphores[OWNED_SEMAPHORE] = handles[OWNED_SEMAPHORE];
	semaphores[MANAGING_SEMAPHORE] = handles[MANAGING_SEMAPHORE];
}


// =========================================================================================================================================================

ProcessInfo::ProcessInfo(const TRSTest& test, char* path, HANDLE semaphores[SEMAPHORES_AMOUNT], ThreadPool* threads, ReportManager* pReporter) : 
test_(test), status_(Status::Waiting), result_(false), duration_(0), pReporter_(pReporter), result_description_(nullptr), threads_(threads)
{
	InitializeCriticalSection(&crt_);
	semaphores_[OWNED_SEMAPHORE] = semaphores[OWNED_SEMAPHORE];
	semaphores_[MANAGING_SEMAPHORE] = semaphores[MANAGING_SEMAPHORE];

	max_time_ = ParseMaxTime();

	int path_len = strlen(path);
	path_ = new char[path_len + 1];
	strcpy_s(path_, path_len + 1, path);

	int exe_path_len = strlen(test_.getExecutablePath());
	command_line_ = new wchar_t[exe_path_len + 1];
	convertToTCHAR(command_line_, test_.getExecutablePath());

	//int exe_path_size = strlen(path) + strlen(test_.get_executableName());
	//if (test_.getParameters() != nullptr)
	//	exe_path_size += strlen(test_.getParameters()) + 1;

	//command_line_ = new wchar_t[exe_path_size + 1];

	//char executable_directory_A[MAX_PATH + 1];
	//executable_directory_A[0] = 0;
	//strcat_s(executable_directory_A, MAX_PATH + 1, path);
	//strcat_s(executable_directory_A, MAX_PATH + 1, test_.get_executableName());


	//if (test_.getParameters() != nullptr)
	//{
	//	strcat_s(executable_directory_A, MAX_PATH + 1, " ");
	//	strcat_s(executable_directory_A, MAX_PATH + 1, test_.getParameters());
	//}
	//convertToTCHAR(command_line_, executable_directory_A);

	ZeroMemory(&process_information_, sizeof(process_information_));
}

ProcessInfo::ProcessInfo(const ProcessInfo& instance):
test_(instance.test_), status_(instance.status_), pReporter_(instance.pReporter_), result_description_(instance.result_description_),
result_(instance.result_), process_information_(instance.process_information_), duration_(instance.duration_), max_time_(instance.max_time_), threads_(instance.threads_)
{
	InitializeCriticalSection(&crt_);

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
	DeleteCriticalSection(&crt_);
	delete[] path_;
	delete[] command_line_;
	if (result_description_)
		delete[] result_description_;
}

// =========================================================================================================================================================

long ProcessInfo::ParseMaxTime()
{
	char* str = test_.getMaxTime();
	if (!str)
		return INFINITE;

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

	ProcessData* parameters = new ProcessData(this, semaphores_);
	if (!threads_->AddTask(&ProcessInfo::StartThread, parameters))
	{
		logger << "Adding Task to thread pool failed";
		return nullptr;
	}

	status_ = Status::Running;
	return nullptr;
}

DWORD WINAPI ProcessInfo::StartThread(LPVOID parameters)
{
	int id = GetCurrentThreadId();
	// recording time in order to evaluate function duration
	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	ProcessData* data = (ProcessData*)parameters;
	// recording time for reporter
	data->running_process->pReporter_->beforeExecution(data->running_process->test_);

	STARTUPINFO startup_info;
	ZeroMemory(&startup_info, sizeof(startup_info));
	startup_info.cb = sizeof(startup_info);

	// starting our desirable executable file
	bool create_result = CreateProcess(NULL, data->running_process->command_line_, NULL, NULL, FALSE, CREATE_NO_WINDOW,
		NULL, NULL, &startup_info, &data->running_process->process_information_);

	char* message;

	if (create_result)
	{
		// Successfully created the process.  Wait for it to finish no more than MAX_TIME
		int wait_result = WaitForSingleObject(data->running_process->process_information_.hProcess, data->running_process->max_time_);

		switch (wait_result)
		{
		case WAIT_OBJECT_0:
		{
			DWORD returned_value;
			bool get_result = GetExitCodeProcess(data->running_process->process_information_.hProcess, &returned_value);
			// setting apropriate description
			if (get_result)
			{
				int expected_value = atoi(data->running_process->test_.get_expectedResult());
				data->running_process->result_ = (expected_value == returned_value);

				if (data->running_process->result_)
					message = "Succeeded";
				else
					message = "Returned value is not mathing with expecting one";
			}
			else
			{
				logger << "Process executed but an error occured while getting its exit code";
				message = "Process executed but an error occured while getting its exit code";
				data->running_process->result_ = false;
			}
			break;
		}
		case WAIT_TIMEOUT:
		{
			TerminateProcess(data->running_process->process_information_.hProcess, -1);
			message = "Timeout";
			data->running_process->result_ = false;
			break;
		}
		default:
		{
			logger << "Waiting for the test failed";
			message = "Can not check test's return value";
			data->running_process->result_ = false;
			break;
		}
		}
	}
	else
	{
		logger << "CreateProcess failed";
		message = "Can not run the test";
		data->running_process->result_ = false;
	}

	data->running_process->set_status(Status::Closed);

	if (!ReleaseSemaphore(data->semaphores[OWNED_SEMAPHORE], 1, NULL))
		logger << "Incrementing OWNED_SEMAPHORE semaphore count is failed";

	if (!ReleaseSemaphore(data->semaphores[MANAGING_SEMAPHORE], 1, NULL))
		logger << "Incrementing MANAGING_SEMAPHORE semaphore count is failed";

	int size = strlen(message);
	data->running_process->result_description_ = new char[size + 1];
	strcpy_s(data->running_process->result_description_, size + 1, message);

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	data->running_process->duration_ = duration_cast<milliseconds>(t2 - t1);


	data->running_process->pReporter_->afterExecution(data->running_process->test_, *data->running_process);

	data->running_process->ReleaseResources();
	delete parameters;
	return 0;
}


bool ProcessInfo::ReleaseResources()
{
	bool ret_val = true;
	if (!CloseHandle(process_information_.hThread))
	{
		logger << "Closing thread failed";
		ret_val = false;
	}
	if (!CloseHandle(process_information_.hProcess))
	{
		logger << "Closing proccess failed";
		ret_val = false;
	}
	return ret_val;
}

bool ProcessInfo::operator<(const ProcessInfo& val)
{
	return GetPriority() < val.GetPriority();
}

ProcessInfo::operator TRSResult() const
{
	return TRSResult(path_, test_.getName(), result_description_,  result_, duration_);
}
