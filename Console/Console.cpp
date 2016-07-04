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
#include <list>

#define MAX_PARAMETERS 7


namespace spd = spdlog;


int ProcessFunction(char* name, char* tag, char* path)
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
		Manager.Run(path, name, tag);
		return 0;
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
		Manager.List(path, name, tag);
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
bool ParseArguments(char* &name, char* &tag, char* &path)
{
	name = tag = path = nullptr;

	// checking whether amount of parameters is correct
	if (__argc < 3 || __argc > MAX_PARAMETERS || __argc % 2 == 0)
	{
		logger<<"Incorrect amount of parameters";
		return false;
	}

	// checking if path parameter is valid
	path = __argv[2];

	DWORD dwAttrib = GetFileAttributesA(path);

	if (dwAttrib == INVALID_FILE_ATTRIBUTES || !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY))
	{
		logger<<"Specified path is not exist";
		return false;
	}

	// checking optional parameters
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
			logger<<"Incorrect order of parameters,  (-n or -t) was expected";
			return false;
		}
	}
	return true;
}


int main(int argc, char* argv[])
{
	
	Manager.Init();


	char *name, *path, *tag;
	name = tag = path = nullptr;

	if (!ParseArguments(name, tag, path))
	{
		return 1;

	}

	return ProcessFunction(name,tag,path);

}

