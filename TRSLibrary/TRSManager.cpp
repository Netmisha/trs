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

bool TRSManager::Run(char* path, char* name, char* tag, unsigned threads_amount, ReportManager* pResult)
{
	if (!VerifyParameters(path, name, tag) || threads_amount > MAX_THREADS)
		return false;

	std::list<Suite*> arr = *List(path, name, tag);
	if (arr.size() == 0)
		return false;

	std::list<Suite> coll;

	for (auto var = arr.begin(); var != arr.end(); ++var)
		coll.push_back(**var);

	// TODO: add parameter to Console command line
	SuiteCollection suits(coll, threads_amount, pResult);

	return suits.Run();
}

int TRSManager::Verify(char* path, char* name, char* tag)
{
	if (!VerifyParameters(path, name, tag))
		return INVALID_PARAMETERS;

		std::list<Suite*>* suiteCollection=List(path, name, tag);
		if (suiteCollection)
		{
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
					if ((*iter)->getExecutablePath())
					{
						DWORD fFile = GetFileAttributesA((*iter)->getExecutablePath());
						if ((fFile != INVALID_FILE_ATTRIBUTES))
						{
							return WRONG_PATH_EXECUTION;
						}
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
		else
		{
			return EXE_OR_XML_ABSENT;
		}
}

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

int TRSManager::FillList(char*path, char*name, char*tag, std::list<Suite*>*suiteCollection)
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
			bool exeExist = false;
			bool xmlExist = false;
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
						if (FillList(way, name, tag, suiteCollection) != EXE_OR_XML_ABSENT)
						{
							delete[] way;
						}
						else
						{
							delete[] way;
							return EXE_OR_XML_ABSENT;
						}
					}
				}
				else
				{

					std::wstring name_(ffd.cFileName);//used for validating file name(checks if there is .xml in the end
					if (Validate(name_))//validating function
					{
						xmlExist = true;
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
					else
					{
						if (name_[name_.length() - 1] == 'e')
						{
							if (name_[name_.length() - 2] == 'x')
							{
								if (name_[name_.length() - 3] == 'e')
								{
									if (name_[name_.length() - 4] == '.')
									{
										exeExist=true;
									}
								}
							}
						}
					}
				}
			} while (FindNextFile(hFind, &ffd) != 0);//repeat
			if (xmlExist)
			{
				if (!exeExist)
					return EXE_OR_XML_ABSENT;
			}
			if (exeExist)
			{
				if (!xmlExist)
					return EXE_OR_XML_ABSENT;
			}
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
	if (FillList(path, name, tag, suiteCollection) != EXE_OR_XML_ABSENT)
	{
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
	else
	{
		return nullptr;
	}
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

bool TRSManager::SetReport(char* path,char* name,char* tag, unsigned threads_amount, ReportManager* pReport)
{
	if (!VerifyParameters(path, name, tag))
		return false;

	Manager.Run(path, name, tag, threads_amount, pReport);
	return true;
}

