#include "stdafx.h"
#define TRSManager_EXPORT
#include "TRSManager.h"

#include <iostream>

TRSManager Manager;

TRSManager::TRSManager()
{

}

TRSManager::~TRSManager()
{

}

bool TRSManager::Init()
{
	return false;
}

bool TRSManager::Verify(char* path, char* name, char* tag)
{
	return false;
}

bool TRSManager::Run(char* path, char* name, char* tag)
{
	return false;
}

bool TRSManager::Pause(char* path, char* name, char* tag)
{
	return false;
}

bool TRSManager::Stop(char* path, char* name, char* tag)
{
	return false;
}

bool TRSManager::List(char* path, char* name, char* tag)
{
	WIN32_FIND_DATA ffd;//variable that contains file info(if such is open with it)
	HANDLE hFind;
	TCHAR szDir[MAX_PATH];//buffer that holds file path
	TCHAR hzDir[MAX_PATH];//help buffer that holds root path

	StringCchCopy(szDir, MAX_PATH, (TCHAR*)path);//copy path from line to buffer for recursive use
	StringCchCopy(hzDir, MAX_PATH, (TCHAR*)path);//and to help buffer
	StringCchCat(szDir, MAX_PATH, TEXT("\\*"));//add end symbol to search in this directory

	hFind = FindFirstFile(szDir, &ffd);//open first Folder
	if (hFind == INVALID_HANDLE_VALUE)
	{
		std::cout << "FindFirstFile failed\n";
		return false;
	}
	else
	{
		do
		{
			if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)//check if it's a folder or not
			{
				_tprintf(TEXT("  %s   <DIR>\n"), ffd.cFileName);
				if (*ffd.cFileName != (WCHAR)'.')//not to enter '.' and '..' folders
				{
					TCHAR subDir[MAX_PATH];//create additional buffer for recursive traverse
					StringCchCopy(subDir, MAX_PATH, hzDir);//fill additional buffer with this folder's path
					StringCchCat(subDir, MAX_PATH, TEXT("\\"));//additional slash))
					StringCchCat(subDir, MAX_PATH, ffd.cFileName);//name of last folder to search in
					std::cout << "\n\t";
					List((char*)subDir,"","");//workin' only for path,not for names or tags yet
				}
			}
			else
			{
				_tprintf(TEXT("  %s   <FILE>\n"), ffd.cFileName);//write file name if it was found in current folder

			}
		} while (FindNextFile(hFind, &ffd) != 0);//repeat
	}
	return true;
}

bool TRSManager::Status(char* path, char* name, char* tag)
{
	return false;
}

bool TRSManager::Info(char* path, char* name, char* tag)
{
	return false;
}

bool TRSManager::Destroy(char* path, char* name, char* tag)
{
	return false;
}