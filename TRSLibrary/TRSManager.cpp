#include "stdafx.h"
#define TRSLibrary_EXPORT
#include "TRSManager.h"
#include "FunctionalityForXML.h"
#include "spdlog\spdlog.h"
#include "ProcessCollection.h"
#include "SuiteCollection.h"
#include "TestsListVerifying.h"
#include <iostream>
#include <memory>
#include "Erorrs.h"
#include <vector>
#include <chrono>

using namespace std;
namespace spd = spdlog;
using namespace std::chrono;

TRSManager Manager;
Logger logger;


bool TRSManager::VerifyParameters(char* path, char* name, char* tag)
{
	DWORD dwAttrib = GetFileAttributesA(path);

	if (dwAttrib == INVALID_FILE_ATTRIBUTES || !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY))
	{
		logger << "Specified path is not exist";
		return false;
	}
	return true;
}

bool TRSManager::Run(char* path, char* name, char* tag, ReportManager* pResult)
{
	if (!VerifyParameters(path, name, tag))
		return false;

	std::list<Suite*> arr = *List(path, name, tag);
	if (arr.size() == 0)
	{
		return false;
	}
	std::list<Suite> coll;

	for (auto var = arr.begin(); var != arr.end(); ++var)
		coll.push_back(**var);
	
	// TODO: add parameter to Console command line
	SuiteCollection suits(coll, 10, pResult);
	
	return suits.Run();
}


int TestRunner::Execute(wchar_t* command)
{
	PROCESS_INFORMATION process_information;
	ZeroMemory(&process_information, sizeof(process_information));

	STARTUPINFO startup_info; 
	ZeroMemory(&startup_info, sizeof(startup_info));

	startup_info.cb = sizeof(startup_info);

	LPTSTR szCmdline = _tcsdup(command);

	bool create_result = CreateProcess(NULL, szCmdline, NULL, NULL, FALSE, CREATE_NO_WINDOW,
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
// ============================================================================================================
void Logger::operator<<(char* message)
{
	text_log_->info(message);
	console_log_->info(message);
}

bool Logger::Init()
{
	try
	{
		auto sink = std::make_shared<spd::sinks::simple_file_sink_mt>("logs.txt");
		text_log_ = std::make_shared<spdlog::logger>("file_logger", sink);
		
		console_log_ = spd::stderr_logger_mt("console_logger");
		console_log_->set_pattern("\t\t\t%v");
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

// ===============================================================================================================

TRSManager::TRSManager()
{
	
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

int TRSManager::Verify(char* path, char* name, char* tag)
{
	if (!VerifyParameters(path, name, tag))
		return INVALID_PARAMETERS;

		std::list<Suite*>* suiteCollection=List(path, name, tag);
		if (suiteCollection->size() == 0)
		{
			return DEAD_LOCK_WAS_FOUND;
		}
		std::list<Suite*>::iterator it = suiteCollection->begin();
		for (it; it != suiteCollection->end(); ++it)
		{
			std::list<TRSTest*>::iterator iter = (*it)->getList().begin();
			std::vector<char*> coll;
			std::vector<TRSTest*>collTests;
			for (iter; iter != (*it)->getList().end(); ++iter)
			{
				if (!((*iter)->getName()))
				{
					return INVALID_NAME;
				}
				if ((!(*iter)->get_executableName()))
				{
					return INVALID_EXECUTION_NAME;
				}
				if ((!(*iter)->get_expectedResult()))
				{
					return INVALID_RESULT;
				}
				char* buf = new char[strlen((*it)->get_path()) + strlen((*iter)->get_executableName()) + 1];
				strncpy_s(buf, strlen((*it)->get_path()) + 1, (*it)->get_path(), strlen((*it)->get_path()));
				strncpy_s(buf + strlen((*it)->get_path()), strlen((*iter)->get_executableName()) + 1, (*iter)->get_executableName(), strlen((*iter)->get_executableName()));
				DWORD fFile = GetFileAttributesA(buf);
				if ((fFile& FILE_ATTRIBUTE_DIRECTORY))
				{
					delete[] buf;
					return INVALID_EXE_FILE;
				}
				else
				{
					delete[] buf;
					collTests.push_back((*iter));
				}
			}
		}
		return SUCCSEED;
}


// OLD RUN FUNCTION
//std::vector<TRSResult> TRSManager::Run(char* path, char* name, char* tag,ReportManager* pResult)
//{
//	std::list<Suite*> arr = *List(path, name, tag);
//
//	char* test_name, *test_path;
//	bool result;
//	std::vector<TRSResult> result_vector;
//
//	for each(Suite* var in arr)
//	{
//		test_path = var->get_path();
//		for each (auto test in var->getList())
//		{
//			test_name = test->getName();
//	
//			// alternative version
//		//	int exe_path_size = strlen(test_path) + strlen(test->get_executableName());
//		//	wchar_t* executable_directory = new wchar_t[exe_path_size + 1];
//			
//			wchar_t executable_directory_W[MAX_PATH + 1];
//
//			char executable_directory_A[MAX_PATH + 1];
//			
//			executable_directory_A[0] = 0;
//			strcat_s(executable_directory_A, MAX_PATH + 1, test_path);
//			strcat_s(executable_directory_A, MAX_PATH + 1, test->get_executableName());
//		
//			
//			convertToTCHAR(executable_directory_W, executable_directory_A);
//	
//
//			int expected_result = atoi(test->get_expectedResult());
//			if (pResult)
//			{
//				pResult->beforeExecution(test);
//			}
//			high_resolution_clock::time_point t1 = high_resolution_clock::now();
//			
//			
//			result = (expected_result == TestRunner::Execute(executable_directory_W));
//			
//			high_resolution_clock::time_point t2 = high_resolution_clock::now();
//
//			auto duration = duration_cast<milliseconds>(t2 - t1);
//			TRSResult resultInfo = TRSResult(test_path, test_name, result, duration);
//			if (pResult)
//			{
//			
//				pResult->afterExecution(test, &resultInfo);
//			}
//			result_vector.push_back(resultInfo);
//
////			delete[] executable_directory;
//		}
//	}
//
//
//	return result_vector;
//}

bool TRSManager::Pause(char* path, char* name, char* tag)
{
	if (!VerifyParameters(path, name, tag))
		return false;
	return false;
}

bool TRSManager::Stop(char* path, char* name, char* tag)
{
	if (!VerifyParameters(path, name, tag))
		return false;
	return false;
}

bool TRSManager::FillList(char*path, char*name, char*tag, std::list<Suite*>*suiteCollection)
{
	if (!VerifyParameters(path, name, tag))
		return false;
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
			return 0;
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
						char* way = convertToChar(subDir);
						FillList(way, name, tag,suiteCollection);
						delete[] way;
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
						char* way = convertToChar(fileDir);
						TiXmlDocument doc(way);//try to open such document wuth tinyXML parser
						bool loadOk = doc.LoadFile();//check if opening was successfull
						if (loadOk)
						{
							Suite* currentSuite = new Suite();
							currentSuite->Parse(&doc, name, tag);
							char*SuiteWay = convertToChar(currentDir);
							currentSuite->setDir(SuiteWay);
							delete[] SuiteWay;
							suiteCollection->push_back(currentSuite);
						}
						delete[] way;
					}
				}
			} while (FindNextFile(hFind, &ffd) != 0);//repeat
		}
		return true;
	}
	else
	{
		//place for exception
	}
}

std::list<Suite*>* TRSManager::List(char* path, char* name, char* tag)
{
	if (!VerifyParameters(path, name, tag))
		return nullptr;

	std::list<Suite*>*suiteCollection = new std::list<Suite*>;
	FillList(path, name, tag, suiteCollection);
	std::list<Suite*>::iterator it = suiteCollection->begin();
	for (it; it != suiteCollection->end(); ++it)
	{
		std::list<TRSTest*>::iterator iter = (*it)->getList().begin();
		std::vector<char*> coll;
		std::vector<TRSTest*>collTests;
		for (iter; iter != (*it)->getList().end(); ++iter)
		{
			if (!((*iter)->getName()))
			{
				std::list<Suite*>::iterator it = suiteCollection->begin();
				for (it; it != suiteCollection->end(); ++it)
				{
					delete (*it);
				}
				suiteCollection->clear();
				return suiteCollection;
			}
			if ((!(*iter)->get_executableName()))
			{
				std::list<Suite*>::iterator it = suiteCollection->begin();
				for (it; it != suiteCollection->end(); ++it)
				{
					delete (*it);
				}
				suiteCollection->clear();
				return suiteCollection;
			}
			if ((!(*iter)->get_expectedResult()))
			{
				std::list<Suite*>::iterator it = suiteCollection->begin();
				for (it; it != suiteCollection->end(); ++it)
				{
					delete (*it);
				}
				suiteCollection->clear();
				return suiteCollection;
			}
			char* buf = new char[strlen((*it)->get_path()) + strlen((*iter)->get_executableName()) + 1];
			strncpy_s(buf, strlen((*it)->get_path()) + 1, (*it)->get_path(), strlen((*it)->get_path()));
			strncpy_s(buf + strlen((*it)->get_path()), strlen((*iter)->get_executableName()) + 1, (*iter)->get_executableName(), strlen((*iter)->get_executableName()));
			DWORD fFile = GetFileAttributesA(buf);
			if ((fFile& FILE_ATTRIBUTE_DIRECTORY))
			{
				delete[] buf;
				std::list<Suite*>::iterator it = suiteCollection->begin();
				for (it; it != suiteCollection->end(); ++it)
				{
					delete (*it);
				}
				suiteCollection->clear();
				return suiteCollection;
			}
			else
			{
				delete[] buf;
				collTests.push_back((*iter));
			}
		}
		for (int i = 0; i < collTests.size(); ++i)
		{
			if (!VerifyTestsList(collTests, (*it)->getList().size(), coll, i))
			{
				std::list<Suite*>::iterator it = suiteCollection->begin();
				for (it; it != suiteCollection->end(); ++it)
				{
					delete (*it);
				}
				suiteCollection->clear();
				return suiteCollection;
			}
		}
	}
	return suiteCollection;
}

bool TRSManager::Status(char* path, char* name, char* tag)
{
	if (!VerifyParameters(path, name, tag))
		return false;
	return false;
}

bool TRSManager::Info(char* path, char* name, char* tag)
{
	if (!VerifyParameters(path, name, tag))
		return false;
	return false;
}

bool TRSManager::SetReport(char* path,char* name,char* tag,ReportManager* pReport)
{
	if (!VerifyParameters(path, name, tag))
		return false;

	Manager.Run(path, name, tag, pReport);
	return true;
}

