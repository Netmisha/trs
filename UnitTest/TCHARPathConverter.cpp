#include "stdafx.h"
#include "TCHARPathConverter.h"

char*  convertToChar(TCHAR*path)//create buffer to set info to tinyXML doc constructor
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

void  convertToTCHAR(TCHAR*dest, char* path)
{
	if (dest != nullptr)
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

TCHAR* convertPath(TCHAR*inPath)
{
	if (inPath)
	{
		char* len = convertToChar(inPath);
		TCHAR* result = new TCHAR[strlen(len) + 1];
		delete[] len;
		TCHAR help = inPath[0];
		int i = 0;
		while (help)
		{
			if (help == '\\')
			{
				result[i]=0[R"(\)"];
			}
			else
			{
				result[i] = help;
			}
			++i;
			help = inPath[i];
		}
		return result;
	}
	return nullptr;
}