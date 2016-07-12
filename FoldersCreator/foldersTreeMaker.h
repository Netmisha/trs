#ifndef FOLDERSTREEMAKER_HEADER
#define FOLDERSTREEMAKER_HEADER

#ifdef FolderCreator_EXPORT
#define FolderTreeMaker_API __declspec(dllexport) 
#else
#define FolderTreeMaker_API __declspec(dllimport) 
#endif

#include "TinyXML\tinyxml.h"
#include "XmlCreator.h"
#include <Windows.h>
#include "Converters.h"
#include <iostream>
#include <fstream>

class FolderTreeMaker_API FoldersTreeMaker
{
public:
	FoldersTreeMaker(char* input_path, char* output_path);
	FoldersTreeMaker();
	~FoldersTreeMaker();
	bool MakeTree();
	bool setInputPath(char* path);
	bool setOutputPath(char* path);
	char* getInputPath();
	char* getOutputPath();
private:
	bool RecourseParse(char* path, TiXmlNode* pParent);
	bool CreateExe(char*path,Suite*suite);
private:
	char* input_path;
	char* output_path;
	int mTestCount;
	XmlCreator currentCreator;
};

extern FolderTreeMaker_API FoldersTreeMaker maker;
#endif