#include "stdafx.h"

#include "foldersTreeMaker.h"

FoldersTreeMaker::FoldersTreeMaker(char* input_path_, char* output_path_)
{
	input_path = input_path_;
	output_path = output_path_;
}

FoldersTreeMaker::~FoldersTreeMaker()
{
	delete[] input_path;
	delete[] output_path;
}

bool FoldersTreeMaker::RecourseParse(char* path, TiXmlNode* pParent)
{
	return true;
}

bool FoldersTreeMaker::MakeTree()
{
	TiXmlDocument doc(input_path);
	if (doc.LoadFile())
	{
		return RecourseParse(output_path, &doc);
	}
	else
	{
		return false;
	}
}