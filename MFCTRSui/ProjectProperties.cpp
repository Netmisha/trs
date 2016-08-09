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
	delete[] threads;
	delete[] tag;
	delete[] testName;
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

bool ProjectProperties::setTag(char* tag_)
{
	if (tag_)
	{
		if (tag)
		{
			delete[] tag;
			tag = new char[strlen(tag_) + 1];
			strncpy_s(tag, strlen(tag_) + 1, tag_, strlen(tag_));
			return true;
		}
		else
		{
			tag = new char[strlen(tag_) + 1];
			strncpy_s(tag, strlen(tag_) + 1, tag_, strlen(tag_));
			return true;
		}
	}
}

bool ProjectProperties::setThreads(char* threads_)
{
	if (threads_)
	{
		if (threads)
		{
			delete[] threads;
			threads = new char[strlen(threads_) + 1];
			strncpy_s(threads, strlen(threads_) + 1, threads_, strlen(threads_));
			return true;
		}
		else
		{
			threads = new char[strlen(threads_) + 1];
			strncpy_s(threads, strlen(threads_) + 1, threads_, strlen(threads_));
			return true;
		}
	}
}

bool ProjectProperties::setTestName(char* testName_)
{
	if (testName_)
	{
		if (testName)
		{
			delete[] testName;
			testName = new char[strlen(testName_) + 1];
			strncpy_s(testName, strlen(testName_) + 1, testName_, strlen(testName_));
			return true;
		}
		else
		{
			testName = new char[strlen(testName_) + 1];
			strncpy_s(testName, strlen(testName_) + 1, testName_, strlen(testName_));
			return true;
		}
	}
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

char* ProjectProperties::getTag()
{
	return tag;
}

char* ProjectProperties::getThreads()
{
	return threads;
}

char* ProjectProperties::getTestName()
{
	return testName;
}

void ProjectProperties::setConsole(bool check)
{
	ConsoleVisible = check;
}

bool ProjectProperties::getConsole()
{
	return ConsoleVisible;
}

ProjectProperties& ProjectProperties::operator=(ProjectProperties& pro)
{
	path = pro.getPath();
	name = pro.getName();
	threads = pro.getThreads();
	tag = pro.getTag();
	testName = pro.getTestName();
	return *this;
}

bool ProjectProperties::SaveProject(CListCtrl*List)
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
		if (List->GetItemCount() > 0)
		{
			for (int i = 0; i < List->GetItemCount(); ++i)
			{
				TiXmlElement* subEl = new TiXmlElement("path");
				element->LinkEndChild(subEl);
				buffer = List->GetItemText(i, 0);

				helpBuffer = buffer;
				char* path = fromCStringToChar(helpBuffer);

				TiXmlText* text = new TiXmlText(path);
				subEl->LinkEndChild(text);
				delete[] path;
			}
			int count = 0;
			for (int i = 0; i < List->GetItemCount(); ++i)
				count += List->GetCheck(i);
			if (count)
			{
				TiXmlElement* ListSel = new TiXmlElement("ListSelection");
				element->LinkEndChild(ListSel);
				for (int j = 0; j < List->GetItemCount(); ++j)
				{
					if (List->GetCheck(j))
					{
						TiXmlElement* curSel = new TiXmlElement("selection");
						ListSel->LinkEndChild(curSel);
						int count = j;
						int lic = 2;
						while (count /= 10)
						{
							++lic;
						}
						char* cur = new char[lic];
						sprintf_s(cur, lic, "%d", j);
						TiXmlText* text = new TiXmlText(cur);
						curSel->LinkEndChild(text);
						delete[] cur;
					}
				}
			}
		}
		if (tag)
		{
			TiXmlElement* Tag = new TiXmlElement("tag");
			element->LinkEndChild(Tag);
			TiXmlText*text = new TiXmlText(tag);
			Tag->LinkEndChild(text);
		}
		if (threads)
		{
			TiXmlElement* Threads = new TiXmlElement("threads");
			element->LinkEndChild(Threads);
			TiXmlText* text = new TiXmlText(threads);
			Threads->LinkEndChild(text);
		}
		if (testName)
		{
			TiXmlElement* TestName = new TiXmlElement("testName");
			element->LinkEndChild(TestName);
			TiXmlText* text = new TiXmlText(testName);
			TestName->LinkEndChild(text);
		}
		if (ConsoleVisible)
		{
			TiXmlElement* console = new TiXmlElement("console");
			element->LinkEndChild(console);
			TiXmlText* text = new TiXmlText("visible");
			console->LinkEndChild(text);
		}
		else
		{
			TiXmlElement* console = new TiXmlElement("console");
			element->LinkEndChild(console);
			TiXmlText* text = new TiXmlText("invisible");
			console->LinkEndChild(text);
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