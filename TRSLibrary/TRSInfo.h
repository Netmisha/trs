#include "Metadata.h"

class TRSInfo
{
	char* testName;
	char* description;
	char* tag;
	char* repeat;
	char* maxTime;
	char* maxThreads;
	Metadata meta;
public:
	TRSInfo(char*, char*, char*, char*, char*, char*, char*  );
};