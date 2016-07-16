// Console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "spdlog/spdlog.h"
#include "TRSLibrary\TRSManager.h"
#include "TRSLibrary\Suite.h"
#include "TRSLibrary\TinyXML\tinyxml.h"
#include "ConsoleReport.h"
#include "TRSLibrary\ReportManager.h"
#include "HTMLReport.h"
#include "TRSLibrary\Erorrs.h"
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <list>

#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#define MAX_PARAMETERS 9
#define MIN_PARAMERES 2


namespace spd = spdlog;
using std::cout;

int ProcessFunction(char* name, char* tag, char* path, int threads)
{
	if (__argc < 2)
		return 1;

	if (!_stricmp(__argv[1], "Verify"))
	{
		int result=Manager.Verify(path, name, tag);
		switch (result)
		{
		case DEAD_LOCK_OR_FILES_ABSENT_WAS_FOUND:
			std::cout << "There are tests that waiting for each other or some xml or exe files are absent\n";
			break;
		case INVALID_NAME:
			std::cout << "There are one(or more) test(s) without name\n";
			break;
		case INVALID_EXECUTION_NAME:
			std::cout << "There are one (or more) test(s) that has wrong execution name\n";
			break;
		case INVALID_RESULT:
			std::cout << "There are one (or more) test(s) that has wrong parameters\n";
			break;
		case WRONG_PATH_EXECUTION:
			std::cout << "There are one (or more) test(s) that has wrong path to exe file\n";
			break;
		case INVALID_EXE_FILE:
			std::cout << "There are no exe file for one or more test(s)\n";
			break;
		case WRONG_WAITFOR:
			std::cout << "There are tests that waiting for each other\n";
			break;
		default :
			std::cout << "Succeeded\n";
			break;
		}
		return 0;
	}
	else if (!_stricmp(__argv[1], "Run"))
	{

		ReportManager reportManager;
		ConsoleReport cReport;
		HTMLReport htmlReport;

		reportManager.addReporter(&cReport);
		reportManager.addReporter(&htmlReport);
		reportManager.Begin();

		bool result = Manager.Run(path, name, tag, threads, &reportManager);
		
		reportManager.End();
		return result;
	}
	else if (!_stricmp(__argv[1], "Pause"))
	{
		Manager.Pause(path, name, tag);
		return 0;
	}
	else if (!_stricmp(__argv[1], "Stop"))
	{
		Manager.Stop(path, name, tag);
		return 0;
	}

	else if (!_stricmp(__argv[1], "List"))
	{
		std::list<Suite*>* list = Manager.List(path, name, tag);
		if (list->size() > 0)
		{
			for each (auto x in *list)
				std::cout << *x << std::endl;
			std::list<Suite*>::iterator it = list->begin();
			for (it; it != list->end(); ++it)
			{
				delete (*it);
			}
		}
		else
		{
			std::cout << "List is empty!\n";
		}
		delete list;
		
		return 0;
	}

	else if (!_stricmp(__argv[1], "Status"))
	{
		Manager.Status(path, name, tag);
		return 0;
	}

	else if (!_stricmp(__argv[1], "Info"))
	{
		Manager.Info(path, name, tag);
		return 0;
	}

	else
	{
		logger<<"Incorrect function name";
		return 1;
	}
	
}

// taking references to pointer and assign them to appropriate console parameter
bool ParseArguments(_Outptr_ char* &name, _Outptr_ char* &tag, _Outptr_ char* &path, _Outptr_ int & threads)
{
	name = tag = path = nullptr;
	threads = 1;
	// checking whether amount of parameters is correct
	if (__argc < MIN_PARAMERES || __argc > MAX_PARAMETERS || __argc % 2 != 0)
	{
		logger<<"Incorrect amount of parameters";
		return false;
	}

	// checking  parameters
	for (int i = 2; i < __argc; i += 2)
	{
		if (_stricmp(__argv[i], "-n") == 0)
		{
			name = __argv[i + 1];
			continue;
		}
		else if (_stricmp(__argv[i], "-t") == 0)
		{
			tag = __argv[i + 1];
			continue;
		}
		else if (_stricmp(__argv[i], "-j") == 0)
		{
			threads = atoi(__argv[i + 1]);
			if (threads <= 0)
				logger << "Amount of threads must be a positive integer!";
			continue;
		}
		else if (_stricmp(__argv[i], "-p") == 0)
		{
			path = __argv[i + 1];
			continue;
		}
		else
		{
			// this mean that there was not a identifier at the place
			// where it was expected to be
			logger<<"Incorrect order of parameters,  (-n or -t) was expected";
			return false;
		}
	}

	if ( !path )
	{
		path = new char[MAX_PATH + 1];
		GetCurrentDirectoryA(MAX_PATH + 1, path);
	}
	//else if (path && strlen(path) > 1 && path[0] == '.' )
	//{
	//	char* coll = new char[MAX_PATH + 1];
	//	GetCurrentDirectoryA(MAX_PATH + 1, coll);
	//	int len = strlen(coll);
	//	coll[len] = '\\';
	//	coll[len + 1] = 0;
	//	strcat_s(coll, MAX_PATH + 1, path);
	//	path = coll;
	//}
	else
	{
		char* coll = new char[MAX_PATH + 1];
		strcpy_s(coll, MAX_PATH + 1, path);
		path = coll;
	}
	DWORD dwAttrib = GetFileAttributesA(path);

	if (dwAttrib == INVALID_FILE_ATTRIBUTES || !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY))
	{
		logger << "Specified path is not exist";
		return false;
	}
		

	return true;
}


int main(int argc, char* argv[])
{

	Manager.Init();

	char *name, *path, *tag;
	int threads;

	if (!ParseArguments(name, tag, path, threads))
	{
		Manager.Destroy();
		return 1;
	}
	int ret_val = ProcessFunction(name, tag, path, threads);

	Manager.Destroy();
	delete[] path;
	_CrtDumpMemoryLeaks();
	return ret_val;
}

