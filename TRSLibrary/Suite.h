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
	std::list<TRSTest*> testList;
	char* directoryName = nullptr;
	bool ParseSuit(TiXmlNode* pParent,char* name_,char* tag_);
public:
	Suite(char*TestName,char*Description,char*DirName);
	Suite();
	~Suite();
	bool addTest(TRSTest&);
	bool removeTest(char*name);


	inline char* get_path()
	{
		return directoryName;
	}

	std::list<TRSTest*>& getList();
	bool Parse(TiXmlNode*pParent,char*name_,char*tag_);
	bool setDir(char*dir_);
	bool setList(std::list<TRSTest*>& testList_);

	friend Suite_API std::ostream& operator<<(std::ostream &, Suite);
};
#endif