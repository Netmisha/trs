// FoldersCreator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define FoldersCreator_EXPORT
#include "foldersTreeMaker.h"

int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << "Process started!\n";

	if (argc == 3)
	{
		std::cout << "Good parameters\n";

		FoldersTreeMaker maker(convertToChar(argv[1]), convertToChar(argv[2]));
		if (maker.MakeTree())
		{
			return 1;
		}
	}
	else
	{
		return 0;
	}
}

