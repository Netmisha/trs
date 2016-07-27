#include "stdafx.h"
#include "ProjectProperties.h"


ProjectProperties::ProjectProperties(char* path_, char* name_)
{
	if (path_)
	{
		path = path_;
	}
	if (name_)
	{
		name = name_;
	}
}

char* ProjectProperties::getProjPath()
{
	if (name&&path)
	{
		int sizePath = strlen(path);
		int sizeName = strlen(name);
		char* fullPath = new char[sizePath + sizeName + 6];
		strncpy_s(fullPath, sizePath + 1, path, sizePath);
		strncpy_s(fullPath + sizePath, 2, "\\", 1);
		strncpy_s(fullPath + sizePath + 1, sizeName + 1, name, sizeName);
		strncpy_s(fullPath + sizePath + sizeName + 1, 5, ".xml", 4);
		return fullPath;
	}
	else
	{
		return nullptr;
	}
}

ProjectProperties::ProjectProperties()
{

}

ProjectProperties::~ProjectProperties()
{
	delete[] name;
	delete[] path;
}

bool ProjectProperties::setName(const char* name_)
{
	if (name_)
	{
		name = new char[strlen(name_)+1];
		int count = 0;
		char help = name_[count];
		while (help)
		{
			name[count]=help;
			++count;
			help = name_[count];
		}
		name[count] = '\0';
		return true;
	}
	return false;
}

bool ProjectProperties::setPath(const char* path_)
{
	if (path_)
	{
		path = new char[strlen(path_) + 1];
		int count = 0;
		char help = path_[count];
		while (help)
		{
			path[count]= help;
			++count;
			help = path_[count];
		}
		path[count] = '\0';
		return true;
	}
	return false;
}

char* ProjectProperties::getName()
{
	return name;
}

char* ProjectProperties::getPath()
{
	return path;
}

ProjectProperties& ProjectProperties::operator=(ProjectProperties& pro)
{
	path = pro.getPath();
	name = pro.getName();
	return *this;
}

bool ProjectProperties::SaveProject(CListBox*List)
{
	if (name&&path)
	{
		int sizePath = strlen(path);
		int sizeName = strlen(name);
		char* fullPath = new char[sizePath + sizeName + 6];
		strncpy_s(fullPath, sizePath + 1, path, sizePath);
		strncpy_s(fullPath + sizePath, 2, "\\", 1);
		strncpy_s(fullPath + sizePath +1, sizeName + 1, name, sizeName);
		strncpy_s(fullPath + sizePath + sizeName +1, 5, ".xml", 4);
		TiXmlDocument doc;
		TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "", "");
		doc.LinkEndChild(dec);
		TiXmlElement* element = new TiXmlElement("TRSProject");
		element->SetAttribute("name", name);
		element->SetAttribute("ProjectPath", path);
		doc.LinkEndChild(element);
		CString buffer;
		CString helpBuffer;
		if (List->GetCount() > 0)
		{
			for (int i = 0; i < List->GetCount(); ++i)
			{
				TiXmlElement* subEl = new TiXmlElement("path");
				element->LinkEndChild(subEl);
				List->GetText(i, buffer);

				helpBuffer = buffer;
				char* path = fromCStringToChar(helpBuffer);

				TiXmlText* text = new TiXmlText(path);
				subEl->LinkEndChild(text);
				delete[] path;
			}
		}
		if (doc.SaveFile(fullPath))
		{
			doc.SaveFile("Last Project.xml");
			return true;
		}
		return false;
	}
	return false;
}