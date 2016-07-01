#ifndef TRSManager_HEADER
#define TRSManager_HEADER

#ifdef TRSManager_EXPORT
#define TRSManager_API  __declspec(dllexport) 
#else
#define TRSManager_API  __declspec(dllimport) 
#endif


TRSManager_API int func();

#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <iostream>
#include <strsafe.h>

class TRSManager_API TRSManager
{
public:
	TRSManager();
	~TRSManager();

	bool Init();
	bool Verify(char* path, char* name, char* tag);
	bool Run(char* path, char* name, char* tag);
	bool Pause(char* path, char* name, char* tag);
	bool Stop(char* path, char* name, char* tag);
	bool List(char* path, char* name, char* tag);
	bool Status(char* path, char* name, char* tag);
	bool Info(char* path, char* name, char* tag);
	bool Destroy(char* path, char* name, char* tag);
};

extern TRSManager_API TRSManager Manager;

#endif