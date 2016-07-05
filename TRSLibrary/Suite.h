#ifndef SUITE_H_
#define SUITE_H_

#ifdef TRSLibrary_EXPORT
#define Suite_API  __declspec(dllexport) 
#else
#define Suite_API  __declspec(dllimport) 
#endif


#include "TRSInfo.h"
#include "TRSTest.h"
#include <list>
#include <istream>

class Suite_API Suite : public TRSInfo
{
	std::list<TRSTest> testList;
	char* directoryName = nullptr;
public:
	Suite(char*TestName,char*Description,char*DirName);
	~Suite();
	bool addTest(TRSTest&);
	bool removeTest(char*name);
	std::list<TRSTest>& getList();

	inline char* get_path()
	{
		return directoryName;
	}

	friend Suite_API std::ostream& operator<<(std::ostream &, Suite);
};
#endif