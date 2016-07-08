#ifndef TRSINFO_H_
#define TRSINFO_H_

#ifdef TRSLibrary_EXPORT
#define TRSInfo_API  __declspec(dllexport) 
#else
#define TRSInfo_API  __declspec(dllimport) 
#endif

#include "Metadata.h"

#include "TinyXML\tinyxml.h"



class TRSInfo_API TRSInfo
{
	char* Name=nullptr;
	char* description=nullptr;
	char* tag=nullptr;
	char* repeat=nullptr;
	char* maxTime=nullptr;
	char* maxThreads=nullptr;
	char* expectedResult=nullptr;
	char* executableName=nullptr;
	char* waitfor = nullptr;
	Metadata* metadata;

public:
	TRSInfo(char*Name, char*Description);
	TRSInfo(const TRSInfo&);
	TRSInfo();
	virtual ~TRSInfo();

	bool setTag(char*tag_);
	bool setRepeat(char*repeat_);
	bool setMaxTime(char*maxTime_);
	bool setMaxThreads(char*maxThreads_);
	bool setExecutableName(char* name_);
	bool setName(char*Name_);
	bool setDescription(char*Desc_);
	bool setMetadata(Metadata* metadata_);
	bool setExpectedResult(char* res_);
	bool setWaitFor(char* wait_);


	inline char* get_executableName() const
	{
		return executableName;
	}
	inline char* get_expectedResult() const
	{
		return expectedResult;
	}
	char* getWaitFor() const;
	char* getName() const;
	char* getDescription() const;
	char* getTag() const;
	char* getRepeat() const;
	char* getMaxTime() const;
	char* getMaxThreads() const;
	Metadata* getMetadata() const;

	bool Parse(TiXmlNode* pParent);
};
#endif