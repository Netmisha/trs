#include "stdafx.h"
#define FolderCreator_EXPORT
#include "foldersTreeMaker.h"

FoldersTreeMaker::FoldersTreeMaker(char* input_path_, char* output_path_)
{
	input_path = input_path_;
	output_path = output_path_;
}

FoldersTreeMaker::~FoldersTreeMaker()
{
	
}

bool FoldersTreeMaker::RecourseParse(char* path, TiXmlNode* pParent)
{
	Suite* currentSuite = new Suite();
	currentSuite->Parse(pParent, nullptr, nullptr);
	currentSuite->setDir(path);
	char* fullName = new char[strlen(path) + strlen(currentSuite->getName()) + 2];
	strncpy_s(fullName, strlen(path) + 1, path, strlen(path));
	strncpy_s(fullName + strlen(path), 2, "\\", 1);
	strncpy_s(fullName + strlen(path)+1, strlen(currentSuite->getName()) + 1, currentSuite->getName(), strlen(currentSuite->getName()));
	TCHAR* buffer = new TCHAR[strlen(path) + strlen(currentSuite->getName()) + 1];
	convertToTCHAR(buffer, fullName);
	currentCreator.setPath(fullName);
	currentCreator.setSuite(currentSuite);
	CreateDirectory(buffer, NULL);
	currentCreator.CreateXML();
	CreateExe(fullName, currentSuite);
	delete[] fullName;
	bool check = false;
	TiXmlNode* pChild=pParent;
	for (pChild=pChild->FirstChild() ; pChild != 0; pChild = pChild->NextSibling())
	{
		if ((pChild->Type() == TiXmlNode::TINYXML_ELEMENT) && (strncmp(pChild->Value(), "suite", strlen("suite")) == 0))
		{
			if (check)
			{
				RecourseParse(convertToChar(buffer), pChild);
			}
			check = true;
			pChild = pChild->FirstChild();
		}
	}
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

bool FoldersTreeMaker::setInputPath(char*path)
{
	if (path)
	{
		input_path = path;
		return true;
	}
	return false;
}

bool FoldersTreeMaker::setOutputPath(char* path)
{
	if (path)
	{
		output_path = path;
		return true;
	}
	return false;
}

bool FoldersTreeMaker::CreateExe(char* path,Suite* suite)
{
	if (input_path&&output_path)
	{
		std::list<TRSTest*>::iterator it = suite->getList().begin();
		char* exeName = new char[strlen(path) + strlen((*it)->get_executableName()) + 2];
		strncpy_s(exeName, strlen(path) + 1, path, strlen(path));
		strncpy_s(exeName + strlen(path), 2, "//", 1);
		strncpy_s(exeName + strlen(path) + 1, strlen((*it)->get_executableName()) + 1, (*it)->get_executableName(), strlen((*it)->get_executableName()));
		std::ifstream infile(R"(../TestEXE.exe)", std::ifstream::binary);
		std::ofstream outfile(exeName, std::ofstream::binary);

		// get size of file
		infile.seekg(0, infile.end);
		long size = infile.tellg();
		infile.seekg(0);

		// allocate memory for file content
		char* buffer = new char[size];

		// read content of infile
		infile.read(buffer, size);

		// write to outfile
		outfile.write(buffer, size);

		// release dynamically-allocated memory
		delete[] buffer;

		outfile.close();
		infile.close();
	}
	return 0;
}