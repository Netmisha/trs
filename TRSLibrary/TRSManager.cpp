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


int TestRunner::Execute(char* command)
{
	return system(command);
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
	List(path, name, tag);
	if (suiteCollection->size() != 0)
	{
		std::list<Suite*>::iterator it = suiteCollection->begin();
		for (it; it != suiteCollection->end(); ++it)
		{
			std::list<TRSTest*>::iterator iter = (*it)->getList().begin();
			for (iter; iter != (*it)->getList().end(); ++iter)
			{
				if (!((*iter)->getName()))
				{
					return 1;
				}
				if ((!(*iter)->get_executableName()))
				{
					return 2;
				}
				if ((!(*iter)->get_expectedResult()))
				{
					return 3;
				}
				char* buf = new char[strlen((*it)->get_path()) + strlen((*iter)->get_executableName()) + 1];
				strncpy_s(buf, strlen((*it)->get_path()) + 1, (*it)->get_path(), strlen((*it)->get_path()));
				strncpy_s(buf + strlen((*it)->get_path()), strlen((*iter)->get_executableName()) + 1, (*iter)->get_executableName(), strlen((*iter)->get_executableName()));
				DWORD fFile = GetFileAttributesA(buf);
				if ((fFile& FILE_ATTRIBUTE_DIRECTORY))
				{
					delete[] buf;
					return 6;
				}
				else
				{
					delete[] buf;
					
				}
			}
			
		}
		return 4;
	}
	return 5;
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
//			int exe_path_size = strlen(test_path) + strlen(test->get_executableName());
//			char* executable_directory = new char[exe_path_size + 1];
			const int exe_path_size = MAX_PATH;
			char executable_directory[exe_path_size + 1];



			executable_directory[0] = 0;
			strcat_s(executable_directory, exe_path_size + 1, test_path);
			strcat_s(executable_directory, exe_path_size + 1, test->get_executableName());

			int expected_result = atoi(test->get_expectedResult());
			
			result = (expected_result == TestRunner::Execute(executable_directory));

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