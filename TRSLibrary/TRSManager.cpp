#include "stdafx.h"
#define TRSLibrary_EXPORT
#include "TRSManager.h"
#include "FunctionalityForXML.h"
#include "spdlog\spdlog.h"
#include <iostream>
#include <memory>
#include <vector>

using namespace std;
namespace spd = spdlog;

TRSManager Manager;
Logger logger;


int TestRunner::Execute(wchar_t* command)
{
	PROCESS_INFORMATION process_information;
	ZeroMemory(&process_information, sizeof(process_information));

	STARTUPINFO startup_info; 
	ZeroMemory(&startup_info, sizeof(startup_info));

	startup_info.cb = sizeof(startup_info);

	//TCHAR* cmd = TEXT("D:\\Repository\\trs\\TestData\\TestStrcuture\\Suite1\\test.exe");
	LPTSTR szCmdline = _tcsdup(command);

	bool create_result = CreateProcess(NULL, szCmdline, NULL, NULL, FALSE, 0,
		NULL, NULL, &startup_info, &process_information);

	if (!create_result)
	{
		logger << "Create process failed with error";
		cout << GetLastError() << endl;
		return -1;
	}

	// Successfully created the process.  Wait for it to finish.
	WaitForSingleObject(process_information.hProcess, INFINITE);

	DWORD ret_val;

	// Get the exit code.
	bool get_result = GetExitCodeProcess(process_information.hProcess, &ret_val);

	// Close the handles.
	CloseHandle(process_information.hProcess);
	CloseHandle(process_information.hThread);

	if (!get_result)
	{
		logger << "Process executed but an error occured while getting its exit code";
		cout << GetLastError() << endl;
		return -1;
	}

	return ret_val;
}

void Logger::operator<<(char* message)
{
	text_log_->info(message);
	console_log_->info(message);
	system("pause");
}

bool Logger::Init()
{
	try
	{
		auto sink = std::make_shared<spd::sinks::simple_file_sink_mt>("logs.txt");
		text_log_ = std::make_shared<spdlog::logger>("file_logger", sink);
		
		console_log_ = spd::stderr_logger_mt("console_logger");
		console_log_->set_pattern(">>>>>>>>> %v <<<<<<<<<");
	}
	catch (const spd::spdlog_ex& ex)
	{
		std::cerr << "Log failed: " << ex.what() << std::endl;
		return false;
	}
	return true;
}

void Logger::Destroy()
{
	spd::drop_all();
}

TRSManager::TRSManager()
{
	suiteCollection = new std::list<Suite*>;
}

TRSManager::~TRSManager()
{
	
}

bool TRSManager::Init()
{
	logger.Init();
	return false;
}

bool TRSManager::Destroy()
{
	logger.Destroy();
	return false;
}

bool TRSManager::Verify(char* path, char* name, char* tag)
{
	return false;
}


std::vector<TRSResult> TRSManager::Run(char* path, char* name, char* tag)
{
	std::list<Suite*> arr = *List(path, name, tag);

	char* test_name, *test_path;
	bool result;
	std::vector<TRSResult> result_vector;

	for each(Suite* var in arr)
	{
		test_path = var->get_path();
		for each (auto test in var->getList())
		{
			test_name = test->getName();
	
			// alternative version
		//	int exe_path_size = strlen(test_path) + strlen(test->get_executableName());
		//	wchar_t* executable_directory = new wchar_t[exe_path_size + 1];
			
			wchar_t executable_directory_W[MAX_PATH + 1];

			char executable_directory_A[MAX_PATH + 1];
			
			executable_directory_A[0] = 0;
			strcat_s(executable_directory_A, MAX_PATH + 1, test_path);
			strcat_s(executable_directory_A, MAX_PATH + 1, test->get_executableName());
		
			
			convertToTCHAR(executable_directory_W, executable_directory_A);
	

			int expected_result = atoi(test->get_expectedResult());
			
			result = (expected_result == TestRunner::Execute(executable_directory_W));

			result_vector.push_back(TRSResult(test_path, test_name, result));

//			delete[] executable_directory;
		}
	}


	return result_vector;
}

bool TRSManager::Pause(char* path, char* name, char* tag)
{
	return false;
}

bool TRSManager::Stop(char* path, char* name, char* tag)
{
	return false;
}

std::list<Suite*>* TRSManager::List(char* path, char* name, char* tag)
{
	DWORD fFile = GetFileAttributesA(path);
	if (fFile& FILE_ATTRIBUTE_DIRECTORY)
	{
		
		TRSInfo* info;
		WIN32_FIND_DATA ffd;//variable that contains file info(if such is open with it)
		HANDLE hFind;
		TCHAR szDir[MAX_PATH];//buffer that holds file path
		TCHAR hzDir[MAX_PATH];//help buffer that holds root path
		char buffer[BUF_SIZE];//buffer for new XML-file
		TiXmlDocument newDoc;//new XML-document


		convertToTCHAR(szDir, path);//converting input parameters from char* to TCHAR*
		convertToTCHAR(hzDir, path);
		StringCchCat(szDir, MAX_PATH, TEXT("\\*"));//add end symbol to search in this directory

		hFind = FindFirstFile(szDir, &ffd);//open first Folder


		if (hFind == INVALID_HANDLE_VALUE)
		{
			std::cout << "FindFirstFile failed\n";
			
		}
		else
		{
			do
			{
				if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)//check if it's a folder or not
				{
					
					if (*ffd.cFileName != (WCHAR)'.')//not to enter '.' and '..' folders
					{
						TCHAR subDir[MAX_PATH];//create additional buffer for recursive traverse
						StringCchCopy(subDir, MAX_PATH, hzDir);//fill additional buffer with this folder's path
						StringCchCat(subDir, MAX_PATH, TEXT("\\"));//additional slash))
						StringCchCat(subDir, MAX_PATH, ffd.cFileName);//name of last folder to search in
						
						List(convertToChar(subDir), name, tag);//workin' only for path,not for names or tags yet
					}
				}
				else
				{
					
					std::wstring name_(ffd.cFileName);//used for validating file name(checks if there is .xml in the end
					if (Validate(name_))//validating function
					{
						TCHAR fileDir[MAX_PATH];//buffer which contains a path to an xml file
						StringCchCopy(fileDir, MAX_PATH, hzDir);//some moves to save path
						StringCchCat(fileDir, MAX_PATH, TEXT("\\"));
						TCHAR currentDir[MAX_PATH];
						StringCchCopy(currentDir, MAX_PATH, fileDir);
						StringCchCat(fileDir, MAX_PATH, ffd.cFileName);
						TiXmlDocument doc(convertToChar(fileDir));//try to open such document wuth tinyXML parser
						bool loadOk = doc.LoadFile();//check if opening was successfull
						if (loadOk)
						{
							Suite* currentSuite=new Suite();
							currentSuite->Parse(&doc,name,tag);
							currentSuite->setDir(convertToChar(currentDir));
							suiteCollection->push_back(currentSuite);
						}
					}
				}
			} while (FindNextFile(hFind, &ffd) != 0);//repeat
		}
		return suiteCollection;
	}
	else
	{
		//place for exception
	}
}

bool TRSManager::Status(char* path, char* name, char* tag)
{
	return false;
}

bool TRSManager::Info(char* path, char* name, char* tag)
{
	return false;
}