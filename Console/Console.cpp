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

#define MAX_PARAMETERS 8


namespace spd = spdlog;


typedef bool (TRSManager::*Func)(char*, char*, char*);

// returned poiner to member function which was indicated at the command line
// Otherwise - return nullptr
Func ParseFunction()
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
		return nullptr;
}

// taking references to pointer and assign them to appropriate console paramer
// or to nullptr otherwise
bool ParseArguments(char* &name, char* &tag, char* &path)
{
	name = tag = path = nullptr;

	// check whether user input neccessary information ( path and function) &&
	// it is not overflow maximum parameter's amount && 
	// that amount of parameters is even ( each parameters specifyer must be followed by string
	// except for firs two parameters which is .exe name and function name )
	//	cout << ____argc << endl;
	if (__argc < 4 || __argc > MAX_PARAMETERS || __argc % 2 == 1)
		return false;

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
		else if (_stricmp(__argv[i], "-p") == 0)
		{
			path = __argv[i + 1];
		}
		else
		{
			// this mean that there was not a identifier at the place
			// where it was expected to be
			return false;
		}
	}

	// checking whether neccessary argument "path" was indicated
	return path != nullptr;
}

int main(int argc, char* argv[])
{
	char *name, *path, *tag;
	name = path = tag = nullptr;
	if (!ParseArguments(name, tag, path))
		return 1;

	Func parsed_func = ParseFunction();
	if (parsed_func == nullptr)
		return 1;
	else
		(Manager.*parsed_func)(path, name, tag);

	return 0;
}

