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
		spd::get("logger")->info("Incorrect function name");
		return nullptr;
	}
}

// taking references to pointer and assign them to appropriate console paramer
// or to nullptr otherwise
// returning pointer to member function if it was specified correctly
// or nullptr othewise
Routine ParseArguments(char* &name, char* &tag, char* &path)
{
	auto logger = spd::get("logger");
	name = tag = path = nullptr;

	// check whether user input neccessary information ( path and function) &&
	// it is not overflow maximum parameter's amount && 
	// that amount of parameters is even ( each parameters specifier must be followed by string
	// except for firs two parameters which is .exe name and function name )
	//	cout << ____argc << endl;
	if (__argc < 4 || __argc > MAX_PARAMETERS || __argc % 2 == 1)
	{
		logger->info("Incorrect amount of parameters");
		return nullptr;
	}
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
			logger->info("Incorrect order of parameters, [-p, -n, -t] was expected");
			return nullptr;
		}
	}

	// checking whether necessary argument "path" was indicated
	if (path == nullptr)
	{
		logger->info("Necessary path (-p) parameter was not specified");
		return nullptr;
	}
	return ParseFunction();
}

#include <vector>

int main(int argc, char* argv[])
{
	char *name, *path, *tag;
	name = path = tag = nullptr;
	Routine parsed_func = nullptr;

	// This code will be hide inside TRSManager constructor as soon as I will have access to my working place
	// **************************************************************************************************
	try
	{
		std::vector<spd::sink_ptr> sinks;
		sinks.push_back(std::make_shared<spd::sinks::simple_file_sink_mt>("../Console/Logs/logs.txt"));
		sinks.push_back(std::make_shared<spd::sinks::stderr_sink_mt>());

		auto logger = std::make_shared<spd::logger>("logger", begin(sinks), end(sinks));
		//register it if you need to access it globally
		spdlog::register_logger(logger);

		parsed_func = ParseArguments(name, tag, path);
	}
	catch (const spd::spdlog_ex& ex)
	{
		std::cout << "Log failed: " << ex.what() << std::endl;
	}

	// **************************************************************************************************
	if (parsed_func == nullptr)
	{
		return 1;
	}
	else
	{
		(Manager.*parsed_func)(path, name, tag);
	}

	spdlog::drop_all();
	return 0;
}

