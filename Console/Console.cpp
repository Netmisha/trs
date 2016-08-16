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
#include "TRSLibrary\Errors.h"
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

int ProcessFunction(char* name, char* tag, char* path, int threads,char* hlogPath)
{
	if (__argc < 2)
		return 1;

	if (!_stricmp(__argv[1], "Verify"))
	{
		Manager.Verify(path, name, tag);
		return 0;
	}
	else if (!_stricmp(__argv[1], "Run"))
	{

		ReportManager reportManager;
		ConsoleReport cReport;
		HTMLReport htmlReport(hlogPath);

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
		Manager.Stop();
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
		logger << "Incorrect function name";
		return 1;
	}

}

// taking references to pointer and assign them to appropriate console parameter
bool ParseArguments(_Outptr_ char* &name, _Outptr_ char* &tag, _Outptr_ char* &path, _Outptr_ int & threads, _Outptr_ char* &logPath, _Outptr_ char* &hlogPath)
{
	name = tag = path = logPath=hlogPath=nullptr;
	threads = -1;
	// checking whether amount of parameters is correct
	if (__argc < MIN_PARAMERES || __argc > MAX_PARAMETERS || __argc % 2 != 0)
	{
		logger << "Incorrect amount of parameters";
		return false;
	}

	// checking  parameters
	for (int i = 2; i < __argc; i += 2)
	{
		if (_stricmp(__argv[i], "-n") == 0)
		{
			if (name)
			{
				logger << "Ambiguous indication of name parameter";
				return false;
			}
			name = __argv[i + 1];
			continue;
		}
		else if (_stricmp(__argv[i], "-t") == 0)
		{
			if (tag)
			{
				logger << "Ambiguous indication of tag parameter";
				return false;
			}
			tag = __argv[i + 1];
			continue;
		}
		else if (_stricmp(__argv[i], "-j") == 0)
		{
			if (threads != -1)
			{
				logger << "Ambiguous indication of threads parameter";
				return false;
			}
			threads = atoi(__argv[i + 1]);

			if (threads <= 0)
			{
				logger << "Amount of threads must be a positive integer!";
				return false;
			}

			continue;
		}
		else if (_stricmp(__argv[i], "-p") == 0)
		{
			if (path)
			{
				logger << "Ambiguous indication of path parameter";
				return false;
			}
			path = __argv[i + 1];
			continue;
		}
		else if (_stricmp(__argv[i], "-log") == 0)
		{
			if (logPath)
			{
				logger << "Ambiguous indication of log path parameter";
				return false;
			}
			logPath = __argv[i + 1];
			continue;
		}
		else if (_stricmp(__argv[i], "-hlog") == 0)
		{
			if (hlogPath)
			{
				logger << "Ambiguous indication of log path parameter";
				return false;
			}
			hlogPath = __argv[i + 1];
			continue;
		}
		else
		{
			// this mean that there was not a identifier at the place
			// where it was expected to be
			logger << "Incorrect order of parameters,  (-n or -t) was expected";
			return false;
		}
	}

	if (!path)
	{
		path = new char[MAX_PATH + 1];
		GetCurrentDirectoryA(MAX_PATH + 1, path);
	}
	else if (path && strlen(path) >= 1 && path[0] == '.')
	{
		char* coll = new char[MAX_PATH + 1];
		GetCurrentDirectoryA(MAX_PATH + 1, coll);
		int len = strlen(coll);
		coll[len] = '\\';
		coll[len + 1] = 0;
		strcat_s(coll, MAX_PATH + 1, path);
		path = coll;
	}
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

	if (threads == -1)
		threads = 1;
	return true;
}


int main(int argc, char* argv[])
{
	char *name, *path, *tag,*logOut,*hlogOut;
	logOut = nullptr;
	int threads;
	Manager.Init(logOut);
	if (!ParseArguments(name, tag, path, threads,logOut,hlogOut))
	{
		return 1;
	}
	Manager.Destroy();
	Manager.Init(logOut);
	int ret_val = ProcessFunction(name, tag, path, threads,hlogOut);

	Manager.Destroy();
	delete[] path;
	_CrtDumpMemoryLeaks();
	return ret_val;
}

