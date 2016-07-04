#include <string>

class Metadata
{
	char* autorName;
	char* date;
	char* version;
	char* mail;
	char* copyright;
	char* license;
	char* info;
public:
	Metadata(char*Name);
	~Metadata();
};