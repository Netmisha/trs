#ifndef PROJECTPROPERTIES_H_
#define PROJECTPROPERTIES_H_
#include "stdafx.h"
#include "TRSLibrary\TinyXML\tinyxml.h"
#include <vector>
#include "Functionality.h"
class ProjectProperties
{
	char* path;
	char* name;
public:
	ProjectProperties(char* path, char* name);
	ProjectProperties();
	~ProjectProperties();
	ProjectProperties& operator=(ProjectProperties& pro);

	bool setPath(const char* path);
	bool setName(const char* name);
	char* getProjPath();
	bool SaveProject(CListBox*List);
	char* getPath();
	char* getName();
};

#endif