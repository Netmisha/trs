#include "Metadata.h"

class TRSInfo
{
	char* testName;
	char* description;
	char* tag=nullptr;
	char* repeat=nullptr;
	char* maxTime=nullptr;
	char* maxThreads=nullptr;
	Metadata meta;
public:
	TRSInfo(char*Name, char*Description,char*metaName);
	~TRSInfo();
	bool setTag(char*tag_);
	bool setRepeat(char*repeat_);
	bool setMaxTime(char*maxTime_);
	bool setMaxThreads(char*maxThreads_);
	char* getTag();
	char* getRepeat();
	char* getMaxTime();
	char* getMaxThreads();
};