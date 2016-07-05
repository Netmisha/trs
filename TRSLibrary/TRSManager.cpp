#include "stdafx.h"
#define TRSLibrary_EXPORT
#include "TRSManager.h"
#include "FunctionalityForXML.h"
#include "spdlog\spdlog.h"
#include <iostream>
#include <memory>
#include <memory>


using namespace std;
namespace spd = spdlog;

TRSManager Manager;
Logger logger;


void TestRunner::Execute(char* command)
{
	system(command);
}

void Logger::operator<<(char* mess)
{
	log_->info(mess);
	system("pause");
}

bool Logger::Init()
{
	try
	{
		std::vector<spd::sink_ptr> sinks;
		sinks.push_back(std::make_shared<spd::sinks::simple_file_sink_mt>("logs.txt"));
		sinks.push_back(std::make_shared<spd::sinks::stderr_sink_mt>());

		 log_ = std::make_shared<spd::logger>("logger", begin(sinks), end(sinks));
	}
	catch (const spd::spdlog_ex& ex)
	{
		std::cerr << "Log failed: " << ex.what() << std::endl;
		return false;
	}
	return true;
}

Logger::~Logger()
{
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

bool TRSManager::Verify(char* path, char* name, char* tag)
{
	return false;
}

bool TRSManager::Run(char* path, char* name, char* tag)
{
	if (path != nullptr)
	{
		cout << "path: ";
		for (int i = 0; path[i] != 0; ++i)
			cout << path[i];
		cout << endl;
	}

	if (name != nullptr)
	{
		cout << "name: ";
		for (int i = 0; name[i] != 0; ++i)
			cout << name[i];
		cout << endl;
	}

	if (tag != nullptr)
	{
		cout << "tag: ";
		for (int i = 0; tag[i] != 0; ++i)
			cout << tag[i];
		cout << endl;
	}
	return false;
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
						
						List(convertToChar(subDir), "", "");//workin' only for path,not for names or tags yet
					}
				}
				else
				{
					
					std::wstring name(ffd.cFileName);//used for validating file name(checks if there is .xml in the end
					if (Validate(name))//validating function
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
							currentSuite->Parse(&doc);
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

bool TRSManager::Destroy(char* path, char* name, char* tag)
{
	return false;
}