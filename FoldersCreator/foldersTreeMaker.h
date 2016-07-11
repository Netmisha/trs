#ifndef FOLDERSTREEMAKER_H_
#define FOLDERSTREEMAKER_H_

#include "TinyXML\tinyxml.h"
#include "XmlCreator.h"

class FoldersTreeMaker
{
public:
	FoldersTreeMaker(char* input_path, char* output_path);
	~FoldersTreeMaker();
	bool MakeTree();
private:
	char* input_path;
	char* output_path;
	XmlCreator currentCreator;
};

#endif