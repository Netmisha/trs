// Console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "spdlog/spdlog.h"
#include "TRSLibrary\TRSManager.h"

#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <stdio.h>
#include <iostream>

#define MAX_PARAMETERS 7


namespace spd = spdlog;


typedef bool (TRSManager::*Routine)(char*, char*, char*);

// returned poiner to member function which was indicated at the command line
// Otherwise - return nullptr
Routine ParseFunction()
{
	if (__argc < 2)
		return nullptr;

	if (!_stricmp(__argv[1], "Verify"))
		return &TRSManager::Verify;

	else if (!_stricmp(__argv[1], "Run"))
		return &TRSManager::Run;

	else if (!_stricmp(__argv[1], "Pause"))
		return &TRSManager::Pause;

	else if (!_stricmp(__argv[1], "Stop"))
		return &TRSManager::Stop;

	else if (!_stricmp(__argv[1], "List"))
		return &TRSManager::List;

	else if (!_stricmp(__argv[1], "Status"))
		return &TRSManager::Status;

	else if (!_stricmp(__argv[1], "Info"))
		return &TRSManager::Info;

	else
	{
		logger<<"Incorrect function name";
		return nullptr;
	}
}

// taking references to pointer and assign them to appropriate console paramer
// or to nullptr otherwise
// returning pointer to member function if it was specified correctly
// or nullptr othewise
Routine ParseArguments(char* &name, char* &tag, char* &path)
{
	name = tag = path = nullptr;

	// check whether user input neccessary information ( path and function) &&
	// it is not overflow maximum parameter's amount && 
	// that amount of parameters is even ( each parameters specifier must be followed by string
	// except for firs two parameters which is .exe name and function name )
	//	cout << ____argc << endl;
	if (__argc < 3 || __argc > MAX_PARAMETERS || __argc % 2 == 0)
	{
		logger<<"Incorrect amount of parameters";
		return nullptr;
	}

	// checking path parameter
	path = __argv[2];

	DWORD dwAttrib = GetFileAttributesA(path);

	if (dwAttrib == INVALID_FILE_ATTRIBUTES || !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY))
	{
		logger<<"Specified path is not exist";
		return nullptr;
	}

	for (int i = 3; i < __argc; i += 2)
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
		else
		{
			// this mean that there was not a identifier at the place
			// where it was expected to be
			logger<<"Incorrect order of parameters, [-p, -n, -t] was expected";
			return nullptr;
		}
	}

	// checking whether necessary argument "path" was indicated
	if (path == nullptr)
	{
		logger<<"Necessary path (-p) parameter was not specified";
		return nullptr;
	}
	return ParseFunction();
}


int main(int argc, char* argv[])
{
	logger.Init();
	char *name, *path, *tag;
	name = path = tag = nullptr;
	Routine parsed_func = ParseArguments(name, tag, path);


	if (parsed_func == nullptr)
	{
		return 1;
	}
	else
	{
		(Manager.*parsed_func)(path, name, tag);
	}

	return 0;
}

