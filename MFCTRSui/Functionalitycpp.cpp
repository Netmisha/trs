#include "stdafx.h"
#include "Functionality.h"
#include <list>
#include "TRSLibrary\TRSManager.h"



void Info(char*path,CTreeCtrl m_Tree)
{
	std::list<Suite*>* suiteColl = Manager.List(path, nullptr, nullptr);
	if (suiteColl->size() > 0)
	{
		HTREEITEM hHead, hSuites, hTests;
		std::list<Suite*>::iterator it = suiteColl->begin();
		hHead = m_Tree.InsertItem(L"Suites", TVI_ROOT);
		for (it; it != suiteColl->end(); ++it)
		{
			TCHAR bufName[MAX_PATH];
			convertToTCHAR(bufName, (*it)->getName());
			hSuites = m_Tree.InsertItem(bufName, hHead);
			std::list<TRSTest*>::iterator iter = (*it)->getList().begin();
			for (iter; iter != (*it)->getList().end(); ++iter)
			{
				TCHAR testName[MAX_PATH];
				convertToTCHAR(testName, (*iter)->getName());
				hTests = m_Tree.InsertItem(testName, hSuites);
			}
		}
	}
}

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