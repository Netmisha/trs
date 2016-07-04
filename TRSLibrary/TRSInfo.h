#ifndef TRSINFO_H_
#define TRSINFO_H_
#include "Metadata.h"
#include "TinyXML\tinyxml.h"
class TRSInfo
{
	char* Name;
	char* description;
	char* tag=nullptr;
	char* repeat=nullptr;
	char* maxTime=nullptr;
	char* maxThreads=nullptr;
	
	Metadata* metadata;
public:
	TRSInfo(char*Name, char*Description);
	~TRSInfo();
	bool setTag(char*tag_);
	bool setRepeat(char*repeat_);
	bool setMaxTime(char*maxTime_);
	bool setMaxThreads(char*maxThreads_);
	char* getName();
	char* getDescription();
	char* getTag();
	char* getRepeat();
	char* getMaxTime();
	char* getMaxThreads();
	bool Parse(TiXmlDocument& doc);
};
#endif