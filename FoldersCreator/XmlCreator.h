#ifndef XMLCREATOR_H_
#define XMLCREATOR_H_

#ifdef FolderCreator_EXPORT
#define XmlCreator_API __declspec(dllexport) 
#else
#define XmlCreator_API __declspec(dllimport) 
#endif

#include "TinyXML\tinyxml.h"
#include "TRSLibrary\Suite.h"
#define FILE_EXPANSION 6

class XmlCreator_API XmlCreator
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
	char* path=nullptr;
	Suite* currentSuite=nullptr;
};

#endif