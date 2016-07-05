#ifndef METADATA_H_
#define METADATA_H_
#include <string>

class Metadata
{
	char* autorName=nullptr;
	char* date=nullptr;
	char* version=nullptr;
	char* mail=nullptr;
	char* copyright=nullptr;
	char* license=nullptr;
	char* info=nullptr;
public:
	Metadata(char*Name);
	Metadata();
	~Metadata();
	bool setDate(char*date_);
	bool setVersion(char*version_);
	bool setMail(char*mail_);
	bool setCopyright(char*copyright_);
	bool setLicense(char*license_);
	bool setInfo(char*info_);
	bool setName(char*name_);
	char* getDate();
	char* getVersion();
	char* getMail();
	char* getCopyright();
	char* getLicense();
	char* getInfo();
};
#endif