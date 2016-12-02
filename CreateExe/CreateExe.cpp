// CreateExe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include "Converters.h"


int _tmain(int argc, _TCHAR* argv[])
{
	if (argc == 3)
	{
		if (atoi(convertToChar(argv[1])))
		{
			for (int i = 0; i < atoi(convertToChar(argv[1])); ++i)
			{
				Sleep(1000);
			}
		}
		else
		{
			return 0;
		}
		return atoi(convertToChar(argv[2]));
	}
	return 0;
}

