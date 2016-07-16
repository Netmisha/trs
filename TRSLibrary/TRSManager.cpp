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
#include "Errors.h"
#include <vector>
#include <chrono>

using namespace std;
namespace spd = spdlog;
using namespace std::chrono;

#define MAX_FILE_NAME_LENGHT 70

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
		system_clock::time_point today = system_clock::now();
		time_t tt = system_clock::to_time_t(today);
		char time[MAX_FILE_NAME_LENGHT];

		if (!ctime_s(time, MAX_FILE_NAME_LENGHT, &tt))
		{
			int len = strlen(time);
			time[len - 1] = 0;

			for (int i = 0; time[i] != 0; ++i)
			{
				if (time[i] == ':')
					time[i] = ' ';
			}
		}

		char buf[MAX_FILE_NAME_LENGHT];
		sprintf_s(buf, MAX_FILE_NAME_LENGHT, "Logger %s.txt", time);
		auto sink = std::make_shared<spd::sinks::simple_file_sink_mt>(buf);
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
	bool ret_val = true;

	if (dwAttrib == INVALID_FILE_ATTRIBUTES || !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY))
	{
		logger << "Specified path is not exist";
		ret_val = false;
	}

	return ret_val;
}

bool TRSManager::Run(char* path, char* name, char* tag, unsigned threads_amount, ReportManager* pResult)
{
	logger->info("Entered Run function with path: {}, amount of threads: {} ", path, threads_amount);
	if (name)
		logger->info("name: {} ", name);
	if (tag)
		logger->info("name: {} ", tag);


	if (Verify(path, name, tag) != SUCCEEDED || threads_amount > MAX_THREADS)

		return false;
	std::list<Suite*> arr = *List(path, name, tag);
	if (arr.size() == 0)
		return false;

	std::list<Suite> coll;

	for (auto var = arr.begin(); var != arr.end(); ++var)
		coll.push_back(**var);

	// TODO: add parameter to Console command line
	SuiteCollection suits(coll, threads_amount, pResult);

	bool ret_val = suits.Run();
	logger->info("Exit Run function with result: {0}", ret_val);
	return ret_val;
}

int TRSManager::Verify(char* path, char* name, char* tag)
{
	logger->info("Entered Verify function with path: {}", path);
	if (name)
		logger->info("name: {} ", name);
	if (tag)
		logger->info("name: {} ", tag);

	if (!VerifyParameters(path, name, tag))
		return INVALID_PARAMETERS;

	std::list<Suite*>* suiteCollection = List(path, name, tag);
	if (suiteCollection->size() == 0)
	{
		logger << "There are tests that waiting for each other or some xml or exe files are absent\n";
		return DEAD_LOCK_OR_FILES_ABSENT_WAS_FOUND;
	}
	std::list<Suite*>::iterator it = suiteCollection->begin();

	for (it; it != suiteCollection->end(); ++it)
	{
		std::list<TRSTest*>::iterator iter = (*it)->getList().begin();
		std::vector<TRSTest*>collTests;
		std::vector<char*> coll;
		for (iter; iter != (*it)->getList().end(); ++iter)
		{
			if (!((*iter)->getName()))
			{
				logger << "There are one(or more) test(s) without name\n";
				return INVALID_NAME;
			}
			if ((!(*iter)->get_executableName()))
			{
				logger << "There are one (or more) test(s) that has wrong execution name\n";
				return INVALID_EXECUTION_NAME;
			}
			if ((!(*iter)->get_expectedResult()))
			{
				logger << "There are one (or more) test(s) that has wrong result\n";
				return INVALID_RESULT;
			}
			else
			{
				char* res = (*iter)->get_expectedResult();
				for (int i = 0; i < strlen(res); ++i)
				{
					if (!isdigit(res[i]))
					{
						logger << "There are one (or more) test(s) that has wrong result (use decimal numbers only)\n";
						return WRONG_PARAMETERS;
					}
				}
			}
			if ((*iter)->getExecutablePath())
			{
				DWORD fFile = GetFileAttributesA((*iter)->getPathForExe());
				if (fFile == INVALID_FILE_ATTRIBUTES && (fFile == ERROR_FILE_NOT_FOUND))

				{
					logger << "There are one (or more) test(s) that has wrong path to exe file\n";
					return WRONG_PATH_EXECUTION;
				}
			}
			if ((*iter)->getRepeat())
			{
				char* res = (*iter)->getRepeat();
				for (int i = 0; i < strlen(res); ++i)
				{
					if (!isdigit(res[i]))
					{
						logger << "There are one (or more) test(s) that has wrong repeat (use decimal numbers only)\n";
						return WRONG_PARAMETERS;
					}
				}
			}
			if ((*iter)->getMaxThreads())
			{
				char* res = (*iter)->getMaxThreads();
				for (int i = 0; i < strlen(res); ++i)
				{
					if (!isdigit(res[i]))
					{
						logger << "There are one (or more) test(s) that has wrong maxThreads (use decimal numbers only)\n";
						return WRONG_PARAMETERS;
					}
				}
			}
			char* buf = new char[strlen((*it)->get_path()) + strlen((*iter)->get_executableName()) + 1];
			strncpy_s(buf, strlen((*it)->get_path()) + 1, (*it)->get_path(), strlen((*it)->get_path()));
			strncpy_s(buf + strlen((*it)->get_path()), strlen((*iter)->get_executableName()) + 1, (*iter)->get_executableName(), strlen((*iter)->get_executableName()));
			DWORD fFile = GetFileAttributesA(buf);
			if (fFile == INVALID_FILE_ATTRIBUTES && (fFile == ERROR_FILE_NOT_FOUND))
			{
				delete[] buf;
				logger << "There are no exe file for one or more test(s)\n";
				return INVALID_EXE_FILE;
			}
			else
			{
				delete[] buf;
				collTests.push_back((*iter));
			}
			if ((*iter)->getWaitFor())
			{
				coll.push_back((*iter)->getWaitFor());
			}
		}
		if (!VerifyWaitForList(collTests, coll))
		{
			logger << "There are tests that waiting for each other\n";
			return WRONG_WAITFOR;
		}
	}
	logger << "Verify Succeeded\n";
	return SUCCEEDED;
}


bool TRSManager::Pause(char* path, char* name, char* tag)
{
	logger->info("Entered Pause function with path: {}", path);
	if (name)
		logger->info("name: {} ", name);
	if (tag)
		logger->info("name: {} ", tag);

	if (!Verify(path, name, tag))
		return false;
	return false;
}

bool TRSManager::Stop(char* path, char* name, char* tag)
{
	logger->info("Entered Stop function with path: {}", path);
	if (name)
		logger->info("name: {} ", name);
	if (tag)
		logger->info("name: {} ", tag);

	if (!Verify(path, name, tag))
		return false;
	return false;
}

int TRSManager::FillList(char*path, char*name, char*tag, std::list<Suite*>*suiteCollection, std::vector<TRSTest*>testList)
{
	logger->info("Entered FillList function with path: {}", path);
	if (name)
		logger->info("name: {} ", name);
	if (tag)
		logger->info("name: {} ", tag);

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
						if (FillList(way, name, tag, suiteCollection, testList) != EXE_OR_XML_ABSENT)
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
							currentSuite->Parse(&doc, name, tag, testList);
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
										exeExist = true;
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
	logger->info("Entered List function with path: {}", path);
	if (name)
		logger->info("name: {} ", name);
	if (tag)
		logger->info("name: {} ", tag
		);

	if (!VerifyParameters(path, name, tag))
		return new std::list<Suite*>;

	std::list<Suite*>*suiteCollection = new std::list<Suite*>;
	std::vector<TRSTest*> testWait;
	if (FillList(path, name, tag, suiteCollection, testWait) != EXE_OR_XML_ABSENT)
	{
		std::list<Suite*>::iterator it = suiteCollection->begin();
		for (it; it != suiteCollection->end(); ++it)
		{
			std::list<TRSTest*>::iterator iter = (*it)->getList().begin();
			std::vector<char*> coll;
			std::vector<char*> collWait;
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
			for (int i = 0; i < testWait.size(); ++i)
			{
				if (testWait[i]->getWaitFor())
				{
					collWait.push_back(testWait[i]->getWaitFor());
				}
			}

			if (!VerifyWaitForList(testWait, collWait))
			{
				std::list<Suite*>::iterator it = suiteCollection->begin();
				for (it; it != suiteCollection->end(); ++it)
				{
					delete (*it);
				}
				suiteCollection->clear();
				return suiteCollection;
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
		logger->info("List returned nullptr");
		return new std::list<Suite*>;
	}
}

bool TRSManager::Status(char* path, char* name, char* tag)
{
	if (!Verify(path, name, tag))
		return false;
	return false;
}

bool TRSManager::Info(char* path, char* name, char* tag)
{
	if (!Verify(path, name, tag))
		return false;
	return false;
}

bool TRSManager::SetReport(char* path, char* name, char* tag, unsigned threads_amount, ReportManager* pReport)
{
	if (!Verify(path, name, tag))
		return false;

	Manager.Run(path, name, tag, threads_amount, pReport);
	return true;
}

