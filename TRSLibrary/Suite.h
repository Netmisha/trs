#ifndef SUITE_H_
#define SUITE_H_

#include "TRSInfo.h"
#include "TRSTest.h"
#include <list>
#include <istream>



#ifdef TRSLibrary_EXPORT
#define Suite_API  __declspec(dllexport) 
#else
#define Suite_API  __declspec(dllimport) 
#endif


class Suite_API Suite : public TRSInfo
{
	std::list<TRSTest*> testList;
	char* directoryName = nullptr;
	bool ParseSuit(TiXmlNode* pParent);
public:
	Suite(char*TestName,char*Description,char*DirName);
	Suite();
	~Suite();
	bool addTest(TRSTest&);
	bool removeTest(char*name);
	std::list<TRSTest*>& getList();
	bool Parse(TiXmlNode*pParent);
	bool setDir(char*dir_);
	bool setList(std::list<TRSTest*>& testList_);
	friend Suite_API std::ostream& operator<<(std::ostream &, Suite);
};
#endif