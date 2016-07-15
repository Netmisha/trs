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
	char* priority = nullptr;
	char* disable = nullptr;
	char* parameters = nullptr;
	char* executablePath = nullptr;
	char* path = nullptr;
	Metadata* metadata;
	
public:
	TRSInfo(char*Name, char*Description);
	TRSInfo(const TRSInfo& val);
	TRSInfo();
	virtual ~TRSInfo();
	bool setDisable(char* disable_);
	bool setTag(char*tag_);
	bool setRepeat(char*repeat_);
	bool setMaxTime(char*maxTime_);
	bool setMaxThreads(char*maxThreads_);
	bool setExecutableName(char* name_);
	bool setExecutablePath(char* exeName);
	bool setName(char*Name_);
	bool setDescription(char*Desc_);
	bool setMetadata(Metadata* metadata_);
	bool setExpectedResult(char* res_);
	bool setWaitFor(char* wait_);
	bool setPriority(char* prior_);
	bool setPath(char* path);
	bool setParameters(char*parameters_);
	inline char* get_executableName() const
	{
		return executableName;
	}
	inline char* get_expectedResult() const
	{
		return expectedResult;
	}
	char* getParameters() const;
	char* getExecutablePath() const;
	char* getPath() const;
	char* getWaitFor() const;
	char* getName() const;
	char* getDescription() const;
	char* getTag() const;
	char* getRepeat() const;
	char* getMaxTime() const;
	char* getMaxThreads() const;
	char* getPriority() const;
	char* getDisable() const;
	Metadata* getMetadata() const;

	bool Parse(TiXmlNode* pParent);
};
#endif