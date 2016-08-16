#ifndef TRSManager_HEADER
#define TRSManager_HEADER

#ifdef TRSLibrary_EXPORT
#define TRSManager_API  __declspec(dllexport) 
#else
#define TRSManager_API  __declspec(dllimport) 
#endif

#include "Suite.h"
#include "TRSResult.h"
#include "spdlog\spdlog.h"
#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <iostream>
#include <strsafe.h>
#include <memory>
#include "Suite.h"
#include <list>
#include <vector>
#include <fstream>
#include "TRSReport.h"
#include "ReportManager.h"
#include <cctype>

#define BUF_SIZE 512
#define MAX_THREADS 128

class TRSManager_API TRSManager
{
	int FillList(char*path, char*name, char*tag, std::list<Suite*>*curList,std::vector<TRSTest*>testList);
public:
	TRSManager();
	~TRSManager();

	bool Init(char* lPath);
	int Verify(char* path, char* name, char* tag);
	bool Run(char* path, char* name, char* tag, unsigned threads_amount = 10, ReportManager* pReport=nullptr);
	bool Pause(char* path, char* name, char* tag);
	bool Stop(/*char* path, char* name, char* tag*/);
	std::list<Suite*>* List(char* path, char* name, char* tag);
	bool Status(char* path, char* name, char* tag);
	bool Info(char* path, char* name, char* tag);
	bool Destroy();
	bool SetReport(char* path,char* name,char* tag, unsigned threads_amount = 10, ReportManager* manager=nullptr);
private:
	bool VerifyParameters(char* path, char* name, char* tag);
	bool running_ = true;
	
};

class TRSManager_API Logger
{
public:
	bool Init(char*path);
	void Destroy();

	void operator<<(char* message);
	std::shared_ptr<spdlog::logger> operator->()
	{
		return text_log_;
	}
private:
	std::shared_ptr<spdlog::logger> text_log_;
	std::shared_ptr<spdlog::logger> console_log_;
};

extern TRSManager_API Logger logger;

extern TRSManager_API TRSManager Manager;

#endif