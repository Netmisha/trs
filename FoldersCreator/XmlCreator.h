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
	~XmlCreator();
	bool CreateXML();
private:
	char* path;
	Suite* currentSuite;
};

#endif