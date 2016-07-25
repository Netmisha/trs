#include "stdafx.h"
#include "Functionality.h"
#include <list>

#include "TRSLibrary\TRSManager.h"




void convertToTCHAR(TCHAR*dest, char* path)
{
	if (dest != nullptr && path != nullptr)
	{
		TCHAR help = path[0];
		int i = 0;
		while (help)
		{
			dest[i] = help;
			++i;
			help = path[i];
		}
		dest[i] = '\0';
	}
}

char* convertToChar(TCHAR*path)//create buffer to set info to tinyXML doc constructor
{
	char* buf = new char[MAX_PATH];
	char help = path[0];
	int i = 0;
	while (help)//i tried to use memcpy,but it didn't work so i used while=(
	{
		buf[i] = help;
		++i;
		help = path[i];
	}
	buf[i] = '\0';
	return buf;
}

char* fromCStringToChar(CString string)
{
	char* buf = new char[string.GetLength()+1];
	char help = string[0];
	int i = 0;
	while (help)//i tried to use memcpy,but it didn't work so i used while=(
	{
		buf[i] = help;
		++i;
		help = string[i];
	}
	buf[i] = '\0';
	return buf;
}

bool ValidateProjXML(char* path)
{
	return false;
}