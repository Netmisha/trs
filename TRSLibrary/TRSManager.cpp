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
	return false;
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