#ifndef XMLCREATOR_H_
#define XMLCREATOR_H_

#include "TinyXML\tinyxml.h"
#include "Suite.h"
#include "TRSInfo.h"
#define NAME_LENGTH 11

class XmlCreator
{
public:
	XmlCreator(char* path, Suite* currentSuite);
	XmlCreator();
	~XmlCreator();
	bool CreateXML();
	bool setPath(char* path);
	bool setSuite(Suite* suite);
	char* getPath() const;
	Suite* getSuite();
private:
	char* path;
	Suite* currentSuite;
};

#endif