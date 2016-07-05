#include "stdafx.h"
#include "FunctionalityForXML.h"

bool Validate(std::wstring& name)//just check ;last 3 letters
{
	if (name[name.length() - 1] == 'l')
	{
		if (name[name.length() - 2] == 'm')
		{
			if (name[name.length() - 3] == 'x')
			{
				if (name[name.length() - 4] == '.')
				{
					return true;
				}
			}
		}
	}
	return false;
}


char* convertToChar( TCHAR*path)//create buffer to set info to tinyXML doc constructor
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

void convertToTCHAR(TCHAR*dest,char* path)
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

